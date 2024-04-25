/*
Compile: make title_case
Run: ./title_case
Compile & run: make title_case && ./title_case
*/

#include "base.h"

char* title_case(char* s) {
	// TODO
	/*int len_s = strlen(s);
	char* res = xmalloc(sizeof(len_s+1));
	bool top = true;
	for(int i = 0; i < len_s; i++){
	   if(top == true){
	     res[i] = toupper(s[i]);
	     top = false;
	   }else{
	     res[i] = tolower(s[i]);
	     if(s[i] == ' '){
	      top = true;
	     }
	   }
	}
	res[len_s] = '\0';
	return res;
	*/
	/*int len = strlen(s);
	char* res = xmalloc((len+1) * sizeof(char));
	bool check = true;
	int index = 0;
	for(int i = 0; i < len; i++){
	   if(check == true){
	      res[index++] = toupper(s[i]);
	      check = false;
	   }else{
	     res[index++] = tolower(s[i]);
	     if(s[i] == ' '){
	       check = true;
	     }
	   }
	}
	res[index] = '\0';
	return res;
	*/
	int len = strlen(s);
	char* res = xmalloc((len+1)* sizeof(char));
	bool check = true;
	int index = 0;
	for(int i = 0; i < len ; i++){
	   if(check == true){
	     res[index++] = toupper(s[i]);
	     check = false;
	   }else{
	     res[index++] = tolower(s[i]);
	     if(s[i] == ' '){ check = true;}
	   }
	}
	res[index] = '\0';
	return res;
}

void test(void) {
	test_equal_s(title_case("test"), "Test");
	test_equal_s(title_case("TEST"), "Test");
	test_equal_s(title_case("HOW can I convert a mixeD CASE string"), "How Can I Convert A Mixed Case String");
	test_equal_s(title_case("Switching elemENT SIZE checking for"), "Switching Element Size Checking For");
}

int main(void) {
	test();
	return 0;
}
