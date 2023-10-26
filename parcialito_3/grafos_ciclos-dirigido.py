"""(★★) Implementar un algoritmo que, dado un grafo dirigido, nos devuelva un ciclo dentro del mismo, 
si es que lo tiene. Indicar el orden del algoritmo."""

def _dfs(grafo, v, visitados, recorrido):
    visitados.add(v)
    recorrido.append(v)
    for w in grafo.adyacentes(v):
        if w in recorrido:
          #hay un ciclo
          break
        if w not in visitados:
            _dfs(grafo, w, visitados)

def obtener_ciclos_dirigidos(grafo):
    visitados = set()
    recorrido = []
    for v in grafo.vertices():
        if recorrido != []:
            break
        if v not in visitados:
            recorrido = []
            _dfs(grafo, v, visitados, recorrido)
    
    return recorrido

