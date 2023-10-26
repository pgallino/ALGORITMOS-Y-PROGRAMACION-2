from queue import deque
from grafo_auxiliares import *

#----------------------------------------------------------------------------#

def camino(grafo, origen, destino):
	q = deque()
	padre = {}
	padre[origen] = None
	q.append(origen)
	while (len(q)):
		v = q.popleft()
		for w in grafo.adyacentes(v):
			if w not in padre:
				q.append(w)
				padre[w] = v
		if v == destino: break
	if destino not in padre:
		return None
	camino = reconstruir_camino(padre, destino, origen)
	return camino

#----------------------------------------------------------------------------#

def conectados(cfcs, pagina):
	return cfcs[pagina]

#----------------------------------------------------------------------------#

def _ciclo(grafo, origen, vertice, ciclo, n):
	ciclo.append(vertice)
	if len(ciclo) == n and grafo.estan_unidos(ciclo[-1], ciclo[0]):
		ciclo.append(origen)
		return True

	if len(ciclo) < n:
		for adyacente in grafo.adyacentes(vertice):
			if not adyacente in ciclo:
				if _ciclo(grafo, origen, adyacente, ciclo, n):
					return True
	ciclo.pop()
	return False

def ciclo(grafo, origen, n):
	ciclo = []
	if _ciclo(grafo, origen, origen, ciclo, n):
		return ciclo

#----------------------------------------------------------------------------#

def diametro(grafo):
	max_min_dist = 0
	for v in grafo.obtener_vertices():
		padre, dist, _, ultimo = bfs(grafo, v)
		if dist >= max_min_dist:
			max_min_dist = dist
			padre_max = padre
			origen = v
			ultimo_max = ultimo
	return reconstruir_camino(padre_max, ultimo_max, origen)

#----------------------------------------------------------------------------#

def _primer_link(grafo, origen, contador, navegacion):
	if not grafo.adyacentes(origen) or contador == 20:
		navegacion.append(origen)
		return
	navegacion.append(origen)
	_primer_link(grafo,grafo.adyacentes(origen)[0],contador+1, navegacion)

def primer_link(grafo, origen):
	navegacion = []
	_primer_link(grafo, origen, 0, navegacion)
	return navegacion

#----------------------------------------------------------------------------#

def coef_clustering(grafo, origen):
	contador = 0
	adyacentes = grafo.adyacentes(origen)
	if len(adyacentes) < 2:
		return 0.0
	for v in adyacentes:
		if v == origen: #por si un vértice se apunta a sí mismo
			continue
		for w in adyacentes:
			if v == w:
				continue
			if grafo.estan_unidos(v,w):
				contador += 1
	return round(contador/(len(adyacentes)*(len(adyacentes)-1)),3)

def coef_clustering_promedio(grafo):
	total = 0
	for v in grafo.obtener_vertices():
		coef = coef_clustering(grafo, v)
		total += coef
	return round(total/len(grafo.obtener_vertices()), 3)

#----------------------------------------------------------------------------#

def rango(grafo, origen, n):
	res = 0
	_, _, distancias, _ = bfs(grafo, origen)
	for dist in distancias.values():
		if dist == n:
			res += 1
	return res

#----------------------------------------------------------------------------#

def lectura(grafo, pags):
	lectura = []
	g_ent = {}
	for pag in pags:
		g_ent[pag] = 0
		for pag_link in pags:
			if grafo.estan_unidos(pag, pag_link):
				g_ent[pag] += 1
	q = deque()
	for pag in pags:
		if g_ent[pag] == 0: q.append(pag)
	while len(q):
		v = q.popleft()
		lectura.append(v)
		for pag in pags:
			if grafo.estan_unidos(pag, v):
				g_ent[pag] -= 1
				if g_ent[pag] == 0:
					q.append(pag)
	if len(lectura) != len(pags):
		return None
	return lectura

#----------------------------------------------------------------------------#

def mas_importantes_n(pagerank, n):
	res = []
	aux = []
	OFFSET_NOMBRE = 1
	for _ in range(n):
		aux.append(heapq.heappop(pagerank))
		res.append(aux[len(aux) - 1][OFFSET_NOMBRE])
	for elem in aux:
		heapq.heappush(pagerank, elem)
	return res

#----------------------------------------------------------------------------#
