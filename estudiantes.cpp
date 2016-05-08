#include <regex>
#include "estudiantes.h"

void Estudiantes::set_estudiantes_file(std::string path)
{
    estudiantes_csv.set_file(path);
}

void Estudiantes::set_logfile(Log* log)
{
    errorlog = log;
}

void Estudiantes::initsearch()
{
    estudiantes_csv.init();
}

void Estudiantes::finishsearch()
{
    estudiantes_csv.close();
}

std::vector<std::string> Estudiantes::next_estudiante(std::string materia)
{
    std::string line;
    std::vector<std::string> records;
    while ((line = estudiantes_csv.next_record()) != "") {
        records = parser_record(line);
        if (!records.empty() && records[1] == materia)
            return records;
    }
    return {};
}

std::vector<std::string> Estudiantes::next_estudiante()
{
    std::string line;
    std::vector<std::string> records;
    while ((line = estudiantes_csv.next_record()) != "") {
        records = parser_record(line);
        if (!records.empty())
            return records;
        else
            errorlog->write("Formato no correcto. Data: " + line + "\n");
    }
    return {};
}


std::vector<std::string> Estudiantes::parser_record(std::string record)
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
