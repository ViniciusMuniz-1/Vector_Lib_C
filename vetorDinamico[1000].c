#include <stdio.h>
#include <stdlib.h>

    struct array_list{
        int *data;
        unsigned int size;
        unsigned int capacity;
    };

    
    //----------------------------------------------------------------------------------------
    //AUMENTA A CAPACIDADE DO VETOR EM 2 VEZES O TAMANHO ATUAL
    //COMPLEXIDADE: O(N), visto que percorre o array inteiro para alocar mais espaço de memória
    void array_list_increase_capacity(struct array_list *list){
        int * new_data = (int*)malloc(sizeof(int)*(list->capacity+1000));
        for(int i = 0; i < list->capacity ; ++i){
            new_data[i] = list->data[i];
        }
        free(list->data);
        list->data = new_data;
        list->capacity = list->capacity+1000;
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //CLONA O VETOR
    //COMPLEXIDADE O(N), visto que percorre o array inteiro passando sues dados para um novo array:
    struct array_list * array_list_clone(struct array_list *list){
        struct array_list *list_clone;
        list_clone = (struct array_list*)malloc(sizeof(struct array_list));
        if (list_clone==0){ /* Error */
        fprintf(stderr,"Error on memory allocation.\n");
        exit(-1);
        }

        list_clone->capacity = list->capacity;
        list_clone->size = list->size;
        list_clone->data = (int*)malloc(sizeof(int)*list_clone->capacity);
        if (list_clone->data==0){ /* Error */
            fprintf(stderr,"Error on memory allocation.\n");
            exit(-1);
        }

        for(int i = 0; i < list_clone->capacity ; ++i){
            list_clone->data[i] = list->data[i];
        }
        return list_clone;
    }
    //----------------------------------------------------------------------------------------
    
    
    //----------------------------------------------------------------------------------------
    //CRIA UM NOVO VETOR ALOCANDO ESPAÇO DE MEMÓRIA PARA ELE
    //Começa com capacidade 8 (oito) e duplica cada vez que precisar de mais.
    struct array_list * array_list_create(){
        struct array_list *new_list;
        new_list = (struct array_list*)malloc(sizeof(struct array_list));
        if (new_list==0){ /* Error */
        fprintf(stderr,"Error on memory allocation.\n");
        exit(-1);
        }
        new_list->capacity = 1000;
        new_list->size = 0;
        new_list->data = (int*)malloc(sizeof(int)*new_list->capacity);
        if (new_list->data==0){ /* Error */
            fprintf(stderr,"Error on memory allocation.\n");
            exit(-1);
        }
        return new_list;
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //Retorna a quantiade de elementos existente na lista;
    //COMPLEXIDADE: O(1)
    unsigned int array_list_size(struct array_list * list){
        return list->size;
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //Para o push_back, saber o tamanho vai ser a chave, visto que o último elemento deve ser adicionado no último index
    //Adiciona um novo elemento ao final do vetor;
    //COMPLEXIDADE: O(1), visto que sempre será adicionado ao final do vetor
    unsigned int array_list_push_back(struct array_list *list, int value){
        if(list->size == list->capacity){
            array_list_increase_capacity(list);
            list->data[list->size++] = value;
            return array_list_size(list);
        }
        else{
            list->data[list->size++] = value;       
        }
        return array_list_size(list);
    }
    //----------------------------------------------------------------------------------------

    
    //----------------------------------------------------------------------------------------
    //LÊ UM VETOR
    void array_list_read_until(struct array_list *list, int end_reading){
        int x;
        while (scanf("%d",&x),x!=end_reading){
            array_list_push_back(list , x);            // Chamando a função array_list_push_back passando a lista e o elemento a ser adicionado
        }
    }
    //----------------------------------------------------------------------------------------
    

    //----------------------------------------------------------------------------------------
    //PRINTA UM VETOR
    void array_list_print(struct array_list *list){
        printf("[");
        if (list->size>0){
        printf("%d",list->data[0]);
        for (int i=1 ; i<list->size ; ++i)
        printf(", %d",list->data[i]);
        }
        printf("]");
    }
    //----------------------------------------------------------------------------------------
    

    //----------------------------------------------------------------------------------------
    //Remove um elemento do final do vetor, caso exista.
    //COMPLEXIDADE: O(1), visto que faz a mesma operação independente do tamanho do vetor
    void array_list_pop_back(struct array_list *list){
        list->size--;
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //Insere um elemento em uma posição específica determinada pelo parâmetro index
    //Complexidade: O(N), visto que precisa encontrar o elmento e depois mover todos os elementos para a direita
    unsigned int array_list_insert_at(struct array_list *list, int value, int index){
        if(index<0 || index > list->size){
            return -1;
        }

        if(index == list->size) {
            array_list_push_back(list, value);
            return array_list_size(list);
        }

        int current = list->data[index], next = list->data[index+1];
        for(int i = index; i < list->size; i++){
            list->data[i+1] = current;
            current = next;
            next = list->data[i+2];
        }

        list->data[index] = value;
        list->size++;
        return array_list_size(list);
    }
    //----------------------------------------------------------------------------------------
    

    //----------------------------------------------------------------------------------------
    //Remove um elemento de um índice específicado determinado pelo parâmetro index
    //Complexidade: O(N), visto que precisa encontrar o elmento e depois mover todos os elementos para a esquerda
    int array_list_remove_from(struct array_list *list, int index) {
        if (list == NULL || index < 0 || index >= list->size) {
            return -1; // Verificar se a lista é válida e se o índice está dentro dos limites
        }

        if(index == list->size-1){
            array_list_pop_back(list);
            return array_list_size(list);
        }

        // Remover o elemento encontrado
        int next = list->data[index+1];
        for(int j = index; j < list->size; j++){
            list->data[j] = next;
            next = list->data[j+1];
        }


        list->size--;
        return array_list_size(list);

        // Verificando se é necessário diminuir a capacidade do array
        //VERIFICAR QUANDO ESTÁ COM 25% DA CARGA
        if (list->capacity - list->size >= 0) {
            int *new_data = (int *)realloc(list->data, sizeof(int) * (list->capacity/2));
            if (new_data != NULL) {
                list->data = new_data;
                list->capacity /= 2;
            }
        }

        return array_list_size(list);
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //Retorna um elemento localizado no índice espeficado por parâmetro
    //Complexidade O(1);
    int array_list_get(struct array_list * list, int index, int *error){
        error = 0;
        if(list == NULL || index < 0 || index >=list->size){
            error = 1;
            return error;
        }

        return list->data[index];
        
    }
    //----------------------------------------------------------------------------------------

    
    //----------------------------------------------------------------------------------------
    //Verifica se um elemento pertence ao array
    //Complexidade O(N);
    int array_list_find(struct array_list * list, int element){
        if(list == NULL){
            return 1000000;
        }

        for(int i = 0; i < list->size; i++){
            if(list->data[i] == element){
                return i;
            }
        }

        return -1;
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //Retorna o espaço efetivamente reservado para a lista.
    //Complexidade O(1)
    unsigned int array_list_capacity(struct array_list * list){
        return list->capacity;
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    void array_list_destroy(struct array_list * list){
        free(list->data);
        free(list);
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //Retorna a porcentagem de espaço ocupado pela lista
    //Complexidade O(1)
    double array_list_percent_occupied(struct array_list * list){
        double percent_occupied = (double)list->size / list->capacity;
        return percent_occupied;
    }
    //----------------------------------------------------------------------------------------