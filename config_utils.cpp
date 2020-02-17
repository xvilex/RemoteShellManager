#include "config_utils.h"

ConfigUtils Config;

ConfigUtils::ConfigUtils() {}
ConfigUtils::~ConfigUtils() {}

int ConfigUtils::find_max_id(const vector<string>& shells) {
	int max = 0;

	for (size_t i = 0; i < shells.size(); i++) {
		int value = stoi(split(shells[i], '\t')[0]);
		if (value > max)
			max = value;
	}
	return max;
}

int ConfigUtils::get_new_id() {
	// I think find max id and then add 1 is best way to get free id.
	// Count lines is bad way because we can delete backdoor from middle. 
	return find_max_id(get_backdoors()) + 1;
}

void ConfigUtils::add_backdoor(const string& str) {
	int id = get_new_id();
	ofstream writer(cfg_name, std::ios::app);

	if (!writer.is_open()) {
		cout << "Config file is busy!" << endl;
		exit(0);
	}

	vector<string> splitted = split(str, ' ');

	writer << id << "\t" << splitted[1] << endl;
	writer.close();

	cout << "Victim added" << endl;
}

vector<string> ConfigUtils::get_backdoors() {
	vector<string> result;

	ifstream reader(cfg_name);

	if (!reader.is_open())
	{
		cout << "Config file is busy!" << endl;
		exit(0);
	}

	string buf;
	while (std::getline(reader, buf))
		result.push_back(buf);

	return result;
}

string ConfigUtils::get_current_backdoor(const string& id) {
	vector<string> backdoors = get_backdoors();

	for (size_t i = 0; i < backdoors.size(); i++) {
		if (split(backdoors[i], '\t')[0] == id)
			return backdoors[i];
	}
	return "No backdoor with id " + id;
}

void ConfigUtils::remove_backdoor(const string& str) {
	vector<string> backdoors = get_backdoors();
	string id = split(str, ' ')[1];

	size_t f_size = backdoors.size();

	for (size_t i = 0; i < f_size; i++) {
		if (split(backdoors[i], '\t')[0] == id) {
			backdoors.erase(backdoors.begin() + i); // delete backdoor
			break; // leave
		}
	}

	if (f_size == backdoors.size()) { // if nothing changed. In case if ID is invalid
		return;
	}

	/* Rewrite base */
	ofstream writer(cfg_name);

	if (!writer.is_open()) {
		cout << "Config file is busy!" << endl;
		exit(0);
	}

	for (size_t i = 0; i < backdoors.size(); i++) {
		writer << backdoors[i] << endl;
	}
	writer.close();
}
