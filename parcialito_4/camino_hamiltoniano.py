def camino_hamiltoniano_dfs(grafo, v, visitados, camino):
    visitados.add(v)
    camino.append(v)
    if len(visitados) == len(grafo.obtener_vertices()):
        return True
    
    for w in grafo.adyacentes(v):
        if w not in visitados:
            if camino_hamiltoniano_dfs(grafo,w,visitados,camino):
                return True
    
    visitados.remove(v)
    camino.pop()
    return False

def camino_hamiltoniano(grafo):
    camino = []
    visitados = set()
    for v in grafo.obtener_vertices():
        if camino_hamiltoniano_dfs(grafo, v, visitados, camino):
            return camino
    return None

#si quiero todos los caminos hamiltonianos

def camino_hamiltoniano_dfs(grafo, v, visitados, camino, caminos_h):
    visitados.add(v)
    camino.append(v)
    if len(visitados) == len(grafo.obtener_vertices()):
        caminos_h.append(camino[:])
        return
    
    for w in grafo.adyacentes(v):
        if w not in visitados:
            camino_hamiltoniano_dfs(grafo, w, visitados, camino, caminos_h):
    
    visitados.remove(v)
    camino.pop()

def camino_hamiltoniano(grafo):
    camino = []
    caminos_h = []
    visitados = set()
    for v in grafo.obtener_vertices():
        camino_hamiltoniano_dfs(grafo, v, visitados, camino, caminos_h)
    return caminos_h