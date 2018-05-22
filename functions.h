
#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <string.h>
#include <assert.h> 
#include <malloc.h>
#include <time.h>
#include "functions.h"

typedef struct apt {
	int id;
	char* address;
	int price;
	short int rooms;
	short int day;
	short int month;
	short int year;
	struct apt* next;
	struct apt* prev;
}Apt;

typedef struct aptlist {
	Apt* head;
	Apt* tail;
}AptList;

typedef struct listNode {
	char* data;
	int size;
	struct listNode* next;
}ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
}List;

List load_commands_from_file();
int upload_commands_to_file(List);
AptList load_apts_from_file();
int  upload_apts_to_file(AptList);
void get_an_apt(AptList* apt_list,char* command);
void buy_an_apt(AptList* apt_list, char* command);
void add_an_apt(AptList* apt_list, char* command);
void delete_an_apt(AptList* apt_list, char* command);
#define N 7
#define COMMAND 256

void insertDataToEndList(List* head, char* data, int size);
void freeList(List* lst);
void shift_command(char *short_term_history[N], char* command, int index_history, List* old_commands);


#endif