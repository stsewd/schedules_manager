#include <fstream>
#include <string>

#include "csvfile.h"

void Csvfile::open_file(std::string path)
{
    flujo_entrada.open(path);
}

std::string Csvfile::next_record()
{
    char line[1000] = "";
    if (!flujo_entrada.eof()) {
        flujo_entrada.getline(line, sizeof(line));
        return line;
    }
    return line;
}

void Csvfile::begin()
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