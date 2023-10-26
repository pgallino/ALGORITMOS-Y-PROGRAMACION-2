#hacer una funcion que determine si un grafo es una lista enlazada.

##ningun vertice puede tener grado de entrada mayor a 1
##ningun vertice puede tener grado de salida mayor a 1
##solo un vertice tiene grado de entrada = 0
##solo un vertice tiene grado de salida = 0
##fuertemente conexo

def _dfs_obtener_cantidad(grafo, visitados, vertice, cantidad):
    visitados[vertice] = True
    cantidad += 1
    for adyacente in vertice.obtener_adyacentes():
        if(not visitados[adyacente]):
            _dfs(grafo,visitados,adyacente, cantidad)

def calcular_grado_de_entrada_y_salida(grafo):
    gr_entrada={}
    gr_salida={}
    for vertice in grafo.obtener_vertices():
        for adyacente in vertice.obtener_adyacentes(): #la len de vertice.obtener_adyacentes() es el grado de salida tambien
            gr_salida[vertice] = gr_salida.get(vertice, 0) + 1
            gr_entrada[vertice] = gr_entrada.get(vertice, 0) + 1
    return gr_entrada, gr_salida

def es_lista_enlazada(grafo):
    if grafo.cantidad_vertices() == 0: return True
    gr_entrada, gr_salida = calcular_grado_de_entrada_y_salida(grafo):
    hay_primero = False
    hay_ultimo = False
    for vertice in grafo.obtener_vertices():
        if gr_salida[vertice] > 1 or gr_entrada[vertice] > 1: return False
        if hay_primero and gr_entrada[vertice] == 0: return False
        if hay_ultimo and gr_salida[vertice] == 0: return False
        if gr_salida[vertice] == 0: hay_ultimo = True
        if gr_entrada[vertice] == 0:
            hay_primero = True
            primero = vertice
        
    cantidad = 0
    _dfs(grafo,visitados,primero,cantidad)
    if cantidad != len(grafo.obtener_vertices()): return False
    return hay_primero and hay_ultimo
