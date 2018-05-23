
#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <string.h>
#include <assert.h> 
#include <malloc.h>
#include <time.h>

typedef struct apt {
	int id;
	char* address;
	int price;
	short int rooms;
	struct tm entry_date;
	struct tm db_entry_date;

}Apt;

typedef struct apt_node {
	Apt* apt;
	struct apt* next;
	struct apt* prev;
}AptNode;

typedef struct aptlist {
	AptNode* head;
	AptNode* tail;
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

void parse_command(char* command, int* max_price, int* min_num_room, int* max_num_room, struct tm* date);
void filter_number_command(char*command, int* var, int command_len);
void filter_date_command(char* command, struct tm* date, int command_len);
void show_recent_apts(AptList* apt_list , int show_days);
void get_sorted_filtered_apt(AptList* apt_list, int max_price, int min_num_room, int max_num_room, struct tm* date);

#endif