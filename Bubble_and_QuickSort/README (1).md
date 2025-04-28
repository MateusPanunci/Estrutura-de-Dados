# BubbleAndQuickSort
Essa é uma atividade de Estrutura de Dados 1 a qual o objetivo era medir o tempo da aplicação do bubble sort e do Quick Sort aplicando cada um a uma lista de 300.000 structs (as listas de cada método de ordenação são iguais), a fim de comparar a diferença de eficiência entre os dois. No repositório estará disponível o programa com a aplicação dos métodos e o enunciado da atividade.

# Relatório

### Comparação dos métodos
O quick Sort demora aproxiadamente 300 milésimos de segundos e o bubble sort 53 minutos para ordenar, o que deixa explícito a vantagem do quick sort em relação ao bubble, já que o tempo de execução dele é O(n.log(n)) e o do bubble é O(n²), fazendo com que quanto mais valores houver para ordenar, maior vai ser a diferença entre a eficiência do quick e a do bubble.

### Escolha dos Pivôs

No quick sort, a escolha dos pivôs sempre é a mediana de cada conjunto em cada nível de recursão, para assim criar partições mais balanceadas e reduzir o número de chamadas recursivas e de comparações


