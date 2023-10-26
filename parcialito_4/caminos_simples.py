"""(★★★) Implementar un algoritmo que reciba un grafo, un vértice v y otro w y, utilizando backtracking, 
obtenga todos los caminos simples de v a w en el grafo."""

def camino_hamiltoniano_dfs(grafo, v, destino, visitados, camino, caminos_h):
    visitados.add(v)
    camino.append(v)
    if len(visitados) == len(grafo.obtener_vertices()):
        caminos_h.append(camino[:])
    
    for w in grafo.adyacentes(v):
        if w not in visitados:
            if w == destino and len(grafo.obtener_vertices) - len(visitados) == 1:
                continue
            camino_hamiltoniano_dfs(grafo, w, visitados, camino, caminos_h):
    
    visitados.remove(v)
    camino.pop()

def camino_hamiltoniano(grafo, v, w):
    camino = []
    caminos_h = []
    visitados = set()
    camino_hamiltoniano_dfs(grafo, v, w, visitados, camino, caminos_h)
    return caminos_h


