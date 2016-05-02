#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <sstream>

#include "materias.h"
#include "docentes.h"
#include "estudiante.h"

void Materias::set_docentes_file(std::string path)
{
    docentes.set_docentes_file(path);
}

void Materias::set_materias_file(std::string path)
{
    csv_materias.set_file(path);
}

void Materias::set_errorlog(Log* log)
{
    errorlog = log;
}

void Materias::join_materias_docentes()
{
    int num_docentes = 0;
    init_streams();
    
    std::string line;
    std::vector<std::string> materia_record;
    while ((line = csv_materias.next_record()) != "") {
        materia_record = parser_record(line);
        if (materia_record.empty()) {
            errorlog->write("Formato no correcto. Data: " + line + "\n");
            continue;
        }
        
        auto docente_record = docentes.search_id(materia_record[2]);
        if (docente_record.empty()) {
            errorlog->write("Id no válido o no encontrado. Data: " + materia_record[2] + "\n");
            continue;
        }
        // TODO se puede omitir el número de docente, luego se recupera según la línea?
        flujo_salida_docentes << docente_record[0] << "," << docente_record[1] << std::endl;
        flujo_salida_materias << materia_record[0] << "," << materia_record[1] << "," << ++num_docentes << std::endl;
    }
}

void Materias::init_streams() 
{
    flujo_salida_materias.open(MATERIAS_PATH);
    flujo_salida_docentes.open(DOCENTES_PATH);
}

void Materias::finish()
{
    flujo_salida_docentes.close();
    flujo_salida_materias.close();
    csv_materias.close();
    docentes.finish();    
}

std::vector<std::string> Materias::parser_record(std::string record)
{
    std::vector<std::string> records;
    std::regex regex_materia("^([^,]*),(\\d),(\\d{10})$");
    std::smatch groups;
    
    if (!std::regex_match(record, groups, regex_materia))
       return records; 
    
    for (int i = 1; i < 4; i++)
        records.push_back(groups[i]);
    return records;
}

std::vector<std::string> Materias::parser_record_inner(std::string record)
{
    std::vector<std::string> records;
    std::regex regex_materia("^([^,]*),(\\d),(\\d*)$");
    std::smatch groups;
    
    if (!std::regex_match(record, groups, regex_materia))
       return records; 
    
    for (int i = 1; i < 4; i++)
        records.push_back(groups[i]);
    return records;
}

void Materias::initsearch()
{
    csv_materias_entrada.set_file(MATERIAS_PATH);
    csv_materias_entrada.init();
}

void Materias::finishsearch()
{
    csv_materias_entrada.close();
}

std::vector<std::string> Materias::next_materia(int minhours, int maxhours)
{
    std::string line;
    std::vector<std::string> materia_record;
    while ((line = csv_materias_entrada.next_record()) != "") {
        materia_record = parser_record_inner(line);
        std::istringstream iss(materia_record[1]);
        int hours;
        iss >> hours;
        if (hours >= minhours && hours <= maxhours)
            return materia_record;
    }
    return {};
}
