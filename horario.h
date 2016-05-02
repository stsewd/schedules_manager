#ifndef HORARIO_H
#define HORARIO_H

#include "csvfile.h"
#include "materias.h"
#include "log.h"

enum class Dia {lunes, martes, miercoles, jueves, viernes};
const Dia dias[] = {Dia::lunes, Dia::martes, Dia::miercoles, Dia::jueves, Dia::viernes};

struct Horario {
private:
    std::string horario[10][5];
    Materias materias;
    const int NUM_HORAS = 10;
    
    Log logfile;
public:
    void set_docentes_file(std::string path);
    void set_materias_file(std::string path);
    void set_estudiantes_file(std::string path);
    void set_aulas_file(std::string path);
    
    void generate();
    void show();
private:
    void init();
    void finish();
    void discard_materias();
    void put_materias(int minhours, int maxhours);
    void put_materia(Dia dia, std::string materia, int* horas);
    int get_dia(Dia dia);
};

#endif /* HORARIO_H */

