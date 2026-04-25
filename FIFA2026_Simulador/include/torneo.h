#ifndef TORNEO_H
#define TORNEO_H

#include "vector.h"
#include "partido.h"
#include "equipo.h"
#include "jugador.h"
#include <string>

using std::string;


class Torneo {
    private:
        Vector<Equipo*> equipos;
        Vector<Partido*> partidos;
        Jugador* maximoGoleador;
        Vector<Jugador*> topGoleadores;
        Vector<Equipo*> rankingFinal;

    public:
        void cargarDatos();
        void conformarFaseGrupos();
        void simularFaseGrupos();
        void simularEliminatorias();
        void generarEstadisticasFinales();
};

#endif
