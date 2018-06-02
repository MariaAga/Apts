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
	int id;
	AptNode* node = apt_list->head;
	AptNode* tmp;
	filter_number_command(command, &id, sizeof("buy-an-apt"));
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
	result->data = (char*)malloc(sizeof(char)*size);
	strcpy_s(result->data, sizeof(char)*size, data);
}


int char_to_int(char ch) {
	return (int)(ch - '0');
}

void free_apt_node(AptNode* node) {
	free(node->apt->address);
	free(node->apt);
	free(node);
}