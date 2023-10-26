from queue import deque
import heapq

def diametro(grafo):
    max_min_dist = 0
    for v in grafo:
        distancias = caminos_minimos(grafo, v)
        for w in distancias:
            if distancias[w] > max_min_dist:
                max_min_dist = distancias[w]
    return max_min_dist

def caminos_minimos(grafo, origen) #si el grafo es no pesado hago un bfs normal
    q = Cola()
    visitados = set()
    distancia = {}
    distancia[origen] = 0
    visitados.add(origen)
    q.encolar(origen)

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                distancia[w] = distancia[v] + 1
                q.encolar(w)
                visitados.add(w)
    return distancia

def camino_minimo_dijkstra(grafo, origen): #si es pesado tengo que usar dijkstra
    dist = {}
    padre = {}
    for v in grafo:
        dist[v] = float("inf")
    dist[origen] = 0
    padre[origen] = None
    q = []
    q.heappush((0, origen))
    while not q.esta_vacio():
        _, v = q.heappop()
        for w in grafo.adyacentes(v):
            if dist[v] + grafo.peso(v,w) < dist[w]:
                dist[w] = dist[v] + grafo.peso(v, w)
                padre[w] = v
                q.heappush((dist[w],w))
    return padre, dist