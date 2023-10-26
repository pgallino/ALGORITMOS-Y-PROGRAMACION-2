#!/usr/bin/python3
import sys, resource
from TDA_grafo import Grafo
from comandos import *

resource.setrlimit(resource.RLIMIT_STACK, (resource.RLIM_INFINITY, resource.RLIM_INFINITY))
sys.setrecursionlimit(100000)


def print_lista(lista, separador, mostrar_costo):
    if not lista:
        print("No se encontro recorrido")
        return
    newline = '\n'
    for i in range(len(lista)):
        print(f"{lista[i]}", end=f"{newline if i == len(lista)-1 else separador}")
    if mostrar_costo:
        print(f"Costo: {len(lista) - 1}")


def netstats():
    OFFSET_TITULO = 0
    OFFSET_ARGS_ARCHIVO = 1
    OFFSET_COMANDO = 0
    OFFSET_ARGS = 1
    OFFSET_ARG_1 = 0
    OFFSET_ARG_2 = 1
    args = sys.argv
    archivo = args[OFFSET_ARGS_ARCHIVO]
    grafo = Grafo(True)
    pagerank = None
    cfcs = None

    with open(archivo) as f:     
        for linea in f:
            linea = linea.rstrip().split("\t")
            titulo = linea[OFFSET_TITULO]
            if not grafo.vertice_pertenece(titulo):
                grafo.agregar_vertice(titulo)
            for i in range(1, len(linea)):
                link = linea[i]
                if not grafo.vertice_pertenece(link):
                    grafo.agregar_vertice(link)
                if not grafo.estan_unidos(titulo, link):
                    grafo.agregar_arista(titulo, link)

    while True:
        comandos = sys.stdin.readline().rstrip().split(" ", 1)
        comando = comandos[OFFSET_COMANDO]
        if comando == "": break
        if len(comandos) == 1:
            if comando == "listar_operaciones":
                print("camino\nciclo\ndiametro\nrango\nnavegacion\nconectados\nlectura\nclustering\nmas_importantes")

            elif comando == "diametro":
                print_lista(diametro(grafo), " -> ", True)

            elif comando == "clustering":
                print(coef_clustering_promedio(grafo))

            else: print("Comando inexistente / Faltan parámetros")

        elif len(comandos) == 2:
            args = comandos[OFFSET_ARGS].split(",")
            
            if comando != "mas_importantes" and not grafo.vertice_pertenece(args[0]):
                print("Página no disponible")
                continue
            
            elif comando == "camino":
                if len(args) != 2:
                    print("Cantidad de argumentos incorrecta")
                else: print_lista(camino(grafo, args[OFFSET_ARG_1], args[OFFSET_ARG_2]), " -> ", True)

            elif comando == "conectados":
                if not cfcs:
                    cfcs = componentes_fuertemente_conexas(grafo, args[OFFSET_ARG_1])
                print_lista(conectados(cfcs, args[OFFSET_ARG_1]), ", ", False)

            elif comando == "clustering":
                coef = str(coef_clustering(grafo, args[OFFSET_ARG_1]))
                while len(coef) < 5:
                    coef += "0"
                print(coef)

            elif comando == "navegacion":
                print_lista(primer_link(grafo,args[OFFSET_ARG_1]), " -> ", False)  

            elif comando == "ciclo":
                if len(args) != 2:
                    print("Cantidad de argumentos incorrecta")
                    continue
                print_lista(ciclo(grafo, args[OFFSET_ARG_1], int(args[OFFSET_ARG_2])), " -> ", False)

            elif comando == "rango":
                if len(args) != 2:
                    print("Cantidad de argumentos incorrecta")
                    continue
                print(rango(grafo, args[OFFSET_ARG_1], int(args[OFFSET_ARG_2])))

            elif comando == "lectura":
                res = lectura(grafo, args)
                if res:
                    print_lista(res, ", ", False)
                else:
                    print("No existe forma de leer las paginas en orden")

            elif comando == "mas_importantes":
                if not pagerank:
                    pagerank = obtener_pagerank(grafo)
                print_lista(mas_importantes_n(pagerank, int(args[OFFSET_ARG_1])), ", ", False)

            else: print("Comando inexistente / Faltan parámetros")
        else: print("Comando inexistente / Faltan parámetros")

netstats()