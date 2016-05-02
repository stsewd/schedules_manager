#include <iostream>

#include "csvfile.h"
#include "materias.h"
#include "log.h"
#include "horario.h"

int main(int argc, char** argv)
{
    Horario horario;
    
    horario.set_aulas_file("");
    horario.set_docentes_file("resources/docentes.csv");
    horario.set_estudiantes_file("");
    horario.set_materias_file("resources/materias.csv");

    horario.init();
    horario.finish();
    return 0;
}
