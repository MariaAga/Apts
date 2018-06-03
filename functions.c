#include "functions.h"

/*
void upload_commands_to_file(List commands) {

}

List load_commands_from_file()
{
	//return List();
}


void upload_apts_to_file(AptList apts) {
	AptNode* node = apts.head;
	FILE* file;

	fopen_s(&file, "apt.bin", "wb");
	while (node != NULL) {
		fwrite(&node->apt->id, sizeof(short int), 1,file);
		fwrite(&node->apt->address_len, sizeof(short int), 1, file);
		fwrite(&node->apt->price, sizeof(int), 1, file);
		bits_to_file(file, *node->apt);
	}

	free_apt_list(apts);
	fclose(file);
}

AptList load_apts_from_file()
{
	//return AptList();
}

void db_date_to_file(FILE* file, Apt apt) {
	/*byte[0] - 5 bits day + 3 bits from month,
	  byte[1] - 1 from month, 7 from year/
	char byte[2];
	char tmp;
	for (int i = 0; i < 2; i++) {
		byte[0] = 0;
	}

	byte[0] = apt.db_entry_date.tm_mday;
	byte[0] = byte[0] << 4;

	tmp = apt.db_entry_date.tm_mon;
	tmp = tmp >> 1;
	byte[0] = byte[0] | tmp;

	tmp = apt.db_entry_date.tm_mon;
	tmp = tmp << 7; 
	byte[1] = byte[1] | tmp;

	tmp = apt.db_entry_date.tm_year;
	byte[1] = byte[1] | tmp;

}

void bits_to_file(FILE* file, Apt apt) {
	/*byte[0] - 4 bits rooms + 4 bits from day, 
	  byte[1] - 1 bit from days, 4 from month, 3 from year
	  byte[2] - 4 from year, 4 zeros/
	char byte[3]; 
	char tmp;
	for (int i = 0; i < 3; i++) {
		byte[0] = 0;
	}

	byte[0] = apt.rooms;
	byte[0]= byte[0] << 4;

	tmp = apt.entry_date.tm_mday;
	tmp = tmp >> 1;
	byte[0] = byte[0] | tmp;

	tmp = apt.entry_date.tm_mday;
	tmp = tmp << 7;
	byte[1] = byte[1] | tmp;

	tmp = apt.entry_date.tm_mon;
	tmp = tmp << 3;
	byte[1] = byte[1] | tmp;

	tmp = apt.entry_date.tm_year;
	tmp = tmp >> 4;
	byte[1] = byte[0] | tmp;

	tmp = apt.entry_date.tm_year;
	tmp = tmp << 3;
	byte[2] = byte[1] | tmp;

	fwrite(byte, sizeof(char), 3, file);

}
*/


void buy_an_apt(AptList* apt_list, char * command)
{	
	int id;
	AptNode* node = apt_list->head;
	AptNode* tmp;
	filter_number_command(command, &id, 0);
	while (node != NULL && node->apt->id != id) {
		node = node->next;
	}
	if (node != NULL) {// prev node next
		tmp = node->prev;
		node->prev->next = node->next;
		node->next->prev = tmp;
		free_apt_node(node);
	}
	
}


void delete_an_apt(AptList* apt_list, char * command)
{
	int show_days;
	filter_number_command(strstr(command, "-Enter"), &show_days, strlen("-Enter"));
	delete_recent_apts(apt_list, show_days);

}

void delete_recent_apts(AptList * apt_list, int show_days)
{
	AptNode* node = apt_list->head;
	AptNode* next;
	time_t curr_time = time(NULL);
	while (node != NULL) {
		next = node->next;
		if (difftime(curr_time, mktime(&node->apt->db_entry_date)) <= (show_days * 86400)) { // there are 86400 sec in 1 day
			free_apt_node(node);
		}
		node = next;
	}
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
	result->data = (char*)malloc(sizeof(char)*size+1);
	strcpy_s(result->data, sizeof(char)*size+1, data);
}


int char_to_int(char ch) {
	return (int)(ch - '0');
}

void free_apt_node(AptNode* node) {
	free(node->apt->address);
	free(node->apt);
	free(node);
}