"""Implementar una función que determine el:

a. El grado de todos los vértices de un grafo no dirigido.

b. El grado de salida de todos los vértices de un grafo dirigido.

c. El grado de entrada de todos los vértices de un grafo dirigido.

Nota: Las funciones deberan devolver un diccionario con clave vertice y valor grado."""

def grado_vertices(grafo): # a
    grado = {}
    for vertice in grafo.obtener_vertices():
        grado[vertice] = len(grafo.adyacentes(vertice))
    return grado


def grado_salida(grafo): # b
    grado = {}
    for vertice in grafo.obtener_vertices():
        grado[vertice] = len(grafo.adyacentes(vertice))
    return grado


def grado_entrada(grafo): #c
    grado = {}
    for vertice in grafo.obtener_vertices():
        grado[vertice] = grado.get(vertice,0)
        for adyacente in grafo.adyacentes(vertice):
            grado[adyacente] = grado.get(adyacente, 0) + 1
    return grado