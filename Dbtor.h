#pragma once

#include <string>
#include <clocale>

using namespace std;



class Dbtor
{
private:

	string deb_name;
	float deb_size;

public:
	Dbtor(string nm);
	Dbtor();
	void ChangeSize(float sz);
	void SetSizeValue(float value);
	void SetNameValue(string value);
	string GetNameValue();
	float GetSizeValue();
	~Dbtor();
};



