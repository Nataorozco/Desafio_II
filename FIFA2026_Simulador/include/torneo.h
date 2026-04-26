#ifndef TORNEO_H
#define TORNEO_H

#include "vector.h"
#include "partido.h"
#include "equipo.h"
#include "jugador.h"
#include "Grupo.h"
#include "Bombo.h"
#include <string>

using std::string;


class Torneo {
private:
    Vector<Equipo*> equipos;
    Vector<Partido*> partidos;
    Vector<Grupo*> grupos;
    Jugador* maximoGoleador;
    Vector<Jugador*> topGoleadores;
    Vector<Equipo*> rankingFinal;

public:
    Torneo();
    ~Torneo();

    // Métodos principales
    void cargarDatos(const string& rutaCSV);
    void conformarFaseGrupos();
    void simularFaseGrupos();
    void simularEliminatorias();
    void generarEstadisticasFinales();

    // Getters
    Vector<Equipo*>& getEquipos() { return equipos; }
    int getNumeroEquipos() const { return equipos.getTamano(); }
    bool sortearBacktracking(int bIdx, int gIdx, Bombo* bombos[], Vector<Grupo*>& grupos, long long& it);
};

#endif
