#ifndef CSVFILE_H
#define CSVFILE_H

#include <string>
#include <fstream>

struct Csvfile {
private:
    std::ifstream flujo_entrada;
public:
    void set_file(std::string path);
    std::string next_record();
    void init();
    void close();
private:
    void open_file(std::string path);
};

#endif /* MATERIA_H */
