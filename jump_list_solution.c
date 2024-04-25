/*
Compile: make jump_list
Run: ./jump_list
Compile & run: make jump_list && ./jump_list
*/

#include "base.h"

typedef struct Node {
	int value;
	struct Node* next;
} Node;

Node* new_node(int i, Node* next) {
	Node* node = xcalloc(1, sizeof(Node));
	node->value = i;
	node->next = next;
	return node;
}

Node* reverse_rec(Node* list, Node* result) {
	if (list == NULL) {
		return result;
	} else {
		return reverse_rec(list->next, new_node(list->value, result));
	}
}

Node* reverse(Node* list) {
	return reverse_rec(list, NULL);
}

void fprint_list(FILE* f, Node* list) {
    require_not_null(list);
    fprintf(f, "[");
    for (Node* n = list; n; n = n->next) {
        fprintf(f, "%d", n->value);
        if (n->next) fprintf(f, ", ");
    }
    fprintf(f, "] ");
}

void push(Node** head, int val){
     Node* current = NULL;
     current = new_node(val, current);
     current->next = *head;
     *head = current;
}
/*
Node* new_list(Node* list, int n){
   Node* ret = NULL;
   if(n == 0) return NULL;
   if(n>0){
     for(Node* n = list; n != NULL; )
   }
}
*/

Node* merge_list(Node* s, Node* b){
     if(s == NULL){return b;}
     if(b == NULL){return s;}
     Node* res = NULL;
     while(s->next != NULL){
       res = new_node(s->value, res);
       s = s->next;
     }
     res->next = b;
     return res;
}
/*
Node* delete_node(Node* list, int i){
     Node* res = NULL;
     int index = 0
     for(Node* n = list; n != NULL; n = n->next, index++){
        if(index != i){
          res = new_node(node->value, res);
        }
     }
}
*/
Node* jump_list(Node* list, int gap) {
	Node* result = NULL;
	int i = 0;
	for (Node* node = list; node != NULL; node = node->next, i++) {
		if(i % (gap+1) == 0){
			result = new_node(node->value, result);
		}
	}
	return reverse(result);
}

Node* sorted_list(Node* list){
   Node* res = NULL;
   int len_list = 0;
   for(Node* node = list; node != NULL; node = node->next){
      len_list++;
   }
   char* temp = xmalloc((len_list+1)*sizeof(char));
   int index = 0;
   for(Node* copy = list; copy != NULL; copy = copy->next){
      temp[index++] = copy->value;
   }
   temp[index] = '\0';
   int a;
   for(int i = 0; i < strlen(temp)-1; i++){
      for(int j = i+1; j < strlen(temp); j++){
         if(temp[i]>temp[j]){
           a = temp[j];
           temp[j] = temp[i];
           temp[i] = a;
         }
      }
   }
   for(int i = 0; i < strlen(temp); i++){
      res = new_node(temp[i], res);
   }
   return reverse(res);
}

int first_odd_pair(Node* list, int* out){
   /* int count = 0;
    if(out == NULL){return 0;}
    //out = xmalloc((2)* sizeof(int));
    int index = 0;
    while(list != NULL && count < 2){
      if(list->value % 2 != 0){
        out[index++] = list->value;
        printf("%d\n", out[index-1]);
        count++;
      }
      list = list->next;
    }
      if(count == 1){
      out[1] = 0;
      }
      if(count == 0){
      out[0] = 0;
      out[1] = 0;
      }
    return count;
    */
    int count = 0;
    int index = 0;
    if(list == NULL) return 0;
    while(list != NULL && count < 2){
      if(list->value % 2 != NULL && count < 2){
        out[index++] = list->value;
        count++;
      }
    }
    if(count == 0){
      out[0] = 0;
      out[1] = 0;
    }
    if(count == 1){
      out[1] = 0;
    }
    return count;
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void test(void) {
	// list: [7, 4, 1, 34, 56]
	size_t len;
    char* buf;
    FILE* f;
	
	Node* list = new_node(7, new_node(4, new_node(1,new_node(34, new_node(56, NULL)))));
	Node* a = jump_list(list, 0); // [7, 4, 1, 34, 56]
	Node* b = jump_list(list, 1); // [7, 1, 56]
	Node* c = jump_list(list, 2); // [7, 34]
	Node* d = jump_list(list, 3); // [7, 56]
	Node* e = jump_list(list, 9); // [7]
	
	f = open_memstream(&buf, &len);
    fprint_list(f, a);
    fclose(f);
    test_equal_s(buf, "[7, 4, 1, 34, 56] ");
	
	f = open_memstream(&buf, &len);
    fprint_list(f, b);
    fclose(f);
    test_equal_s(buf, "[7, 1, 56] ");
	
	f = open_memstream(&buf, &len);
    fprint_list(f, c);
    fclose(f);
    test_equal_s(buf, "[7, 34] ");
	
	f = open_memstream(&buf, &len);
    fprint_list(f, d);
    fclose(f);
    test_equal_s(buf, "[7, 56] ");
	
	f = open_memstream(&buf, &len);
    fprint_list(f, e);
    fclose(f);
    test_equal_s(buf, "[7] ");
}

void test_first_odd_pair() {
    // Sample linked list: 1 -> 2 -> 3 -> 4 -> 5
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    int* out = xmalloc((2)*sizeof(int)); // Array to store output

    printf("Input linked list: ");
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");

    int result = first_odd_pair(head, out);
    if (result == 2) {
        printf("Two odd values found: %d and %d\n", out[0], out[1]);
    } else if (result == 1) {
        printf("Only one odd value found: %d and %d\n", out[0],out[1]);
    } else {
        printf("No odd values found\n");
    }

    //freeList(head); // Free memory
}

int main(void) {
	test();
	test_first_odd_pair();
	return 0;
}