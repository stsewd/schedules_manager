#include "horario.h"
#include "materias.h"
#include <iostream>
#include <string>
#include <array>
#include <algorithm>

void Horario::set_aulas_file(std::string path)
{
    aulas.set_aulas_file(path);
}

void Horario::set_docentes_file(std::string path)
{
    materias.set_docentes_file(path);
}

void Horario::set_estudiantes_file(std::string path)
{
    estudiantes.set_estudiantes_file(path);
}

void Horario::set_materias_file(std::string path)
{
    materias.set_materias_file(path);
}

void Horario::init()
{
    logfile.init();
    materias.set_errorlog(&logfile);
    materias.join_materias_docentes();
}

void Horario::generate()
{
    init();
    add_horario();
    discard_materias();
    put_materias(5, 6);
    put_materias(3, 4);
    put_materias(1, 2);
    matricular_estudiantes();
    put_in_aulas();
    showall();
    finish();
}

void Horario::add_horario()
{
    std::array<std::array<Materia, 5>, 10> horario;
    horarios.push_back(horario);
}

void Horario::put_materias(int minhours, int maxhours)
{
    // TODO clean up all this sh*t code
    std::vector<std::string> materia_record;
    int num_horas;
    int num_horas_aux;
    int dia_actual;
    int indice_horario;
    materias.initsearch();
    while (!(materia_record = materias.next_materia(minhours, maxhours)).empty()) {        
        num_horas = atoi(materia_record[1].c_str());
        Materia materia;
        materia.nombre = materia_record[0];
        materia.docente_id = materia_record[2];
        
        indice_horario = 0;
        while (!can_put_materia(num_horas, indice_horario, materia)) {
            if (indice_horario == horarios.size() - 1)
                add_horario();
            indice_horario++;
        }
        
        dia_actual = 0;
        while (dia_actual < 5 && num_horas > 0) {
            num_horas_aux = num_horas;
            put_materia(dias[dia_actual], materia, &num_horas, indice_horario);
            if (num_horas < num_horas_aux)
                dia_actual += 2;
            else
                dia_actual += 1;
        }
    }
    materias.finishsearch();
}

void Horario::discard_materias()
{
    std::vector<std::string> materia_record;
    materias.initsearch();
    while (!(materia_record = materias.next_materia(7, 100000)).empty())
        logfile.write("Error en carga horaria. Data: " + materia_record[0] + " - " + materia_record[1] + "\n");
    materias.finishsearch();
}

void Horario::put_materia(Dia dia, Materia materia, int* horas, int indice_horario)
{
    int dia_int = get_dia(dia);
    int num_horas_max = 2;
    for (int i = 0; i < NUM_HORAS; i++) {
        if (horarios[indice_horario][i][dia_int].nombre == "" && hora_libre_docente(i, dia_int, materia.docente_id)) {
            horarios[indice_horario][i][dia_int].nombre = materia.nombre;
            horarios[indice_horario][i][dia_int].docente_id = materia.docente_id;
            *horas -= 1;
            num_horas_max--;
            if (num_horas_max > 0 && *horas > 0)
                continue;
            return;
        }
    }
}

bool Horario::hora_libre_docente(int hora, int dia, std::string docente_id)
{
    for (int i = 0; i < horarios.size(); i++) {
        if (horarios[i][hora][dia].docente_id == docente_id)
            return false;
    }
    return true;
}


bool Horario::can_put_materia(int num_horas, int indice_horario, Materia materia)
{
    int dia_actual = 0;
    int num_horas_aux = 0;
    while (dia_actual < 5 && num_horas > 0) {
        num_horas_aux = num_horas;
        materia.nombre = ".";
        put_materia(dias[dia_actual], materia, &num_horas, indice_horario);
        if (num_horas < num_horas_aux)
            dia_actual += 2;
        else
            dia_actual += 1;
    }
    reverse(indice_horario);
    if (num_horas > 0)
        return false;
    return true;
}

void Horario::reverse(int indice_horario)
{
    for (int i = 0; i < NUM_HORAS; i++)
        for (int j = 0; j < 5; j++)
            if (horarios[indice_horario][i][j].nombre == ".") {
                horarios[indice_horario][i][j].nombre = "";
                horarios[indice_horario][i][j].docente_id = "";
            }
}

int Horario::get_dia(Dia dia)
{
    switch (dia) {
    case Dia::lunes:
        return 0;
    case Dia::martes:
        return 1;
    case Dia::miercoles:
        return 2;
    case Dia::jueves:
        return 3;
    default:
        return 4;
    }
}

void Horario::matricular_estudiantes()
{
    flujo_salida_estudiantes.open(ESTUDIANTES_PATH);
    std::vector<std::string> record;
    estudiantes.initsearch();
    estudiantes.set_logfile(&logfile);
    while (!(record = estudiantes.next_estudiante()).empty()) {
        if (existe_materia(record[1])) {
            flujo_salida_estudiantes << record[0] << ",";
            flujo_salida_estudiantes << record[1] << std::endl;
        } else
            logfile.write("Estudiante ID: " + record[0] + " no matriculado. Materia no existente. Data: " + record[1] + "\n");
    }
    flujo_salida_estudiantes.close();
    estudiantes.finishsearch();
}

bool Horario::existe_materia(std::string materia)
{
    for (int i = 0; i < horarios.size(); i++) {
        if (existe_en_horario(i, materia))
            return true;
    }
    return false;
}

bool Horario::existe_en_horario(int index, std::string materia)
{
    for (int hora = 0; hora < NUM_HORAS; hora++) {
        for (int dia = 0; dia < 5; dia++) {
            if (horarios[index][hora][dia].nombre == materia)
                return true;
        }
    }
    return false;
}

void Horario::put_in_aulas()
{
    aulas.set_logfile(&logfile);
    aulas_v = aulas.get_aulas();
    std::sort(aulas_v.begin(), aulas_v.end());
    
    int capacidad_max = capacidad_maxima();
    for (int i = 0; i < horarios.size(); i++) {
        for (int hora = 0; hora < 10; hora++) {
            for (int dia = 0; dia < 5; dia++) {
                if (horarios[i][hora][dia].aula == "") {
                    ubicar_aula(horarios[i][hora][dia].nombre, capacidad_max);
                }
            }
        }
    }
}

int Horario::capacidad_maxima()
{
    return aulas_v[aulas_v.size() - 1].capacidad;
}

void Horario::ubicar_aula(std::string materia, int capacidad_max)
{
    int num_alumnos = num_alumnos_in(materia);
    if (num_alumnos == 0) {
        logfile.write("Materia sin alumnos. Data: " + materia + "\n");
        rellenar_materia("Sin aula", materia);
        return;
    }
    
    if (num_alumnos > capacidad_max)
        logfile.write("Numero de alumnos excedido. Materia: " + materia + ". Alumnos: " + std::to_string(num_alumnos) + "\n");
    
    int indice_aula = 0;
    bool ocupada = true;  // El aula ya esta ocupada en este horario?
    while (indice_aula < aulas_v.size() && aulas_v[indice_aula].capacidad < num_alumnos) {
        // Probar que no se cruce ¿aqui?
        ocupada = false;
        indice_aula++;
    }
    rellenar_materia(aulas_v[indice_aula].codigo, materia);
}

int Horario::num_alumnos_in(std::string materia)
{
    int num = 0;
    Estudiantes alumnos_temp;
    alumnos_temp.set_estudiantes_file(ESTUDIANTES_PATH);
    alumnos_temp.set_logfile(&logfile);
    
    alumnos_temp.initsearch();
    std::vector<std::string> record;
    while (!(record = alumnos_temp.next_estudiante(materia)).empty())
        num++;
    alumnos_temp.finishsearch();
    return num;
}

void Horario::rellenar_materia(std::string aula, std::string materia)
{
    for (int i = 0; i < horarios.size(); i++) {
        for (int hora = 0; hora < 10; hora++) {
            for (int dia = 0; dia < 5; dia++) {
                if (horarios[i][hora][dia].nombre == materia) {
                    horarios[i][hora][dia].aula = aula;
                }
            }
        }
    }
}


void Horario::showall()
{
    flujo_salida_horarios.open(HORARIOS_PATH);
    for (int i = 0; i < horarios.size(); i++) {
        show(i);
        flujo_salida_horarios << std::endl;
    }
    flujo_salida_horarios.close();
}

void Horario::show(int index)
{
    for (int  j = 0; j < 5; j++) {
        for (int i = 0; i < NUM_HORAS; i++) {
            flujo_salida_horarios << horarios[index][i][j].nombre << "|";
            flujo_salida_horarios << horarios[index][i][j].docente_id << "|";
            flujo_salida_horarios << horarios[index][i][j].aula << ",";
        }
        flujo_salida_horarios << std::endl;
    }
}

void Horario::finish()
{
    horarios.clear();
    materias.finish();
    logfile.close();
}
