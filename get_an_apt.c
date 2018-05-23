#include "functions.h"



void get_an_apt(AptList* apt_list, char * command)
{
	int max_price = -1, min_num_room = 0, max_num_room = -1;
	time_t raw_time = 0;
	struct tm date; gmtime_s(&date, raw_time);
	int show_days;
	if (strstr(command, "-Enter") != NULL) {
		filter_number_command(strstr(command, "-Enter"), &show_days, strlen("-Enter"));
		get_recent_apts(apt_list, show_days);
	}
	else {
		parse_command(command, &max_price, &min_num_room, &max_num_room, &date);
		get_sorted_filtered_apt(apt_list, max_price, min_num_room, max_num_room, date);
	}

}

void parse_command(char* command, int* max_price, int* min_num_room, int* max_num_room, struct tm* date) {
	char *max_price_command = "-MaximumPrice"; char *min_num_room_command = "-MinimumNumRooms"; char *max_num_room_command = "-MaximumNumRooms"; char *date_command = "-Date";
	char* command_str;
	int i;
	filter_number_command(strstr(command, max_price_command), max_price, strlen(max_price_command));
	filter_number_command(strstr(command, min_num_room_command), min_num_room, strlen(min_num_room_command));
	filter_number_command(strstr(command, max_num_room_command), max_num_room, strlen(max_num_room_command));
	filter_date_command(strstr(command, date_command), date, strlen(date_command));
}

void filter_number_command(char* command, int* var, int command_len) {
	if (command != NULL) {
		*var = 0;
		command = command + strlen(command_len) + 1;
		int i = 0;
		while (command[i] != ' ' && command[i] != NULL) {
			*var = *var * 10 + atoi(command[i]);
			i++;
		}
	}
}
void filter_date_command(char* command, struct tm* date, int command_len) {
	if (command != NULL) {
		date->tm_mday = date->tm_mon = date->tm_year = 0;
		command = command + strlen(command_len) + 1;
		date->tm_mday = atoi(command[0] * 10) + atoi(command[1]);
		date->tm_mon = atoi(command[2] * 10) + atoi(command[3]);
		date->tm_year = atoi(command[4] * 100)+ atoi(command[5] * 10) + atoi(command[3]) - 1900;
	}
}

void show_recent_apts(AptList * apt_list, int show_days)
{
}


void get_sorted_filtered_apt(AptList* apt_list, int max_price, int min_num_room, int max_num_room, struct tm date) {
	AptNode* node = apt_list->head;
	while (node != NULL) {
		if ((node->apt->price < max_price || max_price < 0) && (node->apt->rooms > min_num_room) && (node->apt->rooms > max_num_room || max_num_room < 0)) {
			printf("Apt details:\nCode : %d\nAddress : %s\n Number of rooms : %d\n",node->apt->id, node->apt->rooms);
			printf("Entry date : %d.%d.%d\n", node->apt->entry_date.tm_mday, node->apt->entry_date.tm_mon, (node->apt->entry_date.tm_year + 1900));
			printf("Database entry date : %d.%d.%d", node->apt->db_entry_date.tm_mday, node->apt->db_entry_date.tm_mon, (node->apt->db_entry_date.tm_year + 1900));
	}


}