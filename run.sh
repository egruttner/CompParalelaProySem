#COMPILA GENERADOR
g++ -o gen gen.cpp -std=c++14 -O2

#COMPILA CALCULA RUTAS
clang++ -Xpreprocessor -fopenmp -I$(brew --prefix libomp)/include -L$(brew --prefix libomp)/lib -lomp -o main main.cpp -std=c++14

#MOSTRAR PYTHON
#python show_ruta.py
#python show_grafo.py

#1.- DIJKSTRA SECUENCIAL

rm -r ./csv/*
rm -r ./output/*
rm -r ./graficos/*
for filas in 200 400 600 800 1000
do
    ./gen $filas $filas 4
    for tipoExp in 4 3 2 1
    do
        mkdir -p ./output/$tipoExp/$filas$filas
        mkdir -p ./output/$tipoExp/$filas$filas/rutas
        cp ./output/grafo.txt ./output/$tipoExp/$filas$filas
        cp ./output/tamano.txt ./output/$tipoExp/$filas$filas
    done

    ./main
done

