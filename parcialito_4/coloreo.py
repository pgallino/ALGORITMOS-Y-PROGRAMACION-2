"""(★★★) Implementar un algoritmo que reciba un grafo y un número nn que, utilizando backtracking,
 indique si es posible pintar cada vértice con nn colores de tal forma que no hayan dos vértices adyacentes con el mismo color."""

def comprobacion_parcial(grafo,v,coloreados):
    for adyacente in grafo.adyacentes(v):
        if coloreados[v] == coloreados.get(adyacente,-1):
            return False
    return True

def _colorear(grafo, v, visitados, colores, coloreados):
    visitados.add(v)
    for i in range(colores):
        coloreados[v] = i
        if comprobacion_parcial(grafo,v,coloreados):
            if len(visitados) == len(grafo.obtener_vertices()):
                return True
            for w in grafo.adyacentes(v):
                if not w in visitados:
                    if _colorear(grafo, w, visitados, colores, coloreados):
                        return True
    
    visitados.remove(v)
    del coloreados[v]
    return False



def colorear(grafo, n):
    if grafo.obtener_vertices() == []:
        return True
    colores = n
    for v in grafo.obtener_vertices():
        visitados = set()
        coloreados = {}
        if _colorear(grafo, v, visitados, colores, coloreados):
            return True
    return False