/*
Compile: make bottom_margin
Run: ./bottom_margin
Compile & run: make bottom_margin && ./bottom_margin
*/

#include "base.h"

int* bottom_margin(char c, char* a, int rows, int cols) {
	/*int* result = xcalloc(cols, sizeof(int));
    int check = 0;
	for (int x = 0; x < cols; x++) {
		int count = 0;
		for (int y = 0; y < rows; y++) {
		   check = y * cols + x;
		   printf("%d\n", check);
			if (a[check] == c) {
				count++;
			}
		}
		result[x] = count; 
	}
	return result;
	*/
	int* res = xcalloc(cols, sizeof(int));
	for(int i = 0; i < cols ; i++){
	   int count = 0;
	   for(int j = 0; j < rows; j++){
	      if(a[j * cols + i] == c){
	        count++;
	      }
	   }
	   res[i] = count;
	}
	return res;
}

int* row_sum(int* a, int rows, int cols) {
    // implement
    int * res = xcalloc(rows ,sizeof(int));
    for(int i = 0; i < rows; i++){
       int sum = 0;
       for(int j = 0; j < cols; j++){
          sum += a[j+i*rows];
       }
       res[i] = sum;
    }
    return res;
}

void test(void) {
	char a[8][8] = {
		{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', ' ', 'y', ' ', ' ', 'a', 'z', 'a' },
		{ ' ', ' ', ' ', ' ', ' ', 'z', 'z', 'z' },
		{ ' ', 'x', ' ', ' ', ' ', 'a', 'z', 'a' },
		{ ' ', 'x', 'x', ' ', ' ', ' ', ' ', ' ' },
		{ ' ', 'x', 'x', 'x', ' ', ' ', ' ', ' ' },
		{ ' ', 'x', 'x', 'x', ' ', 'b', 'b', ' ' },
		};
	
	int* margin1 = bottom_margin('a', (char*)a, 7, 8);
	int expected1[] = { 0, 0, 0, 0, 0, 2, 0, 2 };
	printf("Actual:   ");printialn(margin1, 8);
	printf("Expected: ");printialn(expected1, 8);
	printf("\n");
	
	int* margin2 = bottom_margin('x', (char*)a, 7, 8);
	int expected2[] = { 0, 4, 3, 2, 0, 0, 0, 0 };
	printf("Actual:   ");printialn(margin2, 8);
	printf("Expected: ");printialn(expected2, 8);
	printf("\n");
	
	int* margin3 = bottom_margin('y', (char*)a, 7, 8);
	int expected3[] = { 0, 0, 1, 0, 0, 0, 0, 0 };
	printf("Actual:   ");printialn(margin3, 8);
	printf("Expected: ");printialn(expected3, 8);
	printf("\n");
	
	int* margin4 = bottom_margin('z', (char*)a, 7, 8);
	int expected4[] = { 0, 0, 0, 0, 0, 1, 3, 1 };
	printf("Actual:   ");printialn(margin4, 8);
	printf("Expected: ");printialn(expected4, 8);
	printf("\n");

		    int b[3][3] = {
                { 1, 2, 3 },
                { -1, -2, -3 },
                { 3, 4, 5 },
            };
	int* margin5 = row_sum((int*)b, 3, 3);
	int expected5[] = { 6,-6,12 };
	printf("Actual:   ");printialn(margin5, 3);
	printf("Expected: ");printialn(expected5, 3);
	printf("\n");
}

int main(void) {
	test();
	    int a[3][3] = {
            { 1, 2, 3 },
            { -1, -2, -3 },
            { 3, 4, 5 },
        };
        row_sum((int*)a, 3, 3);
	return 0;
}
