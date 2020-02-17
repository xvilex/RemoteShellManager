#include <iostream>
#include <string>

#include "commands.h"

using namespace std;

int main() {
	CommandCenter cc;
	string command = "";

	system("clear");

	cout << "Coded by qE6" << endl;

	while (true) {
		cout << endl;
		cout << "Remote shell manager" << endl;
		cout << "Type help to get commands" << endl << endl;
		cout << "> ";
		getline(cin, command);

		cc.set_command(command);
		cc.execute_command();
		command = "";
	}

}
