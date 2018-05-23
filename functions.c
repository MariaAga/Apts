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

void filter_number_command(char* command, int* var) {
	int command_len = strlen(command);
	if (command != NULL) {
		*var = 0;
		command = command + strlen(command_len) + 1;
		int i = 0;
		while (command[i] != ' ' && command[i] != NULL) {
			*var = *var * 10 + atoi(command[i]);
			i++;
		}
	}
}