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
    //CRIA UM NOVO VETOR ALOCANDO ESPAÇO DE MEMÓRIA PARA ELE
    //Começa com capacidade 8 (oito) e duplica cada vez que precisar de mais.
    struct linked_list * array_list_create(){
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

    struct linked_list_node *create_node(int value) {
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
