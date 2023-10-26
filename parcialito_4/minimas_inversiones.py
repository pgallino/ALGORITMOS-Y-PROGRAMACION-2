"""(★★★★★) Implementar un algoritmo que, dado un grafo dirigido, un vértice s y otro t determine la cantidad mínima de aristas
que deberían cambiar de sentido en el grafo para que exista un camino de s a t."""

#lo convierto en no dirigido, y las que agrego son de peso 1, las demas de peso 0 y hago bfs camino minimo

def cantidad_a_invertir(grafo, s, t):

    grafo_aux = Grafo(True, True, {}, grafo.obtener_vertices())

    for vertice in grafo.obtener_vertices():
        for adyacente in vertice.adyacentes(vertice):
            if not grafo_aux.estan_unidos(vertice,adyacente):
                grafo_aux.agregar_arista(vertice,adyacente,0)
            if not grafo.estan_unidos(adyacente,vertice):
                if not grafo_aux.estan_unidos(adyacente,vertice):
                    grafo_aux.agregar_arista(adyacente, vertice, 1)
    
    padre, dist = camino_minimo_dijkstra(grafo_aux, s, t)

    return dist[t]
    
def camino_minimo_dijkstra(grafo, origen, destino):
    dist = {}
    padre = {}
    for v in grafo.obtener_vertices():
        dist[v] = float("inf")
    dist[origen] = 0
    padre[origen] = None
    q = []
    heapq.heappush(q,(0, origen))
    while q != []:
        _, v = heapq.heappop(q)
        if v == destino:
            return padre, dist
        for w in grafo.adyacentes(v):
            if dist[v] + grafo.peso_arista(v,w) < dist[w]:
                dist[w] = dist[v] + grafo.peso_arista(v, w)
                padre[w] = v
                heapq.heappush(q,(dist[w],w))
    return padre, dist
            