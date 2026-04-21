#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector {
private:
    T* data;           // Puntero para memoria dinámica [2]
    int capacidad;     // Espacio total reservado en memoria
    int tamano;        // Cantidad de elementos actuales

    // Método privado para redimensionar con criterio de eficiencia [3]
    void redimensionar(int nuevaCapacidad) {
        T* nuevoData = new T[nuevaCapacidad];
        for (int i = 0; i < tamano; i++) {
            nuevoData[i] = data[i]; // Requiere que T tenga operador = o constructor copia
        }
        delete[] data;
        data = nuevoData;
        capacidad = nuevaCapacidad;
    }

public:
    // 1. Constructor por defecto
    Vector() : data(nullptr), capacidad(0), tamano(0) {}

    // 2. Constructor de copia (OBLIGATORIO por Requisito VI [4])
    Vector(const Vector& otro) {
        tamano = otro.tamano;
        capacidad = otro.capacidad;
        if (capacidad > 0) {
            data = new T[capacidad];
            for (int i = 0; i < tamano; i++) {
                data[i] = otro.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    // 3. Destructor para liberar memoria dinámica [2]
    ~Vector() {
        delete[] data;
    }

    // 4. Sobrecarga de Operador de Asignación (Necesario para POO correcta [4])
    Vector& operator=(const Vector& otro) {
        if (this != &otro) {
            delete[] data;
            tamano = otro.tamano;
            capacidad = otro.capacidad;
            data = new T[capacidad];
            for (int i = 0; i < tamano; i++) {
                data[i] = otro.data[i];
            }
        }
        return *this;
    }

    // 5. Sobrecarga de Operador [] (Facilita el acceso a datos [4])
    T& operator[](int indice) {
        return data[indice];
    }

    // 6. Método push_back con eficiencia en instrucciones [3]
    void push_back(const T& elemento) {
        if (tamano == capacidad) {
            // Criterio de eficiencia: duplicar capacidad para reducir llamadas a 'new'
            int nuevaCap = (capacidad == 0) ? 1 : capacidad * 2;
            redimensionar(nuevaCap);
        }
        data[tamano++] = elemento;
    }

    // 7. Métodos de utilidad
    int getTamano() const { return tamano; }

    // 8. Medición de consumo de memoria (Requisito V [5])
    size_t calcularMemoria() const {
        size_t memoriaBase = sizeof(*this);
        size_t memoriaDinamica = sizeof(T) * capacidad;
        return memoriaBase + memoriaDinamica;
    }
};

#endif
