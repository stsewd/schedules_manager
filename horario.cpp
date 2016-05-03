#include "horario.h"
#include <iostream>
#include <string>
#include <array>

void Horario::set_aulas_file(std::string path)
{
    // TODO
}

void Horario::set_docentes_file(std::string path)
{
    materias.set_docentes_file(path);
}

void Horario::set_estudiantes_file(std::string path)
{
    // TODO
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
    finish();
}

void Horario::add_horario()
{
    std::array<std::array<std::string, 5>, 10> horario;
    horarios.push_back(horario);
}

void Horario::put_materias(int minhours, int maxhours)
{
    // TODO cleaning up all this sh*t code
    std::vector<std::string> materia_record;
    int num_horas;
    int num_horas_aux;
    int dia_actual;
    int indice_horario = 0;
    materias.initsearch();
    while (!(materia_record = materias.next_materia(minhours, maxhours)).empty()) {        
        num_horas = atoi(materia_record[1].c_str());
        indice_horario = 0;
        while (!can_put_materia(num_horas, indice_horario)) {
            if (indice_horario == horarios.size() - 1)
                add_horario();
            indice_horario++;
        }
        
        dia_actual = 0;
        while (dia_actual < 5 && num_horas > 0) {
            num_horas_aux = num_horas;
            put_materia(dias[dia_actual], materia_record[0], &num_horas, indice_horario);
            if (num_horas < num_horas_aux)
                dia_actual += 2;
            else
                dia_actual += 1;
        }
        if (num_horas > 0)
            logfile.write("No se pudo completar las horas de: " + materia_record[0] + " - " + materia_record[1] + "\n");
    }
    materias.finishsearch();
}

void Horario::discard_materias()
{
    std::vector<std::string> materia_record;
    materias.initsearch();
    while (!(materia_record = materias.next_materia(7, 10000)).empty())
        logfile.write("Error en carga horaria. Data: " + materia_record[0] + " - " + materia_record[1] + "\n");
    materias.finishsearch();
}

void Horario::put_materia(Dia dia, std::string materia, int* horas, int indice_horario)
{
    int dia_int = get_dia(dia);
    int num_horas_max = 2;
    for (int i = 0; i < NUM_HORAS; i++) {
        if (horarios[indice_horario][i][dia_int] == "") {
            horarios[indice_horario][i][dia_int] = materia;
            *horas -= 1;
            num_horas_max--;
            if (num_horas_max > 0 && *horas > 0)
                continue;
            else
                return;
        }
    }
}

bool Horario::can_put_materia(int num_horas, int indice_horario)
{
    int dia_actual = 0;
    int num_horas_aux = 0;
    while (dia_actual < 5 && num_horas > 0) {
        num_horas_aux = num_horas;
        put_materia(dias[dia_actual], ".", &num_horas, indice_horario);
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
            if (horarios[indice_horario][i][j] == ".")
                horarios[indice_horario][i][j] = "";
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

void Horario::showall()
{
    for (int i = 0; i < horarios.size(); i++) {
        show(i);
        std::cout << std::endl << std::endl;
    }
}

void Horario::show(int index)
{
    for (int  j = 0; j < 5; j++) {
        for (int i = 0; i < NUM_HORAS; i++)
            std::cout << horarios[index][i][j] << " | ";
        std::cout << std::endl;
    }
}

void Horario::finish()
{
    materias.finish();
    logfile.close();
}
