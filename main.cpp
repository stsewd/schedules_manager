#include <iostream>
#include <iomanip> 

#include "csvfile.h"
#include "materias.h"
#include "log.h"
#include "horario.h"

int main(int argc, char** argv)
{
    Horario horario;
    
    horario.set_aulas_file("resources/aulas.csv");
    horario.set_docentes_file("resources/docentes.csv");
    horario.set_estudiantes_file("resources/alumnos.csv");
    horario.set_materias_file("resources/materias.csv");
    horario.generate();
    return 0;
}
