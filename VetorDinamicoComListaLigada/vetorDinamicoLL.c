#include <stdio.h>
#include <stdlib.h>

    struct linked_list_node{
        int value;
        struct linked_list_node *prev;
        struct linked_list_node *next;
    };
    struct linked_list{
        struct linked_list_node *first;
        struct linked_list_node *last;
        unsigned int size;
    };

    //----------------------------------------------------------------------------------------
    //FUNÇÃO RESPONSÁVEL POR CRIA UMA NOVA LISTA ALOCANDO ESPAÇO DE MEMÓRIA PARA ELA
    //Complexidade O(1)  
    struct linked_list * linked_list_create(){
        struct linked_list *new_linked_list = (struct linked_list*)malloc(sizeof(struct linked_list));
        if (new_linked_list == NULL) {
            fprintf(stderr, "Error on memory allocation.\n");
            exit(-1);
        }
        new_linked_list->first = NULL;
        new_linked_list->last = NULL;
        new_linked_list->size = 0;
        return new_linked_list;
    }
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    //FUNÇÃO RESPONSÁVEL POR CRIAR OS NÓS DA LISTA LIGADA
    //Complexidade O(1) 
    struct linked_list_node * create_node(int value) {
        struct linked_list_node *new_node = (struct linked_list_node*)malloc(sizeof(struct linked_list_node));
        if (new_node == NULL) {
            fprintf(stderr, "Error on memory allocation.\n");
            exit(-1);
        }
        new_node->value = value;
        new_node->prev = NULL;
        new_node->next = NULL;
        return new_node;
    }
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    //FUNÇÃO RESPONSÁVEL POR RETORNAR O TAMANHO DA LISTA
    //Complexidade O(1)
    unsigned int linked_list_size(struct linked_list *list){
        return list->size;
    }
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    //FUNÇÃO RESPONSÁVEL POR RETORNAR O ELEMENTO NO ÍNDICE ESPECIFICADO DA LISTA LIGADA
    //Complexidade O(n) - no pior caso, onde n é o índice especificado
    int linked_list_get(struct linked_list *list, int index, int *error) {
        if (index < 0 || index >= linked_list_size(list)) {
            *error = 1;
            return 0;
        }

        struct linked_list_node *current = list->first; //inicia a partir do primeiro elemento
        for (int i = 0; i < index; i++) {
            current = current->next;                    //aponta para o próximo elemento
        }

        *error = 0;
        return current->value;
    }
    //----------------------------------------------------------------------------------------
    
    //----------------------------------------------------------------------------------------
    //FUNÇÃO RESPONSÁVEL POR INSERIR UM ELEMENTO NO FINAL DA LISTA LIGADA
    //Complexidade O(1)
    unsigned int linked_list_push_back(struct linked_list *list, int value) {
        struct linked_list_node *new_node = create_node(value);
        
        if (list->size == 0) {
            list->first = new_node;
            list->last = new_node;
        } 
        else {
            new_node->prev = list->last;
            list->last->next = new_node;
            list->last = new_node;
        }
        
        list->size++;

        return linked_list_size(list);
    }
    //------------------------------------------------------------- 

    //------------------------------------------------------------- 
    //FUNÇÃO RESPONSÁVEL POR REMOVER O ÚLTIMO ELEMENTO DA LISTA LIGADA
    // Complexidade O(1)
    unsigned int linked_list_pop_back(struct linked_list * list){
        if(list->size == 0){
            return linked_list_size(list);
        } 
        if(list->size == 1){
            free(list->first);
            list->first = NULL;
            list->last = NULL;
        } 
        else{
            struct linked_list_node *last_node = list->last;
            list->last = last_node->prev;
            list->last->next = NULL;
            free(last_node);
        }
        
        list->size--;
        return(linked_list_size(list));
    }
    //------------------------------------------------------------- 

    //----------------------------------------------------------------------------------------
    //FUNÇÃO QUE VERIFICA SE UM ELEMENTO EXISTE NA LISTA LIGADA
    //Complexidade O(N);
    int linked_list_find(struct linked_list * list, int element){
        if(list == NULL){
            return 0;
        }

        int index = 0;      //como a lista não possui index, criarei dentro das funções
        struct linked_list_node *current = list->first; //inicia a partir do primeiro elemento
        for (int i = 0; i < list->size; i++) {
            if(current->value == element){
                return index;
            }
            current = current->next;                    //aponta para o próximo elemento
            index++;
        }

        return -1;
    }
    //----------------------------------------------------------------------------------------


    //----------------------------------------------------------------------------------------
    //Insere um elemento em uma posição específica determinada pelo parâmetro index
    //Complexidade: O(N), visto que precisa encontrar o elemento e depois mover todos os elementos para a direita
    unsigned int linked_list_insert_at(struct linked_list *list, int value, int index){
        if(index < 0 || index > linked_list_size(list)){
            printf("Index inválido");
            return linked_list_size(list);
        }

        if(index == linked_list_size(list)-1){
            linked_list_push_back(list, value);
            return linked_list_size(list);
        }

        struct linked_list_node *new_node = create_node(value);

        if(index == 0){
            new_node->next = list->first;
            list->first->prev = new_node;
            list->first = new_node;
        }
        else{
            struct linked_list_node *current = list->first;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            new_node->prev = current->prev;    //o anterior do a ser inserido é o atual encontrado no laço
            new_node->next = current;          //o próximo do a ser inserido é o atual
            current->prev->next = new_node;     //o novo próximo do anterior do atual é o elemento a ser inserido
            current->prev = new_node;           //e o anterior do atual é o valor a ser inserido
            //loucura
        }   

        list->size++;
        return linked_list_size(list);
    }
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    //Remove um elemento de um índice específicado determinado pelo parâmetro index
    //Complexidade: O(N), visto que precisa encontrar o elmento e depois mover todos os elementos para a esquerda
    int linked_list_remove_from(struct linked_list *list, int index) {
        if(index < 0 || index > linked_list_size(list)){
            printf("Index inválido");
            return linked_list_size(list);
        }

        if(index == list->size-1){
            linked_list_pop_back(list);
            return linked_list_size(list);
        }

        struct linked_list_node *current = list->first;
        for (int i = 0; i < index; i++) {
                current = current->next;
        }

        if(current->prev != NULL){
            //Se não for o primeiro da lista, então precisamos atualizar os ponteiros para remover o elemento
            current->prev->next = current->next; //basicamente, o próximo do antes do atual vai ignorar e apenas passar para o próximo do atual
            //explicação na prática: [8] <-> [7] <-> [6]
            // [8] -> [6]
            // agora falta fazer o [6] apontar para o [8]
        }
        else{
            //Se não tiver nada antes, significa que é o primeiro elemento e é isso
            list->first = current->next;
        }

        if(current->next != NULL){
            //Caso não seja o último, então é necessário atualizar os ponteiros novamente
            current->next->prev = current->prev; //basicamente, o próximo do anterior ao atual vai ignorar e apenas apontar para o próximo
            //explicação na prática: [8] <-> [6]
        }
        else{
            list->last = current->prev;
        }

        free(current);
        list->size--;

        return linked_list_size(list);
    }
    //----------------------------------------------------------------------------------------

    //----------------------------------------------------------------------------------------
    //Complexidade O(N)
    void linked_list_destroy(struct linked_list *list){
        struct linked_list_node *current = list->first;
        struct linked_list_node *temporario;

        while(current != NULL){
            temporario = current;
            current = current->next;
            free(temporario);
        }

        free(list);
    }
    //----------------------------------------------------------------------------------------