#include "fila_dinamica.c"

int main(){
    FILA fila;
    inicializarFila(&fila);

    for (int i = 0; i < 10; i++){
        REGISTRO reg;
        reg.chave = i*10;
        inserirNaFila(&fila, reg);
    }
    TIPOCHAVE first;
    TIPOCHAVE last;
    retornarPrimeiro(&fila, &first);
    retornarUltimo(&fila, &last);
    
    printf("Primeiro: %i   Último: %i \n", first, last);
    exibirFila(&fila);


    TIPOCHAVE busca1 = 10;
    TIPOCHAVE busca2 = 60;
    TIPOCHAVE busca3 = 90;
    TIPOCHAVE busca4 = 110;

    printf( "1ª Busca: %p \n", buscaSeq(&fila, busca1));
    printf( "2ª Busca: %p \n", buscaSeqSent1(&fila, busca2));
    printf( "3ª Busca: %p \n", buscaSeqSent2(&fila, busca3));
    printf( "4ª Busca: %p \n", buscaSeq(&fila, busca4));

    for (int i = 0; i < 7; i++){
        REGISTRO reg;
        excluirDaFila(&fila, &reg);
    }

    retornarPrimeiro(&fila, &first);
    retornarUltimo(&fila, &last);
    printf("Primeiro: %i   Último: %i \n", first, last);
    exibirFila(&fila);
}