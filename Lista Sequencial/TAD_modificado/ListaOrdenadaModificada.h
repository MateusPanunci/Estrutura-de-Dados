// listaOrdenadaModificada.h
#ifndef LISTA_ORDENADA_MODIFICADA_H
#define LISTA_ORDENADA_MODIFICADA_H

#include <stdio.h>
#define ERRO -1
#define bool int
#define true 1
#define false 0

typedef int TIPOCHAVE;
typedef struct {
  TIPOCHAVE chave;
  // outros campos...
} REGISTRO;

typedef struct {
  REGISTRO* A;
  int nroElem;
} LISTA;

// Declaração das funções
void inicializarLista(LISTA* );
void liberar_memoria(LISTA*); // Libera a memória de toda a lista
void exibirLista(LISTA*);
int tamanho(LISTA*);
int tamanhoEmBytes(LISTA*);
TIPOCHAVE primeiroElem(LISTA*);
TIPOCHAVE ultimoElem(LISTA* );
TIPOCHAVE enesimoElem(LISTA*, int );
void reinicializarLista(LISTA*);
int buscaSequencial(LISTA*, TIPOCHAVE);
int buscaSentinela(LISTA*, TIPOCHAVE);
int buscaSentinelaOrdenada(LISTA*, TIPOCHAVE);
int buscaBinaria(LISTA*, TIPOCHAVE);
bool excluirElemLista(LISTA*, TIPOCHAVE);
bool excluirElemListaOrd(LISTA*, TIPOCHAVE);
bool inserirElemListaOrd(LISTA*, REGISTRO);
bool inserirElemListaOrdSemDup(LISTA*, REGISTRO);

#endif // LISTA_ORDENADA_MODIFICADA_H
