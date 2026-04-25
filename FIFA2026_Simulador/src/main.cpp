#include <iostream>
#include "torneo.h"
#include "equipo.h"
#include "jugador.h"

using namespace std;

int main() {
    cout << "|=================================|" << endl;
    cout << "| FIFA 2026 - SIMULADOR DE TORNEO |" << endl;
    cout << "|=================================|" << endl << endl;

    // Crear instancia del torneo
    Torneo torneo;

    // Cargar datos desde el CSV
    torneo.cargarDatos("C:/Users/elmer/dev/studentspace/Desafio_II/FIFA2026_Simulador/importAndExport/selecciones_clasificadas_mundial.csv");

    Vector<Equipo*>& equipos = torneo.getEquipos();
    Equipo* equipo = equipos[0];

    cout << "\nJugadores del equipo " << equipo->getPais() <<  " en el sistema:" << endl;

    const Vector<Jugador*>& jugadores = equipo->getJugadores();

    for (int i = 0; i < jugadores.getTamano(); ++i) {
        Jugador* jugador = jugadores[i];
        cout << "\n  Jugador["+to_string(i)<< "]: " << jugador->getNombreCompleto() << " " << jugador->getCamiseta() << endl;
    }

    return 0;
}
