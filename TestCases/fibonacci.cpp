#include <iostream>

using namespace std;

/*

A simple program to generate a Fibonacci sequence of numbers

	cout << fib(int n) << endl;

*/

int main(void){

	int n, term_one = 0, term_two = 1, next = 0;

	cout << "Enter the number of terms: ";
	cin >> n;

	for (int i = 1; i <= n; i++){

		if (i == 1){
			cout << term_one << ", ";
			continue; 
		}

		if (i == 2){					// The first and second terms are set
			cout << term_two << ", ";
			continue;
		}

		// The next fibonacci term is the summation of the previous two terms
		next = term_one + term_two;
		term_one = term_two;
		term_two = next;

		cout << next << ", ";
	}

	// probably could use one // less endl
	cout << endl << endl;

	return 0;
}