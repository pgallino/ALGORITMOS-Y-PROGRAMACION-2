#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include "funcs.h"

void eliminar_newline(char* clave) {
    size_t len = strlen(clave);
    if((len > 0) && (clave[len-1] == '\n')) clave[len-1] = '\0';
}

hash_t* procesar_usuarios(FILE* archivo) {
    hash_t* usuarios = hash_crear(free);
    if (!usuarios) return NULL;
    char* clave = NULL;
    size_t n = 0;
    size_t linea_n = 0; // linea del archivo actual
    while (getline(&clave, &n, archivo) != EOF) {
        eliminar_newline(clave);
        size_t* id = malloc(sizeof(size_t));
        *id = linea_n++;
        hash_guardar(usuarios, clave, id);
    }
    free(clave);
    return usuarios;
}

void esperar_cmd(algogram_t* algogram) {
    char* linea = NULL;
    size_t n = 0;
    ssize_t read;
    while (getline(&linea, &n, stdin) != EOF) {
        eliminar_newline(linea);
        if (!strcmp(linea, "login")) {
            char* usuario = NULL;
            n = 0;
            read = getline(&usuario, &n, stdin);
            if (!read) printf("Falló lectura\n");
            eliminar_newline(usuario);
            algogram_login(algogram, usuario);
            free(usuario);
        }
        else if (!strcmp(linea, "logout")) algogram_logout(algogram);
        else if (!strcmp(linea, "publicar")){
            char* posteo = NULL;
            n = 0;
            read = getline(&posteo, &n, stdin);
            if (!read) printf("Falló lectura\n");
            eliminar_newline(posteo);
            algogram_publicar(algogram, posteo);
            free(posteo);
        }
        else if (!strcmp(linea, "ver_siguiente_feed")) algogram_ver_sig_feed(algogram);
        else if (!strcmp(linea, "likear_post")) {
            char* id_post = NULL;
            n = 0;
            read = getline(&id_post, &n, stdin);
            if (!read) printf("Falló lectura\n");
            eliminar_newline(id_post);
            algogram_likear_post(algogram, id_post);
            free(id_post);
        }
        else if (!strcmp(linea, "mostrar_likes")) {
            char* id_post = NULL;
            n = 0;
            read = getline(&id_post, &n, stdin);
            if (!read) printf("Falló lectura\n");
            eliminar_newline(id_post);
            algogram_mostrar_likes(algogram, id_post);
            free(id_post);
        }
        else printf("Comando inexistente.\n");
    }
    free(linea);
}