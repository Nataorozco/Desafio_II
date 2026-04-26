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
    int goles;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int partidosJugados;
    int minutosJugados;

public:
    // (Constructor de copia obligatorio)
    Jugador();
    Jugador(std::string nom, std::string ape, int numCam);
    Jugador(const Jugador& otro); // Fundamental para el manejo de memoria

    // Métodos de actualización de estadísticas
    void jugarPartido();
    void anotarGol();
    void setGoles(int n); // Solo para carga inicial
    void sumarMinutos(int min);
    void asistir();
    void recibirAmarilla();
    void recibirRoja();
    void cometerFalta();

    // Getters para el informe final de estadísticas
    std::string getNombreCompleto() const;
    int getCamiseta() const;
    int getGoles() const;
    int getTjAmarillas() const;
    int getTjRojas() const;
    int getTjFaltas() const;
    int getAsistencias() const;
    int getMinutosJugados() const;
    int getPartidosJugados() const;

    ~Jugador();

};

#endif
