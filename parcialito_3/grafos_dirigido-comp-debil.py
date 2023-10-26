"""(★★) Implementar un algoritmo que reciba un grafo dirigido y 
nos devuelva la cantidad de componentes débilmente conexas de este. 
Indicar y justificar la complejidad del algoritmo implementado.


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

def dfs_dirigido_a_no_dirigido(grafo, vertice, visitados, grafo_extra):
    visitados.add(vertice)
    grafo_extra.agregar_vertice(vertice)
    for adyacente in grafo.adyacentes(vertice):
        if not vertice in visitados:
            dfs_dirigido_a_no_dirigido(grafo, vertice, visitados, grafo_extra):
        grafo_extra.agregar_arista(adyacente, vertice, peso = 1)

def grafo_dirigido_a_no_dirigido(grafo):
    visitados = set()
    grafo_extra = Grafo(dirigido = False)
    for vertice in grafo.obtener_vertices():
        if not vertice in visitados:
            dfs_dirigido_a_no_dirigido(grafo,vertice,visitados,grafo_extra)
    return grafo_extra

def _dfs(grafo, visitados, vertice):
    visitados.add(vertice)
    for adyacente in grafo.adyacentes(vertice):
        if not adyacente in visitados:
            _dfs(grafo,visitados,adyacente)

def cant_conexas(grafo):
    conexo = 0
    visitados = set()
    for vertice in grafo.obtener_vertices():
        if not vertice in visitados:
            conexo += 1
            _dfs(grafo,visitados,vertice)
    return conexo

def componentes_debilmente_c(grafo):   #primero creo un grafo no dirigido a partir del dirigido y luego cuento las conexas
    grafo_extra = dirigido_a_no_dirigido(grafo)
    return cant_conexas(grafo_extra)