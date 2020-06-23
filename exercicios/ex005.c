// LISTA ENCADEADA
/*
 * As listas encadiadas são estruturas de dados lineares as quais cada elemento
 * tem o seu valor armazenado e a referência para o próximo elemento. São exce-
 * lêntes estruturas para se juntar e dividir umas com as outras. Suas principa-
 * is características são:
 *
 *   - O tamanho da lista é desconhecido no tempo de compilação.
 *   - São simples de serem implementadas.
 *   - Geralmente ocupam menos espaço na memória do que arrays.
 *
 *  Também são muito utilizadas em linguagens funcionais, pois são boas para serem
 *  manipuladas sem alterar seu estado interno, usá-las em funções recursivas e
 *  através de lazy loading. Execelêntes para a construção de estruturas de
 *  dados concorrentes e que sejam livres de lock.
 *
 * Representação visual:
 *
 *          3 -> 6 -> 2 -> 1 -> 5 -> NULL
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


struct nodo {
    int valor;
    struct nodo *proximo;
};


struct lista {
    struct nodo *primeiro;
    struct nodo *ultimo;
    int tamanho;
};


struct lista *new_lista() {
    struct lista *new = malloc(sizeof(struct lista));
    new->tamanho = 0;
    return new;
}

struct nodo *new_nodo(int valor) {
    struct nodo *new = malloc(sizeof(struct nodo));
    new->valor = valor;
    return new;
}

bool esta_vazia(struct lista *lista) {
    if (lista->primeiro == NULL && lista->ultimo == NULL)
        return true;
    return false;
}

void inserir_comeco(struct lista *lista, int valor) {
    struct nodo *new = new_nodo(valor);
    if (esta_vazia(lista)) {
        lista->ultimo = new;
        lista->primeiro = new;
    } else {
        new->proximo = lista->primeiro;
        lista->primeiro = new;
    }
    lista->tamanho++;
}

void inserir_final(struct lista *lista, int valor) {
    if (esta_vazia(lista))
        return inserir_comeco(lista, valor);
    struct nodo *new = new_nodo(valor);
    lista->ultimo->proximo = new;
    lista->ultimo = new;
    lista->tamanho++;
}

// Iserir o valor na posição especificada
void inserir_posicao(struct lista *lista, int valor, int posicao) {
    if (posicao == 0)
        inserir_comeco(lista, valor);
    else if (posicao == lista->tamanho)
        inserir_final(lista, valor);
    else if (posicao > lista->tamanho)
        printf("ERRO: tentou inserir na posicao %d mas lista tem tamanho: %d\n",
                posicao, lista->tamanho);
    else {
        struct nodo *new = new_nodo(valor);
        struct nodo *anterior = lista->primeiro;
        struct nodo *atual = lista->primeiro->proximo;
        for (int i = 0; i<posicao-1; i++) {
            anterior = anterior->proximo;
            atual = atual->proximo;
        }
        anterior->proximo = new;
        new->proximo = atual;
        lista->tamanho++;
    }

}

void print_lista(struct lista *lista) {
    struct nodo *current = lista->primeiro;

    while (current != NULL) {
        printf(" %d ->", current->valor);
        current = current->proximo;
    }
    printf(" NULL\n");
    printf("Tamanho: %d\n", lista->tamanho);
}


int main(void) {
    struct lista *lista = new_lista();
    inserir_comeco(lista, 1);
    inserir_comeco(lista, 3);
    inserir_comeco(lista, 2);
    inserir_final(lista, 6);
    inserir_posicao(lista, 100, 1);
    print_lista(lista);
}
