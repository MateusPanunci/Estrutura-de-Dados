#include "Mateuspanunci_AVL.h"

// =========== Implementação ============ //

/* cria um novo (aloca memoria e preenche valores) no com chave=ch e retorna 
       seu endereco */
PONT criarNovoNo(TIPOCHAVE ch){
	PONT novoNo = (PONT)malloc(sizeof(NO));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->chave = ch;
	novoNo->bal = 0;
	return novoNo;
}


// Retorna o maior valor entre dois inteiros
int max(int a, int b){
	if (a>b) return a;
	return b;
}

// Retorna a altura de uma (sub-)arvore
int altura(PONT p){
	if (!p) return -1;
	else return 1 + max(altura(p->esq),altura(p->dir));
}


/* Exibe arvore Em Ordem         */
void exibirArvoreEmOrdem(PONT raiz){
	if (raiz == NULL) return;
	exibirArvoreEmOrdem(raiz->esq);
	printf("%i ",raiz->chave);
	exibirArvoreEmOrdem(raiz->dir);
}

/* Exibe arvore Pre Ordem         */
void exibirArvorePreOrdem(PONT raiz){
	if (raiz == NULL) return;
	printf("%i ",raiz->chave);
	exibirArvorePreOrdem(raiz->esq);
	exibirArvorePreOrdem(raiz->dir);
}

/* Exibe arvore Pos Ordem         */
void exibirArvorePosOrdem(PONT raiz){
	if (raiz == NULL) return;
	exibirArvorePreOrdem(raiz->esq);
	exibirArvorePreOrdem(raiz->dir);
	printf("%i ",raiz->chave);
}

/* Exibe arvore Em Ordem (com parenteses para os filhos)    */
void exibirArvore(PONT raiz){
	if (raiz == NULL) return;
	printf("%i[%i]",raiz->chave,raiz->bal);
	printf("(");     
	exibirArvore(raiz->esq);
	exibirArvore(raiz->dir);
	printf(")");     
}



/* Rotações à direita (LL e LR) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoL(PONT p){
	printf("\nRotacao a esquerda, problema no no: %i",p->chave);
	PONT u, v;
	u = p->esq;
	if(u->bal == -1) {   // LL
		p->esq = u->dir;
		u->dir = p;
		p->bal = 0;
		u->bal = 0;
		return u;
	} else if (u->bal == 1) {  // LR
		v = u->dir;
		u->dir = v->esq;
		v->esq = u;
		p->esq = v->dir;
		v->dir = p;
		if(v->bal == -1) p->bal = 1;
		else p->bal = 0;
		if(v->bal == 1) u->bal = -1;
		else u->bal = 0;
		v->bal = 0;
		return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
		p->esq = u->dir;
		u->dir = p;
		// p->bal = -1;    desnecessario pois o balanceamento de p nao chegou a ser mudado para -2
		u->bal = 1;
		return u;
	}
}

/* Rotações à esquerda (RR e RL) 
   Retornará o endereço do nó que será a nova raiz da subárvore originalmente 
   iniciada por p */
PONT rotacaoR(PONT p){
	printf("\nRotacao a direita, problema no no: %i",p->chave);
	PONT u, v;
	u = p->dir;
	if(u->bal == 1) {   // RR
		p->dir = u->esq;
		u->esq = p;
		p->bal = 0;
		u->bal = 0;
		return u;
	} else if (u->bal == -1){  // RL
		v = u->esq;
		u->esq = v->dir;
		v->dir = u;
		p->dir = v->esq;
		v->esq = p;
		if(v->bal == 1) p->bal = -1;
		else p->bal = 0;
		if(v->bal == -1) u->bal = 1;
		else u->bal = 0;
		v->bal = 0;
		return v;
	}else{   // caso necessario apenas para a exclusao (u->bal == 0)
		p->dir = u->esq;
		u->esq = p;
		u->bal = -1;
		// p->bal = 1;    desnecessario pois o balanceamento de p nao chegou a ser mudado para 2
		return u;	
	}
}

/* 
   Inserção AVL: 
   - O parâmetro pp é um ponteiro para o nó raiz (ou para o ponteiro do nó atual).
   - O parâmetro ch é a chave a ser inserida.
   - O parâmetro alterou indica se a altura (ou fator de balanceamento) da subárvore foi alterada 
     pela inserção (inicialmente, deve ser false).
*/
void inserirAVL(PONT* pp, TIPOCHAVE ch, bool* alterou){
    // p aponta para o nó atual da subárvore
    PONT p = *pp;
    
    // Se o nó atual é NULL, então chegamos à posição de inserção
    if(!p){
        // Cria um novo nó com a chave ch e o coloca na posição de *pp
        *pp = criarNovoNo(ch);
        // Indica que houve alteração (a altura aumentou)
        *alterou = true;
    } else {
        // Se a chave já existe no nó atual, não há alteração (não permite duplicatas)
        if(ch == p->chave) 
            *alterou = false;
        // Se a chave a inserir é menor ou igual à chave do nó atual, vamos para a subárvore esquerda
        else if(ch <= p->chave) {
            // Chamada recursiva para inserir na subárvore esquerda
            inserirAVL(&(p->esq), ch, alterou);
            // Se a subárvore esquerda foi alterada, precisamos atualizar o fator de balanceamento
            if(*alterou)
                switch (p->bal) {
                    // Caso 1: p->bal era 1 (a subárvore direita era mais alta)
                    // Agora, com a inserção na esquerda, os dois lados ficam equilibrados
                    case 1:
                        p->bal = 0;      // O nó fica balanceado
                        *alterou = false; // Não há mais alteração para propagar
                        break;
                    // Caso 2: p->bal era 0 (a árvore estava balanceada)
                    // A inserção na esquerda faz com que o lado esquerdo fique mais alto
                    case 0:
                        p->bal = -1;     // Aumenta a altura do lado esquerdo
                        break;
                    // Caso 3: p->bal era -1 (a subárvore esquerda já era mais alta)
                    // Com a nova inserção, o fator de balanceamento fica em -2 e é necessário rebalancear
                    case -1:
                        *pp = rotacaoL(p); // Realiza a rotação à esquerda para rebalancear
                        *alterou = false;  // O rebalanceamento corrige a altura, não há mais alteração a propagar
                        break;
                }
        } else { // Caso a chave seja maior que a chave do nó atual: inserir na subárvore direita
            // Chamada recursiva para inserir na subárvore direita
            inserirAVL(&(p->dir), ch, alterou);
            // Se a subárvore direita foi alterada, atualizar o fator de balanceamento
            if(*alterou)
                switch (p->bal) {
                    // Caso 1: p->bal era -1 (a subárvore esquerda era mais alta)
                    // Agora, com a inserção na direita, ambos os lados ficam equilibrados
                    case -1:
                        p->bal = 0;      // O nó fica balanceado
                        *alterou = false; // Não há mais alteração para propagar
                        break;
                    // Caso 2: p->bal era 0 (a árvore estava balanceada)
                    // A inserção na direita faz com que o lado direito fique mais alto
                    case 0:
                        p->bal = 1;      // Aumenta a altura do lado direito
                        break;
                    // Caso 3: p->bal era 1 (a subárvore direita já era mais alta)
                    // Com a nova inserção, o fator de balanceamento fica em +2 e é necessário rebalancear
                    case 1:
                        *pp = rotacaoR(p); // Realiza a rotação à direita para rebalancear
                        *alterou = false;  // O rebalanceamento corrige a altura, não há mais alteração a propagar
                        break;
                }
        }
    }
}



/* retorna o endereco do NO que contem chave=ch ou NULL caso a chave nao seja
       encontrada. Utiliza busca binaria recursiva                                */
PONT buscaBinaria(TIPOCHAVE ch, PONT raiz){
	if (raiz == NULL) return NULL;
	if (raiz->chave == ch) return raiz;
	if (raiz->chave<ch) 
		return buscaBinaria(ch,raiz->dir);
	return buscaBinaria(ch,raiz->esq);
}  


// Busca binária não recursiva devolvendo o nó pai
PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
	PONT atual = raiz;
	*pai = NULL;
	while (atual) {
		if(atual->chave == ch)
			return(atual);
		*pai = atual;
		if(ch < atual->chave) atual = atual->esq;
		else atual = atual->dir;
	}
	return(NULL);
}

/* Auxilir da funcao excluirChave, procura a maior chave menor que a chave que 
   serah excluida            */
PONT maiorAEsquerda(PONT p, PONT *ant){
  *ant = p;
  p = p->esq;
  while (p->dir) {
    *ant = p;
    p = p->dir;
  }
  return(p);
}


/* 
   exclui a chave com valor igual a ch 
   Parâmetros:
     - raiz: ponteiro para o ponteiro do nó raiz (ou nó corrente) da subárvore.
     - ch: a chave a ser excluída.
     - alterou: variável booleana que indica se a altura da subárvore foi alterada após a exclusão.
   Retorna:
     - true se a exclusão foi realizada; false caso contrário.
*/
bool excluirAVL(PONT* raiz, TIPOCHAVE ch, bool* alterou) {
    // Pega o nó atual apontado por *raiz
    PONT atual = *raiz;

    // Se o nó atual for NULL, a chave não foi encontrada; não há alteração
    if (!atual) {
        *alterou = false;
        return false;
    }

    // Se a chave do nó atual é a que desejamos excluir...
    if (atual->chave == ch) {
        PONT substituto, pai_substituto;
        // Se o nó atual tem zero ou um filho
        if (!atual->esq || !atual->dir) {
            // Escolhe o filho existente (ou NULL, se nenhum existir)
            if (atual->esq)
                substituto = atual->esq;
            else
                substituto = atual->dir;
            // Atualiza o ponteiro para o nó atual, removendo-o da árvore
            *raiz = substituto;
            // Libera a memória do nó excluído
            free(atual);
            // Indica que a altura da subárvore foi alterada
            *alterou = true;
            return true;
        }
        else {
            // Se o nó tem dois filhos, encontra o maior nó da subárvore esquerda
            substituto = maiorAEsquerda(atual, &pai_substituto);
            // Copia a chave do substituto para o nó atual
            atual->chave = substituto->chave;
            // Atualiza ch para continuar a exclusão do nó que continha a chave duplicada
            ch = substituto->chave; // continua o código excluindo o substituto
        }
    }
    
    bool res;
    // Se a chave a ser excluída é maior que a chave do nó atual,
    // a exclusão deve ocorrer na subárvore direita
    if (ch > atual->chave) {
        res = excluirAVL(&(atual->dir), ch, alterou);
        // Imprime mensagem para depuração (opcional) informando a exclusão na direita
        //printf("Excluir recursivo a direita: %i(%i)\n", atual->chave, atual->bal); 
        // Se houve alteração na altura da subárvore direita, atualiza o fator de balanceamento do nó atual
        if (*alterou) {
            switch (atual->bal) {
                // Caso 1: se o fator era 1 (direita mais alta), a exclusão equilibrou o nó
                case 1:
                    atual->bal = 0;
                    return true;
                // Caso 2: se o fator era 0, a exclusão faz com que o lado esquerdo fique mais alto (-1)
                case 0:
                    atual->bal = -1;
                    *alterou = false; // a altura do nó atual não diminuiu, não há propagação da alteração
                    return true;
                // Caso 3: se o fator era -1, a exclusão gera desbalanceamento (-2) e é necessária uma rotação à esquerda
                case -1:
                    *raiz = rotacaoL(atual);
                    // Se, após a rotação, o fator de balanceamento não zerar, a alteração não se propaga
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }
    else {
        // Se a chave a ser excluída é menor ou igual à chave do nó atual,
        // a exclusão deve ocorrer na subárvore esquerda
        res = excluirAVL(&(atual->esq), ch, alterou);
        // Imprime mensagem para depuração (opcional) informando a exclusão na esquerda
        //printf("Excluir recursivo a esquerda: %i(%i)\n", atual->chave, atual->bal); 
        // Se houve alteração na altura da subárvore esquerda, atualiza o fator de balanceamento
        if (*alterou) {
            switch (atual->bal) {
                // Caso 1: se o fator era -1 (esquerda mais alta), a exclusão equilibrou o nó
                case -1:
                    atual->bal = 0;
                    return true;
                // Caso 2: se o fator era 0, a exclusão faz com que o lado direito fique mais alto (1)
                case 0:
                    atual->bal = 1;
                    *alterou = false; // a altura não diminuiu, não há propagação da alteração
                    return true;
                // Caso 3: se o fator era 1, a exclusão gera desbalanceamento (fator 2) e é necessária uma rotação à direita
                case 1:
                    *raiz = rotacaoR(atual);
                    if (atual->bal != 0)
                        *alterou = false;
                    return true;
            }
        }
    }
    // Retorna o resultado da operação (a variável res contém o valor retornado pela chamada recursiva)
    return res;
}


/* funcao auxiliar na destruicao (liberacao da memoria) de uma arvore */
void destruirAux(PONT subRaiz){
	if (subRaiz){
		destruirAux(subRaiz->esq);
		destruirAux(subRaiz->dir);
		free(subRaiz);
	}
}


/* libera toda memoria de uma arvore e coloca NULL no valor da raiz    */
void destruirArvore(PONT * raiz){
	destruirAux(*raiz);
	*raiz = NULL;
}


/* inicializa arvore: raiz=NULL */
void inicializar(PONT * raiz){
	*raiz = NULL;
}


/* ----------------------- Funções Novas ------------------------ */


/*Essa função auxiliar percorre a arvore procurando um desbalanceamento, 
se ela encontrar simplesmente altera o valor da variável apontada pelo ponteiro booleano para false, 
e também encerra a verificação no resto da árvore
*/
void ehAvlAux(PONT raiz, bool* avl){
    if (raiz != NULL && *avl){
        if (raiz -> bal > 1 || raiz -> bal < -1){
            *avl = false;    
            return;
        }
        ehAvlAux(raiz-> esq, avl);
        ehAvlAux(raiz -> dir, avl);
    }
}

/*Analisa se é AVL a partir do balanceamento de todos os nós da árvore*/
void ehAvl(PONT raiz){
    if(raiz == NULL) printf("A Raiz esta vazia!");
    else{
        bool avl = true;
        ehAvlAux(raiz, &avl);
        if (avl) printf("A arvore informada segue as regras de uma arvore AVL!");
        else printf("A arvore informada nao segue as regras de uma AVL");
    }
}


/** 
  * @brief conta o número de nós da árvore utilizando recursão
  * @param raiz endereço da raiz
*/
int contagemNos(PONT raiz){
    if (raiz != NULL){
        return 1 + contagemNos(raiz -> esq) + contagemNos(raiz -> dir);
    } else return 0;
}


/*É buscado o endereço do nó com o valor buscado e com ele é executado um loop para percorrer a árvore e 
contar quantos níveis são passados até chegar ao nó desejado*/
int niveldoNodo(PONT raiz, int ch){
    int cont = 0; 
    PONT noBuscado = buscaBinaria(ch, raiz);
    
    if (noBuscado == NULL){
        return naoexiste;
    }
    else{
        //percorre a árvore
        while(raiz != noBuscado){
            cont++;
            if (raiz->chave < ch) raiz = raiz->dir;
            else raiz = raiz -> esq;
        }
        return cont;
    }
}


//Segue até o elemento mais a esquerda
int encontrarMinimo(PONT raiz){
    PONT min;
    while(raiz != NULL){
        min = raiz;
        raiz = raiz -> esq;
    }
    return min -> chave;
}


//Segue até o elemento mais a direita
int encontrarMaximo(PONT raiz){
    PONT max;
    while(raiz != NULL){
        max = raiz;
        raiz = raiz -> dir;
    }
    return max -> chave;
}


/*Esta auxiliar é responsável por fazer a impressão dos valores verificados que são pertencentes ao nível atual buscado, 
se não ela vai descendo na árvore até encontrar alguma chave com o nível procurado
*/
void exibirporNivelAux(PONT raiz, PONT no, int * nivel){
    if(no != NULL){
        int alt_no = niveldoNodo(raiz, no -> chave);
        if (*nivel == alt_no){
            printf("%i{%i} ", no->chave, alt_no);
            return; // A partir do return que ela sobe e continua a busca em outra sub-árvore
        } 
        else{
            exibirporNivelAux(raiz, no->esq, nivel);
            exibirporNivelAux(raiz, no->dir, nivel);
        }
    }
}

// Esta é a função principal da exibição por nível, a qual guarda as informações necessárias para a impressão e altera as váriaveis onde estão acomodadas para que a auxiliar possa procurar as chaves que estão no nível determinado pela principal.
void exibirporNivel(PONT raiz){
    if (raiz == NULL){
        printf("Raiz esta vazia!");
        return;
    }
    
    int h = altura(raiz), 
        nivel = 0;

    //Altera o nível procurado
    while(nivel < h + 1) {
        exibirporNivelAux(raiz, raiz, &nivel);
        nivel++;
    }
}


//Lógica semelhante com a de contagemdeNós, porém com algumas modificações na verificação e no retorno
int contarFolhas(PONT raiz){
    if (raiz == NULL) return 0;
    else if (!raiz -> dir && !raiz -> esq) return 1;
    return 0 + contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}


/*Essa função auxiliar de listarIntervalo() faz a verificação e a impressão dos valores dentro do intervalo informado
e com a sub-arvore advinda da função principal*/
void listarIntervaloAux(PONT raiz, const int* a, const int* b){
    if (raiz == NULL) return;
    listarIntervaloAux(raiz->esq, a, b);
    if(raiz -> chave >= *a && raiz -> chave <= *b) printf("%i ", raiz->chave);
    listarIntervaloAux(raiz->dir, a, b);
}


/**  @brief A função verifica se a raiz de argumento está dentro do intervalo ou não, 
 * se não estiver irá ser chamada novamente só que com alguma das sub-árvore da raiz como argumento,
 * para posteriormente chamar a função auxiliar de impressão*/
void listarIntervalo(PONT raiz, int a, int b){
    if (raiz == NULL) printf("A arvore esta vazia ou nao ha nenhhum nodo no intervalo [%i,%i]!", a, b);
    else if (raiz -> chave < a) listarIntervalo(raiz-> dir, a, b);
    else if(raiz -> chave > b) listarIntervalo(raiz -> esq, a, b);
    else{
        printf("Valores na arvore entre o intervalo [%i,%i]: ", a, b);
        const int* min = &a;
        const int* max = &b;
        listarIntervaloAux(raiz, min, max);
    }
}


/** @brief A função segue com o mesmo k caso o Késimo menor estiver na sub-árvore à esquerda, 
 * se não ela subtrai no valor de k o número de nós na esquerda da raiz + 1 (a própria raiz)
*/
int buscarKesimoMenor(PONT raiz, int k){
    if (raiz != NULL){
        int esq_side = contagemNos(raiz->esq);
        if(k <= esq_side) return buscarKesimoMenor(raiz -> esq, k);
        else if(k == esq_side + 1) return raiz -> chave;
        else return buscarKesimoMenor(raiz -> dir, k - esq_side - 1);
    }
    return naoexiste;
}


//Utiliza a função niveldoNodo para obter os níveis de cada valor e compará-los
int mesmoNivel(PONT raiz, int x, int y){
    int nivel_x = niveldoNodo(raiz, x);
    int nivel_y = niveldoNodo(raiz, y);
    if(nivel_x == nivel_y){
        printf("\nOs valores %i e %i estao no mesmo nivel!", x, y);
        return true;
    } else{
        printf("\nOs valores %i e %i nao estao no mesmo nivel!", x, y);
        return false;
    }
}


//Basicamente é o mesmo algoritmo da contagem de nós, porém retorna o valor da chave dos nós ao invés de retornar 1;
int somaValores(PONT raiz){
    if (raiz == NULL) return 0;
    return raiz->chave + somaValores(raiz -> esq) + somaValores(raiz -> dir);
}


//Função auxiliar que efetivamente executa a impressão da árvore de forma vertical
void exibirVisualAUX(PONT raiz, PONT no, PONT pai, PONT avo){
    if(no){
        PONT no_verificador = raiz;
        bool print_barra = true;
        int alt_no = niveldoNodo(raiz, no -> chave);
        int nivel_verificador = 0;

        //Este loop serve para imprimir as linhas antes da chave de forma correta
            while (no_verificador -> chave != no -> chave){
                if(no_verificador -> chave > no -> chave) { //Se o no a ser imprimido estiver na sub-árvore esq do no_verificador
                    if (nivel_verificador == alt_no - 1) printf("|-----");
                    else printf("|     ");
                    no_verificador = no_verificador -> esq;
                } else { //Se o no a ser imprimido estiver na sub-árvore dir do no_verificador
                    if (nivel_verificador == alt_no - 1) printf("|-----"); 
                    else printf("      ");
                    no_verificador = no_verificador -> dir;
                }
                nivel_verificador++;
            }

        //Define o pai e o avo 
        pai = no;
        buscaNo(raiz, pai->chave, &avo); //Serve para achar o avô
        
        //Faz o percurso pré-ordem
        printf("%i\n", no->chave);
        exibirVisualAUX(raiz, no->esq, pai, avo);
        exibirVisualAUX(raiz, no->dir, pai, avo);
    }
}


//Esta exibição é feita de forma vertical e em pré-ordem
void exibirVisual(PONT raiz){
    if (!raiz) return;
    PONT no = raiz;
    PONT pai = NULL, avo = NULL;
    exibirVisualAUX(raiz, no, pai, avo);
}







