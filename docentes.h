#ifndef DOCENTES_H
#define DOCENTES_H

#include <vector>
#include <string>

#include "csvfile.h"
#include "log.h"

struct Docente {
private:
    Csvfile csv_docentes;
    Log* errorlog;
public:
    void set_errorlog(Log* log);
    void set_docentes_file(std::string path);
    std::vector<std::string> search_id(std::string id);
    std::vector<std::string> parser_record(std::string record);
    void finish();
};

#endif /* DOCENTE_H */
