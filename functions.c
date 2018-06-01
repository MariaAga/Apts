#include "functions.h"

List load_commands_from_file()
{
	//return List();
}

AptList load_apts_from_file()
{
	//return AptList();
}


void buy_an_apt(AptList* apt_list, char * command)
{
}

void add_an_apt(AptList* apt_list, char * command)
{
}

void delete_an_apt(AptList* apt_list, char * command)
{
}

void freeList(List* lst)
{
	ListNode* curr = lst->head, *next;

	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void insertDataToEndList(List* head, char* data,int size)
{
	ListNode *result;
	result = (ListNode *)malloc(sizeof(ListNode));
	result->next = NULL;
	if (head->head == NULL) {
		head->head = head->tail = result;
	}
	else {
		head->tail->next = result;
		head->tail = result;
	}
	result->size = size;
	result->data = (char*)malloc(sizeof(char)*size);
	strcpy_s(result->data, sizeof(char)*size, data);
}


void shift_command(char *short_term_history[N], char* command,int index_history,List* old_commands) {
	
	index_history=(index_history+1)%8;
	if (index_history >= N) { //cut the oldest command from the array to the linked list and update the history array with the new command
		insertDataToEndList(old_commands, short_term_history[0], strlen(short_term_history[0]));
		index_history--;
	}
	for (int i = 1; i < N - 1; i++) { //shift the shrt history array
		strcpy_s(short_term_history[i] ,COMMAND,short_term_history[i+1]);
	}
	strcpy_s(short_term_history[index_history], COMMAND, command);
	short_term_history[0] = "";
}

void get_n_command(int show_index, List old_commands, char command[][COMMAND])
{
	ListNode* node = old_commands.head;
	show_index -= 7;
	while (show_index > 0 && node != NULL) {
		show_index--;
		node = node->next;
	}
	if (show_index == 0) {
		strcpy_s(*command, COMMAND, node->data);
	}
	else {
		printf("Error getting the %d command from old commands index\n", show_index);
	}

}

void filter_number_command(char* command, int* var) {
	int command_len = strlen(command);
	int i = 0;
	if (command != NULL) {
		*var = 0;
		while (command[i] >= 9 && command[i] >= 0 && command[i] != '\0') {
			*var = *var * 10 + char_to_int(command[i]);
			i++;
		}
	}
}

void edit_command(char command[][COMMAND], char prev_command[COMMAND]) {//!num^str1^str2 action
	char str1 [COMMAND];
	char str2 [COMMAND];
	char command_end[COMMAND];
	char* change_point;
	int command_len = strlen(*command), prev_command_len = strlen(prev_command);
	int str1_len = 0 , str2_len = 0;
	strcpy_s(str1,COMMAND,strstr(prev_command, "^"));
	strcpy_s(str2, COMMAND, strstr(str1, "^"));
	str2_len = strlen(str2);
	str1_len = strlen(str1) - str2_len - 1;
	strcpy_s(command_end, COMMAND, *command + str2_len + str1_len + 2);
	change_point = strstr(*command, str1);
	for (int i = 0; i < str2_len; i++) {
		change_point[i] = str2[i];
	}
	change_point[str2_len] = '\0';
	strcat_s(*command, COMMAND, command_end);
}

int char_to_int(char ch) {
	return (int)(ch - '0');
}

