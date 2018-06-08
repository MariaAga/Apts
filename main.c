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



int main()//TODO create empty lists
{
	char* short_term_history[N];
	char* command, *prev_command;
	List old_commands;

	AptList* apt_list = load_apts_from_file();
	int show_index = 0;
	int index_history = 0, total_commands;	
	int i;
	char* add = "add-an-apt"; char* get = "get-an-apt"; char* buy = "buy-an-apt"; char* delete_command = "delete-an-apt";
	command = (char*)malloc(sizeof(char) * (COMMAND + 1));
	prev_command = (char*)malloc(sizeof(char) * (COMMAND + 1));

	total_commands = load_commands_from_file(&old_commands, short_term_history,&show_index)+1;
	printf("Please enter one of the following commands:\n"
	"add-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n"
	"For reconstruction commands, please enter :\n"
	"!!, !num, history, short_history or !num^str1^str2\n"
	"To exit, enter exit.\n>> ");
	fgets(command, COMMAND , stdin);
	//copy_string(short_term_history[show_index], COMMAND , command);
	while (strcmp(command, "exit\n")!=0) {

		if (strstr(command, get) != NULL) {
			get_an_apt(apt_list,strstr(command, get)+strlen(get));
			shift_command(short_term_history, command, &index_history, &old_commands);
			printf(">> ");
			fgets(command, COMMAND , stdin);
			total_commands++;
		}
		else if (strstr(command, add) != NULL) {
			add_an_apt(apt_list,strstr(command,add) + strlen(add));
			shift_command(short_term_history, command, &index_history, &old_commands);
			printf(">> ");
			fgets(command, COMMAND , stdin);
			total_commands++;
		}
		else if (strstr(command, buy) != NULL) {
			buy_an_apt(apt_list,strstr(command, buy) + strlen(buy));
			shift_command(short_term_history, command, &index_history, &old_commands);
			printf(">> ");
			fgets(command, COMMAND , stdin);
			total_commands++;
		}
		else if (strstr(command,delete_command) != NULL) {
			delete_an_apt(apt_list,strstr(command, delete_command) + sizeof(delete_command));
			shift_command(short_term_history, command, &index_history, &old_commands);
			printf(">> ");
			fgets(command, COMMAND , stdin);
			total_commands++;
		}
	
		else if (command== "!!") { // run last command from short_term_history
			printf("%s\n", short_term_history[0]);
			copy_string(command, COMMAND , short_term_history[0]);
		}
		else if (strcmp(command,"history\n")==0) {// show all short_term_history and all old_commands
			show_history(old_commands, short_term_history, total_commands);
			printf(">> ");
			fgets(command, COMMAND, stdin);

		}
		else if (strcmp(command, "short_history\n")==0) {// show all short_term_history

			for (i = N-1; i>=0; i--) {
				if (strlen(short_term_history[i]) > 0) {
					printf("%d: %s\n", (total_commands-i-1), short_term_history[i]);
				}
			}
			printf(">> ");
			fgets(command, COMMAND, stdin);
		}
		else if (strstr(command, "!")!=NULL) {
			filter_number_command(strstr(command, "!"), &show_index, 0);
			if (strstr(command, "^") != NULL) {// !num^str1^str2 action - run the num command and swap str1 with str2
				copy_string(prev_command, COMMAND , command);
				if (total_commands - show_index<=N) { //last command is in the short_term_hisoty
					copy_string(command, COMMAND , short_term_history[total_commands - show_index-1]);
				}
				else {//last command is in the long history
					get_n_command(show_index, old_commands, &command);
				}
				edit_command(&command,prev_command);
			}
			else { //command is !num - show the num command
				if (total_commands - show_index<7) { //last command is in the short_term_hisoty
					copy_string(command, COMMAND , short_term_history[total_commands - show_index]);
				}
				else {//last command is in the long history
					get_n_command(show_index, old_commands, &command);
				}
			}
		}
		else {
			printf("Wrong command \n>> ");
			fgets(command, COMMAND, stdin);
		}

		
	}
	printf("Good Bye!\n");
	upload_apts_to_file(apt_list);
	upload_commands_to_file(&old_commands, total_commands, short_term_history);
	free(command);
	free(prev_command);
	system("PAUSE");
}
