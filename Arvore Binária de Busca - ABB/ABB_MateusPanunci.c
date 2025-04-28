#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct no {
    int chave;
    int contador;           // número de cópias (frequência) dessa chave
    struct no* esq;         // ponteiro para subárvore esquerda
    struct no* dir;         // ponteiro para subárvore direita
} NO, *PONT;

// Protótipos das funções
void inicializar(PONT* raiz);
PONT criarNo(int valor);
PONT inserir(PONT raiz, int valor);
PONT removerUmaOcorrencia(PONT raiz, int valor);
PONT removerTodasOcorrencias(PONT raiz, int valor);
PONT buscar(PONT raiz, int valor);
void exibirInOrder(PONT raiz);
int contarNos(PONT raiz);
int contarTotalElementos(PONT raiz);
int kEsimoMenor(PONT raiz, int k);
void imprimirIntervalo(PONT raiz, int min, int max);
PONT lowestCommonAncestor(PONT raiz, int val1, int val2);

//------------------------------------------------------------------------------
// 1) Inicializar: atribui o valor do ponteiro para NULL
void inicializar(PONT* raiz) {
    *raiz = NULL; 
}

//------------------------------------------------------------------------------
// 2) Criar nó: aloca um espaço na meméria de tamanho NO e atribui ao ponteiro novo, depois é feito a inicialização dos atributos do nó
PONT criarNo(int valor) {
    PONT novo = (PONT) malloc(sizeof(NO));
    if(novo) {
        novo->chave = valor;
        novo->contador = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

//------------------------------------------------------------------------------
// 3) Buscar : utiliza a recursão para encontrar o nó com o valor procurado, se não houver nenhum é retornado NULL, 
// se  houver é retornado atráves das chamadas o endereço do nó encontrado.
PONT buscar(PONT raiz, int valor) {
    if (raiz == NULL) return NULL;
    else if (raiz -> chave == valor) return raiz;
    else if (raiz->chave < valor ) return buscar(raiz->dir, valor);
    else return buscar(raiz-> esq, valor);
}

//------------------------------------------------------------------------------
// 4) Inserir: Primeiro o código encontra o local onde se deve colocar o novo nó pelos comparadores "<" e ">",
// se no meio do camimho houver um nó já existente com tal valor a ser adicionado, irá se feito o acréscimo a seu contador,
//senão haverá chamadas recursivas até encontrar um ponteiro raiz apontando para NULL e 
//irá ser criado e atribuido a ele um novo nó
 
PONT inserir(PONT raiz, int valor) {
    if (raiz == NULL) raiz = criarNo(valor);
    else if(raiz -> chave == valor) raiz->contador++;
    else if(raiz -> chave > valor) raiz -> esq = inserir(raiz-> esq, valor);
    else raiz -> dir = inserir(raiz-> dir, valor);
    return raiz;
}

//------------------------------------------------------------------------------
// 5) Remover UMA ocorrência
PONT removerUmaOcorrencia(PONT raiz, int valor) {

    PONT pai; //Pai do nó a ser removido 
    PONT no; //Nó a ser removido
    PONT p; //pai do nó substituto 
    PONT substituto; //Nó substituto 
    PONT atual;
    pai = NULL;
    atual = raiz;
    
    //Busca o nó que será removido
    while(atual){
        if(atual-> chave == valor){
            no = atual;
            break;
        }
        pai = atual;
        if (valor < atual -> chave) atual = atual -> esq;
        else atual = atual -> dir;
    }

    //Se o nó a ser removido não existir, ele apenas retorna a raiz dele
    if(no == NULL) return raiz;

    // Se o valor do contador for maior que 1, ele decrementa 1 unidade
    else if(no -> contador > 1){
        no->contador--;
        return raiz;
    } 

    else{
        //Ajuste dos ponteiros, caso no->esq e no->dir do nó a ser removido não estejam apontando para outros ou se apenas um deles estiver
        if(!no->esq || !no->dir){
            if(!no -> esq) substituto = no -> dir;
            else substituto = no -> esq;
        } 
        //Ajuste dos ponteiros, caso no->esq e no->dir estejam ocupados
        else {

            // Procura o nó mais a direita da sub-árvore da esquerda do nó a ser removido
            p = no;
            substituto = no -> esq;
            while(substituto -> dir){
                p = substituto;
                substituto = substituto -> dir;
            } 

            // Ajusta os ponteiros do nó substituto caso o pai dele não seja ele mesmo
            if (p != no){
               p -> dir = substituto -> esq;
               substituto -> esq = no -> esq;
            }

            substituto -> dir = no -> dir;
        }

        // Se o nó a ser removido for raiz, é liberado a raiz antiga da memória e retornado para a main o nó substituto dela que se tornou a nova raiz
        if (!pai){
            free(no);
            return(substituto);
        }

        // Verifica qual dos ponteiros do pai do nó a ser removido apontará para o substituto, 
        // e depois libera a memória do que tem que ser excluído
        else if (valor < pai -> chave) pai -> esq = substituto;
        else pai -> dir = substituto;
        free(no);
        return raiz;
    }
}

//------------------------------------------------------------------------------
// 6) Remover TODAS ocorrências: A mesma coisa que a função função removeUmaOcorrencia, porém sem o bloco condicional para decrementar 1 unidade
PONT removerTodasOcorrencias(PONT raiz, int valor) {

    PONT pai, no, p, substituto, atual;
    pai = NULL;
    atual = raiz;

    while(atual){
        if(atual-> chave == valor){
            no = atual;
            break;
        }
        pai = atual;
        if (valor < atual -> chave) atual = atual -> esq;
        else atual = atual -> dir;
    }
    
    if(no == NULL) return raiz;
    else{
        if(!no->esq || !no->dir){
            if(!no -> esq) substituto = no -> dir;
            else substituto = no -> esq;
        } 
        else {
            p = no;
            substituto = no -> esq;
            while(substituto -> dir){
                p = substituto;
                substituto = substituto -> dir;
            } 
            if (p != no){
               p -> dir = substituto -> esq;
               substituto -> esq = no -> esq;
            }
            substituto -> dir = no -> dir;
        }
        if (!pai){
            free(no);
            return(substituto);
        }
        if (valor < pai -> chave) pai -> esq = substituto;
        else pai -> dir = substituto;
        free(no);
        return (raiz);
    }
    return raiz; 
}

//------------------------------------------------------------------------------
// 7) Exibir InOrder: utiliza recursão para imprimir os valores da esquerda para a direita da árvore
void exibirInOrder(PONT raiz) {

    //Exibe se raiz existir
    if(raiz != NULL){
        exibirInOrder(raiz ->esq); 
        for(int i = 0; i < raiz->contador; i++) printf("%i ", raiz -> chave); // imprime n vezes o valor da raiz, com n sendo o contador dela.
        exibirInOrder(raiz -> dir);
    }
}

//------------------------------------------------------------------------------
// 8) Contar nós distintos: quando cada nível de recursão chaga a NULL, começasse a retornar o número de nós das folhas até a raiz
int contarNos(PONT raiz) {
    if(raiz == NULL) return 0;
    else return 1 + contarNos(raiz->esq) + contarNos(raiz->dir); 
}

//------------------------------------------------------------------------------
// 9) Contar total de elementos (somando contadores): a única diferença para o de cima é que é trocado o número 1 do retorno pelo número do contador
int contarTotalElementos(PONT raiz) {
    if(raiz == NULL) return 0;
    else return raiz->contador + contarNos(raiz->esq) + contarNos(raiz->dir);
}

//------------------------------------------------------------------------------
// 10) k-ésimo menor: 
/* O código conta quantos elementos tem na raiz esquerda e verifica se o k-ésimo está na sub-árvore da esquerda:
se estiver, ele realiza uma chamada recursiva para o raiz->esq; caso contrário, ele verifica se o k está na sub-árvore da direita:
se estiver, ele  realiza uma chamada recursiva para a raiz->dir, só que decrementando o valor de k pelo de qtd_esq e pelo de raiz->contador, 
pois se não o algoritmo iria sempre para o elemento mais a direita e não iria encontrar nada, além de que o sétimo menor elemento 
de uma árvore pode ser o segundo menor da sua sub-árvore a direita, por exemplo; caso nenhuma das condições seja atendida, 
o k-ésimo terá sido encontrado e retornado pelas chamadas.
*/
int kEsimoMenor(PONT raiz, int k) {
    if (raiz == NULL) return -1;
    int qtd_esq = contarTotalElementos(raiz->esq);
    if (k <= qtd_esq) return kEsimoMenor(raiz->esq, k);
    else if(k > qtd_esq + raiz->contador) return kEsimoMenor(raiz->dir, k - raiz-> contador - qtd_esq);
    else return raiz -> chave;
}

//------------------------------------------------------------------------------
// 11) Imprimir Intervalo [min, max]: 

/* Basicamente o código verifica se cada nó (começando da raiz) está no intervalo. 
Se não estiver, ele verifica se vai para a sub-árvore da direita ou da esquerda na próxima chamada recursiva.
Caso esteja, ele imprime o nó n vezes (sendo n o número do contador) e após isso chama primeiro uma chamada 
para a sub-árvore da esquerda para achar mais nós dentro do intervalo e depois para o da direita.
Se uma chamada acabar encontrando um NULL, ela só não faz nada.
*/

void imprimirIntervalo(PONT raiz, int min, int max) {
    if (raiz != NULL){
        if (raiz-> chave < min) imprimirIntervalo(raiz->dir, min, max);
        else if (raiz-> chave > max) imprimirIntervalo(raiz->esq, min, max);
        else{
            for(int i = 0; i < raiz->contador; i++) printf("%i ", raiz->chave);
            imprimirIntervalo(raiz-> esq, min, max);
            imprimirIntervalo(raiz-> dir, min, max);
        }
    }
}

//------------------------------------------------------------------------------
PONT lowestCommonAncestor(PONT raiz, int val1, int val2) {
    // Primeiro verifica se existem as raizes com o val1 e val2;
    if(!buscar(raiz, val1) || !buscar(raiz, val2)) return NULL;

    PONT Lca = NULL, no = raiz;

    //Procura o ancestral comum, que é identificado quando um val é maior e o outro menor que raiz -> chave (ou quando raiz -> chave é igual a algum deles)
    while(no){ 
        if (val1 < raiz->chave && val2 < raiz -> chave) no->esq;
        else if (val1 > raiz->chave && val2 > raiz -> chave) no -> dir;
        else return no;
    }
}


//------------------------------------------------------------------------------
int main() {
    PONT raiz;
    inicializar(&raiz);

    raiz = inserir(raiz, 10); 
    inserir(raiz, 5);
    inserir(raiz, 15);
    inserir(raiz, 10); // repetido => contador(10)++
    inserir(raiz, 5);  // repetido => contador(5)++
    inserir(raiz, 5);  // repetido => contador(5)++
    inserir(raiz, 18);

    printf("%p\n", raiz);
     


    printf("\n--- APÓS INSERIR (10,5,15,10,5,5,18) ---\n");
    printf("InOrder esperado: 5 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz); 
    printf("\n");

    // -------------------------------------------------------
    // 2) Busca por valores
    PONT node5 = buscar(raiz, 5);
    if(node5) {
        printf("\nBuscar(5): encontrado com contador=%d (esperado=3)\n", node5->contador);
    } else {
        printf("\nBuscar(5): não encontrado (inesperado)\n");
    }

    PONT nodeX = buscar(raiz, 999); // valor não existente
    if(!nodeX) {
        printf("Buscar(999): não encontrado (esperado)\n");
    } else {
        printf("Buscar(999): encontrado??? (inesperado)\n");
    }


    // -------------------------------------------------------
    // 3) Remover UMA ocorrência 

    raiz = removerUmaOcorrencia(raiz, 5); // contador deve passar de 3 para 2

    printf("\n--- APÓS removerUmaOcorrencia(5) ---\n");
    printf("Esperado InOrder: 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    node5 = buscar(raiz, 5);
    if(node5) {
        printf("Agora contador(5)=%d (esperado=2)\n", node5->contador);
    }

    // -------------------------------------------------------
    // 4) Remover TODAS ocorrências
    raiz = removerTodasOcorrencias(raiz, 10); //=> remove nó com chave=10 por completo

    printf("\n--- APÓS removerTodasOcorrencias(10) ---\n");
    printf("Esperado InOrder: 5 5 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    int qtdNos = contarNos(raiz);
    int totalElem = contarTotalElementos(raiz);
    printf("\ncontarNos => %d (esperado=3)\n", qtdNos);
    printf("contarTotalElementos => %d (esperado=4)\n", totalElem);

   
    printf("\n--- Teste k-ésimo menor ---\n");
    printf("k=1 => %d (esperado=5)\n", kEsimoMenor(raiz,1));
    printf("k=2 => %d (esperado=5)\n", kEsimoMenor(raiz,2));
    printf("k=3 => %d (esperado=15)\n", kEsimoMenor(raiz,3));
    printf("k=4 => %d (esperado=18)\n", kEsimoMenor(raiz,4));
    printf("k=5 => %d (esperado=-1)\n", kEsimoMenor(raiz,5));


    printf("\n--- Teste imprimirIntervalo [6..18] ---\n");
    printf("Esperado: 15 18\nObtido:   ");
    imprimirIntervalo(raiz, 6, 18);
    printf("\n");


    inserir(raiz, 12);
    inserir(raiz, 16);
    inserir(raiz, 3);

    printf("\n--- Árvore após inserir(12,16,3) ---\n");
    printf("InOrder esperado: 3 5 5 12 15 16 18\n");
    printf("Obtido:          ");
    exibirInOrder(raiz);
    printf("\n");

    PONT nLCA;

    nLCA = lowestCommonAncestor(raiz, 3, 5);
    if(nLCA) {
        printf("\nLCA(3,5) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 3, 12);
    if(nLCA) {
        printf("LCA(3,12) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 16, 18);
    if(nLCA) {
        printf("LCA(16,18) => chave=%d (esperado=15)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 5, 18);
    if(nLCA) {
        printf("LCA(5,18) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    // Por fim, buscar um LCA com valor inexistente
    nLCA = lowestCommonAncestor(raiz, 100, 3);
    if(!nLCA) {
        printf("LCA(100,3) => NULL (esperado=chave nao existe)\n");
    }

    printf("\n--- FIM DOS TESTES ---\n");

    return 0;
}
