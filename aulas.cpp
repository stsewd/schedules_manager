#include "aulas.h"
#include "log.h"

#include <regex>

void Aulas::set_aulas_file(std::string path)
{
    aulas_csv.set_file(path);
}

void Aulas::set_logfile(Log* log)
{
    errorlog = log;
}

std::vector<Aula> Aulas::get_aulas()
{
    std::vector<Aula> aulas;
    
    aulas_csv.init();
    std::string line;
    std::vector<std::string> record;
    while ((line = aulas_csv.next_record()) != "") {
        record = parser_record(line);
        if (!record.empty()) {
            Aula aula;
            aula.codigo = record[0];
            aula.capacidad = atoi(record[1].c_str());
            aulas.push_back(aula);
        } else {
            errorlog->write("Aula no valida. Data: " + line);
        }
    }
    aulas_csv.close();
    
    return aulas;
}


std::vector<std::string> Aulas::parser_record(std::string record)
{
    std::vector<std::string> records;
    std::regex regex_docente("^(\\w+|\\w+\\d+),(\\d+)$");
    std::smatch groups;
    
    if (!std::regex_match(record, groups, regex_docente))
       return records;
    
    for (int i = 1; i < 3; i++)
        records.push_back(groups[i]);
    return records;
}



