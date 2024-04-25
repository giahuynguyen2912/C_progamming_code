/*
Compile: make spacecrafts
Run: ./spacecrafts
Compile & run: make spacecrafts && ./spacecrafts
*/

#include "base.h"

#define N 5

// struct of a spacecraft
typedef struct Spacecraft{
    char* name;
    int passengers;
    double reach;
    double load_capacity;
}Spacecraft;

// struct of the fleet.
typedef struct Fleet{
    Spacecraft** ships;
    int maximum_count; //initialize to N, size of ships
    int current_count; //current count of spacecrafts in ships
}Fleet;
    

// returns a pointer to a dynamically allocated ship
Spacecraft* new_spacecraft(int passengers, double reach, double load_capacity, char* name){
    Spacecraft *spc = xmalloc(sizeof(Spacecraft));
    spc->passengers = passengers;
    spc->reach = reach;
    spc->load_capacity = load_capacity;
    spc->name = s_copy(name);
    return spc;
}

// prints a spacecraft
void print_spacecraft(Spacecraft* spc){
    printf("%12s with %3d passengers, a reach of %8.1f au and a load capacity of %4.1f t\n", spc->name, spc->passengers, spc->reach, spc->load_capacity);
}

String s_sub(String s, int i, int j) {
    require_not_null(s);
    int n = strlen(s);
    if (i < 0) i = 0;
    if (j > n) j = n;
    if (i >= j || i >= n || j <= 0) {
        char *a = xmalloc(1 * sizeof(char));
        a[0] = '\0';
        return a;
    }
    // assert i < j && i < n && j > 0
    n = j - i;
    char *a = xmalloc((n + 1) * sizeof(char));
    memcpy(a, s + i, n * sizeof(char));
    a[n] = '\0';
    return a;
}

char* skip_token(char* s){
    while (*s != ' ' && *s != '\n') s++;
    return s;
}

char* get_name(char* s, char* s2 ){

    char* token = xmalloc(s - s2 + 1);
    int i = 0;
        while (s2 < s){
            token[i] = *s2;
            i++;
            s2++;
        }
        token[i]= '\0';
    char* n = token;
    return n;
}

int get_passengers(char* s, char* s2 ){
    int h = 0;
    char* token = xmalloc(s - s2 + 1);
    int i = 0;
        while (s2 < s){
            token[i] = *s2;
            i++;
            s2++;
        }
        token[i]= '\0';
    h = i_of_s(token);
    free(token);
    return h;
}

double get_prl(char* s, char* s2 ){
    double h = 0;
    char* token = xmalloc(s - s2 + 1);
    int i = 0;
        while (s2 < s){
            token[i] = *s2;
            i++;
            s2++;
        }
        token[i]= '\0';
    h = d_of_s(token);
    free(token);
    return h;
}

char* skip_space(char *s){
    while (*s == ' ') s++;
    return s;
}

// imports spacecrafts from file.
Fleet* read_spacecrafts(char* file_name){
    char* s1 = s_read_file(file_name);
    char* s = s1;
    char* start = s;
    int ships = -1;
    while (*start != '\0'){
        if(*start  == '\n')
            ships++;
        start++;
    }
    
    Fleet *fleet = malloc(sizeof(Fleet));
    fleet->current_count = ships;
    fleet->maximum_count = N;
    fleet->ships = xcalloc(N, sizeof(Spacecraft));
    while(*s != '\0'){
    Spacecraft *spc = NULL;
        //skip 1st line
        while (*s != '\n') s++;
        s++;
        
        if(*s == '\0')
            break;
        
        char* s1 = s;
        s = skip_token(s);
        char* name = get_name(s, s1);
    
        s = skip_space(s);
        s1 = s;
        s = skip_token(s);
        double passengers = get_passengers(s, s1);

        s = skip_space(s);
        s1 = s;
        s = skip_token(s);
        double reach = get_prl(s, s1) ;
        
        s = skip_space(s);
        s1 = s;
        s = skip_token(s);
        double load_capacity = get_prl(s, s1);
        

        spc = new_spacecraft(passengers, reach, load_capacity, name);
        print_spacecraft(spc);
        fleet->ships[ships-1] = spc;
        free(name);
        
        ships--;
            
    }
    free(s1);
    return fleet;
}

// prints the fleet.
void print_spacecrafts(Fleet* f){
    for(int i = 0; i< f->maximum_count; i++){
        if(f->ships[i]){
            printf("%2d\t", i);
            Spacecraft* spc = f->ships[i];
            printf("%12s with %3d passengers, a reach of %8.1f au and a load capacity of %4.1f t\n", spc->name, spc->passengers, spc->reach, spc->load_capacity);
            
        }
    }
}

// Entry point with command line arguments.
int main(int argc, String argv[]) {
    base_init();
    //base_set_memory_check(true);
    report_memory_leaks(true);

    Fleet* fleet = NULL;

    if(argc > 1){
        fleet = read_spacecrafts(argv[1]);
    }else{
        fleet = read_spacecrafts("spacecrafts.txt");
    }

    char buffer[256];
    for(int i = 0; i< 256; i++){
        buffer[i] = '\0';
    }

    int c = '\0';
    printf("Your fleet: \n");
    print_spacecrafts(fleet);
    
    while((c = getchar()) != 'p'){
        if (c == 's'){
            //send out a ship, remove it from the fleet
            //example: s1
            //removes ship of index 1
            int index = getchar() - '0';
            if(index> fleet->current_count-1)
                printf("Raumschiff an solche Position nicht existiert.\n");
            else{
                free(fleet->ships[index]->name);
                free(fleet->ships[index]);
                for(int i=index;i<fleet->current_count;i++){
                    fleet->ships[i]=fleet->ships[i+1];
                }
            fleet->current_count--;
            }
        }else if (c == 'n'){
            //change name of ship
            //example: n1 Enterprise
            //renames ship at index 1 to Enterprise
            int index = getchar() - '0';
            getchar();
            int i = 0;
            while ((c = getchar()) != '\n'){
                buffer[i] = c;
                i++;
            }
            buffer[i] = '\0';
            free(fleet->ships[index]->name);
            fleet->ships[index]->name = s_copy(buffer);
        }else if (c == 'a'){
            //add ship
            //example: a Amagedon 34 500.3 2000.0
            getchar();
            int i = 0;
            while ((c = getchar()) != '\n'){
                buffer[i] = c;
                i++;
            }
            buffer[i] = '\0';
            
            char* name = NULL;
            i = 0;
            for(; i< s_length(buffer); i++){
                if(buffer[i] == ' '){
                    break;
                }
            }
            
            name = s_sub(buffer, 0, i);
            i++;
            int j = i;
            printf("Char: '%c'\n", buffer[j]);
            for(; j< s_length(buffer); j++){
                if(buffer[j] == ' '){
                    break;
                }
            }
            char* z=s_sub(buffer, i, j);
            printf("String: %s\n", z);
            free(z);
            char* f=s_sub(buffer, i, j);
            int passengers = i_of_s(f);
            free(f);
            i = j++;
            for(; j< s_length(buffer); j++){
                if(buffer[j] == ' '){
                    break;
                }
            }
            f = s_sub(buffer, i, j);
            double reach = d_of_s(f);
            free(f);
            
            i = j++;
            for(; j < s_length(buffer); j++){
                if(buffer[j] == ' '){
                    break;
                }
            }
            f=s_sub(buffer, i, j);
            double load_capacity =  d_of_s(f);
            free(f);
            
            Spacecraft* spc = new_spacecraft(passengers, reach, load_capacity, name);
            fleet->ships[fleet->current_count] = spc;
            free(name);
            fleet->current_count++;
            if(fleet->current_count >N){
                free(fleet->ships[fleet->current_count-1]->name);
                free(fleet->ships[fleet->current_count-1]);
                fleet->ships[fleet->current_count-1]=fleet->ships[fleet->current_count];
                fleet->current_count--;
                printf("Raumschiffe zur Flotte hat die maximale Kapizitaet erreicht.\n ");
                
            }
        }
        if(c == '\n'){
            printf("Your fleet: \n");
            print_spacecrafts(fleet);
        }
    }
    for(int i = 0;i < fleet->current_count;i++)
        free(fleet->ships[i]->name);
    for(int i = 0;i < fleet->current_count;i++)
        free(fleet->ships[i]);
    
    free(fleet->ships);
    return 0;
}
/*
 man kann ja thereotisch Hilfsfunktionen nutzen. Aber am besten nicht, da es viel mehr komplex macht.
 das Schiff wird nicht sinnvoll gelöst, sondern auf Null gesetzt und dann mit dem nachstehenden Schiff ersetzt wird.
 es ist nicht sichergestellt worden, dass nicht mehr Raumschiffe zur Flotte hinzugefügt werden
können als die maximale Kapazität N.
 das Proggram wird beendet.
 */

