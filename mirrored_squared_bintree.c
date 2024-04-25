/*
Compile: make mirrored_squared_bintree
Run: ./mirrored_squared_bintree
Compile & run: make mirrored_squared_bintree && ./mirrored_squared_bintree
*/

#include "base.h"

typedef struct Tree {
	int value;
	struct Tree* left;
	struct Tree* right;
} Tree;

Tree* node(Tree* left, int i, Tree* right) {
	Tree* t = xcalloc(1, sizeof(Tree));
	t->value = i;
	t->left = left;
	t->right = right;
	return t;
}

Tree* leaf(int i) {
	return node(NULL, i, NULL);
}

void fprint_tree(FILE* f, Tree* n) {
    if (n == NULL) {
        fprintf(f, "_");
    } else if (n->left == NULL && n->right == NULL) {
        fprintf(f, "(");
        fprintf(f, "%d", n->value);
        fprintf(f, ")");
    } else {
        fprintf(f, "(");
        fprint_tree(f, n->left);
        fprintf(f, ", ");
        fprintf(f, "%d", n->value);
        fprintf(f, ", ");
        fprint_tree(f, n->right);
        fprintf(f, ")");
    }
}

Tree* mirror_squared_bintree(Tree* t) {
	// TODO
	if(t == NULL) {
	return NULL;
	}else{
	return node(mirror_squared_bintree(t->right), t->value * t->value,mirror_squared_bintree(t->left));
	}

}

void test(void) {
	size_t len;
    char* buf;
    FILE* f;
	
	Tree* t = node(leaf(1), 2, leaf(3));
	Tree* m = mirror_squared_bintree(t); // m: ((9), 4, (1))
	f = open_memstream(&buf, &len);
    fprint_tree(f, m);
    fclose(f);
    test_equal_s(buf, "((9), 4, (1))");
	
	t = node(leaf(1), 2, node(leaf(4), 3, leaf(5)));
	m = mirror_squared_bintree(t); // m: (((25), 9, (16)), 4, (1))
	f = open_memstream(&buf, &len);
    fprint_tree(f, m);
    fclose(f);
    test_equal_s(buf, "(((25), 9, (16)), 4, (1))");
	
	t = node(leaf(1), 2, node(node(leaf(3), 4, node(leaf(5), 6, NULL)), 7, leaf(8)));
	m = mirror_squared_bintree(t); // m: (((64), 49, ((_, 36, (25)), 16, (9))), 4, (1))
	f = open_memstream(&buf, &len);
    fprint_tree(f, m);
    fclose(f);
    test_equal_s(buf, "(((64), 49, ((_, 36, (25)), 16, (9))), 4, (1))");
}

int main(void) {
	test();
	return 0;
}