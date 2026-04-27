#ifndef BOMBO_H
#define BOMBO_H

#include "vector.h"
#include "equipo.h"
#include <iostream>

class Bombo : public Vector<Equipo*> {
public:
    Bombo();

    // Mezcla aleatoria usando Fisher-Yates
    void mezclar(long long &contadorIteraciones);

    // Sobrecarga del operador de salida
    friend std::ostream& operator<<(std::ostream& os, const Bombo& b);
};


#endif // BOMBO_H
