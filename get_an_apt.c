#include "functions.h"



void get_an_apt(AptList* apt_list, char * command) //TODO: add -sr -s
{
	int max_price = -1, min_num_room = 0, max_num_room = -1,sort=1;
	time_t raw_time = 0;
	struct tm date; gmtime_s(&date, &raw_time); date.tm_year = 0;
	int show_days;
	
	if (strstr(command, "-Enter") != NULL) {
		filter_number_command(strstr(command, "-Enter"), &show_days, strlen("-Enter"));
		show_recent_apts(apt_list, show_days);
	}
	else { 
		if (strstr(command, "-sr") != NULL) {
			sort = 1;
		}
		else if (strstr(command, "-s") != NULL) {
			sort = -1;
		}
		parse_command(command, &max_price, &min_num_room, &max_num_room, &date);
		get_sorted_filtered_apt(apt_list, max_price, min_num_room, max_num_room, date,sort);
	}

}

void show_recent_apts(AptList * apt_list, int show_days)
{
	AptNode* node = apt_list->head;
	time_t curr_time = time(NULL);
	while (node != NULL) {
		if (difftime(curr_time, mktime(&node->apt->db_entry_date)) <= (show_days * 86400)) { // there are 86400 sec in 1 day
			print_apt(*node);
		}
		node = node->next;
	}
}



void get_sorted_filtered_apt(AptList* apt_list, int max_price, int min_num_room, int max_num_room, struct tm date,int sort) {
	AptNode* node;
	if (sort == 1)
		node = apt_list->head;
	else
		node = apt_list->tail;
	while (node != NULL) {
		if ((node->apt->price <= max_price || max_price < 0) && (node->apt->rooms >= min_num_room) && (node->apt->rooms <= max_num_room || max_num_room < 0) && date_filter(node->apt->entry_date,date)) {
			print_apt(*node);
		}
		if (sort == 1)
			node = node->next;
		else
			node = node->prev;
	}
}

void print_apt(AptNode node) {
	printf("Apt details:\nCode : %d\nAddress : %s\nNumber of rooms: %d\n", node.apt->id,node.apt->address, node.apt->rooms);
	printf("Price: %d \n", node.apt->price);
	printf("Entry date : %d.%d.%d\n", node.apt->entry_date.tm_mday, node.apt->entry_date.tm_mon, (node.apt->entry_date.tm_year + 1900));
	printf("Database entry date : %d.%d.%d\n", node.apt->db_entry_date.tm_mday, node.apt->db_entry_date.tm_mon, (node.apt->db_entry_date.tm_year + 1900));
}

int date_filter(struct tm entry_date, struct tm date) {
	if (date.tm_year == 0)
		return 1;
	time_t t1 = mktime(&entry_date);
	time_t t2 = mktime(&date);
	return ( difftime(t1, t2)<0);
}