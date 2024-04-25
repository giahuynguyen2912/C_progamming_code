#include "base.h"

// 1 lb = 0.45359237 kg

typedef enum unit_e {
    G,
    KG,
    T,
    LB
} Unit;

typedef struct weight_s {
    double amount;
    Unit unit;
} Weight;

Weight make_weight(double amount, Unit unit) {
    // todo
    Weight w = { amount, unit };
    return w;
}

bool test_within_weight(int line, Weight a, Weight e, double tolerance) {
    bool x = base_test_within_d(__FILE__, line, a.amount, e.amount, tolerance);
    bool u = base_test_equal_i(__FILE__, line, a.unit, e.unit);
    return x && u;
}

void print_weight(Weight w) {
    // todo
    switch(w.unit) {
        case G :
            printf("%4.0f G\n", w.amount);
            break;
        case KG :
            printf("%.3f KG\n", w.amount);
            break;
        case T :
            printf("%.3f T\n", w.amount);
            break;
        case LB :
            printf("%.2f LB\n", w.amount);
            break;
        default:
            printf("0.0");
            break;
    }
}

void print_weight_test() {
    print_weight(make_weight(1234, G));
    print_weight(make_weight(4.749, KG));
    print_weight(make_weight(3.1001, T));
    print_weight(make_weight(5.40006, LB));
}

// Weight, Unit -> Weight
// Convert weight to the given target unit.
Weight to_unit(Weight w, Unit target_unit) {
    // todo
    double x;
    switch(w.unit){
        case KG :           //Umrechnung nack KG
            x = w.amount;
            break;
        case T :
            x = w.amount * 1000;
            break;
        case LB :
            x = w.amount * 0.45359237;
            break;
        case G :
            x = w.amount / 1000;
            break;
        default:
            break;
    }
    switch(target_unit){
        case KG :
            x = x*1;
            break;
        case T :
            x = x / 1000;
            break;
        case LB :
            x = x / 0.45359237;
            break;
        case G :
            x = x * 1000;
            break;
        default:
            break;
    }
    return make_weight(x, target_unit);
}

void to_unit_test(void) {
    test_within_weight(__LINE__, to_unit(make_weight(1000, G), KG), make_weight(1, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(25000, LB), G), make_weight(11339809.25, G), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(5.8, T), KG), make_weight(5800, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(75800, G), KG), make_weight(75.8, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(1000, LB), KG), make_weight(453.59237, KG), 1e-6);
    test_within_weight(__LINE__, to_unit(make_weight(670, T), LB), make_weight(1477097.157, LB), 1e-3);
    // todo: add tests (at least 5)
}

// Weight, Weight -> int
// Compares two weights. Returns 0 if the two weights are equal,
// -1 if w is smaller than v and +1 otherwise.
int compare(Weight w, Weight v) {
    // todo
    Weight a = to_unit(   w, KG);
    Weight b = to_unit(   v, KG);
    if(a.amount == b.amount){
        return 0;
    }else if(a.amount < b.amount){
        return -1;
    }else{
        return 1;
    }
}

void compare_test(void) {
    test_equal_i(compare(make_weight(1000, G), make_weight(1, KG)), 0);
    test_equal_i(compare(make_weight(700, LB), make_weight(317.514659, KG)), 0);
    test_equal_i(compare(make_weight(870, KG), make_weight(1, T)), -1);
    test_equal_i(compare(make_weight(300, LB), make_weight(137000, G)), -1);
    test_equal_i(compare(make_weight(80, KG), make_weight(80, G)), 1);
    test_equal_i(compare(make_weight(1200, T), make_weight(10000000000, LB)), -1);
    // todo: add tests (at least 5)
}

int main(void) {
    print_weight_test();
    to_unit_test();
    compare_test();
    return 0;
}
