#include <iostream>
#include <fstream>
#include "torneo.h"
// #include "GestorData.h"

using namespace std;

Torneo::Torneo() : maximoGoleador(nullptr) {
    cout << "Torneo FIFA 2026 inicializado" << endl;
}

Torneo::~Torneo() {
    // Liberar memoria de equipos
    for (int i = 0; i < equipos.getTamano(); i++) {
        delete equipos[i];
    }

    // Liberar memoria de partidos
    for (int i = 0; i < partidos.getTamano(); i++) {
        delete partidos[i];
    }
}

/**
 * @brief Carga los datos de equipos desde un archivo CSV
 *
 * Proceso:
 * 1. Abre el archivo CSV desde la ruta especificada
 * 2. Lee la línea de encabezado (se descarta)
 * 3. Para cada fila del CSV:
 *    - Extrae: Ranking, País, Director, Federación, Confederación, GF, GC, PG, PE, PP
 *    - Crea una instancia de Equipo
 *    - Almacena un puntero en el Vector de equipos
 * 4. Cierra el archivo
 *
 * @param rutaCSV Ruta al archivo CSV con los datos de equipos
 */
void Torneo::cargarDatos(const string& rutaCSV) {
    ifstream archivo(rutaCSV);

    if (!archivo.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo " << rutaCSV << endl;
        return;
    }

    cout << "Cargando datos desde: " << rutaCSV << endl;

    string linea;

    // Saltar la primera línea de descripción
    getline(archivo, linea);

    // Saltar la línea de encabezado
    getline(archivo, linea);

    int equiposCargados = 0;

    // Leer cada línea del CSV
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        // Separar por delimitador ; sin usar stringstream
        Vector<string> datos;
        size_t inicio = 0;
        size_t fin;

        while ((fin = linea.find(';', inicio)) != string::npos) {
            string campo = linea.substr(inicio, fin - inicio);
            datos.push_back(campo);
            inicio = fin + 1;
        }
        // Último campo (después del último ';')
        string ultimoCampo = linea.substr(inicio);
        datos.push_back(ultimoCampo);

        // Verificar que haya suficientes campos
        if (datos.getTamano() < 10) continue;

        try {
            int ranking = stoi(datos[0]);
            string pais = datos[1];
            string director = datos[2];
            string federacion = datos[3];
            string confederacion = datos[4];
            int golesAFavor = stoi(datos[5]);
            int golesEnContra = stoi(datos[6]);
            int partidosGanados = stoi(datos[7]);
            int partidosEmpatados = stoi(datos[8]);
            int partidosPerdidos = stoi(datos[9]);

            // Crear equipo (instancia en heap)
            Equipo* nuevoEquipo = new Equipo(ranking, pais, director, federacion,
                                             confederacion, golesAFavor, golesEnContra,
                                             partidosGanados, partidosEmpatados,
                                             partidosPerdidos);

            // Asignar goles a judaores
            nuevoEquipo->repartirGolesCargaInicial();

            // Almacenar PUNTERO en Vector de punteros (sin copia profunda)
            equipos.push_back(nuevoEquipo);
            equiposCargados++;

            cout << "Equipo cargado: " << pais << " (Ranking: " << ranking << ")" << endl;

        } catch (const exception& e) {
            cerr << "ERROR al procesar línea: " << e.what() << endl;
            continue;
        }
    }

    archivo.close();

    // GestorData::exportarMatrizFicherosDataJugador("importAndExport/export/goles-por-jugador.csv", equipos, 1);

    cout << "CARGA DE DATOS COMPLETADA" << endl;
    cout << "Total de equipos cargados: " << equiposCargados << endl;
}

void Torneo::conformarFaseGrupos() {
    if (equipos.getTamano() == 0) {
        cerr << "Error: No hay equipos cargados para conformar los grupos." << endl;
        return;
    }

    int totalEquipos = equipos.getTamano();
    Vector<Equipo*> equiposOrdenados;
    std::string anfitrion = "United States";

    // 1. Encontrar y agregar al país anfitrión de primero (va al Bombo 1) [1]
    for (int i = 0; i < totalEquipos; ++i) {
        if (equipos[i]->getPais() == anfitrion) {
            equiposOrdenados.push_back(equipos[i]);
            break;
        }
    }

    // 2. Agregar equipos restantes (ya ordenados por ranking FIFA en el vector original)
    for (int i = 0; i < totalEquipos; ++i) {
        // Se omite al anfitrión porque ya se agregó en la primera posición
        if (equipos[i]->getPais() != anfitrion) {
            equiposOrdenados.push_back(equipos[i]);
        }
    }

    // Declaración de los 4 bombos de 12 selecciones cada uno [1]
    Vector<Equipo*> bombo1, bombo2, bombo3, bombo4;

    // 3. Lógica para repartir los equipos en los bombos
    // Esta función auxiliar llena un bombo con 12 equipos desde un índice específico
    auto asignarEquiposABombo = [&](Vector<Equipo*>& bomboDestino, int indiceInicio) {
        for (int i = 0; i < 12; ++i) {
            if ((indiceInicio + i) < equiposOrdenados.getTamano()) {
                bomboDestino.push_back(equiposOrdenados[indiceInicio + i]);
            }
        }
    };

    // 4. Conformación de los bombos según el ranking
    asignarEquiposABombo(bombo1, 0);  // Mejores rankings + Anfitrión
    asignarEquiposABombo(bombo2, 12);
    asignarEquiposABombo(bombo3, 24);
    asignarEquiposABombo(bombo4, 36); // Peores rankings

    // TODO: El siguiente paso sería extraer un equipo de cada bombo al azar
    // para formar los 12 grupos finales, respetando las restricciones de confederación [1, 4].
}

void Torneo::simularFaseGrupos() {
    // TODO: Implementar simulación de fase de grupos
}

void Torneo::simularEliminatorias() {
    // TODO: Implementar simulación de eliminatorias
}

void Torneo::generarEstadisticasFinales() {
    // TODO: Implementar generación de estadísticas
}
