#include "BXT.h"
#include "Helper.h"
#include "CorasickAlgorithm.h"
#include "MD5.h"
#include "MD5Scanner.h"

using namespace std;

CorasickAlgorithm corasick;

void ReadVirus() {
	int n;
	cin >> n;
	scanf("\n");
	n = 1000;
	foru(i, 1, n) {
		string str;
		getline(cin, str);
		Virus virus;

		//cout << str << endl;
		vector<string> listStr = Helper::Split(str, ':');
		//cout << listStr.size() << endl;
		if (listStr.size() != 4) continue;
		virus.Name = listStr[0];
		virus.HexString = listStr[3];

		//cout << virus.Name << " " << virus.HexString << endl;

		corasick.AddVirus(virus);
	}
}

int main()
{	
	MD5Scanner md5Scanner;
	md5Scanner.ReadDataBase("md5.txt");
	vector<string> ans = md5Scanner.Scan("d:/md5_pe.txt");
	
	if (!ans.empty())
		foru(i, 0, ans.size() - 1) cout << ans[i] << endl;
	else
		cout << "Clear File" << endl;

	getch();
	return 0;
}
