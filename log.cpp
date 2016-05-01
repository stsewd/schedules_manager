#include "log.h"

void Log::init() 
{
    flujo_salida.open(PATH);
    flujo_salida.close();
    flujo_salida.open(PATH, std::ios_base::app);
}

void Log::write(std::string msj)
{
    flujo_salida << msj;
}

void Log::close()
{
    flujo_salida.close();
}