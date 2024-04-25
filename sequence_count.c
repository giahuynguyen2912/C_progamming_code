/*
Compile: make sequence_count
Run: ./sequence_count
make sequence_count && ./sequence_count
*/

#include "base.h"
#include "string.h"

/**
(a) Todo: Implement.
Returns number of positions at which t occurs in s.
*/
int sequence_count(String s, String t) {
    // ... s_length(s) ... s[i]
    int count = 0;
    int s_length = strlen(s);
    int t_length = strlen(t);
    /*int index_s = 0;
    int res = 0;
    if(t_length == 1){
      for(int i = 0; i < s_length; i++){
               if(t[0] == s[i]){
                  count++;
               }
       }
    }else if(t_length >1){
        while(index_s < s_length){
          if(t[0] == s[index_s]){
             res++;
             for(int i = 1; i < t_length; i++){
                 for(int j = index_s; j < s_length; j++){
                     if(t[i] == s[j]){
                        res++;
                     }
                     if(res == t_length){
                        res = 0;
                        count++;
                        break;
                     }
                 }
             }
          }
          index_s++;
       }
    }*/
    for(int i = 0; i < s_length; i++ ){
       int j = 0;
       for(j = 0; j < t_length; j++){
          if(s[i+j] != t[j]){
            break;
          }
       }
       if(j == t_length) count++;
    }
    return count;
}

/**
(b) Todo: Fix the bug.
Returns true if (and only if) the parentheses in s match and form a 
correctly parenthesized expression. The function just checks the 
parentheses and ignores any other characters.
*/
bool parentheses_correct(String s) {
    int n = s_length(s);
    int p = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') p++;
        if (s[i] == ')') p--;
        if(s[0] == ')') return false;
    }
    return p == 0;
}

String string_replace(char* s, char* t, char* change){
   int len_s = strlen(s);
   int len_t = strlen(t);
   int len_change = strlen(change);
   int index = 0;
   bool check;
   char* res = xmalloc((len_s - len_t + len_change+1)*sizeof(char));
   for(int i = 0; i < len_s; i++){
      int j = 0;
      for(j = 0; j < len_t; j++){
         if(s[i+j] != t[j]){
           check = false;
           break;
         }
      }
      if(j == len_t){
        check = true;
      }
      if(check == false){
        res[index++] = s[i];
      }
      if(check == true){
        i += j-1;
        for(int k = 0; k < len_change; k++){
           res[index++] = change[k];
        }
        check = false;
      }
   }
   res[index] = '\0';
   return res;
}

String encode(char* s){
   char* res = xmalloc((strlen(s)+1)*sizeof(char));
   int index = 0;
   for(int i = 0; i < strlen(s); i++){
      if(s[i] >= 'a' && s[i] <= 'z'){
        res[index++] = (s[i] - 'a' + 5) % 26 + 'a';
      }else if(s[i] >= 'A' && s[i] <= 'Z'){
        res[index++] = (s[i] - 'A' + 5) % 26 + 'A';
      }else{
        res[index++] = s[i];
      }
   }
   res[index] = '\0';
   return res;
}

void test(void) {
    // (a)
    test_equal_i(sequence_count("hello world", "l"), 3);
    test_equal_i(sequence_count("hello world", "w"), 1);
    test_equal_i(sequence_count("hello worlld", "ll"), 2);
    test_equal_i(sequence_count("hello world  ", " "), 3);
    test_equal_i(sequence_count("hello world hello", "hello"), 2);
    test_equal_i(sequence_count("hello world", "not"), 0);
    test_equal_i(sequence_count("hello world", "not in there..."), 0);
    test_equal_i(sequence_count("...", "..."), 1);
    test_equal_i(sequence_count("....", "..."), 2);
    test_equal_i(sequence_count(".....", "..."), 3);
    
    // (b)
    test_equal_i(parentheses_correct("(3"), false);
    test_equal_i(parentheses_correct("3)"), false);
    test_equal_i(parentheses_correct(")3("), false);
    test_equal_i(parentheses_correct("(3)"), true);
    test_equal_i(parentheses_correct("((3))"), true);
    test_equal_i(parentheses_correct("((3)"), false);
    test_equal_i(parentheses_correct("((3)))"), false);
    test_equal_i(parentheses_correct("()((3))"), true);
    test_equal_i(parentheses_correct("(1)+(2)"), true);
    test_equal_i(parentheses_correct(""), true);

    // (c)
    test_equal_s(string_replace("hello world", "world", "Huy"), "hello Huy");
    test_equal_s(string_replace("hello world","hello" ,"bye"), "bye world");
    test_equal_s(string_replace("hate you Mom", "hate", "love"), "love you Mom");

    //(d)
}

int main(void) {
    test();
    return 0;
}
