"""(★★) Implementar una función que permita determinar si un grafo puede ser no dirigido. 
Determinar el orden del algoritmo implementado."""

def puede_ser_no_dirigido(grafo):
    for vertice in grafo.obtener_vertices():
        for adyacente in grafo.adyacentes(vertice):
            if not estan_unidos(adyacente,vertice):
                return False
            arista_ida = grafo.obtener_arista(vertice,adyacente)
            arista_vuelta = grafo.obtener_arista(adyacente,vertice)
            if arista_ida.peso != arista_vuelta != peso:
                return False
    return True