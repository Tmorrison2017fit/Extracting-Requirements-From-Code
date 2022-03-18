#include <iostream>

using namespace std;

int main(void){
	int firstValue = 5, secondValue = 15;

	int *pointer1, *pointer2;

	pointer1 = &firstValue;				//pointer1 is the address of the first value
	/*pointer2 is the address of the second value*/ 						pointer2 = &secondValue;

		*pointer1 = 10;

	*pointer2 = *pointer1;

				pointer1 = pointer2;

			*pointer1 = 20;

	cout << "First = " << firstValue << endl;
	cout << "Second = " << secondValue << endl;

	return 0;
}