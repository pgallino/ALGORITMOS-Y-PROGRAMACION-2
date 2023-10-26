def centralidad(grafo):
    cent = {}
    for v in grafo: cent[v] = 0
    for v in grafo:
        for w in grafo:
            if v == w: continue
            distancia, padre = camino_minimo(grafo,v,w)
            if padre[w] is None: continue
            actual = padre[w]
            while actual != v:
                cent[actual] += 1
                actual = padre[actual]
    return cent

def mas_centrales(grafo):
    cent = centralidad(grafo)
    return max(cent)
    