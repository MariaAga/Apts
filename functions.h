
#ifndef HEADER_FILE
#define HEADER_FILE

typedef struct apt {
	int id;
	char* address;
	int price;
	short int rooms;
	short int day;
	short int month;
	short int year;
	struct apt* next;
	/*OPTION B:
	struct apt* next_id;
	struct apt* next_rooms;
	struct apt* next_date;
	struct apt* next_address;
	struct apt* next price;
	*/
	struct apt* prev;
}Apt;

typedef struct aptlist {
	Apt* head;
	Apt* tail;
}AptList;

typedef struct listNode {
	char* data;
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
void get_an_apt(char* command);
void buy_an_apt(char* command);
void add_an_apt(char* command);
void delete_an_apt(char* command);
#define N 7

#endif