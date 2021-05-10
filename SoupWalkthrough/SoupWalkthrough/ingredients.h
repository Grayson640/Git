#pragma once
#include <string>

using namespace std;

class ingredients
{
public:
	ingredients();
	string name;
	double amount;
	string measurement;
	string type;

	ingredients(string name, double amount, string measurement, string type)
	{
		this->name = name;
		this->amount = amount;
		this->measurement = measurement;
		this->type = type;
	}

	~ingredients();
};

