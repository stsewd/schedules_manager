#include <vector>
#include <regex>

#include "horarioparser.h"
#include "materias.h"

void Horarioparser::set_horarios_file(std::string path)
{
    flujo_entrada.open(path);
    horarios.clear();
}

std::vector<std::array<std::array<Materia, 5>, 10> > Horarioparser::get_horarios()
{
    add_horario();
    char line[10000] = "";
    int dia = 0;
    while (!flujo_entrada.eof()) {
        flujo_entrada.getline(line, sizeof(line));
        if (line[0] == '\0') {
            dia = 0;
            add_horario();
            continue;
        }
        add_materias_to(parser_line(line), dia++);
    }
    flujo_entrada.close();
    return horarios;
}

std::vector<Materia> Horarioparser::parser_line(std::string line)
{
    std::vector<Materia> materias;
    std::regex regex_materias("^([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),$");
    std::regex regex_materia("^([^|]*)\\|([^|]*)\\|([^|]*)$");
    std::smatch groups_materias;
    std::smatch groups_materia;
    
    if (!std::regex_match(line, groups_materias, regex_materias))
       return {};
    
    for (int i = 1; i <= 10; i++) {
        std::string s = groups_materias[i];
        std::regex_match(s, groups_materia, regex_materia);
        Materia materia;
        materia.nombre = groups_materia[1];
        materia.docente_id = groups_materia[2];
        materia.aula = groups_materia[3];
        materias.push_back(materia);
    }
    return materias;
}

void Horarioparser::add_materias_to(std::vector<Materia> materias, int dia)
{
    int index_horario = horarios.size() - 1;
    for (int hora = 0; hora < 10; hora++)
            horarios[index_horario][hora][dia] = materias[hora];
}


void Horarioparser::add_horario()
{
    std::array<std::array<Materia, 5>, 10> horario;
    horarios.push_back(horario);
}
