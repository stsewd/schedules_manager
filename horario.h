#ifndef HORARIO_H
#define HORARIO_H

#include "csvfile.h"
#include "materias.h"
#include "estudiantes.h"
#include "log.h"
#include "aulas.h"
#include <array>

enum class Dia {lunes, martes, miercoles, jueves, viernes};
const Dia dias[] = {Dia::lunes, Dia::martes, Dia::miercoles, Dia::jueves, Dia::viernes};

struct Horario {
private:
    const std::string HORARIOS_PATH = "horario/horarios.txt";
    const std::string ESTUDIANTES_PATH = "horario/estudiantes.csv";
    std::vector<std::array<std::array<Materia, 5>, 10>> horarios;
    std::vector<Aula> aulas_v;
    std::ofstream flujo_salida_horarios;
    std::ofstream flujo_salida_estudiantes;
    Materias materias;
    Estudiantes estudiantes;
    Aulas aulas;
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
    bool existe_materia(std::string materia);
    bool existe_en_horario(int index, std::string materia);
    void put_in_aulas();
    void ubicar_aula(std::string materia, int capacidad_max);
    int num_alumnos_in(std::string materia);
    void rellenar_materia(std::string aula, std::string materia);
    bool can_rellenar_materia(std::string aula, std::string materia);
    void matricular_estudiantes();
    bool aula_disponible(std::string aula, int hora, int dia);
    void add_horario();
    int capacidad_maxima();
    void init();
    void finish();
    void discard_materias();
    void put_materias(int minhours, int maxhours);
    void put_materia(Dia dia, Materia materia, int* horas, int indice_horario);
    bool can_put_materia(int num_horas, int indice_horario, Materia materia);
    bool hora_libre_docente(int hora, int dia, std::string docente_id);
    void reverse(int indice_horario);
    int get_dia(Dia dia);
    void addcabecera_estudiantes();
};

#endif /* HORARIO_H */

