#include "Mateuspanunci_AVL.h"

int main(){
    PONT raiz;
    bool alterou;
    inicializar(&raiz);
    printf("Inserindo elementos...\n");
    inserirAVL(&raiz, 5, &alterou);
    inserirAVL(&raiz, 30, &alterou);
    inserirAVL(&raiz, 2, &alterou);
    inserirAVL(&raiz, 90, &alterou);
    inserirAVL(&raiz, 20, &alterou);
    inserirAVL(&raiz, 10, &alterou);
    inserirAVL(&raiz, 40, &alterou);
    inserirAVL(&raiz, 50, &alterou);
    inserirAVL(&raiz, 35, &alterou);
    inserirAVL(&raiz, 32, &alterou);
    inserirAVL(&raiz, 23, &alterou);
    inserirAVL(&raiz, 22, &alterou);
    inserirAVL(&raiz, 21, &alterou);
    inserirAVL(&raiz, 41, &alterou);
    inserirAVL(&raiz, 42, &alterou);
    inserirAVL(&raiz, 47, &alterou);
    inserirAVL(&raiz, 48, &alterou);

    printf("\n\nImpressao da Arvore com o balanceamento dos valores\n");
    exibirArvore(raiz);
    
    printf("\n\nExibicao Visual:\n\n");
    exibirVisual(raiz);

    printf("\nNumero de nodos na arvore: %i\n", contagemNos(raiz));
    printf("\nAltura da arvore: %i\n", altura(raiz));

    printf("\nNivel do nodo de valor %i: %i", 20, niveldoNodo(raiz, 20));
    printf("\nNivel do nodo de valor %i: %i", 40, niveldoNodo(raiz, 40));
    printf("\nNivel do nodo de valor %i: %i", 32, niveldoNodo(raiz, 32));
    printf("\nNivel do nodo de valor %i: %i", 50, niveldoNodo(raiz, 50));
    printf("\nNivel do nodo de valor %i: %i\n", 21, niveldoNodo(raiz, 21));
    
    printf("\nValor minimo da arvore: %i", encontrarMinimo(raiz));
    printf("\nValor maximo da arvore: %i\n", encontrarMaximo(raiz));


    printf("\nTerceiro menor valor: %i", buscarKesimoMenor(raiz, 3));
    printf("\nSetimo menor valor: %i\n", buscarKesimoMenor(raiz, 7));
    
    printf("\nSoma de todos os valores: %i\n\n", somaValores(raiz));

    listarIntervalo(raiz, 20, 40);
    puts("");
    listarIntervalo(raiz, 2, 19);
    puts("");
    listarIntervalo(raiz, 91, 100);
    printf("\n\n");
    
    ehAvl(raiz);
    printf("\n\n");
    
    printf("Arvore imprimida por nivel \n");
    exibirporNivel(raiz);

    puts("");
    mesmoNivel(raiz, 5, 40);
    mesmoNivel(raiz, 5, 35);
    
    printf("\n\nQuantidade de folhas: %i", contarFolhas(raiz));
    puts("");

    excluirAVL(&raiz, 10, &alterou);
    printf("\nValor excluido: %i", 10);
    excluirAVL(&raiz, 40, &alterou);
    printf("\nValor excluido: %i", 40);
    excluirAVL(&raiz, 50, &alterou);
    printf("\nValor excluido: %i", 50);
    
    printf("\n\nArvore imprimida por nivel \n");
    exibirporNivel(raiz);
    
    printf("\n\nExibicao Visual:\n\n");
    exibirVisual(raiz);
    
    printf("\n\nNumero de nodos na arvore: %i\n", contagemNos(raiz));
    printf("\nQuantidade de folhas: %i", contarFolhas(raiz));
    
}