#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <array>
#include "materias.h"

struct Usuario {
    const std::string HORARIOS_PATH = "horario/horarios.txt";
    const std::string ESTUDIANTES_PATH = "horario/estudiantes.csv";
    const std::string MATERIAS_PATH = "horario/estudiantes.csv";
    const std::string DOCENTES_PATH = "horario/estudiantes.csv";
    std::array<std::string, 5> dias = {{"Lunes", "Martes", "Miércoles", "Jueves", "Viernes"}};
    std::array<std::string, 10> horas = {{"7 - 8", "8 - 9", "9 -10", "10 - 11", "11 - 12", "12 - 13",
                                          "15 - 16", "16 - 17", "17 - 18", "18 - 19"}
                                         };
    
    std::vector<std::array<std::array<Materia, 5>, 10>> horarios;
    
    std::array<std::array<Materia, 5>, 10> horario;
    void show_horario_docente(std::string cedula);
    void show_horario_estudiante(std::string cedula);
    void show_horario_aula(std::string codigo);
    void show_horario_materia(std::string materia);
    void show_estudiantes(std::string materia);
    void init();
    void new_query();
    void finish();
    
    void generate_horario_materia(std::string materia);
    void generate_horario_estudiante(std::string cedula);
    void generate_horario_aula(std::string codigo);
    void generate_horario_docente(std::string cedula);
    
    void exportar_horario(std::string nombre_destino);
};


#endif /* USUARIO_H */

