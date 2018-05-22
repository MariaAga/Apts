//Maria Agaphonchev

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

void shift_command(char *short_term_history[N], char* command,int index_history,List* old_commands) {
	strcpy_s(short_term_history[index_history] , COMMAND, command);
	index_history++;
	if (index_history >= N) { //cut the oldest command from the array to the linked list and update the history array with the new command
		insertDataToEndList(old_commands, short_term_history[N - 1], strlen(short_term_history[N - 1]));
	}
	for (int i = 0; i < N - 1; i++) { //shift the shrt history array
		strcpy_s(short_term_history[i + 1] ,COMMAND,short_term_history[i]);
	}
	short_term_history[0] = "";
}

int main()
{
	char *short_term_history[N]; //array of strings
	char command[COMMAND];
	List old_commands;
	ListNode* node;
	int index_history=0;
	int i;
	char* add = "add-an-apt"; char* get = "get-an-apt"; char* buy = "buy-an-apt"; char* delete_command = "delete-an-apt";
	for (i = 0; i < N; i++) { // init the short term history
		short_term_history[i] = (char*)malloc(sizeof(char) * COMMAND);
		short_term_history[i]= "";
	}
	old_commands.head = old_commands.tail = NULL; //init the long term history
	printf("Please enter one of the following commands:\n"
	"add-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n"
	"For reconstruction commands, please enter :\n"
	"!!, !num, history, short_history or !num^str1^str2\n"
	"To exit, enter exit.\n");
	fgets(command, sizeof(command), stdin);
	strcpy_s(short_term_history[0], COMMAND, command);
	while (command != "exit") {

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

		shift_command(short_term_history, command, index_history, &old_commands);
	}
	system("PAUSE");
}
