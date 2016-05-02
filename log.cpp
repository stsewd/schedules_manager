/**
 * Archivo donde se guardan los errores que puedan ocurrir en el transcurso
 * del programa.
 */

#include "log.h"

void Log::init() 
{
    flujo_salida.open(PATH);
}

void Log::write(std::string msj)
{
    flujo_salida << msj;
}

void Log::close()
{
    flujo_salida.close();
}
