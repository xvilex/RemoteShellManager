#pragma once

#include <string>

enum command_types {
	bad_type = 0, // bad type if command unknown
	help_type = 1, // show help
	add_shell_type = 2, // add backdoor to base
	remove_shell_type = 3, // remove backdoor from base
	show_shells_type = 4, // show all backdoors from base
	sendto_commad_type = 5, // send command to victim
	exit_type = 6, // exit
	send_command_type = 7, // send to all victims
	clear_command_type = 8 // clear screen
};

class CommandCenter {
private:
	std::string current_cmd = "";

	command_types ident_type();
	void show_help();
public:
	CommandCenter();
	CommandCenter(const std::string& cmd);
	~CommandCenter();
	void execute_command();
	void set_command(const std::string& cmd);


};
