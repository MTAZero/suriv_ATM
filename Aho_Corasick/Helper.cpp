#include "Helper.h"

Helper::Helper()
{
}


Helper::~Helper()
{
}

string ToHex(const string& input, bool upper_case)
{
	static const char* const lut = "0123456789ABCDEF";
	int len = input.length();

	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}

	return output;
}

string Helper::getHexString(string path) {

	string ans = "";

	ifstream::pos_type size;
	char * memblock;

	ifstream file(path, ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		memblock = new char[size];
		file.seekg(0, ios::beg);
		file.read(memblock, size);
		file.close();

		//cout << "the complete file content is in memory" << endl;

		ans = ToHex(std::string(memblock, size), true);
	}

	return ans;
}

vector<string> Helper::getListFile(string folderpath) {
	vector<string> v;
	DIR* dirp = opendir(folderpath.c_str());
	struct dirent * dp;
	while ((dp = readdir(dirp)) != NULL) {
		v.push_back(dp->d_name);
	}
	closedir(dirp);
	return v;
}

void Helper::PrintString(vector<string> a) {
	if (!a.empty()) {
		foru(i, 0, a.size() - 1)
			cout << a[i] << endl;
		cout << endl;
	}
	else
	{
		cout << "Rong" << endl;
	}
}

int Helper::ConvertHexToInt(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	return c - 'A' + 10;
}

char Helper::ConvertIntToHex(int a) {
	if (a <= 9) return '0' + a;
	return 'A' + a - 10;
}

vector<string> Helper::Split(string str, char c) {
	vector<string> ans;

	string s = "";
	foru(i, 0, str.size() - 1) {
		if (str[i] == c) {
			ans.push_back(s);
			s = "";
			continue;
		}
		s = s + str[i];
	}
	if (s != "") ans.push_back(s);

	return ans;
}
