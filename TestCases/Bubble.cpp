#include <iostream>
#include <random>

using namespace std;

int main(void){
	int i, j, temp, pass = 0;

	int arraySize = 10;
	int array[arraySize];

	for (int pos = 0; pos <= arraySize; pos++){
		array[pos] = rand() % 100;
	}


	cout << "Input List\n";
	for (int pos = 0; pos <= arraySize; pos++){
		cout << array[pos] << ", ";
 	}
 	cout << endl;

 	for(i = 0; i <= arraySize; i++){
 		for (j = i+1; j <= arraySize; j++){
 			if (array[j] < array[i]){
 				temp = array[i];
 				array[i] = array[j];
 				array[j] = temp;
 			}
 		}
 		pass++;
 	}



 	cout << "Sorted Elements\n";
 	for (int pos = 0; pos <= arraySize; pos++){
 		cout << array[pos] << ", ";
 	}
 	cout <<endl;
	return 0;
}