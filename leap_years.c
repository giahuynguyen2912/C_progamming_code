#include "base.h"

const int LEAP_YEARS = 366;
const int NON_LEAP_YEARS = 365;

/*Return the number of days in the given year. The input represents any year as an integer, the
return value is the number of days.*/
int number_of_days(int year){
	int multiple_of_four = year % 4;    //Leap Years are any year that can be exactly divided by 4
	int multiple_of_hundred = year % 100; //except if it can be exactly divided by 100, then it isn't
	int multiple_of_fourhundred = year % 400; //except if it can be exactly divided by 400, then it is
	if((multiple_of_hundred == 0 && multiple_of_fourhundred != 0) || multiple_of_four != 0){
		return NON_LEAP_YEARS;
	}else{
		return LEAP_YEARS;
	}
}

void number_of_days_test(){
	test_equal_i(number_of_days(2000), LEAP_YEARS);
	test_equal_i(number_of_days(2100), NON_LEAP_YEARS);
	test_equal_i(number_of_days(2022), NON_LEAP_YEARS);
	test_equal_i(number_of_days(2016), LEAP_YEARS);
}
int main(void){
	number_of_days_test();
	return 0;
}