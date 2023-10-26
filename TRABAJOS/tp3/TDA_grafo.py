#TDA GRAFO

"""Métodos del grafo:
agregar_vertice(self, v)
borrar_vertice(self, v)
agregar_arista(self, v, w, peso = 1)
el resultado será v <--> w o v --> w
borrar_arista(self, v, w)
estan_unidos(self, v, w)
peso_arista(self, v, w)
obtener_vertices(self)
Devuelve una lista con todos los vértices del grafo
vertice_aleatorio(self)
adyacentes(self, v)
str

#grafo = {A:{B:2,C:3},B:{A:4},C:{A:3}} ejemplo de dic de dic

"""
import random

class Grafo:

    def __init__ (self, dirigido = False, vertices = {}, lista_vertices = []):

        self.dirigido = dirigido
        self.vertices = vertices

        if lista_vertices != []:
            self.agregar_vertices(lista_vertices) #agrega muchos vertices a partir de una lista

    def __str__(self):
        return f"{self.vertices}\n"

    def __len__(self):
        return len(self.vertices)
    
    def agregar_vertice(self, v):

        if v in self.vertices:
            raise Exception ("Ya se habia creado ese vértice")
        self.vertices[v] = {}
    
    def borrar_vertice(self, v):

        if not v in self.vertices:
            raise Exception ("Vértice inexistente")

        for vertice in self.vertices:
            if v in self.vertices[vertice]:
                del self.vertices[vertice][v]
    
        del self.vertices[v]
    
    def agregar_arista(self, v, w, peso = 1):

        if self.estan_unidos(v,w):
            raise Exception("Ya se habia creado esa arista")

        self.vertices[v][w] = peso
        
        if not self.dirigido:
            self.vertices[w][v] = peso
    
    def borrar_arista(self, v, w):

        if not self.estan_unidos(v,w):
            raise Exception("Arista inexistente")

        del self.vertices[v][w]

        if not self.dirigido:
            del self.vertices[w][v]

    def estan_unidos(self, v, w):

        if not v in self.vertices or not w in self.vertices:
            raise Exception("Vértice/s inexistente")
        
        if self.dirigido:
            return w in self.vertices[v].keys()
        
        return v in self.vertices[w].keys() and w in self.vertices[v].keys()
    
    def peso_arista(self, v, w):

        if not self.estan_unidos(v,w):
            raise Exception("Arista inexistente")
        
        return self.vertices[v][w]
    
    def obtener_vertices(self):
        
        if self.vertices == {}:
            raise Exception("No hay vértices en el grafo")

        return list(self.vertices.keys())
    
    def vertice_aleatorio(self):

        if self.vertices == {}:
            raise Exception("No hay vértices en el grafo")

        numero = random.randint(0, len(self.vertices.keys())-1)
        return list(self.vertices.keys())[numero]
        
    def adyacentes(self, v):

        if not v in self.vertices:
            raise Exception("Vértice inexistente")
        
        return list(self.vertices[v].keys())
    
    def agregar_vertices(self, lista_vertices):
        for i in range(len(lista_vertices)):
            self.agregar_vertice(lista_vertices[i])

    def vertice_pertenece(self, vertice):
        return vertice in self.vertices
