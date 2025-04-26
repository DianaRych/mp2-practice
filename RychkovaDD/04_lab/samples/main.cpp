#include <iostream>
#include <string>

#include "Polinomds.h"

using namespace std;

void printMenu() {
    cout << "\n=== Polynomial Operations Menu ===" << endl;
    cout << "1. Create new polynomial 1" << endl;
    cout << "2. Create new polynomial 2" << endl;
    cout << "3. Add two polynomials" << endl;
    cout << "4. Subtract polynomials" << endl;
    cout << "5. Multiply polynomial by monomial" << endl;
    cout << "6. Multiply two polynomials" << endl;
    cout << "7. Multiply polynomial by scalar" << endl;
    cout << "8. Differentiate polynomial by X" << endl;
    cout << "9. Differentiate polynomial by Y" << endl;
    cout << "10. Differentiate polynomial by Z" << endl;
    cout << "11. Evaluate polynomial at point" << endl;
    cout << "12. Display polynomials" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

TPolinom createPolynomial(int polyNumber) {
    string input;
    while (true) {
        cout << "Enter polynomial " << polyNumber << " (e.g., 2x^3y+5xy^2z-3z^2): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);

        if (!input.empty()) {
            try {
                return TPolinom(input);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << ". Please try again." << endl;
            }
        }
        else {
            cout << "Input cannot be empty. Try again." << endl;
        }
    }
}

TMonom createMonomial() {
    string input;
    while (true) {
        cout << "Enter monomial (e.g., 3x^2y or -2z): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);

        if (!input.empty()) {
            try {
                return TMonom(input);
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << ". Please try again." << endl;
            }
        }
        else {
            cout << "Input cannot be empty. Try again." << endl;
        }
    }
}

void evaluatePolynomial(const TPolinom& p) {
    double x, y, z;
    cout << "Enter x value: ";
    cin >> x;
    cout << "Enter y value: ";
    cin >> y;
    cout << "Enter z value: ";
    cin >> z;

    double result = p(x, y, z);
    cout << "Polynomial value at (" << x << ", " << y << ", " << z << ") = " << result << endl;
}

int main() {
    TPolinom poly1, poly2, result;
    int choice;

    do {
        printMenu();
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }

        try {
            switch (choice) {
            case 1:
                poly1 = createPolynomial(1);
                break;
            case 2:
                poly2 = createPolynomial(2);
                break;
            case 3:
                result = poly1 + poly2;
                cout << "Result: " << result << endl;
                break;
            case 4:
                result = poly1 - poly2;
                cout << "Result: " << result << endl;
                break;
            case 5: {
                TMonom m = createMonomial();
                result = poly1 * m;
                cout << "Result: " << result << endl;
                break;
            }
            case 6:
                result = poly1 * poly2;
                cout << "Result: " << result << endl;
                break;
            case 7: {
                double scalar;
                cout << "Enter scalar value: ";
                cin >> scalar;
                result = poly1 * scalar;
                cout << "Result: " << result << endl;
                break;
            }
            case 8:
                result = poly1.DiffX();
                cout << "Derivative by X: " << result << endl;
                break;
            case 9:
                result = poly1.DiffY();
                cout << "Derivative by Y: " << result << endl;
                break;
            case 10:
                result = poly1.DiffZ();
                cout << "Derivative by Z: " << result << endl;
                break;
            case 11:
                evaluatePolynomial(poly1);
                break;
            case 12:
                cout << "Polynomial 1: " << poly1 << endl;
                cout << "Polynomial 2: " << poly2 << endl;
                break;
            case 0:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        catch (...) {
            cerr << "Unknown error occurred" << endl;
        }

    } while (choice != 0);

    return 0;
}
