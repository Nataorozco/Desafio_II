#include "vector.h"
#include "equipo.h"
#include "jugador.h"

using namespace std;

Equipo::Equipo(int ranking, const string& pais, const string& director,
               const string& federacion, const string& confederacion,
               int gf, int gc, int pg, int pe, int pp,bool asignado = false)
    : rankingFIFA(ranking), pais(pais), directorTecnico(director),
    federacion(federacion), confederacion(confederacion),
    golesAFavor(gf), golesEnContra(gc),
    partidosGanados(pg), partidosEmpatados(pe), partidosPerdidos(pp)
{
    // Generar 26 jugadores artificiales
    generarJugadores();
}

Equipo::~Equipo() {
    // Liberar memoria de jugadores
    for (int i = 0; i < jugadores.getTamano(); i++) {
        delete jugadores[i];
    }
}

int Equipo::getTotalPartidos() const {
    return partidosGanados + partidosEmpatados + partidosPerdidos;
}

double Equipo::getPromedioGolesAFavor() const {
    int total = getTotalPartidos();
    if (total == 0) return 0.0;
    return (double)golesAFavor / total;
}

double Equipo::getPromedioGolesEnContra() const {
    int total = getTotalPartidos();
    if (total == 0) return 0.0;
    return (double)golesEnContra / total;
}

void Equipo::registrarVictoria(int goles) {
    partidosGanados++;
    golesAFavor += goles;
}

void Equipo::registrarEmpate(int goles) {
    partidosEmpatados++;
    golesAFavor += goles;
}

void Equipo::registrarDerrota(int golesRecibidos) {
    partidosPerdidos++;
    golesEnContra += golesRecibidos;
}

void Equipo::generarJugadores(){
    string nombreBase = "nombre";
    string apellidoBase = "apellido";

    for (int i = 1; i <= Equipo::MAX_JUGADORES; ++i) {
        Jugador* jugador = new Jugador(nombreBase+to_string(i), apellidoBase+to_string(i), i);
        jugadores.push_back(jugador);
    }
}

void Equipo::repartirGolesCargaInicial() {
    if (jugadores.getTamano() == 0) return;

    // 1. Calcular cuántos goles le tocan a todos por igual
    int golesBase = golesAFavor / MAX_JUGADORES;

    // 2. Calcular cuántos goles sobran (residuo)
    int residuo = golesAFavor % MAX_JUGADORES;

    for (int i = 0; i < jugadores.getTamano(); ++i) {
        // Los primeros 'residuo' jugadores reciben un gol extra
        int golesParaEsteJugador = golesBase + (i < residuo ? 1 : 0);

        // 3. Asignar al objeto jugador
        jugadores[i]->setGoles(golesParaEsteJugador);
    }
}

bool Equipo::isAsignado() const {
    return asignado;
}

void Equipo::setAsignado(bool estado) {
    asignado = estado;
}
