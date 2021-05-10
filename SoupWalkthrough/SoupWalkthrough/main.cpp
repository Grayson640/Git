// Frederick Grayson Tarr
// Date: 5/3/21
// Soup Walk Through Program

// TODO: GUI, batch() commands, list() functions: veg, toppings

// Include
#include "ingredients.h"
#include "Recipe.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdlib.h>

// Main Method
int main() {
	// User input menu control
	char selection;
	// Declare Recipe object
	Recipe recipe;

	// Menu interface
	cout << "Recipe Walkthrough v0.0" << endl;
	cout << "\nMain Menu-------------------";
	cout << "\nSelect Recipe" << "\t\tS" << endl;
	cout << "Generate Shopping List" << "\tG" << endl;
	cout << "Prep" << "\t\t\tP" << endl;
	cout << "Execute Recipe" << "\t\tE"<< endl;
	cout << "Quit" << "\t\t\tQ" << endl;

	do
	{
		cout << "Selection: ";
		cin >> selection;
		switch (toupper(selection))
		{
		case 'S':
			recipe.selectRecipe(recipe);
			break;
		case 'G':
			recipe.shoppingList(recipe);
			break;
		case 'P':
			recipe.prep(recipe);
			break;
		case 'E':
			recipe.execute(recipe);
			break;
		case 'Q':
			break;
		default:
			cout << "Error. Try again." << endl;
		}
		cout << "\nMain Menu-------------------" << endl;
	} while (toupper(selection) != 'Q');

	system("pause");

	return 0;
}
