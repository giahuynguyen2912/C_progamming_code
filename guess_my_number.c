#include "base.h"

int main(void){	
	int rand = i_rnd(101);
	printsln("Guess my Number!");
	
	for(int i = 0; i < 100; i++){
		int guess = i_input();
		if(guess < rand){
			printsln("Too Small!");
		}else if(guess > rand){
			printsln("Too Large!");
		}else{
			printsln("Match!");
			break;
		}
	}
	return 0;
}