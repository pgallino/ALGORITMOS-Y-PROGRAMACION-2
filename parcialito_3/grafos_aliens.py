"""ARSAT asegura haber tenido contacto con alienigenas a traves de uno de sus atelites. 
Si bien no tienen pruebas fotograficas (TODO:agregar en ARSAT-SG1) 
interceptaron una lista de palabras escritas en un lenguaje extraño, 
y mediante tecnicas especiales lograron darse cuenta que estan ordenadas segun su criterio de lenguaje.
Se quiere a partir de la lista de palabras, poder inferir algun posible orden del alfabeto de los aliens."""

def grafo_desde_palabras(palabras):
    grafo = Grafo(es_dirigido=True)
    for i in range(len(palabras) -1):
        p1 = palabras[i]
        p2 = palabras[i+1]

        for letra in p1: grafo.agregar_vertice(letra)

        for j in range(len(p1)):
            if p1[j] != p2[j]:
                grafo.agregar_vertice(p2[j])
                grafo.agregar_arista(p1[j],p2[j],1)
                break
    return grafo

def idioma_alien(palabras):
    grafo=grafo_desde_palabras(palabras)
    grados={}
    for v in grafo:
        for w in grafo.adyacentes(v):
            grados[w] = grados.get(w,0) + 1
    
    cola = Cola()
    for v in grafo:
        if v not in grados:
            cola.encolar(v)
    
    resultado = []
    while len(cola) > 0:
        v = cola.desencolar()
        resultado.append(v)
        for ady in grafo.adyacentes(v):
            grados[ady] = grados[ady] - 1
            if grados[ady] == 0:
                cola.encolar(ady)
    return resultado