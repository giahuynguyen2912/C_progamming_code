// strings mit xmalloc kopieren über string laufen
// und alle lowercases in string direkt übergeben, leerzeichen auch, uppercases je nach position übergeben oder zu "_x" transformieren.
// die zusätzliche größenveränderung beim allocieren natürlich vorher beachten
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
bool is_letter(char current)
{
  bool result = false;
  if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z'))
  {
    result = true;
  }
  return result;
}
bool is_upper(char current)
{
  bool result = false;
  if (current >= 'A' && current <= 'Z')
  {
    result = true;
  }
  return result;
}
bool is_lower(char current)
{
  bool result = false;
  if (current >= 'a' && current <= 'z')
  {
    result = true;
  }
  return result;
}
char to_upper(char current)
{
  if (is_lower(current))
  {
    return toupper(current);
  }
  else
  {
    printf("char is not lower case\n");
    return -1;
  }
}
char to_lower(char current)
{
  if (is_upper(current))
  {
    return tolower(current);
  }
  else
  {
    printf("char is not upper case\n");
    return -1;
  }
}

char* camelCase(String s){
    int len = strlen(s);
    int count = 0;
    for(int i = 0; i < len; i++){
       if(i != 0 && is_upper(s[i])){
         count++;
       }
    }
    char* result = xmalloc((len+count+1) * sizeof(char));
    int index = 0;
    for(int i = 0; i < len ; i++){
      if(i == 0){
        result[index++] = s[i];
      }
      if(i != 0){
        if(s[i] == ' '){
          result[index++] = s[i];
          result[index++] = s[i+1];
          i+=2;
        }
        if(is_upper(s[i])){
          result[index++] = '_';
          result[index++] = tolower(s[i]);
        }else{
          result[index++] = tolower(s[i]);
        }
      }
    }
    result[index] = '\0';
    return result;
}

int main(){

  test_equal_s(camelCase("abcd"), "abcd");
  test_equal_s(camelCase("Abcd"), "Abcd");
  test_equal_s(camelCase("ABCD"), "A_b_c_d");
  test_equal_s(camelCase("ABCDEF"), "A_b_c_d_e_f");
  test_equal_s(camelCase("ABCD EF"), "A_b_c_d E_f");
  return 0;
}