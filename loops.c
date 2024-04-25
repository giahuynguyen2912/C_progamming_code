/*
Compile: make loops
Run: ./loops
make loops && ./loops
*/

#include "base.h"

void loops_a(int n) {
    for (int i = 1; i <= n; i++){
		for (int j = 1; j <= i; j++) {
			printf("%d ", j);
		};
		printf("\n");
	}
}

void loops_b(int n) {
    for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n - i; j++){
			printf("  ");
		}
		for (int y = 1; y <= i; y++){
			printf("%d ", y);
		} 
		printf("\n");	
	}
}

void loops_c(int n) {
    for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n - i; j++){
			printf(" ");
		}
		for (int y = 1; y <= i; y++){
			printf("%d ", y);
		} 
		printf("\n");	
	}
}

void loops_d(int n) {
    for(int i = 0; i <= n+1 ; i++){
		for(int j = 0; j <= n+1 ; j++){
			if(i == j || j == n - i + 1){
				//
				if(i<=n/2){
				printf("%d ",i);
				}else{
				int a = n+1-i;
				printf("%d ",a);
				}

			}else{
				printf("  ");
			}
		}
		 printf("\n");
	}
}

// todo: implement helper functions for loops_e (recommended)

void loops_e(int n) {
    for(int i=1; i<= n ; i++)
    {
        /* Print trailing spaces */
        for(int j = 1; j <= n-i; j++)
        {
            printf(" ");
        }
        for(int j = 1; j <= 2*n; j++)
        {
            if((i == 1 && j == 1) || (i == 1 && j == 2*n) || (i == n && j == 1) || (i == n && j == 2*n)) {
                printf("+");	
            } else if ((i == 1 && j != 1 && j != 2*n) || (i == n && j != 1 && j != 2*n) ) {
				printf("-");
			} else if ( i != 1 && i != n ) {
				if(j == 1 || j == 2*n) {
				printf("/");
				}else {
					printf(" ");
				}
			}
                
        }

        printf("\n");
    }
}


// todo: implement helper functions for loops_f (recommended)

void loops_f(int n) {
    char C = '0';
	for(int i=1; i<= n ; i++)
    {
        for(int j = 1; j <= n-i; j++)
        {
            printf(" ");
        }
        for(int j = 1; j <= 2*n; j++)
        {
            if((i == 1 && j == 1) || (i == 1 && j == 2*n) || (i == n && j == 1) || (i == n && j == 2*n)) {
                printf("+");	
            } else if ((i == 1 && j != 1 && j != 2*n) || (i == n && j != 1 && j != 2*n) ) {
				printf("-");
			} else if ( i != 1 && i != n ) {
				if(j == 1 || j == 2*n) {
				printf("/");
				}else if (j % 2 == 1){
					printf("%c ", C);
					if(C == '9') {
						C = '0';
					} else {
						C++;
					}
				}
			}
                
        }

        printf("\n");
    }
}

int main(void) {
    loops_a(5);
    loops_b(5);
    loops_c(5);
    loops_d(5);
    loops_a(9);
    loops_b(9);
    loops_c(9);
    loops_d(9);
    loops_e(3);
    loops_e(4);
    loops_e(5);
    loops_e(9);
    loops_e(12);
    loops_f(5);
    loops_f(9);
    return 0;
}
