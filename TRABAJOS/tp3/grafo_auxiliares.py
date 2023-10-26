from queue import deque
import heapq

def _componentes_fuertemente_conexas(grafo, v, visitados, apilados, mb, pila, orden, orden_g, cfcs):
	visitados.add(v)
	orden[v] = orden_g 
	mb[v] = orden[v]
	pila.appendleft(v)
	apilados.add(v)
	orden_g += 1
	for w in grafo.adyacentes(v):
		if w not in visitados:
			_componentes_fuertemente_conexas(grafo, w, visitados, apilados, mb, pila, orden, orden_g, cfcs)
		if w in apilados:
			mb[v] = min(mb[v], mb[w])
	if orden[v] == mb[v] and len(pila) > 0:
		nueva_cfc = []
		while True:
			w = pila.popleft()
			apilados.remove(w)
			nueva_cfc.append(w)
			cfcs[w] = nueva_cfc
			if w == v:
				break

def componentes_fuertemente_conexas(grafo, v):
	visitados = set()
	apilados = set()
	orden = dict()
	mb = dict()
	pila = deque()
	cfcs = {}
	orden_g = 0
	_componentes_fuertemente_conexas(grafo, v, visitados, apilados, mb, pila, orden, orden_g, cfcs)
	return cfcs


def bfs(grafo, origen):
	q = deque()
	padre = {}
	distancias = {}
	distancias[origen] = 0
	padre[origen] = None
	dist_max = 0
	q.append(origen)
	ultimo = origen
	while (len(q)):
		v = q.popleft()
		for w in grafo.adyacentes(v):
			if w in padre: continue
			ultimo = w
			q.append(w)
			padre[w] = v
			distancias[w] = distancias[v] + 1
			if distancias[w] >= dist_max:
				dist_max = distancias[w]
	return padre, dist_max, distancias, ultimo


def obtener_pagerank(grafo):
	CANT_ITER = 10
	COEF_D = 0.85
	VALOR_INICIAL = (1 - COEF_D) / len(grafo)
	rank = {}
	for v in grafo.obtener_vertices():
		rank[v] = VALOR_INICIAL
	for _ in range(CANT_ITER):
		rank_nuevo = {}
		for v in grafo.obtener_vertices():
			rank_nuevo[v] = VALOR_INICIAL
		for v in grafo.obtener_vertices():
			if not grafo.adyacentes(v): continue
			a_sumar = COEF_D * rank[v] / len(grafo.adyacentes(v))
			for w in grafo.adyacentes(v):
				rank_nuevo[w] += a_sumar
		rank = rank_nuevo
	heap = []
	for item, rango in rank.items():
		heapq.heappush(heap, (- rango, item))
	return heap


def reconstruir_camino(dic, v, destino):
	camino = [v]
	while v != destino:
		camino.append(dic[v])
		v = dic[v]
	camino.reverse()
	return camino
