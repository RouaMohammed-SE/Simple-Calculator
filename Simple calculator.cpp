//Name: Roaa mohammed sayed
//email :rouamohamedse@gmail.com
// Program Description: This is a calculator program that takes two negative or positive rational numbers an apply on them subtraction,
//  dividion, multiplacation and addition

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <regex>
#include <numeric>

using namespace std;

// Structure to represent a fraction
struct Fraction {
    int numer; // Numerator
    int denumer; // Denominator
};

// Function to read input from the user
vector<string> readInput() {
    while (true) {
        cout << ">> ";
        string str;
        getline(cin, str);

        if (str == "exit") {
            cout << "Thank you for using rational number calculator\n";
            exit(0);
        }

        smatch sm;
        // Regular expression to match and extract components of a rational number expression
        // first the regular expression tries to match an optionally negative sign digit or positive sign >>>> [-+]
        // second regular expresion tries to match the / sign and the denumer value if exsisting (they are optionally taken) >>>> (/([-+]?[1-9]+))?
        // third regular expresion tries to match the inputed operand to be + or - or / or * >>>> ([-+*/])
        //then the same with the second part
        regex re("([-+]?\\d+)(/([-+]?[1-9]+))? ([-+*/]) ([-+]?\\d+)(/([-+]?[1-9]+))?");

        if (regex_match(str, sm, re)) {
            // Extracting components of the expression
            vector<string> arr(5);
            arr[0] = sm[1].str();  //assign the first index to the first digit(numer) which is in sm[1]
            arr[1] = sm[3].str() == "" ? "1" : sm[3].str(); //assign the second index to the second digit(denumer) which is in sm[3] and if there is no digit, assign denumer to one
            arr[2] = sm[4].str();   // assign the third index to the operand at sm[4]
            arr[3] = sm[5].str();   //assign the fourth index to the third digit(numer) which is in sm[5]
            arr[4] = sm[7].str() == "" ? "1" : sm[7].str();  //assign the fifth index to the fourth digit(denumer) which is in sm[7] and if there is no digit, assign denumer to one
            return arr;
        }
        else {
            cout << "Bad Expression. Try again.\n";
        }
    }
}

// Function to perform addition of two fractions
Fraction add(const Fraction& f1, const Fraction& f2) {
    Fraction res;
    res.denumer = f1.denumer * f2.denumer;
    res.numer = (f1.numer * f2.denumer) + (f2.numer * f1.denumer);
    return res;
}

// Function to perform multiplication of two fractions
Fraction mul(const Fraction& f1, const Fraction& f2) {
    Fraction res;
    res.denumer = f1.denumer * f2.denumer;
    res.numer = f1.numer * f2.numer;
    return res;
}

// Function to perform subtraction of two fractions
Fraction sub(const Fraction& f1, const Fraction& f2) {
    Fraction res;
    res.denumer = f1.denumer * f2.denumer;
    res.numer = (f1.numer * f2.denumer) - (f2.numer * f1.denumer);
    return res;
}

// Function to perform division of two fractions
Fraction div(const Fraction& f1, const Fraction& f2) {
    Fraction res;
    res.denumer = f1.denumer * f2.numer;
    res.numer = f1.numer * f2.denumer;
    return res;

}

// Function to simplify a fraction
Fraction simplify(const Fraction& f) {
    // Calculating greatest common divisor (GCD) using std::gcd function
    int gcd = std::gcd(f.numer, f.denumer);
    Fraction simplified;
    simplified.numer = f.numer / gcd;
    simplified.denumer = f.denumer / gcd;
    return simplified;
}

int main() {
    cout << "**********Welcome to Rational Calculator**********\n";
    cout << "Please enter a rational number operations (or exit):\n";
    while (true) {
        // Read input expression from the user
        vector<string> tokens = readInput();

        // Parse fractions from input tokens
        Fraction f1;
        f1.numer = stoi(tokens[0]);
        f1.denumer = stoi(tokens[1]);
        Fraction f2;
        f2.numer = stoi(tokens[3]);
        f2.denumer = stoi(tokens[4]);

        // Perform arithmetic operation based on the operator
        Fraction res;
        char operation = tokens[2][0];
        bool divideByZero = false;
        switch (operation) {
        case '+':
            res = add(f1, f2);
            break;
        case '*':
            res = mul(f1, f2);
            break;
        case '-':
            res = sub(f1, f2);
            break;
        case '/':
            if (f2.numer == 0) {
                cout << "Error: Division by zero\n";
                divideByZero = true;
            }
            else {
                res = div(f1, f2);
                res = simplify(res);
            }
            break;
        }

        if (divideByZero) continue;

        // Simplify the result fraction
        res = simplify(res);

        // Removing the negative sign from denumer
        if (res.denumer < 0) {
            res.numer *= -1;
            res.denumer *= -1;
        }

        // Output the result
        cout << "= " << res.numer;
        if (res.denumer != 1) {
            cout << "/" << res.denumer;
        }
        cout << '\n';
    }
}