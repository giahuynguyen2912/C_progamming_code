/*
Compile: make primes
Run: ./primes
make primes && ./primes
*/

#include "base.h" //include prog1lib  
/*
    Prints the primes in the given interval [lower, upper)].
*/
int print_primes_in_intervall(int lower, int upper){
    int prime = lower;
    if( upper > lower){       
        if(prime < 2) 
            prime = 2;;
        }
        int count = 0;
        while (prime < upper){  
            int i = 2;
            bool is_a_prime = true;
            while(i <= (prime >> 1)){
                    if( prime % i == 0 ){
                    is_a_prime = false;
                    break;
                }
                i++;
            }
            if(is_a_prime){
                count++;
                printf("Die %2d. Primzahl im Intervall: [%d,%d)] ist: %2d\n", count, lower, upper, prime);
			}
            prime++;
        }
    return count;   
}

void test_print_primes_in_intervall(){
    test_equal_i(print_primes_in_intervall(0, 10), 4);
    test_equal_i(print_primes_in_intervall(10, 20), 4);
    test_equal_i(print_primes_in_intervall(20, 30), 2);
    test_equal_i(print_primes_in_intervall(600, 700), 16);
    test_equal_i(print_primes_in_intervall(-10, 0), 0);
    test_equal_i(print_primes_in_intervall(50, 100), 10);
    test_equal_i(print_primes_in_intervall(50, 50), 0);
    test_equal_i(print_primes_in_intervall(80, 50), 0);
}

int main(void){
    test_print_primes_in_intervall();
    return 0;
}


/*
primes.c:7:10: fatal error: Bas.eh: No such file or directory
    7 | #include "Bas.eh" //include prog1lib
      |          ^~~~~~~~
Fehlermeldung: Die Datei oder das Verzeichnis nicht finden.
Problem: Die Bibliothek wurde falsch bennent. 

***********

primes.c:19:16: error: ‘prime’ undeclared (first use in this function)
   19 |         while (prime < upper){
      |                ^~~~~
Fehlermeldung: Die Variable "prime" ist noch nicht deklariert.
Problem: Der Compiler kann die Variable "prime" nicht finden.

***********

primes.c:21:13: error: expected ‘,’ or ‘;’ before ‘_Bool’
   21 |             bool is_a_prime = true;
      |             ^~~~
Fehlermeldung: ein Semikolon order ein Komma wird vor 'bool' erwartet.
Problem: es fehlt hinter "int i = 2" ein Simikolon.

***********

primes.c:23:35: error: lvalue required as left operand of assignment
   23 |                     if( prime % i = 0 ){
      |                                   ^
Fehlermeldung: L-Wert als linker Operand der Zuweisung erforderlich.
Problem: falsches Operand verwenden.

***********

primes.c:29:13: warning: this ‘if’ clause does not guard... [-Wmisleading-indentation]
   29 |             if(is_a_prime)
      |             ^~
Fehlermeldung:Die if-Anweisung schützt den darunter liegenden Codeblock 
möglicherweise nicht ordnungsgemäß.
Problem: Der if-Befehl fehlt die Klammern.

***********

primes.c:37:1: error: expected identifier or ‘(’ before ‘}’ token
   37 | }
      | ^
Fehlermeldung: erwarteter Bezeichner oder „(“ vor „}“-Token.
Problem: Es gibt eine überflüssige Klammer.
*/