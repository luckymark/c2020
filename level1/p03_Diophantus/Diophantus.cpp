#include<stdio.h>

int main(){
	float age;
	for(age = 10; age <= 1000000; age++){
		float son = age - 4 - (age/6 + age/12 + age/7 + 5) + 1;		// The year when his son passed away still counts a year in age;		 
		if(son == (age - 4)/2)
			printf("%.0f\n", age-4);
	}
	return 0;
}
