"""se quiere implementar un algoritmo de recomendaciones para twitter para un usuario en particular
Se considera que un usuario V puede estar interesado en seguir a X si:

V no sigue a X
V sigue a alguien W que sigue a X"""

""" agregar_vertice(self, v)
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


def recomendaciones_twitter(grafo, v): #mi version, para mi es mas facil.
    recomendados = []
    for w in grafo.adyacentes(v):
        for x in grafo.adyacentes(w):
            if not estan_unidos(v,x):
                recomendados.append(x)
    return recomendados

def recomendaciones(grafo, usuario):
    visitados = set()
    orden = {}
    recomendaciones = []
    q = Cola()
    
    visitados.add(usuario)
    orden[usuario] = 0
    q.encolar(usuario)

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes[v]:
            if w not in visitados:
                visitados.add(w)
                orden[w] = orden[v] + 1
                if (order[w] == 2):
                    recomendaciones.append(w)
                else:
                    q.encolar(w)
    return recomendaciones

