#pragma once
#include "BXT.h"
#include "sha1.hpp"
#include "Virus.h"
#include "Helper.h"

class SHA1Scanner
{
public:
	SHA1Scanner();
	~SHA1Scanner();

private:
	vector<Virus> viruss;

public:
	void ReadDataBase(string path);
	vector<string> Scan(string path);
};

