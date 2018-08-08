#pragma once

#include "BXT.h"

class Virus
{
public:
	Virus();
	Virus(string name, string hexString);

	~Virus();

public:
	string Name;
	string HexString;
};

