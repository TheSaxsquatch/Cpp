#include <iostream>
#include <ctime>

using namespace std;

// Welcome to Triple X. This is a simple terminal based C++ Game
// Nat Hurt April 2018
// This was written using pre-defined Unreal naming convention rules.


void PrintIntroduction() {

	// Print the starting messages of the Game
	cout << "Hello, Agent.\nYour mission, should you choose to accept it, is to break into this secret lair.\n" << endl;
	cout << "You must enter the code correctly to get in, get the information, and get out.\n" << endl;
	cout << "Good luck, Agent.\nOur whole mission rests in your hands now." << endl;
}

void LevelUpMessage(int SecurityLevel) {
	cout << "\n\nThis is a level " << SecurityLevel << " secure area!\nGood luck, Agent!\n" << endl;
}

bool PlayGame(int Difficulty) {

	LevelUpMessage(Difficulty);

	// Randomize our variables in the game and calculate the clue variables.
	const int CodeA = rand() % Difficulty + Difficulty;
	const int CodeB = rand() % Difficulty + Difficulty;
	const int CodeC = rand() % Difficulty + Difficulty;

	const int CodeSum = CodeA + CodeB + CodeC;
	const int CodeProduct = CodeA * CodeB * CodeC;

	// Supply user hints
	cout << "Here are your hints: \n" << endl;
	cout << "> There are 3 numbers in the code." << endl;
	cout << "> The sum of the numbers in the code is: " << CodeSum << endl;
	cout << "> The product of the numbers in the code is: " << CodeProduct << endl;

	// Initialize user input variables, accept user input into variables, and calculate comparison values.
	int GuessA, GuessB, GuessC;

	cin >> GuessA;
	cin >> GuessB;
	cin >> GuessC;

	int GuessSum = GuessA + GuessB + GuessC;
	int GuessProduct = GuessA * GuessB * GuessC;

	// If-Else statement to compare variables to determine progression in the game.
	if ((GuessSum == CodeSum) && (GuessProduct == CodeProduct)) {
		cout << "\nCongratulations, Agent!\nYou've cracked the code!" << endl;
		return true;
	}
	else {
		cout << "\nI'm sorry, Agent.\nThat code was incorrect..." << endl;
		return false;
	}
}

int main() {

	// Global Variable
	srand(time(NULL));
	int LevelDifficulty = 1;
	int MaxDifficulty = 10;

	PrintIntroduction();

	while (LevelDifficulty <= MaxDifficulty) {

		bool bLevelComplete = PlayGame(LevelDifficulty);
		cin.clear(); // Clears errors in the game
		cin.ignore(); // Discards the buffer

		if (bLevelComplete) {
			// Code to increase level difficulty
			++LevelDifficulty;

		}
	}
	
	return 0;
}