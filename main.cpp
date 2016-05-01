#include <iostream>

#include "csvfile.h"
#include "materia.h"
#include "log.h"

int main(int argc, char** argv)
{
    Log log_file;
    log_file.init();
    Materia materia;
    // TODO cerrar archivos luego de ser usados
    materia.set_docentes_file("resources/docentes.csv");
    materia.set_materias_file("resources/materias.csv");
    materia.set_errorlog(&log_file);
    materia.join_materias_docentes();
    
    log_file.close();
    return 0;
}
