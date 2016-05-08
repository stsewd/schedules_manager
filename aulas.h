#ifndef AULAS_H
#define AULAS_H

#include "csvfile.h"
#include "log.h"
#include <vector>


struct Aula {
    std::string codigo;
    int capacidad;
    bool operator < (const Aula& aula) const {
        return capacidad < aula.capacidad;
    }
};

struct Aulas {
    Log* errorlog;
    Csvfile aulas_csv;
    void set_aulas_file(std::string path);
    void set_logfile(Log* log);
    std::vector<Aula> get_aulas();
    std::vector<std::string> parser_record(std::string record);
};

#endif /* AULA_H */
