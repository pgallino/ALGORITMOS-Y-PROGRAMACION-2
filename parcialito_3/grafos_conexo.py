"""Implementar un algoritmo que determine si un grafo no dirigido es conexo o no. 
Indicar la complejidad del algoritmo si el grafo está implementado con una matriz de adyacencia."""

def _dfs(grafo, visitados, vertice):
    visitados.add(vertice)
    for adyacente in grafo.adyacentes(vertice):
        if not adyacente in visitados:
            _dfs(grafo,visitados,adyacente)

def es_conexo(grafo): #lo bueno es que sirve para contar componentes
    conexo = 0
    visitados = set()
    for vertice in grafo.obtener_vertices():
        if not vertice in visitados:
            conexo += 1
            _dfs(grafo,visitados,vertice)
    return conexo <= 1


#otra forma mas copada tal vez:

def es_conexo(grafo):
    visitados = set()
    vertice = grafo.vertice_random()
    _dfs(grafo,visitados,vertice)
    return len(visitados) == len(grafo.obtener_vertices())
