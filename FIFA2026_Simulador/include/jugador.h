#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>

using std::string;

class Jugador {
    private:
        string nombre;
        string apellido;
        string camiseta;
        int goles;
        int minutos;
        int tajetasAmarilla;
        int tajetasRojas;
        int faltas;
    public:
        Jugador(const std::string& nombre, const std::string& camiseta);
        void anotarGol();
        void jugarMinutos();
        void recibirAmarilla();
        void recibirRojas();
        void cometerFalta();
};

#endif
