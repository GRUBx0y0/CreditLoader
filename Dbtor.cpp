#include "stdafx.h"
#include "Dbtor.h"


Dbtor::Dbtor(string nm)
{
	setlocale(LC_CTYPE, "Russian");
	deb_name = nm;
	deb_size = 0;
	
}

Dbtor::Dbtor()
{
	setlocale(LC_CTYPE, "Russian");
}

void Dbtor::ChangeSize(float sz)
{
	deb_size += sz;
}

void Dbtor::SetSizeValue(float value)
{
	deb_size = value;
}

void Dbtor::SetNameValue(string value)
{
	deb_name = value;
}

string Dbtor::GetNameValue()
{
	return(deb_name);
}

float Dbtor::GetSizeValue()
{
	return(deb_size);
}

Dbtor::~Dbtor()
{
}
