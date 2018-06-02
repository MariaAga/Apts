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

void add_an_apt(AptList* apt_list, char * command) //TODO: ALWAYS ADD SORTED BY PRICE (HIGH PRICE FIRST)
{//Example: add-an-apt "Hasavyonim 23 Ramat Ono" 2000000 4 01 01 20
	AptNode* node = (AptNode*) malloc(sizeof(AptNode));
	Apt* apt = (Apt*)malloc(sizeof(Apt));
	int address_length = 0;
	int i = 0;
	char* command_part;

	command = strstr(command, "\"")+1;
	command_part = strstr(command, "\"")+1;
	address_length = (command - command_part+1)/sizeof(char);
	apt->address = (char*)malloc(sizeof(char)*address_length+1);
	strncpy_s(apt->address, address_length, command, address_length);
	apt->address[address_length] = '\0';

	while (command_part[i] >= 9 && command_part[i] >= 0 && command_part[i] != '\0') {
		apt->price = apt->price * 10 + char_to_int(command_part[i]);
		i++;
	}
	i++;


	
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


int char_to_int(char ch) {
	return (int)(ch - '0');
}

