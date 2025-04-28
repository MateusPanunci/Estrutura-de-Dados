#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>


using namespace std;

class Prato{
    public:
        int prioridade;
        int tempo;
        string nome;
};

void preenche_dados(Prato* lista){
    string linha;
    ifstream file("pratos.csv");
 
    for (int i = 0; getline(file, linha); i++){
        if (i == 0)continue;

        stringstream ss(linha);
        string cell;

        for (int j = 0; getline(ss, cell, ','); j++){
            if(j == 0) lista[i-1].prioridade = stoi(cell);
            else if(j == 1) lista[i-1].tempo = stoi(cell);
            else lista[i-1].nome = cell;
        }
    }
}


void bubbleSort(Prato* lista, int n){
    int i, j;
    Prato aux;
    bool trocas;
    for(i = 0; i < n - 1; i++){
        trocas = false;
        for(j = 0; j < n - i - 1; j++){
            if(lista[j].prioridade < lista[j + 1].prioridade || (lista[j].prioridade == lista[j + 1].prioridade && lista[j].tempo > lista[j + 1].tempo)){
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
                trocas = true;
            }
        }

        if (!trocas)break;
    }
}


void QuickSortPartition(Prato *lista, int esq, int dir, int &i, int &j ){
    Prato pivo, aux;
    i = esq;
    j = dir;
    int indPivo = (i+j)/2;
    pivo = lista[indPivo];

    while(i <= j){
        while((lista[i].prioridade > pivo.prioridade) || (pivo.prioridade == lista[i].prioridade && lista[i].tempo < pivo.tempo)){
            i++;
        }
        while((pivo.prioridade > lista[j].prioridade) || (pivo.prioridade == lista[j].prioridade && pivo.tempo < lista[j].tempo))j--;
        if (i <= j){
            aux = lista[i];
            lista[i] = lista[j];
            lista[j] = aux;
            i++;
            j--;
            
        }
    }
}

void quickSortOrdenacao(Prato * lista, int esq, int dir){
    int i, j;
    QuickSortPartition(lista, esq, dir, i, j);
    if(esq < j) quickSortOrdenacao(lista, esq, j);
    if(i < dir) quickSortOrdenacao(lista, i, dir);
}


void quickSort(Prato *lista, int n){
    quickSortOrdenacao(lista, 0, n - 1);
}


/**
 * @param lista passar uma lista do tipo Prato
 * @param n quantas linhas deseja imprimir, o máximo que tem nas listas é 300000
 */
void imprimirLista(Prato *lista, int n){
    for (int i = 0; i<n-1; i++){
        cout << lista[i].prioridade << " " << lista[i].nome <<  " " << lista[i].tempo << endl;
    }
}


int main(){

    Prato* listaQuick = new Prato [300000];
    Prato* listaBubble = new Prato [300000];

    preenche_dados(listaQuick);
    preenche_dados(listaBubble);

    cout << "-------------------------------------------------------\n";
    cout << "Aplicando o Quick sort... \n";
    auto inicio = chrono::high_resolution_clock::now();
    quickSort(listaQuick, 300000);
    auto fim = chrono::high_resolution_clock::now();
    auto duracaoQuick = chrono::duration_cast<chrono::milliseconds>(fim - inicio);
    cout << "Tempo de execução do QuickSort: " << duracaoQuick.count() << " millisegundos" << endl;
    // imprimirLista(listaQuick, 300000);


    cout << "-------------------------------------------------------\n";
    cout << "Aplicando o Bubble sort...\n";
    auto inicio2 = chrono::high_resolution_clock::now();
    bubbleSort(listaBubble, 300000);
    auto fim2 = chrono::high_resolution_clock::now();
    auto duracaoBubble = chrono::duration_cast<chrono::seconds>(fim2 - inicio2);
    cout << "Tempo de execução do BubbleSort: " << duracaoBubble.count() << " segundos" << endl;  // O tempo é aproxidamente 53 minutos
    // imprimirLista(listaBublle, 300000);
    cout << "-------------------------------------------------------";

}




