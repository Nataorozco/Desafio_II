#include <iostream>
#include <fstream>
#include "torneo.h"
#include <random>

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
                                             partidosPerdidos, false);

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

    // Bombos
    Bombo bombo1, bombo2, bombo3, bombo4;

    // Buscamos al anfitrión (USA) para asegurarlo en la primera posición
    Equipo* anfitrion = nullptr;
    for (int i = 0; i < equipos.getTamano(); ++i) {
        if (equipos[i]->getPais() == "United States") {
            anfitrion = equipos[i];
            break;
        }
    }

    Vector<Equipo*> equiposOrdenados;

    // 1. El anfitrión siempre va primero
    if (anfitrion != nullptr) {
        equiposOrdenados.push_back(anfitrion);
    }

    // 2. Agregar el resto de los equipos
    for (int i = 0; i < equipos.getTamano(); ++i) {
        if (equipos[i] != anfitrion) {
            equiposOrdenados.push_back(equipos[i]);
        }
    }

    // 3. Ordenar por Ranking FIFA (Omitiendo al anfitrión en la posición 0)
    // Se usa un ordenamiento burbuja sencillo para respetar la restricción de "No STL"
    for (int i = 1; i < equiposOrdenados.getTamano() - 1; ++i) {
        for (int j = 1; j < equiposOrdenados.getTamano() - i; ++j) {
            if (equiposOrdenados[j]->getRankingFIFA() > equiposOrdenados[j+1]->getRankingFIFA()) {
                Equipo* temp = equiposOrdenados[j];
                equiposOrdenados[j] = equiposOrdenados[j+1];
                equiposOrdenados[j+1] = temp;
            }
        }
    }

    int gruposPorBombo = 12;

    // 4. Repartir en bombos según el ranking ya ordenado
    for (int i = 0; i < gruposPorBombo; ++i) {
        bombo1.push_back(equiposOrdenados[i]);
        bombo2.push_back(equiposOrdenados[i + 12]);
        bombo3.push_back(equiposOrdenados[i + 24]);
        bombo4.push_back(equiposOrdenados[i + 36]);
    }

    grupos.clear();

    // 5. Crear los 12 grupos (A-L)
    for (int i = 0; i < gruposPorBombo; ++i) {
        std::string letra(1, 'A' + i);
        grupos.push_back(new Grupo(letra));
    }

    // 6. Asignación del Bombo 1 (Cabezas de serie)
    // El anfitrión (USA) típicamente va al Grupo A (índice 0)
    grupos[0]->agregarEquipo(bombo1[0]); // Asignamos USA al Grupo A
    bombo1.removeAt(0);

    std::random_device rd;
    std::mt19937 gen(rd());

    // Asignamos el resto de los cabezas de serie aleatoriamente a los grupos B-L
    for (int i = 1; i < gruposPorBombo; ++i) {
        std::uniform_int_distribution<> distrib(0, bombo1.getTamano() - 1);
        int numeroAleatorio = distrib(gen);
        grupos[i]->agregarEquipo(bombo1[numeroAleatorio]);
        bombo1.removeAt(numeroAleatorio);
    }

    // 7. Preparar Sorteo (Backtracking)
    long long iteraciones = 0;

    // Asumiendo que implementaste un método mezclar() en tu clase Bombo
    bombo2.mezclar(iteraciones);
    bombo3.mezclar(iteraciones);
    bombo4.mezclar(iteraciones);

    Bombo* bombosArray[] = { &bombo1, &bombo2, &bombo3, &bombo4 };

    //Iniciar el retroceso desde el Bombo 2 (índice 1) y Grupo A (índice 0)
    if (!sortearBacktracking(1, 0, bombosArray, grupos, iteraciones)) {
        cerr << "Error: No se encontró una configuración válida para los grupos." << endl;
    } else {
        cout << "\n--- SORTEO FINALIZADO CON EXITO ---" << endl;
        // Imprimir grupos (Asegúrate de tener un método toString() o similar)
        for(int i = 0; i < grupos.getTamano(); ++i) {
            cout << grupos[i]->toString() << endl;
        }
    }

    // Requisito V: Mostrar métricas
    cout << "\nEstadisticas de Eficiencia:" << endl;
    cout << "Iteraciones de Backtracking: " << iteraciones << endl;
    // cout << "Memoria total: " << calcularMemoria() << " bytes" << endl; // Descomentar si lo tienes
}

bool Torneo::sortearBacktracking(int bIdx, int gIdx, Bombo* bombos[], Vector<Grupo*>& grupos, long long& it) {
    it++; // Contar cada paso recursivo

    // Caso base: Si ya pasamos el último bombo (índice 3 es el bombo 4), terminamos con éxito.
    if (bIdx > 3) return true;

    // Calcular siguiente paso
    // Si llegamos al grupo 11 (Grupo L), saltamos al siguiente bombo y volvemos al grupo 0.
    int sigG = (gIdx + 1) % 12;
    int sigB = (sigG == 0) ? bIdx + 1 : bIdx;

    Bombo& bActual = *bombos[bIdx];

    for (int i = 0; i < bActual.getTamano(); ++i) {
        Equipo* e = bActual[i];

        // Solo probamos con equipos que no han sido asignados
        if (!e->isAsignado()) {

            // Intentamos agregar al equipo. Asumiendo que tu método 'agregarEquipo'
            // ya incluye internamente la llamada a tu 'esValido()' y retorna true si fue exitoso.
            if (grupos[gIdx]->agregarEquipo(e)) {
                e->setAsignado(true);

                // Llamada recursiva (avanzamos en profundidad)
                if (sortearBacktracking(sigB, sigG, bombos, grupos, it)) {
                    return true; // Encontramos el camino correcto
                }

                // RETROCESO (Backtracking): Si la rama falló, deshacemos los cambios
                grupos[gIdx]->quitarUltimoEquipo();
                e->setAsignado(false);
            }
        }
    }

    // Si probamos todos los equipos de este bombo y ninguno encaja, retornamos false (callejón sin salida)
    return false;
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
