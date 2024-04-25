// Es bestand darin, die Summe eines Arrays zu bilden, das ganze Zahlen, aber auch andere Arrays enthielt, also rekursiv ist. 

// make array_sum && ./array_sum

#include "base.h"
#define MAX_LENGTH 10

typedef enum Type {
	TInt,
	TArray,
} Type;

typedef struct Item {
	Type type;
	union {
		int value;
		struct Array *array;
	};
} Item;

typedef struct Array {
	Item* items;
	int length;
} Array;

Item* make_item(Type type, int value, Array* array) {
	Item *item = (Item *) xmalloc(sizeof(Item));
	item->type = type;
	switch (type) {
		case TInt:
			item->value = value;
			break;
			
		case TArray:
			item->array = array;
			break;

		default:
			break;
	}
	return item;
}

Array* make_array(void) {
	Array *array = (Array *) xmalloc(sizeof(Array));
	array->length = 0;
	array->items = (Item *) xcalloc(MAX_LENGTH, sizeof(Item));
	return array;
}

void add_to_array(Array* array, Item* item) {
	require_not_null(array);
	require("Array not full", array->length < MAX_LENGTH);
	array->items[array->length++] = *item;
	return;
}

int sum_array(Array* array) {
	// todo: implement
	/*int sum = 0;
	if(array == NULL){
	return 0;
	}
	for(int i = 0; i < array->length; i++){
	   if(array->items[i].type == TInt){
	     sum += array->items[i].value;
	   }else{
	     sum += sum_array(array->items[i].array);
	   }
	}
	return sum;
	*/
	int sum = 0;
	if(array == NULL) return 0;
	for(int i = 0; i < array->length; i++){
	   if(array->items[i].type == TInt){
	     sum += array->items[i].value;
	   }else if(array->items[i].type == TArray){
	     sum += sum_array(array->items[i].array);
	   }
	}
	return sum;
}

void test(void) {
	Array *array = make_array();

	test_equal_i(sum_array(array), 0);

	add_to_array(array, make_item(TInt, 1, NULL));
	add_to_array(array, make_item(TInt, 2, NULL));
	add_to_array(array, make_item(TInt, 3, NULL));
	add_to_array(array, make_item(TInt, 4, NULL));

	test_equal_i(sum_array(array), 10);

	Array *array2 = make_array();
	add_to_array(array2, make_item(TInt, 0, NULL));
	add_to_array(array2, make_item(TInt, -1, NULL));
	add_to_array(array2, make_item(TInt, 2, NULL));
	add_to_array(array2, make_item(TInt, -3, NULL));

	test_equal_i(sum_array(array2), -2);

	add_to_array(array, make_item(TArray, 0, array2));

	test_equal_i(sum_array(array), 8);
}	

int main(void) {
	test();
	return 0;
}