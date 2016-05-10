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
string leer_cedula();
string leer_materia();
string leer_sala();

void panel_administrador();
void panel_usuario();
void show_help();

void ingresar_archivos_csv_adm(Administrador* admin);
void ver_archivos_adm(Administrador* admin);
void generar_horarios_adm(Administrador* admin);

void mostrar_horario_docente(Usuario* usuario);
void mostrar_horario_estudiante(Usuario* usuario);
void mostrar_horario_sala(Usuario* usuario);
void mostrar_horario_materia(Usuario* usuario);
string consultar_exportar();
void exportar(Usuario* usuario);

int main(int argc, char** argv)
{
    // TODO listar estudiantes de una materia, agregar opcion al menu?
    // TODO Redactar ayuda
    // TODO implementar caché en busquedas
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
    cout << "1) Ver horario de un docente" << endl;
    cout << "2) Ver horario de un estudiante" << endl;
    cout << "3) Ver horario de una sala" << endl;
    cout << "4) Ver horario de una materia" << endl;
    cout << "5) Atras" << endl;
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
    system("clear");
    Usuario usuario;
    usuario.init();
    
    int opcion = -1;
    while (opcion != 5) {
        show_menu_usuario();
        opcion = leer_opcion();
        switch (opcion) {
        case 1:
            mostrar_horario_docente(&usuario);
            break;
        case 2:
            mostrar_horario_estudiante(&usuario);
            break;
        case 3:
            mostrar_horario_sala(&usuario);
            break;
        case 4:
            mostrar_horario_materia(&usuario);
            break;
        case 5:
            usuario.finish();
            system("clear");
            break;
        default:
            cout << "Opcion incorrecta. Vuelva a intentarlo." << endl;
        }
    }
}

void mostrar_horario_docente(Usuario* usuario)
{
    usuario->new_query();
    string cedula = leer_cedula();
    cout << "HORARIO" << endl;
    usuario->show_horario_docente(cedula);
    exportar(usuario);
}

void exportar(Usuario* usuario)
{
    string export_path = consultar_exportar();
    if (export_path != "") {
        usuario->exportar_horario(export_path);
        cout << "Horario exportado a: export/" << export_path << ".csv" << endl;
    }
}

string leer_cedula()
{
    string cedula;
    regex cedula_regex("^\\d{10}$");
    while (true) {
        cout << "Ingrese un numero de cédula válido: " << endl;
        cin >> cedula;
        cin.ignore(1024, '\n');
        if (regex_match(cedula, cedula_regex))
            break;
        cout << "Cedula no válida" << endl;
    }
    return cedula;
}

string leer_materia()
{
    string materia;
    regex materia_regex("^.+$");
    while (true) {
        cout << "Ingrese el nombre de la materia:" << endl;
        getline(cin, materia);
        if (regex_match(materia, materia_regex))
            break;
        cout << "Nombre no válido" << endl;
    }
    return materia;
}

string leer_sala()
{
    string sala;
    regex sala_regex("^.+$");
    while (true) {
        cout << "Ingrese el código de la sala:" << endl;
        getline(cin, sala);
        if (regex_match(sala, sala_regex))
            break;
        cout << "Sala no válida" << endl;
    }
    return sala;
}

void mostrar_horario_estudiante(Usuario* usuario)
{
    usuario->new_query();
    string cedula = leer_cedula();
    cout << "HORARIO" << endl;
    usuario->show_horario_estudiante(cedula);
    exportar(usuario);
}

void mostrar_horario_sala(Usuario* usuario)
{
    usuario->new_query();
    string sala = leer_sala();
    cout << "HORARIO" << endl;
    usuario->show_horario_aula(sala);
    exportar(usuario);
}

void mostrar_horario_materia(Usuario* usuario)
{
    usuario->new_query();
    string materia = leer_materia();
    cout << "HORARIO" << endl;
    usuario->show_horario_materia(materia);
    exportar(usuario);
}

string consultar_exportar()
{
    string export_path;
    regex regex_nombre("\\w+");
    cout << "¿Desea exportar el horario? (s/n)" << endl;
    char opc = getchar();
    if (opc != 's' && opc != 'S')
        return "";
    
    while (true) {
        cout << "Ingrese el nombre del horario: " << endl;
        getline(cin, export_path);
        if (regex_match(export_path, regex_nombre))
            break;
        cout << "Nombre no valido" << endl;
    }
    return export_path;
}

void show_help()
{
    
}