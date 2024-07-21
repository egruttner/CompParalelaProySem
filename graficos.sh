#Comparaciones

python plot_uno.py \
./csv/experimento_1.csv \
Secuencial "Dijkstra Secuencial" "Cantidad de nodos" "Tiempo[ms]"

python plot_uno.py \
./csv/experimento_2.csv \
Paralelo "Dijkstra Paralelo" "Cantidad de nodos" "Tiempo[ms]"


python plot_dos.py \
./csv/experimento_1.csv \
./csv/experimento_2.csv \
Secuencial Paralelo "Dijkstra Secuencial Vs Paralelo" "Cantidad de nodos" "Tiempo[ms]"

python plot_dos.py \
./csv/experimento_3.csv \
./csv/experimento_4.csv \
Secuencial Paralelo "A* Secuencial Vs Paralelo" "Cantidad de nodos" "Tiempo[ms]"

python plot_dos.py \
./csv/experimento_1.csv \
./csv/experimento_3.csv \
Dijkstra AStar "Dijkstra vs A* (secuencial)" "Cantidad de nodos" "Tiempo[ms]"

python plot_dos.py \
./csv/experimento_2.csv \
./csv/experimento_4.csv \
Dijkstra AStar "Dijkstra vs A* (paralalelos)" "Cantidad de nodos" "Tiempo[ms]"

python plot_cuatro.py \
./csv/experimento_1.csv \
./csv/experimento_2.csv \
./csv/experimento_3.csv \
./csv/experimento_4.csv \
DijkstraSec DijkstraPar AStarSec AStarPar "Todas" "Cantidad de nodos" "Tiempo[ms]"



python plot_tres.py \
./csv/experimento_2.csv \
./csv/experimento_3.csv \
./csv/experimento_4.csv \
DijkstraPar AStarSec AStarPar "Sin Dijkstra Secuencial" "Cantidad de nodos" "Tiempo[ms]"


# python plot_uno.py \
# ./csv/experimento_1.csv \
# Paralelo "Dijkstra Paralelo" "Cantidad de hebras" "Tiempo[ms]"

