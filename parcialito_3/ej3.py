"""(★★) Implementar una función que reciba un grafo no dirigido y no pesado implementado con listas de adyacencia 
(diccionario de diccionarios) y devuelva una matriz que sea equivalente 
a la representación de matriz de adyacencia del mismo grafo. 
Indicar y justificar el orden del algoritmo implementado."""

#grafo = {A:{B:2,C:3},B:{A:4},C:{A:3}} ejemplo de dic de dic

def obtener_matriz_equivalente(grafo_dic):

    ancho = len(grafo.obtener_vertices())
    alto = ancho

    matriz = []
    for _ in range(ancho):     #creo matriz vacia con ceros
        matriz.append([0]*ancho)
    
    contador = 1
            
    for vertice in grafo.obtener_vertices(): #lleno la primera columna y la primera fila con los vertices
        matriz[0][contador] = vertice
        matriz[contador][0] = vertice
        for adyacente in grafo.adyacentes(vertice): 
            pos = matriz[0].index(adyacente)
            matriz[contador][pos] = grafo.peso_arista(vertice,adyacente)
        contador += 1
    
    return matriz

#el orden seria o(v+e) ya que por cada vertice miro sus aristas
