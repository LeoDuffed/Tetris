
# 🎮 Tetris en C++

Este proyecto implementa el clásico juego de **Tetris** en C++ utilizando técnicas de programación orientada a objetos. El juego permite mover, rotar y acomodar bloques que caen, y cuenta con un sistema de **puntuación**, **pausa**, **detección de colisiones**, y una función de **"pieza fantasma"** (ghost piece) para facilitar la jugabilidad. Además, guarda las **tres mejores puntuaciones** en un archivo externo.

## 📁 Estructura del Proyecto

- `main.cpp`  
  Punto de entrada del juego. Inicializa la ventana, instancia el juego y ejecuta el ciclo principal.

- `Game.cpp` / `Game.h`  
  Controla la lógica del juego: movimiento de bloques, detección de colisiones, bloqueo de piezas, control de puntuaciones y renderizado.

- `Grid.cpp` / `Grid.h`  
  Representa el tablero donde se juegan las piezas. Controla el estado de las celdas, elimina líneas llenas y dibuja la cuadrícula.

- `Block.cpp` / `Block.h`  
  Clase base para los bloques de Tetris. Define funciones comunes como rotar, mover y obtener posiciones.

- `Blocks.cpp`  
  Contiene la implementación de las siete formas clásicas del Tetris: I, J, L, O, S, T, Z. Cada clase hereda de `Block`.

- `Position.cpp` / `Position.h`  
  Estructura simple para representar coordenadas `(fila, columna)`.

- `Colors.cpp` / `Colors.h`  
  Define los colores de los bloques en el juego.

- `highscores.txt`  
  Archivo de texto donde se guardan las **tres mejores puntuaciones** en formato:  
  `NOMBRE PUNTUACION`

## 🕹️ Características del Juego

- Movimiento de bloques: izquierda, derecha, abajo y rotación.
- Pausar/reanudar con la tecla **Espacio**.
- Piezas fantasma (ghost pieces) para vista previa de caída.
- Detección de líneas completas y aumento de puntuación.
- Guardado automático de mejores puntuaciones.
- Reinicio del juego tras Game Over.

## ⌨️ Controles

| Tecla        | Acción                  |
|--------------|-------------------------|
| ⬅️ / ➡️      | Mover bloque            |
| ⬇️           | Acelerar caída          |
| ⬆️           | Rotar bloque            |
| Espacio      | Pausar / Reanudar      |

## 🏆 Puntuación

| Líneas completadas | Puntos otorgados |
|--------------------|------------------|
| 1 línea            | 100              |
| 2 líneas           | 200              |
| 3 líneas           | 500              |
| 4 líneas           | 700              |

+ 1 punto adicional por cada movimiento hacia abajo.

## 🔄 Sistema de HighScores

- Se almacenan las **3 mejores puntuaciones** en `highscores.txt`.
- Al superar una, el jugador puede escribir su nombre (máx. 6 letras).
- Se actualiza automáticamente al terminar una partida.

## 💻 Compilación y Ejecución

### 🔷 En Windows (g++)

Asumiendo que tienes instalado [MinGW](https://www.mingw-w64.org/):

```bash
g++ -std=c++17 -o tetris.exe main.cpp Game.cpp Grid.cpp Block.cpp Blocks.cpp Colors.cpp Position.cpp -lraylib -lopengl32 -lgdi32 -lwinmm
tetris.exe
```

### 🍎 En macOS (clang++)

Asumiendo que tienes [raylib](https://github.com/raysan5/raylib) instalado con Homebrew:

```bash
clang++ -std=c++17 -o tetris main.cpp Game.cpp Grid.cpp Block.cpp Blocks.cpp Colors.cpp Position.cpp -lraylib -framework OpenGL -framework Cocoa -framework IOKit
./tetris
```

### 🐧 En Linux (g++)

```bash
g++ -std=c++17 -o tetris main.cpp Game.cpp Grid.cpp Block.cpp Blocks.cpp Colors.cpp Position.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./tetris
```

> ❗ **Nota:** Asegúrate de tener instalada la librería `raylib` correctamente para tu sistema operativo.

## 👨‍💻 Autor

Leonardo 