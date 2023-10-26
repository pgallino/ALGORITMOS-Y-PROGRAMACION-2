"""contar aristas de grafo no dirigido"""

def contar_aristas(grafo):
    e = 0
    for vertice in grafo.obtener_vertices():
        e += len(grafo.adyacentes(vertice))
    e = e//2
    return e