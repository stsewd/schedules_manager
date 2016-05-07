#ifndef MATERIAS_H
#define MATERIAS_H

#include "csvfile.h"
#include "docentes.h"

struct Materia {
    std::string nombre;
    std::string aula;
};

struct Materias {
private:
    const std::string MATERIAS_PATH = "horario/materias.csv";
    const std::string DOCENTES_PATH = "horario/docentes.csv";
    
    Csvfile csv_materias_entrada;
    
    std::ofstream flujo_salida_materias;
    std::ofstream flujo_salida_docentes;
    
    Csvfile csv_materias;
    Docente docentes;
    Log* errorlog;
public:
    void set_docentes_file(std::string path);
    void set_materias_file(std::string path);
    std::vector<std::string> parser_record(std::string record);
    std::vector<std::string> next_materia(int minhours, int maxhours);
    void set_errorlog(Log* log);
    void finish();
    void initsearch();
    void finishsearch();
    void join_materias_docentes();
private:
    void init_streams();
    void addcabecera_docentes();
    void addcabecera_materias();
    std::vector<std::string> parser_record_inner(std::string record);
};


#endif /* MATERIA_H */
