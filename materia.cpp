#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

#include "materia.h"
#include "docente.h"

void Materia::set_docentes_file(std::string path)
{
    docentes.set_docentes_file(path);
}

void Materia::set_materias_file(std::string path)
{
    csv_materias.set_file(path);
}

void Materia::set_errorlog(Log* log)
{
    errorlog = log;
}

void Materia::join_materias_docentes()
{
    int num_docentes = 0;
    init_streams();
    
    std::string materia_record;
    std::vector<std::string> materia_records;
    while ((materia_record = csv_materias.next_record()) != "") {
        materia_records = parser_record(materia_record);
        if (materia_records.empty()) {
            errorlog->write("Formato no correcto. Data: " + materia_record + "\n");
            continue;
        }
        
        auto docente_records = docentes.search_id(materia_records[2]);
        if (docente_records.empty()) {
            errorlog->write("Id no válido o no encontrado. Data: " + materia_records[2] + "\n");
            continue;
        }
        flujo_salida_docentes << docente_records[0] << "," << docente_records[1] << std::endl;
        flujo_salida_materias << materia_records[0] << "," << materia_records[1] << "," << ++num_docentes << std::endl;
    }
}

void Materia::init_streams() 
{
    flujo_salida_materias.open(MATERIAS_PATH);
    flujo_salida_docentes.open(DOCENTES_PATH);
}

std::vector<std::string> Materia::parser_record(std::string record)
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
