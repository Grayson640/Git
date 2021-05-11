#include "Recipe.h"
#include "ingredients.h"
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;


Recipe::Recipe()
{
}


Recipe::~Recipe()
{
}

// Outputs ingredients
void Recipe::printIngredients()
{
	for (ingredients ingredient : Ingredients)
	{
		cout << ingredient.name << endl;
	}
}

// Set up so it reads tags from recipeCards.txt
void Recipe::selectRecipe(Recipe& recipe)
{
	fstream inFile;
	string line;
	vector<string> recipeNames;
	char selection;
	int index;
	int select;

	recipe = Recipe();

	// Looks over file for <name> tags
	inFile.open("recipeCards.txt");	// recipeCards.txt holds all recipes
	while (inFile)	// File opened successfully
	{
		getline(inFile, line);
		index = line.rfind("<name>"); // Looks for all <name> tags

		if (index > -1)	// <name> tag is found
		{
			recipeNames.push_back(line.substr(line.find_last_of(">") + 1));	// Name is added to vector
			line.clear();	// Clear buffer
		}
	}

	inFile.close();	// Close file

	// Prompts user to select a recipe
	cout << "\nSelect Recipe: " << endl;
	for (int i = 0; i < recipeNames.size(); i++)
	{
		cout << i << ": " << "\t" << recipeNames[i] << endl;
	}

	cout << "Selection: ";

	bool check = 0;
	while (!check)
	{
		cin >> selection;
		select = selection - '0'; // Convert char to int

		if (select >= recipeNames.size() || select < 0)
		{
			cout << "Error, try again: ";
		}
		else { check = 1; }
	}

	// Calls load functions based on user input
	do
	{
		if (isdigit(selection))
		{
			recipe.name = recipeNames[select];
			recipe.loadRecipe(recipe);
			//recipe.loadPrep(recipe);
			//recipe.loadExec(recipe);
			break;
		}
	} while (toupper(selection) != 'Q');
}

// Outputs shopping list to text file
void Recipe::shoppingList(Recipe& recipe)
{
	string filename;
	fstream infile;

	while (true)
	{
		filename = recipe.name + "ShoppingList.txt";
		infile.open(filename, ios::out);
		if (infile) // File opened successfully
		{
			cout << "\nFile created successfully" << endl;
			break;
		}
		else
		{
			cout << "Some Error" << endl;
		}
	}

	infile << recipe.name << " Shopping List" << endl;
	infile << "-----" << endl;
	for (ingredients ingredient : recipe.Ingredients)
	{
		infile << setw(25) << left << ingredient.name << right
			<< ingredient.amount << " "
			<< ingredient.measurement << endl;
	}


	infile.close();

}

// Outputs prep steps
void Recipe::prep(Recipe& recipe)
{
	cout << endl << "Prep-------------------------" << endl;
	for (int i = 0; i < recipe.Prep.size(); i++)
	{
		if (recipe.Prep[i] == "<listVeg>")
		{
			recipe.listVeg(recipe);
		}
		else
		{
			cout << recipe.Prep[i] << endl;
		}
	}
	system("pause");
}

// Outputs execution steps
void Recipe::execute(Recipe& recipe)
{
	cout << endl << "Execute----------------------" << endl;
	for (int i = 0; i < recipe.Execute.size(); i++)
	{
		if (recipe.Execute[i] == "<listTopping>")
		{
			recipe.listTopping(recipe);
		}
		else if (recipe.Execute[i] == "<listStock>")
		{
			recipe.listStock(recipe);
		}
		else
		{
			cout << recipe.Execute[i] << endl;
		}
	}
	system("pause");
}

// Extracts ingredients from text file
void Recipe::loadRecipe(Recipe& recipe)
{
	fstream inFile;
	string line, ingName, ingAmount, ingMeasure, ingType;
	int index, temp, convIngAmount, nameIndex;

	// Looks over file for <ing> tags
	inFile.open("recipeCards.txt");
	while (inFile)
	{
		// Loop until <name>Name is found
		getline(inFile, line);
		nameIndex = line.find("<name>" + recipe.name);
		// cout << "<name>" + name << endl;
		while (nameIndex > -1 && line != "</Recipe>")	// getline is at <name>Name
		{
			getline(inFile, line);
			index = line.find("<ing>");
			if (index > -1)
			{
				// Seperate line into ingredient variables for Ingredients vector
				// Name
				index = line.find(',');
				ingName = line.substr(5, index - 5);
				// Amount
				temp = index;
				index = line.find(",", temp + 1);
				ingAmount = line.substr(temp + 1, index - temp - 1);
				// Measurement
				temp = index;
				index = line.find(",", temp + 1);
				ingMeasure = line.substr(temp + 1, index - temp - 1);
				// Type
				ingType = line.substr(index + 1);

				// Convert ingAmount to an integer
				convIngAmount = stoi(ingAmount);

				recipe.Ingredients.push_back(ingredients(ingName, convIngAmount,
					ingMeasure, ingType));
			}

			index = line.find("<prep>");	// Prep tag
			if (index > -1)
			{
				// Add line to vector
				recipe.Prep.push_back(line.substr(6));
			}

			index = line.find("<exec>");	// Execute tag
			if (index > -1)
			{
				// Add line to vector
				recipe.Execute.push_back(line.substr(6));
			}
		}
	}
}

/*// Read and save prep steps from file
void Recipe::loadPrep(Recipe& recipe)
{
	fstream inFile;
	string line;
	int index;
	int nameIndex;

	inFile.open("recipeCards.txt");
	while (inFile)
	{
		// Loop until <name>Name is found
		getline(inFile, line);
		nameIndex = line.find("<name>" + recipe.name);
		// cout << "<name>" + name << endl;
		while (nameIndex > -1 && line != "</Recipe>")	// getline is at <name>Name
		{												// </Recipe> is closing tag of individual recipe
			getline(inFile, line);
			index = line.find("<prep>");
			if (index > -1)
			{
				// Add line to prep vector
				recipe.Prep.push_back(line.substr(6));
			}
		}
	}
}

// Reads and save execution steps from file
void Recipe::loadExec(Recipe& recipe)
{
	fstream inFile;
	string line;
	int index;
	int nameIndex;

	inFile.open("recipeCards.txt");
	while (inFile)
	{
		// Loop until <name>Name is found
		getline(inFile, line);
		nameIndex = line.find("<name>" + recipe.name);
		// cout << "<name>" + name << endl;
		while (nameIndex > -1 && line != "</Recipe>")	// getline is at <name>Name
		{												// </Recipe> is closing tag of individual recipe
			getline(inFile, line);
			index = line.find("<exec>");
			if (index > -1)
			{
				// Add line to execute vector
				recipe.Execute.push_back(line.substr(6));
			}
		}
	}
}*/

void Recipe::listVeg(Recipe& recipe)
{
	for (int i = 0; i < recipe.Ingredients.size(); i++)
	{
		if (recipe.Ingredients[i].type == "Veg")
		{
			cout << recipe.Ingredients[i].name << endl;
		}
	}
}

void Recipe::listTopping(Recipe& recipe)
{
	for (int i = 0; i < recipe.Ingredients.size(); i++)
	{
		if (recipe.Ingredients[i].type == "Topping")
		{
			cout << recipe.Ingredients[i].name << endl;
		}
	}

}

void Recipe::listStock(Recipe& recipe)
{
	for (int i = 0; i < recipe.Ingredients.size(); i++)
	{
		if (recipe.Ingredients[i].type == "Stock")
		{
			cout << recipe.Ingredients[i].name << endl;
		}
	}
}
