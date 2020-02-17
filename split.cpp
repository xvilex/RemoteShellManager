#include "split.h"


vector<string> split(const string& str, char s) {
	string buffer = "";
	vector<string> result;

	int a = str.size();

	for (int i = 0; i < a; i++) {
		if (str[i] == s) {
			result.push_back(buffer);
			buffer = "";
			continue;
		}
		buffer += str[i];
	}
	result.push_back(buffer);
	return result;
}

