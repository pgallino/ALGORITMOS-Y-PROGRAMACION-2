from heap import heap

def camino_minimo_dijkstra(grafo, origen):
    dist = {}
    padre = {}
    for v in grafo:
        dist[v] = float("inf")
    dist[origen] = 0
    padre[origen] = None
    q = Heap()
    q.encolar((0, origen))
    while not q.esta_vacio():
        _, v = q.desencolar()
        for w in grafo.adyacentes(v):
            if dist[v] + grafo.peso(v,w) < dist[w]:
                dist[w] = dist[v] + grafo.peso(v, w)
                padre[w] = v
                q.encolar((dist[w],w))
                #o: q.actualizar(w, dist[w])
    return padre, dist

def obtener_aristas(grafo):
    aristas = []
    for v in grafo:
        for w in grafo.adyacentes(v):
            aristas.append((v,w,grafo.peso(v,w)))
    return aristas

def camino_minimo_bf(grafo, origen):
    distancia = {}
    padre = {}
    for v in grafo.obtener_vertices():
        distancia[v] = float("inf")
    distancia[origen] = 0
    padre[origen] = None
    aristas = obtener_aristas(grafo)
    for _ in range(len(grafo.obtener_vertices())):
        for v,w,peso in aristas:
            if distancia[v] + peso < distancia[w]:
                padre[w] = v
                distancia[w] = distancia[v] + peso

    for v, w, peso in aristas: #ultima pasada
        if distancia[v] + peso < distancia[w]:
            return None #ciclo negativo retorna None
    return padre, distancia

def camino_minimo_dijkstra(grafo, origen, destino):
    dist = {}
    padre = {}
    for v in grafo:
        dist[v] = float("inf")
    dist[origen] = 0
    padre[origen] = None
    q = Heap()
    q.encolar((0, origen))
    while not q.esta_vacio():
        _, v = q.desencolar()
        if v == destino:
            return padre, dist
        for w in grafo.adyacentes(v):
            if dist[v] + grafo.peso(v,w) < dist[w]:
                dist[w] = dist[v] + grafo.peso(v, w)
                padre[w] = v
                q.encolar((dist[w],w))
                #o: q.actualizar(w, dist[w])
    return padre, dist