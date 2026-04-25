# Carga de datos

Cordial saludo en esta seccion de detallan los pasos, que se llevaron/llevarán a cabo para desarrollar satisfactoriamente esta etapa.

## ¿Que se desarrollara en esta seccion?

> Se requiere desarrollar los algoritmos requeridos a fin de leer y actualizar los datos desde/hacia el almacenamiento permanente.

Los datos históricos de cada equipo deben tomarse de la tabla anexa a este enunciado (selecciones_clasificadas_mundial.csv). No se deben usar librerías de terceros para leerlos/actualizarlos. Asuma para todos los equipos que la cantidad inicial de tarjetas amarillas, rojas y de faltas es cero.

Al inicio, las estadísticas históricas por jugador deben fabricarse artificialmente. Para la lista de jugadores de cada equipo, asigne números consecutivos para las camisetas, use las etiquetas “nombre1”, “apellido1”,...,  “nombreN”, “apellidoN”, según el número de la camiseta.  La cantidad de: tarjetas rojas, amarillas,  faltas, minutos jugados, asistencias y partidos jugados;  debe establecerlas  a cero.  La cantidad de goles de cada jugador debe repartirse uniformemente, hasta completar la cantidad de goles que el equipo lleva según la tabla histórica inicial. Luego de cada partido, se deben ir actualizando dichos datos. Los programadores deben diseñar el formato de uno o más archivos para almacenar los datos históricos totales de cada jugador en cada equipo. El formato de los archivos debe presentarse y explicarse adecuadamente dentro del informe de documentación a entregar. Justifique las decisiones tomadas en este particular.

## Analisis preliminar

> [!IMPORTANT]
> Se requiere desarrollar los algoritmos requeridos a fin de leer y actualizar los datos desde/hacia el almacenamiento permanente.

Esta frase indica que todo debe registrarse ficheros, en es sistema, para esto es necesario responder algunas preguntas guía para que el desarrollo se simente sobre una base solida.

- ### ¿Cuantos ficheros se leen al principio del Torneo?

    Los datos históricos de cada equipo deben tomarse de **la tabla** anexa a este enunciado (selecciones_clasificadas_mundial.csv).

    **UN ARCHIVO**

- ### ¿Que contienen?

    Se nos proporciono una tabla; el contenido es tal como se describe acontinuacion (fidelidad de columnas por fila).  

    | Ranking FIFA | País | Director técnico | Federación de fútbol | Confederación | Goles a favor | Goles en contra | Partidos ganados | Partidos empatados | Partidos perdidos |
    |--------------|------|------------------|----------------------|---------------|---------------|----------------|------------------|--------------------|--------------------|
    | 1 | France | Didier Deschamps | French Football Federation | UEFA | 20 | 5 | 7 | 1 | 0 |
    | 2 | Spain | Luis de la Fuente | Royal Spanish Football Federation | UEFA | 20 | 5 | 7 | 1 | 0 |
    | 3 | Argentina | Lionel Scaloni | Argentina Football Association | CONMEBOL | 26 | 8 | 8 | 1 | 1 |
    | 4 | England | Thomas Tuchel | The Football Association | UEFA | 20 | 5 | 7 | 1 | 0 |
    | 5 | Portugal | Roberto Martinez | Portuguese Football Federation | UEFA | 20 | 5 | 7 | 1 | 0 |
    | 6 | Brazil | Dorival Junior | Brazilian Football Confederation | CONMEBOL | 20 | 7 | 6 | 3 | 1 |
    | 7 | Netherlands | Ronald Koeman | Royal Dutch Football Association | UEFA | 20 | 5 | 7 | 1 | 0 |
    | . | ----------- | ------------- | -------------------------------- | ---- | -- | - | - | - | - |
    | . | ----------- | ------------- | -------------------------------- | ---- | -- | - | - | - | - |
    | . | ----------- | ------------- | -------------------------------- | ---- | -- | - | - | - | - |
    | 59 | Cabo Verde | Bubista | Cape Verdean Football Federation | CAF | 10 | 1 | 5 | 1 | 0 |

    ---


    Hay 48 equipos (selecciones nacionales). Cada equipo tiene:

    - Un **Ranking FIFA (número: 1,2,3... Hasta 59).
    - Un **país**
    - Un **director técnico** (no lo usaremos mucho pero ahí está).
    - **Estadisticas hístoricas:** Goles a favor (GF), goles en contra (GC), partidos ganados (PG), empatados (PE), perdidos (PP)

- ### ¿Que no contienen?

    - La cantidad inicial de tarjetas amarillas, rojas y de faltas de totales de cada equipo.
    - La lista de jugadores de cada equipo. _nombres o referencias individuales_
    - Las estadísticas históricas por jugador.

- ### ¿Que se debe hacer para obtener/generar los datos no contenidos?

    <mark>Al inicio</mark>, **las estadísticas históricas por jugador deben fabricarse artificialmente**. 
    
    Para la lista de jugadores de cada equipo, **asigne números consecutivos para las camisetas**, use las etiquetas “nombre1”, “apellido1”,...,  “nombreN”, “apellidoN”, según el número de la camiseta.  La cantidad de: tarjetas rojas, amarillas,  faltas, minutos jugados, asistencias y partidos jugados;  debe establecerlas  a cero.


- ### ¿Que se espera que se haga con los datos de entrada? _"Los que estan el/los en el fichero/s de entrada"_

    La cantidad de goles de cada jugador debe repartirse uniformemente, hasta completar la cantidad de goles que el equipo lleva según la tabla histórica inicial.

---

Hasta este punto de comprede la parte inicial de carga de datos **importacion**, ahora continuamos con la exportacion que tambien debe definirse en esta etapa.

---

> [!IMPORTANT]
> Luego de cada partido, se deben ir actualizando dichos datos. Los programadores deben diseñar el formato de uno o más archivos para almacenar los datos históricos totales de cada jugador en cada equipo.

- ### ¿Que datos se guardan?

  las estadísticas históricas personales de jugador:  
    1. cantidad de partidos jugados
    2. cantidad de goles
    3. minutos totales jugados
    4. cantidad de asistencias
    5. cantidad de tarjetas amarillas
    6. cantidad de tarjetas rojas
    7. cantidad de de faltas acumuladas.


## Ruta solutiva a partir de analsís

Los resultados del torneo se guardaran en multiples archivos con todos los equipos, usando los numeros de camiseta como identificadores referenciales a los jugadores.

El formato de los ficheros igualmente en **csv** debido a la estandarizacion de un formato con separacion, y del cual hay una gran comunidad (foros, tutoriales), que aplanan la curva de aprendizaje para esta actividad. Un formato personalizado requiere una justificacion mas estendida.

El contenido de cada fichero `.csv` debe estructurarse de la siguiente manera:

> [!NOTE]
> La unica forma de distingir si se habla de goles o faltas, es la forma en la que se organiza la informacion. Ya que todos los ficheros tendran el formato de estructura de datos.

### goles-por-judaor.csv

| (NumCamiseta →) (País ↓) | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | ... | 26 |
|-- | - | - | - | - | - | - | - | - | - | -- | -- | -- | - | - |
| France | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Spain | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Argentina| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| England| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Portugal| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Brazil | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Netherlands | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| ... | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Cabo Verde| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |


### Justificacion

La consitencia entre formatos, facilitan la manipulacion del contenido.

## TO-DO

Partiendo de abajo hacia arriba

### Modelado de Clases:

- [x] Crear/Corregir la clase Jugador (incluir: numero de camiseta, nombre/apellido generico y los 7 contadores de estadisticas).
- [x] Crear/Corregir la clase Equipo (lista de jugadores y datos historicos del ranking).

### Logica de Generacion de Datos

- [X] Implementar algoritmo de Generacion Artificial: Nombres genericos y numeros de camiseta consecutivos (1 a 26).
- [x] Crear algoritmo de **Reparto Uniforme de Goles**: Distribuir los goles historicos del equipo entre sus jugadores.

### Persistencia

- [ ] Crear modulo de Gestion de Archivos (Lectura de selecciones_clasificadas_mundial.csv).
- [ ] Implementar logica de escritura de los nuevos archivos .csv (formato matriz Numero de Camiseta vs Pais).

### Validacion

- [ ] Verificar que la suma de goles de los jugadores coincida con el total del equipo tras la carga inicial.
- [ ] Comprobar que los archivos de salida se generan correctamente y son legibles.

## Novedades de avance

> [!IMPORTANT]
> Los primeros 3 elementos de la lista de tareas no se mencionan a acontinuacion debido a la falta del tiempo con el que se cuenta para desarrollar, los detalles sobre lo que se hizo estan en el mensaje del commit.

### Reparto Uniforme de Goles

Fue necesario invetigar en que consiste el **reparto uniforme** y se llego a la **definicion tecnica de distribución uniforme en un conjunto discreto**. Bastante interesante por cierto, una propuesta compleja es _**un reparto equitativo con sorteo de sobrantes**, donde cada jugador recibe una base igual y los goles restantes se rifan de uno en uno para que nadie tenga nunca más de un gol de ventaja sobre los demás._ Sin emargo, se opto por una solucion mas simple que consiste en _**un reparto equitativo determinista** donde todos reciben una base igual y los sobrantes se asignan por orden de lista a los primeros jugadores hasta agotarse._

> [!IMPORTANT]
> Considerando que los jugadores seleccionados para un partido tienen cierto indice de aleatoriedad, el determinismo no favorece ni entorpese los enfrentamientos.