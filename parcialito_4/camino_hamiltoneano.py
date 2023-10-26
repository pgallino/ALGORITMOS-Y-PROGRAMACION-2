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