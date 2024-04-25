/*
 * Compile:         make X
 * Run:             ./X
 * Compile and Run: make X && ./X
 */
#include "base.h" // prog1lib

// todo: define constants
const int ONE_UNIT_COST = 100;
const int TEN_UNIT = 10;
const int TEN_UNIT_COST = 90;
const int FIFTY_UNIT = 50;
const int FIFTY_UNIT_COST = 75;
const int DELIVERY_COST = 500;
const int LIMIT_COST = 2000;
// todo: write function price
int price(int amount){
	int total;
	if(amount <= 0){
		total = 0;
	}else if(amount > 0 && amount < TEN_UNIT){
		total = amount * ONE_UNIT_COST + DELIVERY_COST;
	}
	if(amount >= TEN_UNIT){
		total = amount * TEN_UNIT_COST;
			if(total < LIMIT_COST){
				total = amount * TEN_UNIT_COST + DELIVERY_COST;
			}
	}
	if(amount >= FIFTY_UNIT){
		total = amount * FIFTY_UNIT_COST;
	}	
	return total;
}
// todo: write function price_test
// test returned values of price using test_equal_i
void price_test(){
	test_equal_i(price(-5), 0);
	test_equal_i(price(5), 1000);
	test_equal_i(price(10), 1400);
	test_equal_i(price(20), 2300);
	test_equal_i(price(22), 2480);
	test_equal_i(price(35), 3150);
	test_equal_i(price(55), 4125);
	test_equal_i(price(23),2070);
}

int main(void) {
    // todo: call price_test function
	price_test();
    return 0;
}
