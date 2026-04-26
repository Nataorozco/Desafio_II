#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "vector.h"

using std::string;

class Jugador; // Declaración adelantada

class Equipo {
private:
    int rankingFIFA;
    string pais;
    string directorTecnico;
    string federacion;
    string confederacion;
    bool asignado;

    // Estadísticas históricas
    int golesAFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;

    // Jugadores del equipo
    Vector<Jugador*> jugadores;

    // De enorno
    static const int MAX_JUGADORES = 26;

public:
    // Constructor
    Equipo(int ranking, const string& pais, const string& director,
           const string& federacion, const string& confederacion,
           int gf, int gc, int pg, int pe, int pp, bool asignado);

    // Destructor
    ~Equipo();

    // Getters
    int getRankingFIFA() const { return rankingFIFA; }
    string getPais() const { return pais; }
    string getDirectorTecnico() const { return directorTecnico; }
    string getFederacion() const { return federacion; }
    string getConfederacion() const { return confederacion; }

    int getGolesAFavor() const { return golesAFavor; }
    int getGolesEnContra() const { return golesEnContra; }
    int getPartidosGanados() const { return partidosGanados; }
    int getPartidosEmpatados() const { return partidosEmpatados; }
    int getPartidosPerdidos() const { return partidosPerdidos; }

    const Vector<Jugador*>& getJugadores() const { return jugadores; }

    // Métodos de utilidad
    int getTotalPartidos() const;
    double getPromedioGolesAFavor() const;
    double getPromedioGolesEnContra() const;

    // Métodos para actualizar estadísticas
    void registrarVictoria(int goles);
    void registrarEmpate(int goles);
    void registrarDerrota(int golesRecibidos);

    // Método para generar jugadores artificiales
    void generarJugadores();

    // Método para repatir goles
    void repartirGolesCargaInicial();

    bool isAsignado() const;
    void setAsignado(bool estado);
};

#endif // EQUIPO_H
