/*
Compile: make is_search_tree
Run: ./is_search_tree
Compile & run: make is_search_tree && ./is_search_tree
*/

#include "base.h"

typedef struct Node{
	int value;
	struct Node* left;
	struct Node* right;
}Node;

typedef struct List{
   int data;
   struct List* next;
}List;

Node* new_node(Node* left, int value, Node* right){
	Node* node = xmalloc(sizeof(Node));
	node->left = left;
	node->value = value;
	node->right = right;
	return node;
}

void free_node(Node * node){
	if(node){
		free_node(node->left);
		free_node(node->right);
		node->left = NULL;
		node->right = NULL;
		free(node);
	}
}

void print_node(Node* node) {
	if (node == NULL) {
		printf("E");
	} else {
		printf("Node(");
		print_node(node->left);
		printf(", %d, ", node->value);
		print_node(node->right);
		printf(")");
	}
}

int min_int(int a, int b){
	if(a < b){
		return a;
	}
	return b;
}

int max_int(int a, int b){
	if(a > b){
		return a;
	}
	return b;
}

int max_tree(Node* node){
    if(node){
      int max = node->value;
      if(node->left){
        max = max_int(max, max_tree(node->left));
      }
      if(node->right){
        max = max_int(max, max_tree(node->right));
      }
      return max;
    }
    return 0;

}

int min_tree(Node* node){
    if(node){
      int min = node->value;
      if(node->left){
        min = min_int(min, min_tree(node->left));
      }
      if(node->right){
        min = min_int(min, min_tree(node->right));
      }
      return min;
    }
    return 0;
}


bool is_search_tree_node(Node* node){
    Node* left = node->left;
   	Node* right = node->right;
    if(left){
    	if (left->value >= node->value) return false;
    	if (max_tree(left) >= node->value) return false;
    	if (!is_search_tree_node(left)) return false;
    }
    if (right){
    if (right->value <= node->value) return false;
    if (min_tree(right) <= node->value) return false;
    if (!is_search_tree_node(right)) return false;
    }
    return true;
}

int height_tree(Node* tree){
   if(tree == NULL){
     return 0;
   }else{
     if(tree-left == NULL && tree->right == NULL) return 0;
     int left = height_tree(tree->left);
     int right = height_tree(tree->right);
     return 1 + ((left > right)? left:right);
   }
}



bool checkParentChild (Node* node){
    bool res = false;
    if(node != NULL){
      if(node->left != NULL && node->right != NULL){
         if(node->left->value == node->value || node->right->value == node->value){
           res = true;
         }
      }
    }
    return res;
}

void new_list_node(int data, List* next){
     List* list_node = xmalloc(sizeof(List));
     list_node->data = data;
     list_node->next = next;
}

List* treeToList(Node* Tree, List* list){
     if(Tree == NULL){
       return list;
     }
     list =treeToList(Tree->left, list); 
     temp->data = Tree->value;
     temp->next = *list;
     *list = temp;
     treeToList(Tree->right, list);
     return *list;
}

Node* insert_odered_node(Node* tree, int value){
   if(tree == NULL){
     tree = new_node(NULL, value, NULL);
   }else if(value < tree->value){
     tree->left = insert_odered_node(tree->left, value);
   }else if(value > tree->value){
     tree->right = insert_odered_node(tree->right, value);
   }
   return tree;
}

bool trees_equal(Node* t1, Node* t2){
    if(t1 == t2) return true;
    if(t1 == NULL || t2 == NULL) return false;
    if(t1->value != t2->value) return false;
    return trees_equal(t1->left, t2->left) && trees_equal(t1->right, t2->right);
}

bool tree_contain(Node* tree, int val){
    if(tree == NULL) return false;
    if(tree->value == val) return true;
    else return tree_contain(tree->left) || tree_contain(tree->right);
}

bool tree_contain_check(Node* tree, int x){
    if(tree == NULL) return false;
    else return (tree->value == x) ||
    tree_contain_check(tree->left) ||
    tree_contain_check(tree->right);
}

bool mono_tree(Node* tree){
    Node* left = tree->left;
    Node* right = tree->right;
    if(tree == NULL){
      return true;
    }else{
      if(left != NULL || right != NULL){
        if(left->value > tree->value || right->value > tree->value) return false;
      }
    }
    return true;
}

Node* copy_tree_node(Node* tree){
    if(tree == NULL) return NULL;
    else return new_node(copy_tree_node(tree->left), tree->value, copy_tree_node(tree->right));
}

typedef struct{
	Node* root;
}Tree;

Tree* new_tree(Node* root){
	Tree* tree = xmalloc(sizeof(Tree));
	tree->root = root;
	return tree;
}

void free_tree(Tree* tree){
	if(tree){
		free_node(tree->root);
		tree->root = NULL;
		free(tree);
	}
}

void print_tree(Tree* tree){
	printf("Tree: ");
	if(tree)
		print_node(tree->root);
	printf("\n");
}


/** Returns true if this is a search tree. Returns false otherwise.
  * May need a helper method. */
bool is_search_tree(Tree* tree) {
	//return tree->root == NULL ? true : is_search_tree_node(tree->root);
	if(tree->root == NULL){
	  return true;
	}else{
	  if(is_search_tree_node(tree->root)){
	    return true;
	  }
	}
	return false;
}


void test() {
	Tree* t = new_tree(NULL);
	test_equal_b(is_search_tree(t), true);
	free_tree(t);
		
	t = new_tree(new_node(NULL, 100, NULL));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);
	
	t = new_tree(new_node(new_node(NULL, 99, NULL), 100, new_node(NULL, 101, NULL)));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);
	
	t = new_tree(new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 99, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
		
	t = new_tree(new_node(new_node(NULL, 101, NULL), 100, new_node(NULL, 199, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
	
	t = new_tree(new_node(new_node(new_node(NULL, 6, NULL), 7, new_node(NULL, 9, NULL)), 8, NULL));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
	
	t = new_tree(new_node(new_node(NULL, 11, NULL), 100, new_node(NULL, 99, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
	
	t = new_tree(new_node(new_node(new_node(NULL, 25, NULL), 50, new_node(NULL,75, NULL)), 100, new_node(new_node(NULL,125, NULL), 150, new_node(NULL, 175, NULL))));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

	t = new_tree(new_node(new_node(new_node(NULL, 55, NULL), 50, new_node(NULL, 75, NULL)), 100, new_node(new_node(NULL, 125, NULL), 150, new_node(NULL, 175, NULL))));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
		
	t = new_tree(new_node(NULL, 101, new_node(NULL, 100, NULL)));
	test_equal_b(is_search_tree(t), false);
	free_tree(t);
		
	t = new_tree(new_node(new_node(NULL, 50, NULL), 100, NULL));
	test_equal_b(is_search_tree(t), true);
	free_tree(t);

}
	
			
int main(void) {
	report_memory_leaks(true);
	test();
	return 0;
}
