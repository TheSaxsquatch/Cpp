#include <iostream>
#include <limits.h>

using namespace std;

// Declaration of the global variable, clears up main function.
int var1, var2;

// In the first code, this was an unused function. We're going to fix that.
void DisplayMenu() {
	cout << "\n----------------" << endl;
	cout << "- 1)Add -" << endl;
	cout << "- 2)Subtract -" << endl;
	cout << "- 3)Multiply -" << endl;
	cout << "- 4)Exit -" << endl;
	cout << "----------------" << endl;
}

// We are going to create functions for each of our operations, this makes the code cleaner.
void AddVariables() {
	// This is a variable specific to the function. I do not like to put operations in cout
	int userSum;

	// We have a user message to clarify what the input is used for.
	cout << "Please enter two integer variables: " << endl;

	cin >> var1 >> var2;

	// Checks for over and underflow attack
	if ((var1 > 0) && (var2 > INT_MAX - var1)) { /* `var2 + var1` would overflow */
		cout << "OVERFLOW POSSIBLE" << endl;
	}
	else if ((var1 < 0) && (var2 < INT_MIN - var1)) { /* `var2 + var1` would underflow */
		cout << "UNDERFLOW POSSIBLE" << endl;
	}
	else {
		userSum = var1 + var2;

		// Shows correct opperand for function
		cout << var1 << " + " << var2 << " = " << userSum;
	}
}

void SubtractVariables() {
	// This is a variable specific to the function. I do not like to put operations in cout
	int userDiff;

	// We have a user message to clarify what the input is used for.
	cout << "Please enter two integer variables: " << endl;

	cin >> var1 >> var2;

	// Checks for over and underflow attack
	if ((var2 < 0) && (var1 > INT_MAX + var2)) { /* `var1 - var2` would overflow */
		cout << "OVERFLOW POSSIBLE" << endl;
	}
	else if ((var2 > 0) && (var1 < INT_MIN + var2)) { /* `var1 - var2` would underflow */
		cout << "UNDERFLOW POSSIBLE" << endl;
	}
	else {
		userDiff = var1 - var2;

		// Shows correct opperand for function
		cout << var1 << " - " << var2 << " = " << userDiff;
	}
}

void MultiplyVariables() {
	// This is a variable specific to the function. I do not like to put operations in cout
	int userProduct;

	// We have a user message to clarify what the input is used for.
	cout << "Please enter two integer variables: " << endl;

	cin >> var1 >> var2;

	// Checks for over and underflow attack
	if ((var1 == -1) && (var2 == INT_MIN)) { /* `var1 * var2` can overflow */
		cout << "OVERFLOW POSSIBLE" << endl;
	}
	else if ((var2 == -1) && (var1 == INT_MIN)) { /* `var1 * var2` can overflow */
		cout << "OVERFLOW POSSIBLE" << endl;
	}
	else if (var1 > INT_MAX / var2) { /* `var1 * var2` would overflow */
		cout << "OVERFLOW POSSIBLE" << endl;
	}
	else if ((var1 < INT_MIN / var2)) { /* `var1 * var2` would underflow */
		cout << "UNDERFLOW POSSIBLE" << endl;
	}
	else {
		userProduct = var1 * var2;

		// Shows correct opperand for function
		cout << var1 << " * " << var2 << " = " << userProduct;
	}
}

int main() {
	int userInput = 0;

	// We are putting better ristrictions on the while loop
	while (userInput < 5) {

		// Utilize the display menu function above.
		DisplayMenu();

		cin >> userInput;

		switch (userInput)
		{
		case 1:
			AddVariables();
			break;
		case 2:
			SubtractVariables();
			break;
		case 3:
			MultiplyVariables();
			break;
		case 4:
			// This creates actual exit conditions.
			cout << "Thank you for playing!" << endl;
			userInput = 5;
			break;
		default:
			cout << "Invalid Input, Try Again" << endl;
			break;
		}
	}

	return 0;
}