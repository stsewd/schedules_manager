#include <cstdlib>
#include <iostream>
#include "csvfile.h"
#include "materia.h"

int main(int argc, char** argv)
{
    std::string line;
    Csvfile csvfile;
    csvfile.set_file("resources/materias.csv");
    while((line = csvfile.next_record()) != "")
        std::cout << line << std::endl;
    csvfile.close();
    
    return 0;
}

