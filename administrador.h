#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "horario.h"


struct Administrador {
    Horario horario;
    std::string aulas_path;
    std::string estudiantes_path;
    std::string materias_path;
    std::string docentes_path;
    
    bool exist_file(std::string path);
    bool set_aulas_file(std::string path);
    bool set_estudiantes_file(std::string path);
    bool set_docentes_file(std::string path);
    bool set_materias_file(std::string path);
    bool generar_horarios();
    bool archivos_introducidos();
    
    void show_logfile();
    void show_csv_file(std::string path);
};


#endif /* ADMINISTRADOR_H */
