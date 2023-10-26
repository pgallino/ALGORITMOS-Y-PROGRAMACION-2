#include "pila.h"

bool balancear(char* cadena) {

    pila_t* pila = pila_crear();
    bool centinela = true;
    for(int i = 0; cadena[i] != '\0'; i++) {

        void* caracter_apilable = &cadena[i]

        if (cadena[i] == '(') pila_apilar(pila, caracter_apilable);
        if (cadena[i] == '[') pila_apilar(pila, caracter_apilable);
        if (cadena[i] == '{') pila_apilar(pila, caracter_apilable);

        if (cadena[i] == ')' && pila_esta_vacia(pila)) centinela = false;
        if (cadena[i] == ']' && pila_esta_vacia(pila)) centinela = false;
        if (cadena[i] == '}' && pila_esta_vacia(pila)) centinela = false;

        if (!centinela) break; //lo pongo simplemente para cortar más rápido el ciclo y que no rompa al desapilar y comparar después

        if (cadena[i] == ')' && *(char*)pila_desapilar(pila) != '(') centinela = false;
        if (cadena[i] == ']' && *(char*)pila_desapilar(pila) != '[') centinela = false;
        if (cadena[i] == '}' && *(char*)pila_desapilar(pila) != '{') centinela = false;

        if (!centinela) break; //lo pongo simplemente para cortar más rápido el ciclo
    }

    pila_destruir(pila);
    return centinela
}

//Tengo entendido que se pueden comparar caracteres sueltos con comilla simple y == pero si no, se podría
//usar strcmp convirtiendo cadena[i] en una string con otra string = "{" o "[" o "("

//basicamente voy apilando los signos que abren y si encuentro alguno que cierra me fijo si coincide con el ultimo que abrió
//que se encuentra en el tope de la pila

//el algoritmo es lineal ya que las primitivas de la pila son O(1) (salvo crear y destruir que son o(n))
//además solo hay un ciclo con operaciones o(1) dentro de él.
//Por lo tanto al recorrer la cadena el algoritmo es o(n)