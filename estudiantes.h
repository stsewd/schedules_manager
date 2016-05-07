#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

#include <vector>
#include "csvfile.h"
#include "log.h"

struct Estudiante {
    Log* errorlog;
    Csvfile estudiantes_csv;
    void set_estudiantes_file(std::string path);
    void set_logfile(Log* log);
    std::vector<std::string> next_estudiante(std::string materia);
    void initsearch();
    void finishsearch();
    std::vector<std::string> parser_record(std::string record);
};




#endif /* ESTUDIANTES_H */
