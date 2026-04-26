#include "Grupo.h"
#include <string>

Grupo::Grupo(std::string id) : idGrupo(id) {}

int Grupo::contarEquiposPorConfederacion(std::string conf) {
    int contador = 0;
    for (int i = 0; i < equipos.getTamano(); i++) {
        if (equipos[i]->getConfederacion() == conf) {
            contador++;
        }
    }
    return contador;
}

bool Grupo::esValido(Equipo* e) {
    // Máximo 4 equipos por grupo
    if (equipos.getTamano() >= 4) return false;

    std::string confNueva = e->getConfederacion();
    int actuales = contarEquiposPorConfederacion(confNueva);

    // Regla UEFA: Máximo 2 equipos
    if (confNueva == "UEFA") {
        return actuales < 2;
    }

    // Otras confederaciones: Máximo 1 equipo
    return actuales < 1;
}

bool Grupo::agregarEquipo(Equipo* e) {
    if (!esValido(e)) return false; // El método esValido que me compartiste
    if (equipos.getTamano() >= 4) return false; // Límite por grupo

    equipos.push_back(e);
    return true;
}

std::string Grupo::toString() {
    std::string reporte = "Grupo: " + idGrupo + "\n";
    for (int i = 0; i < equipos.getTamano(); i++) {
        reporte += equipos[i]->getPais() + " (" + equipos[i]->getConfederacion() + ")\n";
    }
    return reporte;
}

int Grupo::getCantidadEquipos() {
    return equipos.getTamano();
}

void Grupo::quitarUltimoEquipo() {
    if (equipos.getTamano() > 0) {
        // Obtenemos la posición del último equipo
        int ultimaPos = equipos.getTamano() - 1;

        // Removemos de nuestro vector personalizado.
        // Asegúrate de que removeAt reduzca el tamaño interno del vector y no pierda la referencia a memoria.
        equipos.removeAt(ultimaPos);
    }
}
