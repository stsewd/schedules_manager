#ifndef HORARIOPARSER_H
#define HORARIOPARSER_H

#include <array>
#include <fstream>
#include <vector>
#include "materias.h"

struct Horarioparser {
    std::vector<std::array<std::array<Materia, 5>, 10>> horarios;
    std::ifstream flujo_entrada;
    void add_horario();
    void set_horarios_file(std::string path);
    void add_materias_to(std::vector<Materia> materias, int dia);
    std::vector<Materia> parser_line(std::string line);
    std::vector<std::array<std::array<Materia, 5>, 10>> get_horarios();
};

#endif /* HORARIOPARSER_H */

