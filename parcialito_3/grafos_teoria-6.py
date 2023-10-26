"""(★★★) La teoría de los 6 grados de separación dice que cualquiera en la Tierra 
puede estar conectado a cualquier otra persona del planeta a través 
de una cadena de conocidos que no tiene más de cinco intermediarios 
(conectando a ambas personas con solo seis enlaces).
Suponiendo que se tiene un grafo G en el que cada vértice es una persona 
y cada arista conecta gente que se conoce (el grafo es no dirigido):

a. Implementar un algoritmo para comprobar si se cumple tal teoría 
para todo el conjunto de personas representadas en el grafo G. Indicar el orden del algoritmo.

b. Suponiendo que en el grafo G no habrán altas ni bajas de vértices, 
pero podrían haberla de aristas (la gente se va conociendo), 
explicar las ventajas y desventajas que tendría implementar al grafo G con una matriz de adyacencia."""

from cola import Cola  #le hago un bfs a cada vertice para medir las distancias y si alguno se pasa es falsa la teoria

def bfs(grafo, origen):
    visitados = set()
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
                visitados.add(w)
                q.encolar(w)
    return orden

def comprobar_teoria(grafo):
    for vertice in grafo.obtener_vertices():
        orden = bfs(grafo, vertice)
        if orden > 6: return False
    return True

#orden O(V*(V+E))

