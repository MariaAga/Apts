
#include "functions.h"

void add_an_apt(AptList* apt_list, char * command) //TODO: ALWAYS ADD SORTED BY PRICE (HIGH PRICE FIRST)
{//Example: add-an-apt "Hasavyonim 23 Ramat Ono" 2000000 4 01 01 20
	AptNode* node = (AptNode*)malloc(sizeof(AptNode));
	Apt* apt = (Apt*)malloc(sizeof(Apt));
	int address_length = 0;
	int i = 0;
	char* command_part;

	command = strstr(command, "\"") + 1;
	command_part = strstr(command, "\"") ;
	address_length = (command_part - command ) / sizeof(char);
	apt->address_len = address_length;
	apt->address = (char*)malloc(sizeof(char)*address_length + 1);
	strncpy_s(apt->address, address_length+1, command, address_length);
	apt->address[address_length] = '\0';
	fill_apt_from_str(apt, command_part+1);

	node->apt = apt;
	instert_apt_sorted(apt_list, node);

}

void instert_apt_sorted(AptList* apt_list, AptNode* node) {//TODO: FIX
	AptNode* tmp;
	node->next = NULL;
	node->prev = NULL;
	if (apt_list->head == NULL) {
		apt_list->head = apt_list->tail = node;
		apt_list->amount = 0;
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
		else if (tmp->prev == NULL) { //insert at the beginning
			tmp->prev = node;
			node->next = tmp;
			apt_list->head = node;
		}
		else { //insert at the middle
			node->prev = tmp;
			node->next = tmp->next;
			tmp->next->prev = node;
			tmp->next = node;
		}
	}

	apt_list->amount++;
	node->apt->id = apt_list->amount;

}

void fill_apt_from_str(Apt* apt, char* str) {
	int i = 0;
	time_t curtime;
	curtime = time(NULL);
	localtime_s(&apt->db_entry_date, &curtime);
	apt->price = apt->rooms = apt->entry_date.tm_mday = apt->entry_date.tm_mon = apt->entry_date.tm_year = 0;
	while (str[i] == ' ') { i++; }
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0') {
		apt->price = apt->price * 10 + char_to_int(str[i]);
		i++;
	}
	i++;
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0') {
		apt->rooms = apt->rooms * 10 + char_to_int(str[i]);
		i++;
	}
	i++;
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0') {
		apt->entry_date.tm_mday = apt->entry_date.tm_mday * 10 + char_to_int(str[i]);
		i++;
	}
	i++;
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0') {
		apt->entry_date.tm_mon = apt->entry_date.tm_mon * 10 + char_to_int(str[i]);
		i++;
	}
	i++;
	while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0') {
		apt->entry_date.tm_year = apt->entry_date.tm_year * 10 + char_to_int(str[i]);
		i++;
	}
	apt->entry_date.tm_year += 2000;
	apt->entry_date.tm_year -= 1900;


}