#pragma once
#include "BXT.h"
#include "MD5.h"
#include "Virus.h"
#include "Helper.h"

class MD5Scanner
{
public:
	MD5Scanner();
	~MD5Scanner();

private:
	vector<Virus> viruss;

public:
	 void ReadDataBase(string path);
	 vector<string> Scan(string path);
};

