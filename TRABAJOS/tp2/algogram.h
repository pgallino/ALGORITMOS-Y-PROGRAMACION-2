#ifndef ALGOGRAM_H
#define ALGOGRAM_H

#include <stdlib.h>
#include <string.h>
#include "abb.h"
#include "heap.h"
#include "hash.h"

typedef struct algogram algogram_t;

/*  Crea el algogram, recibe un hash de usuarios donde la clave es el "nick" y el dato el ID del usuario */
algogram_t* algogram_crear(hash_t* usuarios);

/*  Inicia sesión con el usuario ingresado, en caso de no encontrarse el usuario devuelve error.
    Pre: el algoram fue creado */
void algogram_login(algogram_t* algogram, char* usuario);

/*  Cierra la sesión actual.
    Pre: hay una sesión activa. */
void algogram_logout(algogram_t* algogram);

/*  Publica un posteo a los feeds de los demás usuarios.
    Pre: hay una sesión activa. */
void algogram_publicar(algogram_t* algogram, char* posteo);

/*  Muestra el siguiente post en el feed
    Pre: hay una sesión activa. */
void algogram_ver_sig_feed(algogram_t* algogram);

/*  Marca con un like el post que se encontró con la ID ingresada, en caso de no encontrarse post
    devuelve error.
    Pre: hay una sesión activa. */
void algogram_likear_post(algogram_t* algogram, char* id_post);

/*  Muestra la lista de usuarios  que dieron like al post que se encontró con la ID ingresada,
    en caso de no encontrarse post devuelve error. */
void algogram_mostrar_likes(algogram_t* algogram, char* id_post);

/*  Destruye el algogram
    Pre: el algoram fue creado */
void algogram_destruir(algogram_t* algogram);

#endif  // ALGOGRAM_H