#include <regex>

#include "docentes.h"
#include "csvfile.h"
#include "log.h"

std::vector<std::string> Docente::search_id(std::string id)
{   
    std::string line;
    std::vector<std::string> records;
    csv_docentes.init();
    while ((line = csv_docentes.next_record()) != "") {
        records = parser_record(line);
        if (!records.empty() && records[0] == id)
            return records;
    }
    return {};
}

void Docente::set_errorlog(Log* log)
{
    errorlog = log;
}

void Docente::set_docentes_file(std::string path)
{
    csv_docentes.set_file(path);
}

std::vector<std::string> Docente::parser_record(std::string record) 
{
    std::vector<std::string> records;
    std::regex regex_docente("^(\\d{10}),([^,]*)$");
    std::smatch groups;
    
    if (!std::regex_match(record, groups, regex_docente))
       return records;
    
    for (int i = 1; i < 3; i++)
        records.push_back(groups[i]);
    return records;
}

void Docente::finish()
{
    csv_docentes.close();
}
