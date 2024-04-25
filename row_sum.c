/*
make row_sum && ./row_sum
*/

#include "base.h"

// <purpose statement>
int* row_sum(int* a, int rows, int cols) {
    // implement}
    int * res = xmalloc((rows+1) *sizeof(int));
    int index = 0;
    for(int i = 0; i < rows; i++){
       int sum = 0;
       for(int j = 0; j < cols; j++){
          printf("%d\n", a[j+i*rows]);
          sum += a[j+i*rows];
       }
       res[index++] = sum;
    }
    res[index]='\0';
    printf("\n");
    for(int i =0; i < rows; i++ ){
       printf("%c\n", res[i]);
    }
    return res;

}
/*
void test(void) {
    int a[3][3] = {
        { 1, 2, 3 }, 
        { -1, -2, -3 }, 
        { 3, 4, 5 }, 
    };
    int* margin = row_sum((int*)a, 3, 3);
    int expected[] = { 6, -6, 12 };
    test_equal_i(a_of_buffer(margin, 3, sizeof(int)),
                  a_of_buffer(expected, 3, sizeof(int)));
}
*/
int main(void) {
    int a[3][3] = {
        { 1, 2, 3 },
        { -1, -2, -3 },
        { 3, 4, 5 },
    };
    row_sum((int*)a, 3, 3);
    //test();
    return 0;
}