#include "vetorDinamico.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



    int main(){
        int *error = 0;
        struct array_list *list01 = array_list_create(); // Criando o array
        array_list_read_until(list01,-1);
        array_list_print(list01);
        printf("\n");
        array_list_insert_at(list01, 6, 5);
        array_list_print(list01);
        printf("\n");
        array_list_insert_at(list01, 1, 1);
        array_list_print(list01);
        printf("\n");
        array_list_remove_from(list01, 1);
        array_list_print(list01);
        printf("\n");
        int num = array_list_get(list01, 8, error);
        printf("%d", num);
        printf("\n");
        array_list_pop_back(list01);
        array_list_print(list01);
        printf("\n");
        num = array_list_size(list01);
        printf("%d", num);
        printf("\n");
        num = array_list_find(list01, 1);
        printf("%d", num);
        printf("\n");
        num = array_list_capacity(list01);
        printf("%d", num);
        printf("\n");
        double num1 = array_list_percent_occupied(list01);
        printf("%f", num1);
        printf("\n");
        array_list_destroy(list01);
        return 0;
    }
