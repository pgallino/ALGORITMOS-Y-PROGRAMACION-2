"""(★★) Implementar una función que reciba un grafo no dirigido, 
y que compruebe la siguiente afirmación: “La cantidad de vértices de grado IMPAR es PAR”. 
Indicar y justificar el orden del algoritmo si el grafo está implementado como matriz de adyacencia."""

def grado_vertices(grafo): # a
    cant_impares = 0
    for vertice in grafo.obtener_vertices():
        grado = len(grafo.adyacentes(vertice))
        if grado%2 != 0: cant_impares+=1
    return cant_impares

def grado_impar_es_par(grafo):
    return grado_vertices(grafo)%2 == 0

#o(V al cubo) porque obtengo todos los adyacentes de cada vertice y encima calculo la len