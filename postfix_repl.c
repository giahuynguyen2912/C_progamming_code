/*
	make postfix_repl && ./postfix_repl
*/

#include "base.h"

#define STACK_SIZE  10

//Returns substring of s from character i to character j
String s_sub(String s, int i, int j) {
    require_not_null(s);
    int n = strlen(s);
    if (i < 0) i = 0;
    if (j > n) j = n;
    if (i >= j || i >= n || j <= 0) {
        char *a = xmalloc(1 * sizeof(char));
        a[0] = '\0';
        return a;
    }
    // assert i < j && i < n && j > 0
    n = j - i;
    char *a = xmalloc((n + 1) * sizeof(char));
    memcpy(a, s + i, n * sizeof(char));
    a[n] = '\0';
    return a;
}

typedef enum {
	OPERATION, VALUE, EMPTY
} Tag;

typedef struct{
	Tag tag;
	
	union{
		int value;
		char operation;
	};
} StackElement;

typedef struct{
	StackElement elements[STACK_SIZE];
	int stack_pointer;
} Stack;

//checks if char c belongs to an operation
bool is_operation(char c){
	return c == '+' || c == '/' || c == '-' || c == '*';
}

//checks wheter c is a digit
bool is_digit(char c){
	return c >= '0' && c <= '9';
}

//todo:
StackElement make_StackElement(Tag tag){
	StackElement ele;
	switch (tag){
		case OPERATION :
		    ele.tag = OPERATION;
			ele.operation = '+';
			break;
		case VALUE : 
			ele.tag = VALUE;
			ele.value = 0;
			break;
		case EMPTY :
			ele.tag = EMPTY;
			ele.operation = '$';
	}
	return ele;
} 
//todo:
StackElement make_Value(int value){
	StackElement ele;
	ele = make_StackElement(VALUE);
	ele.value = value;
	return ele;
}
//todo:
StackElement make_Operation(char operation){
	StackElement ele;
	ele = make_StackElement(OPERATION);
	ele.operation = operation;
	return ele;
}


bool is_empty(Stack* stack){
	return stack->stack_pointer < 0;
}

//todo:
void clear_stack(Stack* stack, int n){
	stack->elements[0] = make_StackElement(EMPTY);
	stack->stack_pointer = -1;
}

//die funktion nimmt als param. eine stack stackelement, n : stack grosse, und stack pointer  
//der stackelement wir in der nachste position eingefugt und stack_pointer um 1 erhoht. 
void push(StackElement element, Stack* stack, int n){
	if(stack->stack_pointer < (n - 1)){
		stack->stack_pointer++;
		stack->elements[stack->stack_pointer] = element;
	}
}

//der oberste element geloscht und zuruckgegeben,stack_pointer um 1 reduziert. 
StackElement pop(Stack* stack, int n){
	StackElement ele = stack->elements[stack->stack_pointer ];
	stack->elements[stack->stack_pointer] = make_StackElement(EMPTY);
	stack->stack_pointer--;
	return ele;
}

//todo:
void print_stackElement(StackElement ele){
	switch(ele.tag) {
		case EMPTY : 
			printf("[empty]\n");
			break;
		case VALUE :
			printf("[%d]\n", ele.value);
			break;
		case OPERATION :
			printf("[%c]\n", ele.operation);
			break;
	}
}

//todo:
void print_stack(Stack* stack, int n){
	for(int i = 0; i < n ; i = i + 1) {
		if((stack->stack_pointer - i) >= 0) {
		    print_stackElement(stack->elements[stack->stack_pointer - i]);
		}
	}
}

void compute(Stack* stack, int n){
	//todo
	if(stack->stack_pointer < 2) {
		
		printf(" mindesten 2 operanden \n");
		
	}else if(!(stack->elements[stack->stack_pointer - 1].tag == VALUE && stack->elements[stack->stack_pointer - 2].tag == VALUE)) {
		
		printf("mindesten 2 operanden \n");
		
	}else if(stack->elements[stack->stack_pointer].tag == OPERATION) {
		
		StackElement a = pop(stack, n);
		
		StackElement b = pop(stack, n);
		
		StackElement c = pop(stack, n);
		
		int x;
		
		switch(a.operation){
			
			case '+' :
				x = b.value + c.value;
				push(make_Value(x), stack, n);
				break;
			case '-' :
				x = c.value - b.value;
				push(make_Value(x), stack, 128);
				break;
			case '*' :
				x = c.value * b.value;
				push(make_Value(x), stack, 128);
				break;
			case '/' :
				x = c.value / b.value;
				push(make_Value(x), stack, 128);
				break;
		}
		
	}
}

int main (void){	
	Stack stack;
	
	clear_stack(&stack, STACK_SIZE);
	

	int input_size = 128;	
	char input[input_size];
	
	for(int i = 0; i< input_size; i++){
		input[i] = '\0';
	}
	int input_index = 0;
	
	
	int c;
	while((c = getchar()) != 'q'){

		if(c == '\n'){
			for(int i = 0; i< input_index; i++){
				//todo:
				if(is_digit(input[i])){
					
					int u = input[i] - '0';
					
					push(make_Value(u), &stack, 128);
					
					print_stack(&stack, 5);
					
					printf("...........\n");
					
			    } else if(is_operation(input[i])) {
			    	
					char t = input[i];
					
					push(make_Operation(t), &stack, 128);
					
					compute(&stack, 128);
					
					print_stack(&stack, 5);
					
					printf("...........\n");
		     	}
			}
			
			for(int i = 0; i< input_size; i++){
				input[i] = '\0';
			}
			input_index = 0;
			
		}else{
			input[input_index] = c;
			input_index++;
		}

	
	}
	return 0;
}