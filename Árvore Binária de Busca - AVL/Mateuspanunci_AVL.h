#ifndef MATEUSPANUNCI_AVL_H
#define MATEUSPANUNCI_AVL_H

/******************************************************************************/
/*              Este programa gerencia arvores AVL                            */
/*  Arvores AVL sao arvores balanceadas na altura.                            */
/*  O nome AVL vem de seus criadores Adelson Velsky e Landis, cuja primeira   */
/*    referência encontra-se no documento "Algoritmos para organização da     */
/*    informação" de 1962.                                                    */
/******************************************************************************/

//Nome: Mateus Panunci Gonçalves   Turma: 2° ano de Ciência de Dados e IA   Ano: 2025

#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0
#define naoexiste -1

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
	TIPOCHAVE chave;
	struct aux *esq;
	struct aux *dir;
	int bal; // fator de balanceamento (0, -1 ou +1) => alt. direita - alt. esquerda
} NO, *PONT;


//Funções já prontas
PONT criarNovoNo(TIPOCHAVE ch); 
int max(int a, int b); 
int altura(PONT p); 
void exibirArvoreEmOrdem(PONT raiz); 
void exibirArvorePreOrdem(PONT raiz); 
void exibirArvorePosOrdem(PONT raiz); 
void exibirArvore(PONT raiz);
PONT rotacaoL(PONT p); 
PONT rotacaoR(PONT p); 
void inserirAVL(PONT* pp, TIPOCHAVE ch, bool* alterou);
PONT buscaBinaria(TIPOCHAVE ch, PONT raiz); 
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai); 
PONT maiorAEsquerda(PONT p, PONT *ant); 
bool excluirAVL(PONT* raiz, TIPOCHAVE ch, bool* alterou);
void destruirArvore(PONT * raiz); //Com aux
void inicializar(PONT * raiz);

//Funções novas
void ehAvl(PONT raiz); // Com aux
int contagemNos(PONT raiz);
int niveldoNodo(PONT raiz, int ch);
int encontrarMinimo(PONT raiz);
int encontrarMaximo(PONT raiz);
int contarFolhas(PONT raiz);
int buscarKesimoMenor(PONT raiz, int k);
int somaValores(PONT raiz);
int mesmoNivel(PONT raiz, int x, int y); 
void listarIntervalo(PONT raiz, int a, int b); // Com aux
void exibirporNivel(PONT raiz); // Com aux
void exibirVisual(PONT raiz); //Com aux

/* OBSERVAÇÂO: 
As funções que estiverem com o comentário "Com aux" possuem outras auxiliares, que podem ser encontradas no arquivo de implementação 
*/

#endif
