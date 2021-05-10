#pragma once
#include "ingredients.h"
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

class Recipe : public ingredients
{
public:
	Recipe();		// Default Constructor
	~Recipe();		// Default Deconstructor
	string name;	// Name of Recipe
	// Ingredients Container
	vector<ingredients> Ingredients;

	// String containers
	vector<string> Prep;
	vector<string> Execute;

	// Custom Constructor
	Recipe(string name, vector<ingredients> ingredients) {}

	// Print functions
	void printIngredients();

	// Select Recipe
	void selectRecipe(Recipe& recipe);

	// Generate Shopping List
	void shoppingList(Recipe& recipe);

	// Loads recipe from file
	void loadRecipe(Recipe& recipe);

	// Loads prep instructions from file
	void loadPrep(Recipe& recipe);

	// Loads execute instructions from file
	void loadExec(Recipe& recipe);

	// Prep
	void prep(Recipe& recipe);

	// Execute
	void execute(Recipe& recipe);

	// List functions
	void listVeg(Recipe& recipe);
	void listTopping(Recipe& recipe);
	void listStock(Recipe& recipe);

};

