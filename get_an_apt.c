#include "functions.h"



void get_an_apt(AptList* apt_list, char * command) //TODO: add -se -s
{
	int max_price = -1, min_num_room = 0, max_num_room = -1;
	time_t raw_time = 0;
	struct tm date; gmtime_s(&date, &raw_time);
	int show_days;
	if (strstr(command, "-Enter") != NULL) {
		filter_number_command(strstr(command, "-Enter"), &show_days);
		get_recent_apts(apt_list, show_days);
	}
	else { //TODO: sort?
		parse_command(command, &max_price, &min_num_room, &max_num_room, &date);
		get_sorted_filtered_apt(apt_list, max_price, min_num_room, max_num_room, date);
	}

}

void parse_command(char* command, int* max_price, int* min_num_room, int* max_num_room, struct tm* date) {
	char *max_price_command = "-MaximumPrice"; char *min_num_room_command = "-MinimumNumRooms"; char *max_num_room_command = "-MaximumNumRooms"; char *date_command = "-Date";
	filter_number_command(strstr(command, max_price_command), max_price);
	filter_number_command(strstr(command, min_num_room_command), min_num_room);
	filter_number_command(strstr(command, max_num_room_command), max_num_room);
	filter_date_command(strstr(command, date_command), date);
}


void filter_date_command(char* command, struct tm* date ) { 
	int command_len = strlen(command);
	if (command != NULL) {
		date->tm_mday = date->tm_mon = date->tm_year = 0;
		date->tm_mday = char_to_int(command[0]) * 10 + char_to_int(command[1]);
		date->tm_mon = char_to_int(command[2]) * 10 + char_to_int(command[3]);
		date->tm_year = char_to_int(command[4]) * 100+ char_to_int(command[5]) * 10 + char_to_int(command[3]) - 1900;
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


void get_sorted_filtered_apt(AptList* apt_list, int max_price, int min_num_room, int max_num_room, struct tm date) {
	AptNode* node = apt_list->head;
	while (node != NULL) {
		if ((node->apt->price < max_price || max_price < 0) && (node->apt->rooms > min_num_room) && (node->apt->rooms > max_num_room || max_num_room < 0)) {
			print_apt(*node);
		}
		node = node->next;
	}
}

void print_apt(AptNode node) {
	printf("Apt details:\nCode : %d\nAddress : %s\n Number of rooms : %d\n", node.apt->id,node.apt->address, node.apt->rooms);
	printf("Entry date : %d.%d.%d\n", node.apt->entry_date.tm_mday, node.apt->entry_date.tm_mon, (node.apt->entry_date.tm_year + 1900));
	printf("Database entry date : %d.%d.%d", node.apt->db_entry_date.tm_mday, node.apt->db_entry_date.tm_mon, (node.apt->db_entry_date.tm_year + 1900));
}