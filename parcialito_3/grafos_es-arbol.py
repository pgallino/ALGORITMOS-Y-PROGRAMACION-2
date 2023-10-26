"""(★★) Un árbol es un grafo no dirigido que cumple con las siguientes propiedades:

a. ∥E∥=∥V∥−1
b. Es acíclico
c. Es conexo

Por teorema, si un grafo cumple dos de estas tres condiciones, será árbol (y por consiguiente, cumplirá la tercera). 
Haciendo uso de ésto (y únicamente de ésto), se pide implementar una función que reciba un grafo no dirigido 
y determine si se trata de un árbol, o no. 
Indicar el orden de la función implementada."""

def dfs_es_arbol(grafo, visitados, vertice, aristas):
    visitados.add(vertice)
    for adyacente in grafo.adyacentes(vertice):
        if ciclo: break
        if adyacente in visitados:
            if adyacente != padre[v]:
                ciclo = True
                break
                #por el algoritmo no hace falta sumar arista porque total hay ciclo
        if not adyacente in visitados:
            aristas += 1
            padre[adyacente] = vertice
            dfs_es_arbol(grafo,visitados,adyacente, aristas)

def es_arbol(grafo):
    conexo = 0
    aristas = 0
    visitados = set()
    padre = {}
    for vertice in grafo.obtener_vertices():
        if not vertice in visitados:
            conexo += 1
            if conexo > 1: return False
            dfs_es_arbol(grafo,visitados,vertice, aristas)

    if ciclo: return False
    return aristas == len(grafo.obtener_vertices())-1