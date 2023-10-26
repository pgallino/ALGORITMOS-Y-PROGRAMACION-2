def esBipartito(grafo):
    if len(grafo.vertices) == 0:
        return True
    color = {}
    VERDE = 1
    ROJO = 2

    for v in grafo.vertices:
        color[v] = None

    nodoRandom = grafo.vertices[0]
    color[nodoRandom] = VERDE
    cola = Cola()
    cola.encolar(nodoRandom)

    while (not cola.esta_vacia()):
        nodo = cola.desencolar()
        for v in grafo.obtener_adyacentes(nodo):
            if (color[v] == color[nodo]):
                return False
            if (color[v] == None):
                if (color[nodo] == VERDE):
                    color[v] = ROJO
                else:
                    color[v] = VERDE
                cola.encolar(v)
    return True

