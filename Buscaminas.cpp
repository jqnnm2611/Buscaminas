#include <iostream>

// Tamaño fijo del tablero
const int FILAS = 5;
const int COLUMNAS = 6;

// Estas arrays sirven para movernos en las 8 direcciones (arriba, abajo, izquierda, derecha y diagonales)
int dFila[8] = {-1, -1, -1,  0, 0, 1, 1, 1};
int dCol[8]  = {-1,  0,  1, -1, 1, -1, 0, 1};

// Esta función recorre todo un grupo de 1s conectados (una mina) y los marca como visitados
void marcarMina(int* grid, bool* visitado, int fila, int col) {
    // Vamos a simular una pila (stack) para hacer el recorrido SIN usar recursividad
    int stackFilas[FILAS * COLUMNAS];
    int stackCols[FILAS * COLUMNAS];
    int tope = 0; // tope de la pila

    // Marcamos la celda inicial como visitada
    *(visitado + fila * COLUMNAS + col) = true;

    // Metemos la primera celda al stack
    stackFilas[tope] = fila;
    stackCols[tope] = col;
    tope++;

    // Recorremos mientras haya celdas en el stack
    while (tope > 0) {
        tope--; // Sacamos el último elemento
        int f = stackFilas[tope];
        int c = stackCols[tope];

        // Revisamos las 8 direcciones alrededor de la celda actual
        for (int d = 0; d < 8; d++) {
            int nf = f + dFila[d];
            int nc = c + dCol[d];

            // Verificamos que esté dentro del tablero
            if (nf >= 0 && nf < FILAS && nc >= 0 && nc < COLUMNAS) {
                // Obtenemos el valor de la celda vecina
                int* celda = grid + nf * COLUMNAS + nc;
                bool* vis = visitado + nf * COLUMNAS + nc;

                // Si es un 1 y no fue visitado, lo marcamos y lo metemos al stack
                if (*celda == 1 && !(*vis)) {
                    *vis = true;
                    stackFilas[tope] = nf;
                    stackCols[tope] = nc;
                    tope++;
                }
            }
        }
    }
}

// Esta función cuenta cuántas minas hay (cuántos grupos de 1s conectados)
int contarMinas(int* grid) {
    // Creamos una matriz para marcar qué celdas ya revisamos
    bool visitado[FILAS][COLUMNAS] = {false};
    int minas = 0;

    // Recorremos toda la matriz
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            int* celda = grid + i * COLUMNAS + j;          // puntero a la celda actual
            bool* vis = *(visitado + i) + j;               // puntero al valor de "visitado" en esa celda

            // Si encontramos un 1 que no fue visitado, es una nueva mina
            if (*celda == 1 && !(*vis)) {
                minas++; // contamos la mina
                marcarMina(grid, (bool*)visitado, i, j); // marcamos toda la mina conectada
            }
        }
    }

    return minas;
}

int main() {
    // Definimos el tablero (matriz con 1s y 0s)
    int grid[FILAS][COLUMNAS] = {
        {1, 0, 0, 1, 1, 0},
        {1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0}
    };

    // Contamos la cantidad de minas
    int cantidad = contarMinas((int*)grid);

    // Mostramos el resultado
    std::cout << "Cantidad de minas: " << cantidad << std::endl;

    return 0;
}
