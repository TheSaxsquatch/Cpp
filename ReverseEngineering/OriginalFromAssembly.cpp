#include <iostream>

using namespace std;

void DisplayMenu() {
	cout << "----------------" << endl;
	cout << "- 1)Add -" << endl;
	cout << "- 2)Subtract -" << endl;
	cout << "- 3)Multiply -" << endl;
	cout << "- 4)Exit -" << endl;
	cout << "----------------" << endl;
}

int main() {
	int userInput = 0;
	int var1, var2;

	while (userInput != 5) {
		cout << "----------------" << endl;
		cout << "- 1)Add -" << endl;
		cout << "- 2)Subtract -" << endl;
		cout << "- 3)Multiply -" << endl;
		cout << "- 4)Exit -" << endl;
		cout << "----------------" << endl;

		cin >> userInput;

		if (userInput == 1) {
			cin >> var1 >> var2;
			cout << var1 << " - " << var2 << " = " << var1 + var2 << endl;
			break;
		}
		else if (userInput == 2) {
			cin >> var1 >> var2;
			cout << var1 << " - " << var2 << " = " << var1 - var2 << endl;
			break;
		}
		else if (userInput == 3) {
			cin >> var1 >> var2;
			cout << var1 << " - " << var2 << " = " << var1/var2 << endl;
			break;
		}
	}

	return 0;
}