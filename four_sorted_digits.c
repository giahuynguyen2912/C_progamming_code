/*
Compile: make four_sorted_digits
Run: ./four_sorted_digits
Compile and run:
make four_sorted_digits && ./four_sorted_digits
*/

#include "base.h"
#include "string.h"

/* 
Returns true if s contains at least 4 incrementing digits right behind one another. Else it returns false.
*/ 
bool four_sorted_digits(String s) {
     /*int count = 0;
     bool res = false;
     if(strlen(s) <= 3){
        return false;
     }
     for(int i = 0; i<strlen(s); i++){
         if(s[i] >= '0' && s[i] <= '9'){
         count++;
         }
     }
     if(count <= 3){
        return false;
     }
     for(int i = 0; i < strlen(s)-1; i++){
        for(int j = i+1; j < strlen(s); j++){
           if(s[i] >= '0' && s[i] <= '9' && s[j] >= '0' && s[j] <= '9'){
             if(s[j] >= s[i]){
              res = true;
             }else{return false;}
           }else{ i++;}
        }
     }
     return res;*/
    /* int len = strlen(s);
     int count = 0;
     int min = -1;
     int num = 0;
     if(len < 3){
       return false;
     }else{
        for(int i = 0; i < len; i++){
           if(s[i] >= '0' && s[i] <= '9'){
             num = s[i];
             if(num >= min){
               min = num;
               count++;
             }else{
               min = -1;
               count--;
             }
             if(count > 3) return true;
           }else{
             count = 0;
             min = -1;

           }
        }
     }
     return false;*/
     int count = 0;
     int num = 0;
     int min = -1;
     if(strlen(s) < 3){return false;}
     for(int i = 0; i < strlen(s); i++){
        if(s[i] >= '0' && s[i] <= '9'){
          num = s[i];
          if(num >= min){
            min = num;
            count++;
          }else{
            min = -1;
            count--;
          }
          if(count >3) return true;
        }else{
        count = 0;
        min = -1;
        }
     }
     return false;
}

bool is_alphabet(char t){
   if((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z')){
   return true;
   }
   return false;
}

bool is_digits(char t){
   if(t >= '0' && t <= '9'){
     return true;
   }
   return false;
}

String compress(String s){
    int len = strlen(s);
    int count = 1;
    int index = 0;
    char* res = xmalloc(len*2*sizeof(char));
    for(int i = 0; i < len; i++){
       if(s[i] == s[i+1]){
         count++;
       }else{
       if(count == 1){
         res[index++] = s[i];
       }else{
         res[index++] = count + '0';
         res[index++] = s[i];
         count = 1;
         }
       }
    }
    res[index] = '\0';
    return res;
}

String decompress(String s){
  if(strlen(s) == 0){
    return s;
  }
  int count_num = 0;
  int count_alp = 0;
  int sum_len = 0;
  for(int i = 0; i < strlen(s); i++){
     if(is_alphabet(s[i])){
       count_alp++;
     }else if(is_digits(s[i])){
       count_num = count_num + s[i] - '0' - 1;
     }
     if(s[i] == ' '){
       sum_len++;
     }
  }
  sum_len = sum_len + count_num + count_alp;
  char* res = xmalloc((sum_len +1)* sizeof(char));
  int count = 0;
  int index = 0;
  char current;
  for(int i = 0; i < strlen(s); i++){
     if(is_alphabet(s[i]) || s[i] == ' '){
       res[index++] = s[i];
     }
     if(is_digits(s[i])){
       count = s[i] - '0';
       count = count - 1;
       current = s[i+1];
       while(count != 0){
         res[index++] = current;
         count--;
       }
     }
  }
  res[sum_len] = '\0';
  return res;
}



void four_sorted_digits_test(void) {
    test_equal_i(four_sorted_digits(""), false);
    test_equal_i(four_sorted_digits("123"), false);
    test_equal_i(four_sorted_digits("abcd"), false);
    test_equal_i(four_sorted_digits("1234"), true);
    test_equal_i(four_sorted_digits("12342"), true);
    test_equal_i(four_sorted_digits("2479"), true);
    test_equal_i(four_sorted_digits("1111"), true);
    test_equal_i(four_sorted_digits("a123"), false);
    test_equal_i(four_sorted_digits("123a"), false);
    test_equal_i(four_sorted_digits("1234a"), true);
    test_equal_i(four_sorted_digits("1294a"), false);
    test_equal_i(four_sorted_digits("xx1234y"), true);
    test_equal_i(four_sorted_digits("abc12145"), false);
    test_equal_i(four_sorted_digits("a 1 2 3 4 c"), false);
    test_equal_i(four_sorted_digits("a 3333 c"), true);
    test_equal_s(decompress(""), "");
            test_equal_s(decompress("Sample String"), "Sample String");
            test_equal_s(decompress("He2lo World"), "Hello World");
            test_equal_s(decompress("4A4B4C"), "AAAABBBBCCCC");
            test_equal_s(decompress("9A3A"), "AAAAAAAAAAAA");
            test_equal_s(decompress("B9A3AB"), "BAAAAAAAAAAAAB");
            test_equal_s(decompress("B9A3A9BB"), "BAAAAAAAAAAAABBBBBBBBBB");
            test_equal_s(decompress("9AA"), "AAAAAAAAAA");
            test_equal_s(decompress("3F3d6B3eE2e"), "FFFdddBBBBBBeeeEee");
            test_equal_s(compress("BBAAAABCC"),"2B4AB2C");
            test_equal_s(compress("BBCAAABCC"),"2BC3AB2C");
            test_equal_s(compress("CCAABCC"),"2C2AB2C");
}

int main(void) {
    //report_memory_leaks(true);
    four_sorted_digits_test();
    return 0;
}
