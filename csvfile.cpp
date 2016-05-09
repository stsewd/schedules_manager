#include <fstream>
#include <string>
#include <iostream>

#include "csvfile.h"

void Csvfile::open_file(std::string path)
{
    flujo_entrada.open(path);
}

std::string Csvfile::next_record()
{
    char line[10000] = "";
    if (!flujo_entrada.eof()) {
        flujo_entrada.getline(line, sizeof(line));
        return line;
    }
    return line;
}

void Csvfile::init()
{
    flujo_entrada.seekg(0);
    next_record();
}

void Csvfile::set_file(std::string path)
{
    open_file(path);
    next_record();
}

void Csvfile::close()
{
    flujo_entrada.close();
}

void Csvfile::show_file()
{
    flujo_entrada.seekg(0);
    std::string line;
    while ((line = next_record()) != "")
        std::cout << line << std::endl;
}

