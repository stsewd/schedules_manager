#ifndef CSVFILE_H
#define CSVFILE_H

#include <string>
#include <fstream>

struct Csvfile {
    std::ifstream flujo_entrada;
    
    void set_file(std::string path);
    std::string next_record();
    void init();
    void close();
    void open_file(std::string path);
    void show_file();
};

#endif /* MATERIA_H */
