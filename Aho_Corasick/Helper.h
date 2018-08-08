#pragma once

#include "BXT.h"

class Helper
{
public:
	Helper();
	~Helper();

public:
	static string getHexString(string path);
	static vector<string> getListFile(string folderpath);
	static void PrintString(vector<string> a);

	static int ConvertHexToInt(char c);
	static char ConvertIntToHex(int c);
	static vector<string> Split(string str, char c);
};

