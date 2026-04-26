#ifndef PARTIDO_H
#define PARTIDO_H
#include "equipo.h"
#include <string>

using std::string;


class Partido {
    private:
        string fecha;
        string hora;
        string arbitros[3];
        Equipo* equipo1;
        Equipo* equipo2;
        int golesEquipo1;
        int golesEquipo2;
        bool uboProrroga;
        Equipo* equipoGanador;
    public:
        void simularPartido();
        void actualizarResultado();
};

#endif
