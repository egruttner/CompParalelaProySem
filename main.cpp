#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <chrono>
#include <omp.h> // Incluir la librería de OpenMP

using namespace std;
using namespace std::chrono;

const int INF = numeric_limits<int>::max();

bool guardaRutas = true;

vector<vector<pair<int, int>>> grafo;

int filas, columnas, nodoInicio, nodoFin;
string archivoTamano = "output/tamano.txt";
string archivoGrafo = "output/grafo.txt";

struct NodoDistancia {
    int nodo;
    int distancia;
    bool operator>(const NodoDistancia& otro) const {
        return distancia > otro.distancia;
    }
};

int calcularHeuristica(int nodo, int objetivo) {
    int x1 = nodo % columnas;
    int y1 = nodo / columnas;
    int x2 = objetivo % columnas;
    int y2 = objetivo / columnas;
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx * dx + dy * dy; // Distancia Euclidiana al cuadrado


    // int x1 = nodo % columnas;
    // int y1 = nodo / columnas;
    // int x2 = objetivo % columnas;
    // int y2 = objetivo / columnas;
    // return abs(x1 - x2) + abs(y1 - y2); // Distancia Manhattan

}


pair<vector<int>, int> encontrarRutaDijkstraLento(int inicio, int objetivo) {
    int n = grafo.size();
    vector<int> distancia(n, INF);
    vector<int> padre(n, -1);
    vector<bool> visitado(n, false);

    distancia[inicio] = 0;

    for (int i = 0; i < n; ++i) {
        int nodo_actual = -1;
        int dist_actual = INF;

        // Encontrar el nodo no visitado con la menor distancia
        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && distancia[j] < dist_actual) {
                dist_actual = distancia[j];
                nodo_actual = j;
            }
        }

        if (nodo_actual == -1) {
            break; // No hay más nodos alcanzables
        }

        visitado[nodo_actual] = true;

        // Si llegamos al objetivo, reconstruimos la ruta
        if (nodo_actual == objetivo) {
            vector<int> ruta;
            int nodo = objetivo;
            while (nodo != -1) {
                ruta.push_back(nodo);
                nodo = padre[nodo];
            }
            reverse(ruta.begin(), ruta.end());
            return {ruta, dist_actual};
        }

        // Actualizar las distancias de los vecinos
        for (auto vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            int peso = vecino.second;

            if (!visitado[nodo_vecino] && distancia[nodo_vecino] > distancia[nodo_actual] + peso) {
                distancia[nodo_vecino] = distancia[nodo_actual] + peso;
                padre[nodo_vecino] = nodo_actual;
            }
        }
    }

    return {{}, 0}; // Si no se encuentra una ruta
}



pair<vector<int>, int> encontrarRutaDijkstra(int inicio, int objetivo) {
    int n = grafo.size();
    vector<int> distancia(n, INF);
    vector<int> padre(n, -1);
    priority_queue<NodoDistancia, vector<NodoDistancia>, greater<NodoDistancia>> pq;

    distancia[inicio] = 0;
    pq.push({inicio, 0});

    while (!pq.empty()) {
        NodoDistancia actual = pq.top();
        pq.pop();
        int nodo_actual = actual.nodo;
        int dist_actual = actual.distancia;

        if (nodo_actual == objetivo) {
            vector<int> ruta;
            int nodo = objetivo;
            while (nodo != -1) {
                ruta.push_back(nodo);
                nodo = padre[nodo];
            }
            reverse(ruta.begin(), ruta.end());
            return {ruta, dist_actual};
        }

        if (dist_actual > distancia[nodo_actual]) {
            continue;
        }

        for (auto vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            int peso = vecino.second;

            if (distancia[nodo_vecino] > distancia[nodo_actual] + peso) {
                distancia[nodo_vecino] = distancia[nodo_actual] + peso;
                padre[nodo_vecino] = nodo_actual;
                pq.push({nodo_vecino, distancia[nodo_vecino]});
            }
        }
    }

    return {{}, 0};
}



pair<vector<int>, int> encontrarRutaAStar(int inicio, int objetivo) {
    int n = grafo.size();
    vector<int> distancia(n, INF);
    vector<int> heuristica(n, INF);
    vector<int> padre(n, -1);
    priority_queue<NodoDistancia, vector<NodoDistancia>, greater<NodoDistancia>> pq;

    distancia[inicio] = 0;
    heuristica[inicio] = calcularHeuristica(inicio, objetivo);
    pq.push({inicio, heuristica[inicio]});

    while (!pq.empty()) {
        NodoDistancia actual = pq.top();
        pq.pop();
        int nodo_actual = actual.nodo;

        if (nodo_actual == objetivo) {
            vector<int> ruta;
            int nodo = objetivo;
            while (nodo != -1) {
                ruta.push_back(nodo);
                nodo = padre[nodo];
            }
            reverse(ruta.begin(), ruta.end());
            return {ruta, distancia[objetivo]};
        }

        for (auto vecino : grafo[nodo_actual]) {
            int nodo_vecino = vecino.first;
            int peso = vecino.second;
            int nueva_distancia = distancia[nodo_actual] + peso;

            if (nueva_distancia < distancia[nodo_vecino]) {
                distancia[nodo_vecino] = nueva_distancia;
                heuristica[nodo_vecino] = nueva_distancia + calcularHeuristica(nodo_vecino, objetivo);
                padre[nodo_vecino] = nodo_actual;
                pq.push({nodo_vecino, heuristica[nodo_vecino]});
            }
        }
    }

    return {{}, 0};
}

void leerGrafoDesdeArchivo(const string& archivoTamano, const string& archivoGrafo) {
    ifstream archivoTamanoStream(archivoTamano);
    if (!archivoTamanoStream.is_open()) {
        cout << "Error al abrir el archivo para leer el tamaño de la cuadrícula." << endl;
        return;
    }

    archivoTamanoStream >> filas >> columnas;
    archivoTamanoStream.close();

    int n = filas * columnas;
    grafo.resize(n);

    ifstream archivoGrafoStream(archivoGrafo);
    if (!archivoGrafoStream.is_open()) {
        cout << "Error al abrir el archivo para leer el grafo." << endl;
        return;
    }

    string linea;
    while (getline(archivoGrafoStream, linea)) {
        istringstream iss(linea);
        int nodo;
        char separador;
        iss >> nodo >> separador;

        string conexion;
        while (iss >> conexion) {
            int pos = conexion.find(",");
            if (pos != string::npos) {
                int nodo_vecino = stoi(conexion.substr(0, pos));
                int peso = stoi(conexion.substr(pos + 1));
                grafo[nodo].push_back({nodo_vecino, peso});
            }
        }
    }
    archivoGrafoStream.close();
}

int calcularRuta(int nodoInicio, int nodoFin, int modo, int tipo_experimento) {
    pair<vector<int>, int> resultado;
    vector<int> ruta;
    int pesoTotal = 0;
    string nombreRuta = "output/" + to_string(tipo_experimento) + "/" + to_string(filas) + to_string(columnas);

    nombreRuta = nombreRuta + "/rutas/inicio-" + to_string(nodoInicio) + ".txt";

    if (modo == 1) {    // DIJKSTRA
        resultado = encontrarRutaDijkstra(nodoInicio, nodoFin);
    } else if (modo == 2) {    // A*
        resultado = encontrarRutaAStar(nodoInicio, nodoFin);
    }

    ruta = resultado.first;
    pesoTotal = resultado.second;

    if (guardaRutas)
    {
        ofstream archivoRuta(nombreRuta);
        if (!archivoRuta.is_open()) {
            cout << "Error al abrir el archivo para escribir la ruta." << endl;
        }

        for (int nodo : ruta) {
            archivoRuta << nodo << " ";
        }
        archivoRuta.close();
    }


    return pesoTotal;
}

void guardarResultadosCSV(int experimento, int n, double tiempoTotal) {
    string archivoCSV = "csv/experimento_" + to_string(experimento) + ".csv";
    ofstream archivo(archivoCSV, ios::app);

    if (archivo.is_open()) {
        if (archivo.tellp() == 0) {
            archivo << "n,tiempo[ms]" << endl; // Escribir el encabezado solo si el archivo está vacío
        }
        archivo << n * n << "," << tiempoTotal << endl;
        archivo.close();
        cout << "Resultados guardados en " << archivoCSV << endl;
    } else {
        cout << "Error al abrir el archivo CSV para guardar los resultados." << endl;
    }
}

int main() {
    leerGrafoDesdeArchivo(archivoTamano, archivoGrafo);

    int total_nodos = filas * columnas;
    int nodoInicio = 0;
    int nodoFin = total_nodos - 4;
    int cantidadExperimentos = 10;

    vector<int> nodosOrigen;
    nodosOrigen.push_back(0);
    nodosOrigen.push_back(total_nodos * 10/100);
    nodosOrigen.push_back(total_nodos * 20/100);
    nodosOrigen.push_back(total_nodos * 30/100);
    nodosOrigen.push_back(total_nodos * 40/100);
    nodosOrigen.push_back(total_nodos * 50/100);
    nodosOrigen.push_back(total_nodos * 60/100);
    nodosOrigen.push_back(total_nodos * 70/100);
    nodosOrigen.push_back(total_nodos * 80/100);
    nodosOrigen.push_back(total_nodos * 90/100);


    double tiempoTotal;
    double tiempoPromedio;

    vector<int> experimentos = {1,2,3,4}; // 1,2,3,4,5

    int cantMaxThreads = 50;

    for (int experimento : experimentos) {
        tiempoPromedio = 0.0;
        tiempoTotal = 0.0;

        for (int j = 0; j < cantidadExperimentos; j++) {
            auto start = high_resolution_clock::now();

            switch (experimento) {
                case 1: // DIJKSTRA SECUENCIAL
                    for (int i = 0; i < nodosOrigen.size(); i++) {
                        int peso = calcularRuta(nodosOrigen[i], nodoFin, 1, experimento);
                    }
                    break;

                case 2: // DIJKSTRA PARALELO
                    #pragma omp parallel
                    {
                        #pragma omp for
                        {
                            for (int i = 0; i < nodosOrigen.size(); i++) 
                            {
                                int peso = calcularRuta(nodosOrigen[i], nodoFin, 1, experimento);
                            }
                        }
                    }
                    break;

                case 3: // A* SECUENCIAL
                    for (int i = 0; i < nodosOrigen.size(); i++) {
                        int peso = calcularRuta(nodosOrigen[i], nodoFin, 2, experimento);
                    }
                    break;

                case 4: // A* PARALELO
                    #pragma omp parallel
                    #pragma omp for
                    for (int i = 0; i < nodosOrigen.size(); i++) {
                        int peso = calcularRuta(nodosOrigen[i], nodoFin, 2, experimento);
                    }
                    break;

                default:
                    break;
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            tiempoTotal += duration.count();
        }
        tiempoPromedio = tiempoTotal / cantidadExperimentos;

        guardarResultadosCSV(experimento, filas, tiempoPromedio);
    }




    //PARA MEDIR CANTIDAD DE HEBRAS
    
    // for (int hebras = 0; hebras < cantMaxThreads; hebras++) 
    // {
    //     tiempoPromedio = 0.0;
    //     tiempoTotal = 0.0;

    //     auto start = high_resolution_clock::now();

    //     omp_set_num_threads(hebras);
    //     #pragma omp parallel
    //     #pragma omp for
    //         for (int i = 0; i < nodosOrigen.size(); i++) {
    //             int peso = calcularRuta(nodosOrigen[i], nodoFin, 1, 1);
    //         }


    //     auto stop = high_resolution_clock::now();
    //     auto duration = duration_cast<milliseconds>(stop - start);
    //     tiempoTotal += duration.count();
    //     tiempoPromedio = tiempoTotal / cantidadExperimentos;

    //     cout << hebras << endl;

    //     guardarResultadosCSV(1, hebras, tiempoPromedio);

    // }


    // return 0;
}
