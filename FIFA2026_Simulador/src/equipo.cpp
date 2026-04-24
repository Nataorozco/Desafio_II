#include "vector.h"
#include "equipo.h"
#include "jugador.h"

using namespace std;

Equipo::Equipo(int ranking, const string& pais, const string& director,
               const string& federacion, const string& confederacion,
               int gf, int gc, int pg, int pe, int pp)
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
    string camisetaBase = "camiseta";

    for (int i = 1; i <= 26; ++i) {
        Jugador* jugador = new Jugador(nombreBase+to_string(i), apellidoBase+to_string(i), camisetaBase+to_string(i));
        jugadores.push_back(jugador);
    }
}
