#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int choice;

    do
    {
        cout << "\n====== Scientific Calculator ======\n";
        cout << "1. Add multiple numbers\n";
        cout << "2. Multiply multiple numbers\n";
        cout << "3. Subtraction\n";
        cout << "4. Division\n";
        cout << "5. Power\n";
        cout << "6. Square Root\n";
        cout << "7. Trigonometric Functions\n";
        cout << "8. Logarithm (base 10)\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1)
        {
            int n;
            double sum = 0, x;

            cout << "How many numbers? ";
            cin >> n;

            for (int i = 1; i <= n; i++)
            {
                cout << "Enter number " << i << ": ";
                cin >> x;
                sum += x;
            }
            cout << "Result = " << sum << endl;
        }

        else if (choice == 2)
        {
            int n;
            double result = 1, x;

            cout << "How many numbers? ";
            cin >> n;

            for (int i = 1; i <= n; i++)
            {
                cout << "Enter number " << i << ": ";
                cin >> x;
                result *= x;
            }
            cout << "Result = " << result << endl;
        }

        else if (choice == 3)
        {
            double a, b;
            cout << "Enter two numbers: ";
            cin >> a >> b;
            cout << "Result = " << a - b << endl;
        }

        else if (choice == 4)
        {
            double a, b;
            cout << "Enter two numbers: ";
            cin >> a >> b;

            if (b == 0)
                cout << "Error: Division by zero"<<endl;
            else
                cout << "Result = " << a / b << endl;
        }

        else if (choice == 5)
        {
            double base, power;
            cout << "Enter base and power: ";
            cin >> base >> power;
            cout << "Result = " << pow(base, power) << endl;
        }

        else if (choice == 6)
        {
            double a;
            cout << "Enter number: ";
            cin >> a;
            cout << "Result = " << sqrt(a) << endl;
        }

        else if (choice == 7)
        {
            int t;
            double angle;

            cout << "\n1. Sin\n2. Cos\n3. Tan\nChoose: ";
            cin >> t;

            cout << "Enter angle (degrees): ";
            cin >> angle;

            double rad = angle * 3.141592653589 / 180;

            if (t == 1)
                cout << "sin = " << sin(rad) <<endl;
            else if (t == 2)
                cout << "cos = " << cos(rad) <<endl;
            else if (t == 3)
                cout << "tan = " << tan(rad) <<endl;
            else
                cout << "Invalid choice"<<endl;
        }

        else if (choice == 8)
        {
            double a;
            cout << "Enter number: ";
            cin >> a;
            cout << "log10 = " << log10(a) << endl;
        }
        else if (choice == 0)
        {
            cout << "Calculator Closed"<<endl;
        }
        else
        {
            cout << "Invalid choice"<<endl;
        }

    } while (choice != 0);

    return 0;
}
