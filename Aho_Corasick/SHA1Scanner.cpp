#include "SHA1Scanner.h"



SHA1Scanner::SHA1Scanner()
{
}


SHA1Scanner::~SHA1Scanner()
{
}

bool cmpz(Virus a, Virus b) {
	return a.HexString < b.HexString;
}

void SHA1Scanner::ReadDataBase(string path) {
	cout << "-------------------- SHA1 -----------------" << endl;

	FILE *f = fopen(path.c_str(), "r");

	int n;
	char _str[100];
	fscanf(f, "%d", &n);
	foru(i, 1, n) {
		string str;

		fscanf(f, "%s\n", &_str);
		str = _str;
		Virus virus;
		vector<string> listStr = Helper::Split(str, ':');
		if (listStr.size() != 2) continue;
		virus.Name = listStr[0];
		virus.HexString = listStr[1];
		viruss.push_back(virus);
	}

	cout << "Read database done " << endl;
	cout << "--- Begin sort ---" << endl;
	sort(viruss.begin(), viruss.end(), cmpz);
	cout << "--- Sort done ---" << endl;
	fclose(f);
}

vector<string> SHA1Scanner::Scan(string path) {
	cout << "start scann " << endl;
	vector<string> ans;

	// if list virus empty quit
	if (viruss.empty()) return ans;

	string str = SHA1::from_file(path);
	cout << str << endl;
	cout << "--- Hash done ---" << endl;

	int low = 0, high = viruss.size() - 1;
	while (high >= low) {
		cout << low << " " << high << endl;
		int mid = (high + low) / 2;
		if (viruss[mid].HexString.compare(str) == 0) {
			ans.push_back(viruss[mid].Name);
			return ans;
		}

		if (viruss[mid].HexString > str)
			high = mid - 1;
		else
			low = mid + 1;
	}

	return ans;
}
