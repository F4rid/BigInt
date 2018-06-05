#include <iostream>
#include "BigInt.h"

using namespace std;

// Driver code
int main()
{
    BigInt a,b;
    char operation;
    
    while (true)
    {
        cout << "Enter two bigint values: ";
        cin >> a >> b;
        cout << "Enter operation (+ - * /) : ";
        cin >> operation;
        
        switch (operation) {
            case '+':
                cout << "sum = " << a + b << endl;
                break;
            case '-':
                cout << "subtract = " << a - b << endl;
                break;
            case '*':
                cout << "multiplication = " << a * b << endl;
                break;
            case '/':
                cout << "division = " << a / b << endl;
                break;
                
            default:
                break;
        }
        
    }
    return 0;

}
