#include <iostream>

#include "administrador.h"

void Administrador::generar_horarios()
{
    if (archivos_introducidos())
        horario.generate();
    else
        std::cout << "No ha ingresado los archivos necesarios para generar los horarios." << std::endl;
}

bool Administrador::archivos_introducidos()
{
    return aulas_path != "" && estudiantes_path != "" && materias_path != "" && docentes_path != "";
}


bool Administrador::set_aulas_file(std::string path)
{
    if (!exist_file(path))
        return false;
    horario.set_aulas_file(path);
    return true;
}

bool Administrador::set_docentes_file(std::string path)
{
    if (!exist_file(path))
        return false;
    horario.set_docentes_file(path);
    return true;
}

bool Administrador::set_estudiantes_file(std::string path)
{
    if (!exist_file(path))
        return false;
    horario.set_estudiantes_file(path);
    return true;
}

bool Administrador::set_materias_file(std::string path)
{
    if (!exist_file(path))
        return false;
    horario.set_materias_file(path);
    return true;
}

bool Administrador::exist_file(std::string path)
{
    if (std::ifstream(path))
        return true;
    return false;
}


void Administrador::show_csv_file(std::string path)
{
    if (!exist_file(path)) {
        std::cout << "El archivo no existe" << std::endl;
        return;
    }
    Csvfile archivo;
    archivo.set_file(path);
    archivo.show_file();
    archivo.close();
}

void Administrador::show_logfile()
{
    std::string path = "horario/log.txt";
    if (!exist_file(path))
        std::cout << "Horario generado sin ningún problema" << std::endl;
    else {
        std::ifstream flujo_entrada;
        flujo_entrada.open(path);
        char line[10000] = "";
        while (!flujo_entrada.eof()) {
            flujo_entrada.getline(line, sizeof(line));
            std::cout << line << std::endl;
        }
    }
}
