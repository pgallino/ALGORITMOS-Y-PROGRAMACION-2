from TDA_grafo import Grafo

def _caminos_menores_k(grafo, vertice, destino, k, camino, caminos):

    if camino[-1] == destino and len(camino) < k:  #si el camino va de origen a destino y su largo es menor a k lo agrego.
        caminos.append(camino[:])
    
    for adyacente in grafo.adyacentes(vertice):  
        camino.append(adyacente)       #miro un adyacente y lo agrego
        if len(camino) >= k:           #si llego a k, no tiene sentido seguir esta iteracion entonces lo saco y corto el for
            camino.pop()
            break
        _caminos_menores_k(grafo, adyacente, destino, k, camino, caminos) #si fue bien, llamo de nuevo
    
    camino.pop() 

def caminos_menores_K(grafo, origen, destino, k):
    camino = [origen]
    caminos = []
    _caminos_menores_k(grafo, origen, destino, k, camino, caminos)
    return caminos

#la complejidad es exponencial. La poda tampoco es la mejor, podría cortarse antes si ya veo que los adyacentes no llegan a destino.

grafo = Grafo(False,False,{"A":{"B":1,"C":1},"B":{"A":1},"C":{"A":1,"D":1},"D":{"C":1}}) #una pruebita
print(grafo)
print(caminos_menores_K(grafo, "D", "B", 7))