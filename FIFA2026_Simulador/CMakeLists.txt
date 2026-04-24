cmake_minimum_required(VERSION 3.16)
project(FIFA2026_Simulador LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Le decimos a CMake dónde están los encabezados (.h)
include_directories(include)

# 2. Registramos los archivos indicando en qué carpeta están
add_executable(FIFA2026_Simulador
    src/main.cpp

    src/torneo.cpp
    src/partido.cpp
    src/equipo.cpp
    src/jugador.cpp

    include/vector.h

    include/torneo.h
    include/partido.h
    include/equipo.h
    include/jugador.h
    importAndExport/selecciones_clasificadas_mundial.csv
)

# 3. Configuración obligatoria de Qt
find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(FIFA2026_Simulador PRIVATE Qt6::Core)
