#ifndef GESTORDATA_H
#define GESTORDATA_H

#include <string>
#include "vector.h"
#include "equipo.h"
#include "jugador.h"

class GestorData {
public:
    // Exporta cualquier estadística tipo int de los jugadores a una matriz CSV
    static void exportarMatrizFicherosDataJugador(const std::string& nombreArchivo,
                                       const Vector<Equipo*>& equipos,
                                       int tipoEstadistica);

private:
    static int obtenerDatoSegunTipoDataJugador(Jugador* j, int tipo);
    static void actualizarDatosPaisDataJugador(const std::string& ruta, Equipo* equipo, int tipoEstadistica);
};

#endif
