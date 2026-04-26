#include "Bombo.h"
#include <ostream>
#include <random>

Bombo::Bombo() : Vector<Equipo*>() {}

void Bombo::mezclar(long long &contadorIteraciones) {
    int n = getTamano();
    if (n <= 1) return;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = n - 1; i > 0; --i) {
        std::uniform_int_distribution<> distrib(0, i);
        int j = distrib(gen);

        // Intercambio
        Equipo* temp = operator[](i);
        (*this)[i] = (*this)[j];
        (*this)[j] = temp;

        contadorIteraciones++;
    }
}

std::ostream& operator<<(std::ostream& os, const Bombo& b) {
    for (int i = 0; i < b.getTamano(); ++i) {
        os << b[i]->getPais() << " (" << b[i]->getConfederacion() << ")\n";
    }
    return os;
}
