#include "horario.h"
#include <iostream>
#include <string>

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
    discard_materias();
    put_materias(5, 6);
    put_materias(3, 4);
    put_materias(1, 2);
    finish();
}

void Horario::put_materias(int minhours, int maxhours)
{
    std::vector<std::string> materia_record;
    int num_horas;
    int num_horas_aux;
    int dia_actual;
    materias.initsearch();
    while (!(materia_record = materias.next_materia(minhours, maxhours)).empty()) {
        num_horas = atoi(materia_record[1].c_str());
        dia_actual = 0;
        while (dia_actual < 5 && num_horas > 0) {
            num_horas_aux = num_horas;
            put_materia(dias[dia_actual], materia_record[0], &num_horas);
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

void Horario::put_materia(Dia dia, std::string materia, int* horas)
{
    int dia_int = get_dia(dia);
    int num_horas_max = 2;
    for (int i = 0; i < NUM_HORAS; i++) {
        if (horario[i][dia_int] == "") {
            horario[i][dia_int] = materia;
            *horas -= 1;
            num_horas_max--;
            if (num_horas_max > 0 && *horas > 0)
                continue;
            else
                return;
        }
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

void Horario::show()
{
    for (int  j = 0; j < 5; j++) {
        for (int i = 0; i < NUM_HORAS; i++)
            std::cout << horario[i][j] << " | ";
        std::cout << std::endl;
    }
}

void Horario::finish()
{
    materias.finish();
    logfile.close();
}
