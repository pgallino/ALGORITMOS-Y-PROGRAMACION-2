#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include "algogram.h"
#include "funcs.h"

typedef struct usuario {
    size_t id;
    char* nick;
    heap_t* feed;
} usuario_t;

typedef struct post {
    char* posteo;
    usuario_t* autor;
    size_t id;
    abb_t* likes;
} post_t;

typedef struct feed_elem {
    post_t* post;
    size_t afinidad;
    size_t post_id;
} feed_elem_t;

struct algogram {
    hash_t* usuarios;
    hash_t* posts;
    usuario_t* usuario_act;
    size_t n_posts;
};

int _cmp(const void *a, const void *b) { //funcion de comparacion
    if (((feed_elem_t*)a)->afinidad < ((feed_elem_t*)b)->afinidad) return 1;
    if (((feed_elem_t*)a)->afinidad > ((feed_elem_t*)b)->afinidad) return -1;
    if (((feed_elem_t*)a)->post_id < ((feed_elem_t*)b)->post_id) return 1;
    return -1;
}

usuario_t* _usuario_crear(const char* nick, size_t id) {
    usuario_t* usuario = malloc(sizeof(usuario_t));
    usuario->id = id;
    usuario->nick = strdup(nick);
    if (!usuario->nick) {
        free(usuario);
        return NULL;
    }
    usuario->feed = heap_crear(_cmp);
    if (!usuario->feed) {
        free(usuario->nick);
        free(usuario);
        return NULL;
    }
    return usuario;
}

void _usuario_destruir(void* usuario) {
    heap_destruir(((usuario_t*) usuario)->feed, free);
    free(((usuario_t*) usuario)->nick);
    free(usuario);
}

post_t* _post_crear(char* posteo, usuario_t* autor, size_t id_post) {
    post_t* post = malloc(sizeof(post_t));
    if (!post) return NULL;
    post->posteo = strdup(posteo);
    post->autor = autor;
    post->id = id_post;
    post->likes = abb_crear(strcmp, NULL);
    if(!post->likes) {
        free(post->posteo);
        free(post);
        return NULL;
    }
    return post;
}

void _post_destruir(void* post) {
    free(((post_t*)post)->posteo);
    abb_destruir(((post_t*)post)->likes);
    free(post);
}

feed_elem_t* _feed_elem_crear(post_t* post, size_t usuario_id, size_t usuario_act_id) {
    feed_elem_t* feed_elem = malloc(sizeof(feed_elem_t));
    if (!feed_elem) return NULL;
    feed_elem->post = post;
    feed_elem->post_id = post->id;
    feed_elem->afinidad = usuario_id > usuario_act_id ? (usuario_id - usuario_act_id) : (usuario_act_id - usuario_id);
    return feed_elem;
}

void _encolar_post_heaps(hash_t* usuarios, usuario_t* usuario_act, post_t* post) {
    hash_iter_t* iter = hash_iter_crear(usuarios);
    while (!hash_iter_al_final(iter)) {
        const char* clave = hash_iter_ver_actual(iter);
        if (!strcmp(clave, usuario_act->nick)){
            hash_iter_avanzar(iter);
            continue;
        }
        usuario_t* usuario = (usuario_t*) hash_obtener(usuarios, clave);
        heap_encolar(usuario->feed, _feed_elem_crear(post, usuario->id, usuario_act->id));
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
}


algogram_t* algogram_crear(hash_t* usuarios) {
    algogram_t* algogram = malloc(sizeof(algogram_t));
    if (!algogram) return NULL;
    algogram->usuarios = hash_crear(_usuario_destruir);
    if (!algogram->usuarios) {
        free(algogram);
        return NULL;
    }
    hash_iter_t* iter = hash_iter_crear(usuarios);
    while (!hash_iter_al_final(iter)) {
        const char* act = hash_iter_ver_actual(iter);
        usuario_t* usuario = _usuario_crear(act, *(size_t*)hash_obtener(usuarios, act));
        hash_guardar(algogram->usuarios, act, usuario);
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    algogram->posts = hash_crear(_post_destruir);
    if (!algogram->posts) {
        hash_destruir(algogram->usuarios);
        free(algogram);
        return NULL;
    }
    algogram->usuario_act = NULL;
    algogram->n_posts = 0;
    return algogram;
}

void algogram_login(algogram_t* algogram, char* clave) {
    if (algogram->usuario_act) {
        printf("Error: Ya habia un usuario loggeado\n");
        return;
    }
    if (hash_pertenece(algogram->usuarios, clave)) {
        usuario_t* usuario = (usuario_t*) hash_obtener(algogram->usuarios, clave);
        algogram->usuario_act = usuario;
        printf("Hola %s\n", usuario->nick); 
    }
    else {
        printf("Error: usuario no existente\n");
    }
}

void algogram_logout(algogram_t* algogram) {
    if (!algogram->usuario_act) {
        fprintf(stdout, "%s", "Error: no habia usuario loggeado\n");
        return;
    }
    algogram->usuario_act = NULL;
    printf("Adios\n");
}

void algogram_publicar(algogram_t* algogram, char* posteo) {
    if (!algogram->usuario_act) {
        fprintf(stdout, "%s", "Error: no habia usuario loggeado\n");
        return;
    }
    post_t* post = _post_crear(posteo, algogram->usuario_act, algogram->n_posts++);
    char str[12];
    snprintf(str, sizeof str, "%zu", post->id);
    hash_guardar(algogram->posts, str, post);
    _encolar_post_heaps(algogram->usuarios, algogram->usuario_act, post);
    fprintf(stdout, "%s", "Post publicado\n");
}

void algogram_ver_sig_feed(algogram_t* algogram) {
    usuario_t* usuario = algogram->usuario_act;
    if(!usuario || heap_esta_vacio(usuario->feed)) {
        printf("Usuario no loggeado o no hay mas posts para ver\n");
        return;
    }
    heap_t* feed = usuario->feed;
    feed_elem_t* feed_elem = (feed_elem_t*) heap_desencolar(feed);
    post_t* post = feed_elem->post;
    free(feed_elem);
    printf("Post ID %ld\n", post->id);
    printf("%s dijo: %s\n", post->autor->nick, post->posteo);
    printf("Likes: %ld\n", abb_cantidad(post->likes));
}

void algogram_likear_post(algogram_t* algogram, char* id_post) {
    post_t* post = hash_obtener(algogram->posts, id_post);
    if (!algogram->usuario_act || !post) {
        printf("Error: Usuario no loggeado o Post inexistente\n");
        return;
    }
    abb_guardar(post->likes, algogram->usuario_act->nick, algogram->usuario_act->nick);
    printf("Post likeado\n");
}

bool _print_like(const char* clave, void* dato, void* extra) {
    printf("	%s\n", clave);
    return true;
}

void algogram_mostrar_likes(algogram_t* algogram, char* id_post) {
    post_t* post = hash_obtener(algogram->posts, id_post);
    if (!post || !abb_cantidad(post->likes)) {
        printf("Error: Post inexistente o sin likes\n");
        return;
    }
    printf("El post tiene %lu likes:\n", abb_cantidad(post->likes));
    abb_in_order(post->likes, _print_like, NULL);
}

void algogram_destruir(algogram_t* algogram) {
    hash_destruir(algogram->posts);
    hash_destruir(algogram->usuarios);
    free(algogram);
}