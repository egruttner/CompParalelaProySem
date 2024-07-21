#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>  // Para atoi y std::strtol

using namespace std;

// Función para generar el grafo en forma de cuadrícula con pesos aleatorios y buscar una ruta entre los nodos inicio y fin utilizando Dijkstra
void generarGrafo(int filas, int columnas, int tipo) {
    srand(time(NULL));
    vector<vector<pair<int, int>>> grafo(filas * columnas);

    //TIPOS DE ASIGNACIÓN DE PESOS
    switch (tipo)
    {
    case 1: //Peso aleatorio entre 0 y 10
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                int nodoActual = i * columnas + j;

                // Conexión hacia la derecha en filas impares (0, 2, 4, ...)
                if (i % 2 == 0 && j < columnas - 1) {
                    int peso = rand() % 10 + 1;
                    grafo[nodoActual].push_back({nodoActual + 1, peso});
                }

                // Conexión hacia la izquierda en filas pares (1, 3, 5, ...)
                if (i % 2 == 1 && j > 0) {
                    int peso = rand() % 10 + 1;
                    grafo[nodoActual].push_back({nodoActual - 1, peso});
                }

                // Conexión hacia abajo en columnas impares (0, 2, 4, ...)
                if (j % 2 == 0 && i < filas - 1) {
                    int peso = rand() % 10 + 1;
                    grafo[nodoActual].push_back({nodoActual + columnas, peso});
                }

                // Conexión hacia arriba en columnas pares (1, 3, 5, ...)
                if (j % 2 == 1 && i > 0) {
                    int peso = rand() % 10 + 1;
                    grafo[nodoActual].push_back({nodoActual - columnas, peso});
                }
            }
        }
        break;

    case 2: //Peso aleatorio horizontal 1 y vertical 2
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                int nodoActual = i * columnas + j;

                // Conexión hacia la derecha en filas impares (0, 2, 4, ...)
                if (i % 2 == 0 && j < columnas - 1) {
                    int peso = 1;
                    grafo[nodoActual].push_back({nodoActual + 1, peso});
                }

                // Conexión hacia la izquierda en filas pares (1, 3, 5, ...)
                if (i % 2 == 1 && j > 0) {
                    int peso = 1;
                    grafo[nodoActual].push_back({nodoActual - 1, peso});
                }

                // Conexión hacia abajo en columnas impares (0, 2, 4, ...)
                if (j % 2 == 0 && i < filas - 1) {
                    int peso = 2;
                    grafo[nodoActual].push_back({nodoActual + columnas, peso});
                }

                // Conexión hacia arriba en columnas pares (1, 3, 5, ...)
                if (j % 2 == 1 && i > 0) {
                    int peso = 2;
                    grafo[nodoActual].push_back({nodoActual - columnas, peso});
                }
            }
        }
        break;

    case 3: // Conexiones bidireccionales con pesos aleatorios entre 1 y 10
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                int nodoActual = i * columnas + j;

                if (j < columnas - 1) {
                    int peso = rand() % 10 + 1;
                    grafo[nodoActual].push_back({nodoActual + 1, peso});
                    grafo[nodoActual + 1].push_back({nodoActual, peso}); // Bidireccional
                }

                if (i < filas - 1) {
                    int peso = rand() % 10 + 1;
                    grafo[nodoActual].push_back({nodoActual + columnas, peso});
                    grafo[nodoActual + columnas].push_back({nodoActual, peso}); // Bidireccional
                }
            }
        }
        break;

    case 4: // Conexiones bidireccionales con pesos 1 horizontal 2 vertical
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                int nodoActual = i * columnas + j;

                if (j < columnas - 1) {
                    int peso = 1;
                    grafo[nodoActual].push_back({nodoActual + 1, peso});
                    grafo[nodoActual + 1].push_back({nodoActual, peso}); // Bidireccional
                }

                if (i < filas - 1) {
                    int peso = 2;
                    grafo[nodoActual].push_back({nodoActual + columnas, peso});
                    grafo[nodoActual + columnas].push_back({nodoActual, peso}); // Bidireccional
                }
            }
        }
        break;
    
    default:
        break;
    }



    ofstream archivoTamano("output/tamano.txt");
    if (!archivoTamano.is_open()) {
        cout << "Error al abrir el archivo para escribir el tamaño de la cuadrícula." << endl;
        return;
    }
    archivoTamano << filas << " " << columnas << endl;
    archivoTamano.close();

    ofstream archivo("output/grafo.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para escribir el grafo." << endl;
        return;
    }

    for (int i = 0; i < grafo.size(); ++i) {
        archivo << i << ": ";
        for (auto conexion : grafo[i]) {
            archivo << conexion.first << "," << conexion.second << " ";
        }
        archivo << endl;
    }
    archivo.close();

    cout << "Grafo generado y exportado correctamente en output/grafo.txt" << endl;
}

int main(int argc, char* argv[]) {
    int filas = 10;  // Valor por defecto
    int columnas = 10;  // Valor por defecto
    int tipo = 1; //Tipo de asignación de peso

    filas = strtol(argv[1], nullptr, 10);
    columnas = strtol(argv[2], nullptr, 10);
    tipo = strtol(argv[3], nullptr, 10);

    generarGrafo(filas, columnas, tipo);
    return 0;
}
