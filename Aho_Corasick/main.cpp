#include "BXT.h"
#include "Helper.h"
#include "CorasickAlgorithm.h"
#include "MD5Scanner.h"
#include "SHA1Scanner.h"

using namespace std;

CorasickAlgorithm corasick;

void ReadVirus() {
	int n;
	cin >> n;
	n = 10000;
	scanf("\n");
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
	SHA1Scanner sha1Scanner;
	try {
		// md5
		md5Scanner.ReadDataBase("md5.txt");
		int start = GetTickCount();
		vector<string> ans = md5Scanner.Scan("D:\\calc.exe");
		int end = GetTickCount();

		if (!ans.empty())
			foru(i, 0, ans.size() - 1) cout << ans[i] << endl;
		else
			cout << "Clear File" << endl;

		cout << "MD5 scan time : " << end - start << " ms" << endl;

		// sha
		sha1Scanner.ReadDataBase("sha1.txt");
		start = GetTickCount();
		
		vector<string> ans1 = sha1Scanner.Scan("D:\\calc.exe");
		end = GetTickCount();

		if (!ans1.empty())
			foru(i, 0, ans1.size() - 1) cout << ans1[i] << endl;
		else
			cout << "Clear File" << endl;

		cout << "SHA1 scan time : " << end - start << " ms" << endl;
	}
	catch (exception ex) {

	}

	// aho corasick
	//freopen("db_virus.txt", "r", stdin);
	////freopen("output.txt", "w", stdout);
	//ios::sync_with_stdio(0);
	//cin.tie(NULL);

	//ReadVirus();

	//int start = GetTickCount();
	//corasick.BuildTree();
	//int end = GetTickCount();
	//cout << "Build Tree Time : " << end - start << " ms" << endl;
	////corasick.Debug();

	//start = GetTickCount();
	//string hexString = Helper::getHexString("D:\\calc.exe");
	//corasick.PrintVirus(corasick.Scan(hexString));
	//end = GetTickCount();
	//cout << "Scan time : " << end - start << " ms" << endl;

	getch();
	return 0;
}
