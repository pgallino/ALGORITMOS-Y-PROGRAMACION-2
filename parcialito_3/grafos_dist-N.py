"""(★★★) Implementar un algoritmo que reciba un grafo dirigido, un vértice V y un número N, 
y devuelva una lista con todos los vértices que se encuentren a exactamente N aristas de distancia del vértice V. 
Indicar el tipo de recorrido utilizado y el orden del algoritmo. Justificar."""

from cola import Cola

def bfs_vertices_N_distancia(grafo, origen, n):
    visitados = set()
    lista = []
    orden = {}
    orden[origen] = 0
    visitados.add(origen)
    q = Cola()
    q.encolar(origen)
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                orden[w] = orden[v] + 1
                if orden[w] == n:
                    lista.append(w)
                visitados.add(w)
                q.encolar(w)
    return lista
