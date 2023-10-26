"""Un autor decidió escribir un libro con varias tramas que se puede leer de forma no lineal. 
Es decir, por ejemplo, después del capítulo 1 puede leer el 2 o el 73; 
pero la historia no tiene sentido si se abordan estos últimos antes que el 1.
Siendo un aficionado de la computación, el autor ahora necesita un orden para publicar su obra, 
y decidió modelar este problema como un grafo dirigido, en dónde los capítulos son los vértices 
y sus dependencias las aristas. Así existen, por ejemplo, las aristas (v1, v2) y (v1, v73).
Escribir un algoritmo que devuelva un orden en el que se puede leer la historia sin obviar ningún capítulo. 
Indicar la complejidad del algoritmo."""


from cola import Cola

def grado_entrada(grafo): #c
    grado = {}
    for vertice in grafo.obtener_vertices():
        grado[vertice] = grado.get(vertice,0)
        for adyacente in grafo.adyacentes(vertice):
            grado[adyacente] = grado.get(adyacente, 0) + 1
    return grado

def obtener_orden(grafo):
    orden = []
    grados = grado_entrada(grafo)
    cola = Cola()
    for vertice in grados:
        if grados[vertice] == 0:
            cola.encolar(vertice)
    
    while not cola.esta_vacia():
        nodo = cola.desencolar()
        orden.append(nodo)
        for adyacente in grafo.adyacentes(nodo):
            grados[adyacente] -= 1
            if grados[adyacente] == 0:
                cola.encolar(adyacente)
    return orden