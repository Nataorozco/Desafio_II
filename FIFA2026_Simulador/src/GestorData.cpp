#include "GestorData.h"
#include <fstream>

void GestorData::exportarMatrizFicherosDataJugador(const std::string& nombreArchivo,
                                        const Vector<Equipo*>& equipos,
                                        int tipoEstadistica) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;

    // 1. Cabecera de dorsales (1 a 26)
    archivo << "(NumCamiseta →) (País ↓)";
    for (int i = 1; i <= 26; i++) {
        archivo << ";" << i;
    }
    archivo << "\n";

    // 2. Filas por país
    for (int i = 0; i < equipos.getTamano(); i++) {
        Equipo* eq = equipos[i];
        archivo << eq->getPais();

        for (int j = 0; j < 26; j++) {
            Jugador* jug = eq->getJugadores()[j];
            archivo << ";" << obtenerDatoSegunTipoDataJugador(jug, tipoEstadistica);
        }
        archivo << "\n";
    }
    archivo.close();
}

int GestorData::obtenerDatoSegunTipoDataJugador(Jugador* j, int tipo) {
    switch(tipo) {
    case 1: return j->getGoles();
    case 2: return j->getAsistencias();
    case 3: return j->getTjAmarillas();
    case 4: return j->getTjRojas();
    case 5: return j->getTjFaltas();
    case 6: return j->getMinutosJugados();
    case 7: return j->getPartidosJugados();
    default: return 0;
    }
}

void GestorData::actualizarDatosPaisDataJugador(const std::string& ruta, Equipo* equipo, int tipoEstadistica) {
    Vector<std::string> lineasMemoria;
    std::string linea;
    bool paisEncontrado = false;

    // 1. Lectura
    std::ifstream archivoLectura(ruta);
    if (archivoLectura.is_open()) {
        while (std::getline(archivoLectura, linea)) {
            if (linea.empty()) continue;

            // Buscamos el país al inicio de la línea
            std::string nombrePais = equipo->getPais();
            if (linea.compare(0, nombrePais.length(), nombrePais) == 0 &&
                (linea.length() > nombrePais.length() && linea[nombrePais.length()] == ';')) {

                // Reemplazamos con datos frescos
                std::string nuevaLinea = nombrePais;
                for (int i = 0; i < 26; i++) {
                    int valor = obtenerDatoSegunTipoDataJugador(equipo->getJugadores()[i], tipoEstadistica);
                    nuevaLinea += ";" + std::to_string(valor);
                }
                lineasMemoria.push_back(nuevaLinea);
                paisEncontrado = true;
            } else {
                lineasMemoria.push_back(linea);
            }
        }
        archivoLectura.close();
    }

    // 2. Escritura (Sobrescribe con ios::trunc)
    std::ofstream archivoEscritura(ruta, std::ios::trunc);
    for (int i = 0; i < lineasMemoria.getTamano(); i++) {
        archivoEscritura << lineasMemoria[i] << "\n";
    }

    // Si es un país nuevo que no estaba en el archivo
    if (!paisEncontrado) {
        std::string nuevaLinea = equipo->getPais();
        for (int i = 0; i < 26; i++) {
            nuevaLinea += ";" + std::to_string(obtenerDatoSegunTipoDataJugador(equipo->getJugadores()[i], tipoEstadistica));
        }
        archivoEscritura << nuevaLinea << "\n";
    }
    archivoEscritura.close();
}