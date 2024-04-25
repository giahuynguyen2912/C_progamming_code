#include "base.h"

typedef struct s_List {
    int value;
    struct s_List* next;
} List;

List* prepend(int value, List* before) {
    List* new = xmalloc(sizeof(List));
    new->value = value;
    new->next = before;
    return new;
}

void print_list(List* list) {
    printf("[");
    while (list != NULL) {
        printf("%d", list->value);
        List* next = list->next;
        if (next) {
            printf(", ");
        }
        list = next;
    }
    printf("]\n");
}

// TODO: Die Funktion soll die letzten beiden ungeraden Zahlen in einer Liste identifizieren, wobei die Reihenfolge ihres Auftretens beibehalten wird.
int odd_last_two(List* list, int* out) {
    int odd_count = 0;
    while (list != NULL) {
        int value = list->value;
        if (value % 2) {
            out[0] = out[1];
            out[1] = value; // Add last to end to preserve order
            ++odd_count;
        }
        list = list->next;
    }
    if (odd_count > 2) odd_count = 2; // We don't store more than 2 elements in out
    // If there is only one odd number, set it to the first
    if (odd_count == 1) {
        out[0] = out[1];
        out[1] = 0;
    }
    return odd_count;

}

int main() {
    int out[2];

    List* list_0 = NULL;
    printf("Input: ");
    print_list(list_0);
    test_equal_i(odd_last_two(list_0, &out), 0);

    List* list_1 = prepend(2,NULL);
    printf("Input: ");
    print_list(list_1);
    test_equal_i(odd_last_two(list_1, &out), 0);

    List* list_2 = prepend(7,NULL);
    printf("Input: ");
    print_list(list_2);
    test_equal_i(odd_last_two(list_2, &out), 1);
    test_equal_i(out[0], 7);
    printf("Output: ");
    printialn(out, 1);

    List* list_3 = prepend(9, prepend(11, NULL));
    printf("Input: ");
    print_list(list_3);
    test_equal_i(odd_last_two(list_3, &out), 2);
    printf("Output: ");
    printialn(out, 2);
    test_equal_i(out[0], 9);
    test_equal_i(out[1], 11);

    List* list_4 = prepend(1, prepend(2, prepend(3, prepend(4, prepend(5, NULL)))));
    printf("Input: ");
    print_list(list_4);
    test_equal_i(odd_last_two(list_4, &out), 2);
    printf("Output: ");
    printialn(out, 2);
    test_equal_i(out[0], 3);
    test_equal_i(out[1], 5);

    List* list_5 = prepend(1, prepend(2, prepend(3, prepend(4, prepend(5, prepend(6, prepend(7, prepend(8, NULL))))))));
    printf("Input: ");
    print_list(list_5);
    test_equal_i(odd_last_two(list_5, &out), 2);
    printf("Output: ");
    printialn(out, 2);
    test_equal_i(out[0], 5);
    test_equal_i(out[1], 7);
    return 0;
}