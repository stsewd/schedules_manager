#ifndef MATERIA_H
#define MATERIA_H

#include "csvfile.h"
#include "docente.h"

struct Materia {
private:
    const std::string MATERIAS_PATH = "horario/materias.csv";
    const std::string DOCENTES_PATH = "horario/docentes.csv";
    
    std::ofstream flujo_salida_materias;
    std::ofstream flujo_salida_docentes;
    
    Csvfile csv_materias;
    Docente docentes;
    Log* errorlog;
public:
    void set_docentes_file(std::string path);
    void set_materias_file(std::string path);
    std::vector<std::string> parser_record(std::string record);
// TODO private:
    void set_errorlog(Log* log);
    void join_materias_docentes();
};


#endif /* MATERIA_H */

