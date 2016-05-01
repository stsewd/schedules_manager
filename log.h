#ifndef LOG_H
#define LOG_H

#include <fstream>

struct Log {
    const std::string PATH = "horario/log.txt";
    std::ofstream flujo_salida;
    void init();
    void write(std::string msj);
    void close();
};

#endif /* LOG_H */
