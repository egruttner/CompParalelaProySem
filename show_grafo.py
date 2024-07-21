import networkx as nx
import matplotlib.pyplot as plt

# Función para cargar el tamaño de la cuadrícula desde el archivo generado por C++
def cargar_tamano():
    with open('output/tamano.txt', 'r') as file:
        tamano = list(map(int, file.readline().strip().split()))
    return tamano[0], tamano[1]

# Función para cargar el grafo desde el archivo generado por C++
def cargar_grafo():
    G = nx.DiGraph()  # Grafo dirigido
    with open('output/grafo.txt', 'r') as file:
        for line in file:
            line = line.strip()
            if line:  # Ignorar líneas en blanco
                partes = line.split(':')
                nodo_str = partes[0].strip()
                if nodo_str.isdigit():
                    nodo_actual = int(nodo_str)
                    conexiones = partes[1].strip().split()
                    for conexion in conexiones:
                        vecino, peso = map(int, conexion.split(','))
                        G.add_edge(nodo_actual, vecino, weight=peso)  # Agregar arco con peso
    return G


# Función para visualizar el grafo como una cuadrícula con la ruta encontrada
def visualizar_grafo():
    filas, columnas = cargar_tamano()
    G = cargar_grafo()

    # Configurar posiciones de los nodos en una cuadrícula
    pos = {i: (i % columnas, -(i // columnas)) for i in G.nodes()}
    
    edge_labels = {(n1, n2): G[n1][n2]['weight'] for (n1, n2) in G.edges()}  # Obtener etiquetas de los pesos


    # Obtener y dibujar la ruta desde el archivo generado por C++
    #path_colors = ['g' if edge in path_edges else 'b' for edge in G.edges()]
    path_colors = ['b' if edge in G.edges() else 'b' for edge in G.edges()]


    nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=100, font_size=4, font_color='black',
            arrows=True, edge_color=path_colors, width=1.0)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color='red')  # Mostrar etiquetas de pesos
    #plt.title(f'Grafo en forma de cuadrícula (Dirigido con Pesos Aleatorios y Ruta de {ruta[0]} a {ruta[-1]})')
    plt.show()




# Visualizar el grafo generado por C++ con la ruta encontrada
if __name__ == '__main__':
    #visualizar_grafo_con_ruta()
    visualizar_grafo()
