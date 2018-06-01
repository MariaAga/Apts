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



int main()
{
	char *short_term_history[N];
	char command[COMMAND];
	List old_commands;
	ListNode* node;
	ListNode* curr;
	AptList* apt_list;
	int show_index = 0;
	int index_history=0,total_commands=1;
	int i,j;
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
			get_an_apt(apt_list,strstr(command, get)+sizeof(get));
			shift_command(short_term_history, command, index_history, &old_commands);
			fgets(command, sizeof(command), stdin);
			total_commands++;
		}
		else if (strstr(command, add) != NULL) {
			add_an_apt(apt_list,strstr(command,add) + sizeof(add));
			shift_command(short_term_history, command, index_history, &old_commands);
			fgets(command, sizeof(command), stdin);
			total_commands++;
		}
		else if (strstr(command, buy) != NULL) {
			buy_an_apt(apt_list,strstr(command, buy) + sizeof(buy));
			shift_command(short_term_history, command, index_history, &old_commands);
			fgets(command, sizeof(command), stdin);
			total_commands++;
		}
		else if (strstr(command,delete_command) != NULL) {
			delete_an_apt(apt_list,strstr(command, delete_command) + sizeof(delete_command));
			shift_command(short_term_history, command, index_history, &old_commands);
			fgets(command, sizeof(command), stdin);
			total_commands++;
		}
	
		else if (command== "!!") { // run last command from short_term_history
			printf("%s\n", short_term_history[0]);
			strcpy_s(command, COMMAND, short_term_history[0]);
		}
		else if (command == "history") {// show all short_term_history and all old_commands
			i = 0;
			curr = old_commands.head;
			while (curr != NULL) {
				i++;
				printf("%d = %s\n", i, curr->data);
			}
			for ( j = 0; j < N; j++) {
				if (strlen(short_term_history[j]) > 0) {
					printf("%d - %s\n", (i + j), short_term_history[j]);
				}
				i++;
			}
		}
		else if (command == "short_history") {// show all short_term_history

			for (i = 0; i < N; i++) {
				if (strlen(short_term_history[i]) > 0) {
					printf("%d - %s\n", (i+1), short_term_history[i]);
				}
			}
		}
		else if (strstr(command, "!")!=NULL) {
			if (strstr(command, "^") != NULL) {//TODO !num^str1^str2 action - run the num command and swap str1 with str2
				
			}
			else { //TODO command is !num - show the num command
				filter_number_command(command, &show_index);
				if (total_commands - show_index<7) { //last command is in the short_term_hisoty
					strcpy_s(command, COMMAND, short_term_history[total_commands - show_index]);
				}
				else {//last command is in the long history
					get_n_command(show_index, old_commands, &command);
				}
			}
		}

		
	}
	system("PAUSE");
}
