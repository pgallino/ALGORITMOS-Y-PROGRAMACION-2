"""(★★) Proponer una función para calcular el grafo traspuesto G^T
de un grafo dirigido G.
El grafo traspuesto G^T posee los mismos vértices que G, pero con todas sus aristas invertidas.
(por cada arista (v, w) en G, existe una arista (w, v) en G^T). 

Indicar la complejidad para un grafo implementado con:

a. lista de adyancencias

b. matriz de adyacencias

Métodos del grafo:
agregar_vertice(self, v)
borrar_vertice(self, v)
agregar_arista(self, v, w, peso = 1)
el resultado será v <--> w
borrar_arista(self, v, w)
estan_unidos(self, v, w)
peso_arista(self, v, w)
obtener_vertices(self)
Devuelve una lista con todos los vértices del grafo
vertice_aleatorio(self)
adyacentes(self, v)
str
"""

def dfs_gtrans(grafo,visitados,resultado,vertice):
    resultado.agregar_vertice(vertice)
    visitados.add(vertice)
    for adyacente in grafo.adyacentes(vertice):
        if not adyacente in visitados:
            dfs_gtrans(grafo,visitados,resultado,vertice)
        resultado.agregar_arista(adyacente,vertice)

def calcular_grafo_transpuesto(grafo):
    visitados = set()
    resultado = Grafo(es_dirigido=True)
    for vertice in grafo.obtener_vertices():
        if not vertice in visitados:
            dfs_gtrans(grafo,visitados,resultado,vertice)
    return resultado