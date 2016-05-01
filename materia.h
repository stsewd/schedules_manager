#ifndef MATERIA_H
#define MATERIA_H

#include "csvfile.h"

struct Materia {
private:
    const std::string MATERIAS_PATH = "horario/materias.csv";
    const std::string DOCENTES_PATH = "horario/docentes.csv";
    
    std::ofstream flujo_salida_materias;
    std::ofstream flujo_salida_docentes;
    Csvfile csv_materias;
    Csvfile csv_docentes;
    
    std::ofstream errorlog;
public:
    void set_docentes_file(std::string path);
    void set_materias_file(std::string path);
private:
    void set_log(std::string path);
    void join_materias_docentes();
};


#endif /* MATERIA_H */

