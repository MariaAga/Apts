
#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <string.h>
#include <assert.h> 
#include <malloc.h>
#include <time.h>
#include <stdlib.h> 

#define N 7
#define COMMAND 512

typedef unsigned char BYTE;

typedef struct apt {
	short int id;
	short int address_len;
	char* address;
	int price;
	short int rooms;
	struct tm entry_date;
	struct tm db_entry_date;

}Apt;

typedef struct apt_node {
	Apt* apt;
	struct apt_node* next;
	struct apt_node* prev;
}AptNode;

typedef struct aptlist {
	AptNode* head;
	AptNode* tail;
	int amount;
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

int load_commands_from_file(List* commands, char *short_term_history[N], int*show_index);
void upload_commands_to_file(List* commands, int total_commands, char *short_term_history[N]);
AptList* load_apts_from_file();
void upload_apts_to_file(AptList* apts);


void get_an_apt(AptList* apt_list,char* command);
void buy_an_apt(AptList* apt_list, char* command);
void add_an_apt(AptList* apt_list, char* command);
void delete_an_apt(AptList* apt_list, char* command);


void insertDataToEndList(List* head, char* data, int size);
void freeList(List* lst);
void shift_command(char *short_term_history[N], char* command, int* index_history, List* old_commands);
void get_n_command(int show_index, List old_commands , char **command );
void edit_command(char** command, char* prev_command);
void show_history(List old_commands, char *short_term_history[N], int total);
void free_commands(char *short_term_history[N]);
void free_old_commands(List* commands);


void parse_command(char* command, int* max_price, int* min_num_room, int* max_num_room, struct tm* date);
void filter_number_command(char*command, int* var, int command_len);
void filter_date_command(char* command, struct tm* date, int command_len);
void show_recent_apts(AptList* apt_list , int show_days);
void get_sorted_filtered_apt(AptList* apt_list, int max_price, int min_num_room, int max_num_room, struct tm date,int sort);
void print_apt(AptNode node);
int date_filter(struct tm entry_date, struct tm date);

void number_from_string(char* str, int* num);
int char_to_int(char ch);

void fill_apt_from_str(Apt* apt, char* str);
void instert_apt_sorted(AptList* apt_list, AptNode* node);
void free_apt_node(AptNode* node);
void free_apt_list(AptList* apts);

void delete_recent_apts(AptList * apt_list, int show_days);

void bits_to_file(FILE* file, Apt apt);
void db_date_to_file(FILE* file, Apt apt);
void file_to_bits(FILE* file, Apt* apt);
void file_to_db_date(FILE* file, Apt* apt);

void copy_string(char* dest, int len, char* source);

#endif
