// For testing purposes only
// Code from https://www.programiz.com/cpp-programming/examples/average-arrays

#include <iostream>
using namespace std;

int TestFunc1(int value);
void TestFunc2();
void TestFunc3();
void TestFunc4();
void TestFunc5();

int main()
{
    int n, i;
    float num[100], sum=0.0, average;

    cout << "Enter the numbers of data: "; // Comment One.
    cin >> n;

    while (n > 100 || n <= 0)
    {
        cout << "Error! number should in range of (1 to 100)." << endl;
        cout << "Enter the number again: ";
        cin >> n;
    }

    for(i = 0; i < n; ++i)
    {
        cout << i + 1 << ". Enter number: "; // Comment two.
        cin >> num[i];
        sum += num[i];
    }

    average = sum / n;
    cout << "Average = " << average;

    TestFunc2();

    return 0;
}

int TestFunc1(int value){
  value = 5;
  cout << value << endl;
}
int TestFunc2(){
    TestFunc3();
    TestFunc5();
}
int TestFunc3(){
  TestFunc4();
}
int TestFunc4(){
  cout << " Does nothing"<< endl;
}
int TestFunc5(){
  cout << " Does nothing"<< endl;
}
