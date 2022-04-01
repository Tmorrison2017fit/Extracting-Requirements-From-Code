#include <iostream>
#include <cmath>


using namespace std;


// Function declaration
int convert(long long);


/* 
Convert a binary value to decimal value using weird logic
*/
int main(){
	long long value;
	cout << "Enter a binary number: ";

	cin >> value;

	cout << value << " in binary = " << convert(value) << " in decimal" << endl; 
	return 0;
}

int convert(long long n){
	int dec = 0, i = 0, rem;

	while (n != 0){
		rem = n % 10;
		n /= 10;
		dec += rem * pow(2,i);
		++i;
	}

	return dec;
}