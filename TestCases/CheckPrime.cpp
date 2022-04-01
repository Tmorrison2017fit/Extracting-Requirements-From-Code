#include <iostream>

using namespace std;

int main() {
	int i, n;

	bool prime = true;

	cout << "Enter a positive integer: ";

	cin >> n;

	// 0 and 1 are not prime numbers
	if (n == 0 || n == 1){
		prime = false;
	}

	for (i = 2; i <= n/2; i++){
		if (n % i == 0){
			prime = false;
			break;
		}
	}

	if(prime){			// Differing print statements depending on whether the value is prime or not
		cout << n << " is a prime number\n";
	}
	else{
		cout << n << " is a composite number\n";
	}

	return 0;
}