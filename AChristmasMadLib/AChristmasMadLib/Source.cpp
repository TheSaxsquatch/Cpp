// Code crafted on December 9, 2021 by Nat Hurt

#include <iostream>
#include <string>

using namespace std;

int main() {

	// Name string
	string name;

	// Adjective strings
	string adj1, adj2, adj3, adj4, adj5;

	// Noun strings
	string noun1, noun2, noun3;

	// Verb strings
	string verb1, verb2, verb3, verb4;

	// Number
	int userNum;

	// User input by word of the madlib

	cout << "Welcome to our Christmas MadLib, where we put a fun twist on a Christmas Classic!" << endl;
	cout << "What is your name?" << endl;
	getline(cin, name);

	cout << "Hello, " << name << "! Let's get creative!!" << endl;
	cout << "Our first word is an ADJECTIVE... What will it be?" << endl;
	getline(cin, adj1);

	cout << "Our next word is also an ADJECTIVE... What will it be?" << endl;
	getline(cin, adj2);

	cout << "Our next word is a NUMBER... What will it be?" << endl;
	cin >> userNum;
	cin.get();

	cout << "Our next word is a NOUN... What will it be?" << endl;
	getline(cin, noun1);

	cout << "Our next word is also a NOUN... What will it be?" << endl;
	getline(cin, noun2);

	cout << "Our next word is also a NOUN... What will it be?" << endl;
	getline(cin, noun3);

	cout << "Our next word is an ADJECTIVE... What will it be?" << endl;
	getline(cin, adj3);

	cout << "Our next word is a VERB... What will it be?" << endl;
	getline(cin, verb1);
	
	cout << "Our next word is an ADJECTIVE... What will it be?" << endl;
	getline(cin, adj4);

	cout << "Our next word is a VERB... What will it be?" << endl;
	getline(cin, verb2);

	cout << "Our next word is also a VERB... What will it be?" << endl;
	getline(cin, verb3);

	cout << "Our next word is an ADJECTIVE... What will it be?" << endl;
	getline(cin, adj5);

	cout << "Our last word is a VERB... What will it be?" << endl;
	getline(cin, verb4);

	// Title of the Story
	cout << "Now let's hear your version of FROSTY THE SNOWMAN: " << endl;

	// Body of our madlib with user input
	cout << "Frosty the Snowman was a jolly " << adj1 << " soul with a " << adj2 << " pipe and a button nose, and " << userNum << " eyes made out of " << noun1 << endl;
	cout << "Frost the Snowman is a fairytail they say. He was made of " << noun2 << " but the children know how he came to life one day." << endl;
	cout << "There must have been some " << noun3 << " in that old " << adj3 << " hat they found. For when they placed it on his head, he began to " << verb1 << " around!" << endl;
	cout << "Frosty the Snowman was as " << adj4 << " as he could be. And the children say he could " << verb2 << " and " << verb3 << " just the same as you and me." << endl;
	cout << "Frosty the Snowman knew the sun was " << adj5 << " that day so he said let's " << verb4 << " and we'll have some fun before I melt away!" << endl;

	// Author Credits!
	cout << "Wonderful Rendition of a Classic by: " << name << endl;

	return 0;
}