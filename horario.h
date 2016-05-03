#ifndef HORARIO_H
#define HORARIO_H

#include "csvfile.h"
#include "materias.h"
#include "log.h"
#include <array>

enum class Dia {lunes, martes, miercoles, jueves, viernes};
const Dia dias[] = {Dia::lunes, Dia::martes, Dia::miercoles, Dia::jueves, Dia::viernes};

struct Horario {
private:
    std::vector<std::array<std::array<std::string, 5>, 10>> horarios;
    Materias materias;
    const int NUM_HORAS = 10;
    Log logfile;
public:
    void set_docentes_file(std::string path);
    void set_materias_file(std::string path);
    void set_estudiantes_file(std::string path);
    void set_aulas_file(std::string path);
    
    void generate();
    void show(int index);
    void showall();
private:
    void add_horario();
    void init();
    void finish();
    void discard_materias();
    void put_materias(int minhours, int maxhours);
    void put_materia(Dia dia, std::string materia, int* horas, int indice_horario);
    bool can_put_materia(int num_horas, int indice_horario);
    void reverse(int indice_horario);
    int get_dia(Dia dia);
};

#endif /* HORARIO_H */

