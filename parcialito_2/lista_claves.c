/* Para un hash cerrado, 
implementar una primitiva lista_t* hash_claves(const hash_t*) que reciba un hash 
y devuelva una lista con sus claves. */

#include "hash.h"
#include "hash_struct.h"

lista_t* hash_claves(const hash_t* hash) {  //con iterador
    hash_iter_t* iterador = hash_iter_crear(hash);
    lista_t* lista = lista_crear();

    while(!hash_iter_al_final(iterador)){
      lista_insertar_ultimo(lista,hash_iter_ver_actual(iterador));
      hash_iter_avanzar(iterador);
    }
    hash_iter_destruir(iterador);
    return lista;
}

lista_t* hash_claves(const hash_t* hash) { //sin iterador
  lista_t* lista = lista_crear();
  size_t contador = 0;
  size_t i=0;
  
  while (contador != hash->cantidad) {
    campo_t campo = (hash->tabla)[i];
    if (campo.estado == OCUPADO){
      lista_insertar_ultimo(lista, campo.clave);
      contador++;
    }
    i++;
  }
  return lista;
}