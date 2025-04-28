#include "ListaLigadaDuplamente.h"
#include <stdio.h>

int main() {
    LISTA lista;
    inicializarLista(&lista);

    REGISTRO reg1 = {10};
    REGISTRO reg2 = {20};
    REGISTRO reg3 = {15};

    printf("Inserindo elementos...\n");
    inserirElemListaOrd(&lista, reg1);
    printf("Inserindo elementos...\n");
    inserirElemListaOrd(&lista, reg2);
    inserirElemListaOrd(&lista, reg3);

    printf("Lista após inserções:\n");
    exibirLista(&lista);

    printf("Tamanho da lista: %d\n", tamanho(&lista));
    printf("Tamanho em bytes: %d\n", tamanhoEmBytes(&lista));


    excluirElemLista(&lista, 15);
    printf("Removendo elemento com chave 15...\n");
    excluirElemLista(&lista, 15);
    printf("Removendo elemento com chave 15...\n");
    excluirElemLista(&lista, 15);

    printf("Lista após remoção:\n");
    exibirLista(&lista);

    reinicializarLista(&lista);
    printf("Lista após reinicialização:\n");
    exibirLista(&lista);

    reg1.chave = 40;
    reg2.chave = 20;
    reg3.chave = 50;

    printf("Inserindo elementos...\n");
    inserirElemListaOrd(&lista, reg1);
    printf("Inserindo elementos...\n");
    inserirElemListaOrd(&lista, reg2);
    inserirElemListaOrd(&lista, reg3);
    exibirLista(&lista);

    return 0;
}
