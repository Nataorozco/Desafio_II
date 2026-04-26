#include <iostream>
#include "torneo.h"
#include "equipo.h"
// #include "jugador.h"

using namespace std;

int main() {
    cout << "|=================================|" << endl;
    cout << "| FIFA 2026 - SIMULADOR DE TORNEO |" << endl;
    cout << "|=================================|" << endl << endl;

    // Crear instancia del torneo
    Torneo torneo;

    string rutaRelativa = "importAndExport/selecciones_clasificadas_mundial.csv";

    // Cargar datos desde el CSV
    torneo.cargarDatos(rutaRelativa);

    // Vector<Equipo*>& equipos = torneo.getEquipos();
    // Equipo* equipo = equipos[10];

    // cout << "\nJugadores del equipo " << equipo->getPais() <<  " en el sistema:" << endl;

    // const Vector<Jugador*>& jugadores = equipo->getJugadores();

    // for (int i = 0; i < jugadores.getTamano(); ++i) {
    //     Jugador* jugador = jugadores[i];
    //     cout << "\n  Jugador["+to_string(i)<< "]: " << jugador->getNombreCompleto() << " " << jugador->getCamiseta() << endl;
    //     cout << "  Cantidad de goles " << jugador->getGoles() << endl;
    // }

    torneo.conformarFaseGrupos();


    return 0;
}
