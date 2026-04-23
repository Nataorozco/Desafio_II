#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
private:
    // Identificación (Requisito I: nombres fabricados artificialmente)
    std::string nombre;
    std::string apellido;
    int numeroCamiseta;

    // Estadísticas que se actualizan tras cada partido
    int partidosJugados;
    int goles;
    int minutosJugados;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    // (Constructor de copia obligatorio)
    Jugador();
    Jugador(std::string nom, std::string ape, int num);
    Jugador(const Jugador& otro); // Fundamental para el manejo de memoria

    // Métodos de actualización de estadísticas
    void anotarGol();
    void sumarMinutos(int min);
    void recibirAmarilla();
    void recibirRoja();
    void cometerFalta();

    // Getters para el informe final de estadísticas
    std::string getNombreCompleto() const;
    int getGoles() const;

    ~Jugador();
};

#endif
