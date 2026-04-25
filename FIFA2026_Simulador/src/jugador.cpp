#include "Jugador.h"

// Inicialización de estadísticas en cero según el Requisito
Jugador::Jugador() : nombre(""), apellido(""), numeroCamiseta(0),
    partidosJugados(0), goles(0), minutosJugados(0), asistencias(0),
    tarjetasAmarillas(0), tarjetasRojas(0), faltas(0) {}

// Constructor
Jugador::Jugador(std::string nom, std::string ape, int numCam) :
    nombre(nom), apellido(ape), numeroCamiseta(numCam),
    partidosJugados(0), goles(0), minutosJugados(0), asistencias(0),
    tarjetasAmarillas(0), tarjetasRojas(0), faltas(0) {}

// Implementación del constructor de copia para cumplir con el buen diseño
Jugador::Jugador(const Jugador& otro) {
    nombre = otro.nombre;
    apellido = otro.apellido;
    numeroCamiseta = otro.numeroCamiseta;
    partidosJugados = otro.partidosJugados;
    goles = otro.goles;
    minutosJugados = otro.minutosJugados;
    asistencias = otro.asistencias;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    faltas = otro.faltas;
}

// Lógica simple para actualizar el desempeño deportivo
void Jugador::jugarPartido() { partidosJugados++; }
void Jugador::anotarGol() { goles++; }
void Jugador::setGoles(int n) { goles+=n; }
void Jugador::sumarMinutos(int min) { minutosJugados += min; }
void Jugador::asistir() {asistencias++;}
void Jugador::recibirAmarilla() { tarjetasAmarillas++; }
void Jugador::recibirRoja() { tarjetasRojas++; }
void Jugador::cometerFalta() { faltas++; }

std::string Jugador::getNombreCompleto() const { return nombre + " " + apellido; }
int Jugador::getCamiseta() const {return numeroCamiseta;}
int Jugador::getGoles() const { return goles; }

Jugador::~Jugador() {}
