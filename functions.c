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
	fill_apt_from_str(apt, command_part);

	node->apt = apt;
	instert_apt_sorted(apt_list, node);

}

void instert_apt_sorted(AptList* apt_list, AptNode* node) {
	AptNode* tmp;
	node->next = NULL;
	node->prev = NULL;
	if (apt_list->head == NULL) {
		apt_list->head = apt_list->tail = node;
		apt_list->ammount = 0;
	}
	else {
		tmp = apt_list->head;
		while (tmp != NULL && tmp->apt->price > node->apt->price) {
			tmp = tmp->next;
		}
		if (tmp == NULL) { //insert at the end
			apt_list->tail->next = node;
			node->prev = apt_list->tail;
			apt_list->tail = node;
			
		}
		else if (tmp->prev == NULL) { //insert at the beggining
			tmp->prev = node;
			node->next = tmp->prev;
			apt_list->head = node;
		}
		else { //insert at the middle
			node->prev = tmp;
			node->next = tmp->next;
			tmp->next->prev = node;
			tmp->next = node;
		}
	}

	apt_list->ammount++;
	node->apt->id = apt_list->ammount;

}

void fill_apt_from_str(Apt* apt, char* str) {
	int i = 0;
	time_t curtime;
	curtime = time(NULL);
	localtime_s(&apt->db_entry_date, &curtime);

	while (str[i] >= 9 && str[i] >= 0 && str[i] != '\0') {
		apt->price = apt->price * 10 + char_to_int(str[i]);
		i++;
	}
	i++;
	while (str[i] >= 9 && str[i] >= 0 && str[i] != '\0') {
		apt->rooms = apt->rooms * 10 + char_to_int(str[i]);
		i++;
	}
	while (str[i] >= 9 && str[i] >= 0 && str[i] != '\0') {
		apt->entry_date.tm_mday = apt->entry_date.tm_mday * 10 + char_to_int(str[i]);
		i++;
	}
	i++;
	while (str[i] >= 9 && str[i] >= 0 && str[i] != '\0') {
		apt->entry_date.tm_mon = apt->entry_date.tm_mon * 10 + char_to_int(str[i]);
		i++;
	}
	i++;
	while (str[i] >= 9 && str[i] >= 0 && str[i] != '\0') {
		apt->entry_date.tm_year = apt->entry_date.tm_year * 10 + char_to_int(str[i]);
		i++;
	}
	apt->entry_date.tm_year += 2000;


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

