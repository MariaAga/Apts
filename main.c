//Maria Agaphonchev
#include <stdio.h>
#include <string.h>
#include <assert.h> 
#include <malloc.h>
#include <time.h>
#include "functions.h"


/*char str[26];
get_time(str);
printf("%s", str);*/
void get_time(char s[26]){
	time_t result = time(NULL);
	char str[26];
	ctime_s(str, sizeof str, &result);
	strcpy_s(s,26, str);
}
int main()
{
	char *short_term_history[N];
	char command[256];
	List old_commands;
	int index_history=0;
	char* add = "add-an-apt"; char* get = "get-an-apt"; char* buy = "buy-an-apt"; char* delete_command = "delete-an-apt";
	printf("Please enter one of the following commands:\n"
	"add-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n"
	"For reconstruction commands, please enter :\n"
	"!!, !num, history, short_history or !num^str1^str2\n"
	"To exit, enter exit.\n");
	fgets(command, sizeof(command), stdin);

	while (command != "exit") {
		short_term_history[index_history] = command;
		index_history++;
		if (index_history >= N) { //TODO cut the oldest command from the array to the linked list and update the history array with the new command

		}
		if (strstr(command, get) != NULL) {
			get_an_apt(strstr(command, get)+sizeof(get));
			fgets(command, sizeof(command), stdin);
		}
		else if (strstr(command, add) != NULL) {
			add_an_apt(strstr(command,add) + sizeof(add));
			fgets(command, sizeof(command), stdin);
		}
		else if (strstr(command, buy) != NULL) {
			buy_an_apt(strstr(command, buy) + sizeof(buy));
			fgets(command, sizeof(command), stdin);
		}
		else if (strstr(command,delete_command) != NULL) {
			delete_an_apt(strstr(command, delete_command) + sizeof(delete_command));
			fgets(command, sizeof(command), stdin);
		}
		else if (command== "!!") { //TODO show last command from short_term_history

		}
		else if (command == "history") {//TODO show all short_term_history and all old_commands

		}
		else if (command == "short_history") {//TODO show all short_term_history
			
		}
		else if (strstr(command, "!")!=NULL) {
			if (strstr(command, "^") != NULL) {//TODO !num^str1^str2 action - run the num command and swap str1 with str2
				
			}
			else { //TODO command is !num - show the num command

			}
		}
		
	}
	system("PAUSE");
}