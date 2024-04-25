/*
Compile: make palindrome
Run: ./palindrome
make palindrome && ./palindrome
*/

#include "base.h"

/**
(a) Todo: Implement.
Return whether a character is in the alphabet
*/
bool is_in_alphabet(char c) {
    
    // TODO implement
    if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
       return true;
    }
    return false;
}

/**
(b) Todo: Implement.
Return whether a String is a palindrome
*/
bool is_palindrome(char* s) {
    
    // TODO implement
   /*int n = strlen(s);
    int a = 0;
    for(int i = 0; i < n ; i++){
       if(!is_in_alphabet(s[i])){
         a++;
       }
    }
    if(n == 0){
      return false;
    }
    char* res = xmalloc((n-a+1) * sizeof(char));
    int i = 0;
    int j = 0;
    while(i<n && j < n-a){
         if(is_in_alphabet(s[i])){
           res[j] = s[i];
           j++;
         }
         i++;
    }
    res[n-a] = '\0';
    int low = 0;
    int high = strlen(res)-1;
    while(high > low){
         if(res[low++] != res[high--]){
            return false;
         }else{
           return true;
         }
    }
    return false;
*/
   int len = strlen(s);
   int low = 0;
   int high = len-1;
   if(len == 0) return false;
   while(high > low){
       while(!is_in_alphabet(s[high]) && high > 0){ high--;}
       while(!is_in_alphabet(s[low]) && low < len-1){low++;}
       if(s[high] != s[low]) return false;
       high--;
       low++;
   }
   return true;
}

/**
(c) Todo: Implement.
Return whether a String contains at least one palindrome of minimum size minimum_palindrome_size
*/
bool contains_palindrome(char* s, int minimum_palindrome_size) {
    int len = strlen(s);
    for(int check = minimum_palindrome_size; check <= len; check++){
       char* temp =  xmalloc((check+1) * sizeof(char));
       int count = 0;
       while(count <= len - check){
          int i = count;
          int index = 0;
          while(index < check){
            temp[index++] = s[i++];
          }
          temp[index] = '\0';
          if(is_palindrome(temp)) return true;
          count++;
       }
    }
    return false;
}




void test(void) {
    // (a)
    test_equal_b(is_in_alphabet('a'), true);
    test_equal_b(is_in_alphabet('y'), true);
    test_equal_b(is_in_alphabet('B'), true);
    test_equal_b(is_in_alphabet('X'), true);
    test_equal_b(is_in_alphabet(' '), false);
    test_equal_b(is_in_alphabet('.'), false);
    test_equal_b(is_in_alphabet('{'), false);
    
    // (b)
    test_equal_b(is_palindrome("hello world"), false);
    test_equal_b(is_palindrome("anna"), true);
    test_equal_b(is_palindrome(""), false);
    test_equal_b(is_palindrome("shower."), false);
    test_equal_b(is_palindrome("madam ?"), true);
    test_equal_b(is_palindrome("nurses run"), true);
    test_equal_b(is_palindrome("abbba"), true);

    // (c)
    test_equal_b(contains_palindrome("hello world", 5), false);
    test_equal_b(contains_palindrome("hello world", 3), true);
    test_equal_b(contains_palindrome("anna", 3), true);
    test_equal_b(contains_palindrome("", 0), false);
    test_equal_b(contains_palindrome("shower thoughts by madam anna", 4), true);
    test_equal_b(contains_palindrome("madam anna is a nurse", 3), true);
    test_equal_b(contains_palindrome("nurses run", 4), true);
}

int main(void) {
    test();
    return 0;
}
