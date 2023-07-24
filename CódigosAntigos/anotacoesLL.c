
     int main(){
        int n, i, x;
        struct linked_list *l01 = linked_list_create(); // Criando o array
        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            scanf("%d", &x);
            if (linked_list_push_back(l01, x) != (i + 1)) {
                error_at_insertion(l01, x);
            }
        }
        print_vector(l01);
        linked_list_pop_back(l01);
        print_vector(l01);
        int index = linked_list_find(l01, 7);
        printf("%d", index);
        printf("\n");
        linked_list_insert_at(l01, 5, 5);
        print_vector(l01);
        index = linked_list_find(l01, 7);
        printf("%d", index);
        printf("\n");
        linked_list_remove_from(l01, 5);
        print_vector(l01);
        index = linked_list_find(l01, 7);
        printf("%d", index);
        printf("\n");
        return 0;
    }
