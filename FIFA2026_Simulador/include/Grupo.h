#ifndef GRUPO_H
#define GRUPO_H

#include <string>
#include "Vector.h" // Tu implementación propia de Vector
#include "Equipo.h"

class Grupo {
private:
    std::string idGrupo;
    Vector<Equipo*> equipos; // Almacena punteros para eficiencia

public:
    // Constructor
    Grupo(std::string id);

    // Reglas de validación
    int contarEquiposPorConfederacion(std::string conf);
    bool esValido(Equipo* e);
    bool agregarEquipo(Equipo* e);

    // Salida de datos
    std::string toString();
    int getCantidadEquipos();
    void quitarUltimoEquipo();
};



#endif // GRUPO_H
