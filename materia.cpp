#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

#include "materia.h"

struct Materia;
void Materia::set_docentes_file(std::string path)
{
    csv_docentes.set_file(path);
}

void Materia::set_materias_file(std::string path)
{
    csv_materias.set_file(path);
}

void Materia::set_log(std::string path)
{
    errorlog.open(path, std::ios_base::app);
}

void Materia::join_materias_docentes()
{
    std::string line;
    std::vector<std::string> records;
    while ((line = csv_materias.next_record()) != "") {
        records = parser_record(line);
        if (records == nullptr) {
            errorlog << "Formato no correcto. Data: " << line << std::endl;
            return;
        }
        
    }
}

std::vector<std::string> parser_record(std::string record)
{
    std::vector<std::string> records;
    std::regex regex_materia("^([^,]*),(\\d),(\\d{10})$");
    std::smatch groups;
    
    if (!std::regex_match(record, groups, regex_materia))
       return nullptr; 
    
    for (std::string r : groups)
        records.push_back(r);
    return records;
}

