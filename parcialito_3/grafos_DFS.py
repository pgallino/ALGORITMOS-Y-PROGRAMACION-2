def _dfs(grafo, visitados, vertice):
    visitados.add(vertice)
    for adyacente in grafo.adyacentes(vertice):
        if not adyacente in visitados:
            _dfs(grafo,visitados,adyacente)

def dfs_generalizado(grafo):
    visitados = set()
    for vertice in grafo.obtener_vertices():
        if(not vertice in visitados):
            _dfs(grafo,visitados,vertice)