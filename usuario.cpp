#include <iostream>

#include "usuario.h"
#include "estudiantes.h"
#include "horarioparser.h"

void Usuario::show_horario_estudiante(std::string cedula)
{
    generate_horario_estudiante(cedula);
    for (int dia = 0; dia < 5; dia++) {
        for (int hora = 0; hora < 10; hora++)
            if (horario[hora][dia].nombre != "")
                std::cout << dias[dia] << " (" << horas[hora] << "): " << horario[hora][dia].nombre << " Aula: " + horario[hora][dia].aula << std::endl;
        std::cout << std::endl;
    }
}

void Usuario::generate_horario_estudiante(std::string cedula)
{
    Estudiantes estudiantes;
    estudiantes.set_estudiantes_file(ESTUDIANTES_PATH);
    estudiantes.initsearch();
    
    std::vector<std::string> record;
    while (!(record = estudiantes.next_estudiante()).empty()) {
        if (record[0] == cedula) {
            generate_horario_materia(record[1]);
        }
    }
    estudiantes.finishsearch();
}


void Usuario::generate_horario_materia(std::string materia)
{
    for (int hora = 0; hora < 10; hora++) {
        for (int dia = 0; dia < 5; dia++) {
            for (int i = 0; i < horarios.size(); i++) {
                if (horarios[i][hora][dia].nombre == materia) {
                    horario[hora][dia] = horarios[i][hora][dia];
                    break;
                }
            }
        }
    }
}

void Usuario::init()
{
    Horarioparser horarioparser;
    horarioparser.set_horarios_file(HORARIOS_PATH);
    horarios = horarioparser.get_horarios();
}

void Usuario::finish()
{
    horarios.clear();
}

void Usuario::new_query()
{
    for (int hora = 0; hora < 10; hora++)
        for (int dia = 0; dia < 5; dia++) {
            horario[hora][dia].aula = "";
            horario[hora][dia].docente_id = "";
            horario[hora][dia].nombre = "";
        }
}
