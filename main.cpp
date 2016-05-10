#include <iostream>
#include <iomanip> 
#include <regex>
#include <stdlib.h>

#include "csvfile.h"
#include "materias.h"
#include "log.h"
#include "horario.h"
#include "administrador.h"
#include "usuario.h"

using namespace std;

void show_menu();
void show_menu_administrador();
void show_menu_usuario();

int leer_opcion();

void panel_administrador();
void panel_usuario();
void show_help();

void ingresar_archivos_csv_adm(Administrador* admin);
void ver_archivos_adm(Administrador* admin);
void generar_horarios_adm(Administrador* admin);


int main(int argc, char** argv)
{
    Usuario usuario;
    
    int opcion = -1;
    while (opcion != 4) {
        show_menu();
        opcion = leer_opcion();
        switch (opcion) {
        case 1:
            panel_administrador();
            break;
        case 2:
            panel_usuario();
            break;
        case 3:
            show_help();
            break;
        case 4:
            break;
        default:
            cout << "Opcion incorrecta. Vuelva a intentarlo." << endl;
        }
    }
    
    /*
    Horario horario;
    
    horario.set_aulas_file("resources/aulas.csv");
    horario.set_docentes_file("resources/docentes.csv");
    horario.set_estudiantes_file("resources/alumnos.csv");
    horario.set_materias_file("resources/materias.csv");
    horario.generate();
    */
    
    
    // TODO Establecer acciones del docente
    // TODO Establecer acciones del estudiante
    // TODO Quien puede ver el horario de una sala?
    // TODO Redactar ayuda
    // TODO mostrar horarios en pantalla
    
    // TODO implementar caché en busquedas
    return 0;
}

void show_menu()
{
    cout << "ADMINISTRADOR DE HORARIOS" << endl;
    cout << "1) Ingresar como administrador" << endl;
    cout << "2) Ingresar como usuario" << endl;
    cout << "3) Mostrar ayuda" << endl;
    cout << "4) Salir" << endl;
}

void show_menu_administrador()
{
    cout << "ZONA DE ADMINISITRADOR" << endl;
    cout << "1) Ingresar archivos csv" << endl;
    cout << "2) Ver archivo" << endl;
    cout << "3) Generar horarios" << endl;
    cout << "4) Atras" << endl;
}

void show_menu_usuario()
{
    cout << "ZONA DE USUARIO" << endl;
}

int leer_opcion()
{
    int result = -1;
    
    std:string line;
    cin >> line;
    cin.ignore(1024, '\n');
    
    std::regex regex_opcion("^(\\d{1,3})$");
    std::smatch groups;
    
    if (std::regex_match(line, groups, regex_opcion))
       result = atoi(line.c_str());
    return result;
}

void panel_administrador()
{
    system("clear");
    Administrador administrador;
    int opcion = -1;
    while (opcion != 4) {
        show_menu_administrador();
        opcion = leer_opcion();
        switch (opcion) {
        case 1:
            ingresar_archivos_csv_adm(&administrador);
            break;
        case 2:
            ver_archivos_adm(&administrador);
            break;
        case 3:
            generar_horarios_adm(&administrador);
            break;
        case 4:
            system("clear");
            break;
        default:
            cout << "Opcion incorrecta. Vuelva a intentarlo." << endl;
        }
    }
}

void ingresar_archivos_csv_adm(Administrador* admin)
{
    // TODO clean up!
    string line;
    while (true) {
        cout << "Ingrese el archivo csv de las aulas:" << endl;
        cin >> line;
        cin.ignore(1024, '\n');
        if (admin->set_aulas_file(line))
            break;
        cout << "Archivo no valido, vuelva a intentarlo." << endl;
    }
    
    while (true) {
        cout << "Ingrese el archivo csv de las materias:" << endl;
        cin >> line;
        cin.ignore(1024, '\n');
        if (admin->set_materias_file(line))
            break;
        cout << "Archivo no valido, vuelva a intentarlo." << endl;
    }
    
    while (true) {
        cout << "Ingrese el archivo csv de los estudiantes:" << endl;
        cin >> line;
        cin.ignore(1024, '\n');
        if (admin->set_estudiantes_file(line))
            break;
        cout << "Archivo no valido, vuelva a intentarlo." << endl;
    }
    
    while (true) {
        cout << "Ingrese el archivo csv de los docentes:" << endl;
        cin >> line;
        cin.ignore(1024, '\n');
        if (admin->set_docentes_file(line))
            break;
        cout << "Archivo no valido, vuelva a intentarlo." << endl;
    }
}

void ver_archivos_adm(Administrador* admin)
{
    string line;
    cout << "Ingrese la ruta del archivo:" << endl;
        cin >> line;
        cin.ignore(1024, '\n');
        admin->show_csv_file(line);
}

void generar_horarios_adm(Administrador* admin)
{
    cout << "Generando horarios..." << endl;
    if (!admin->generar_horarios())
        return;
    cout << "Horarios generados" << endl;
    cout << "Presione una tecla para ver el informe." << endl;
    getchar();
    cout << "Registro:" << endl;
    admin->show_logfile();
    cout << "Puede ver el registro en: horario/log.txt" << endl;
}

void panel_usuario()
{
    // TODO
}

void show_help()
{
    
}