#include "functions.h"

void shift_command(char *short_term_history[N], char* command, int index_history, List* old_commands) {

	index_history = (index_history + 1) % 8;
	if (index_history >= N) { //cut the oldest command from the array to the linked list and update the history array with the new command
		insertDataToEndList(old_commands, short_term_history[0], strlen(short_term_history[0]));
		index_history--;
	}
	for (int i = 1; i < N - 1; i++) { //shift the shrt history array
		strcpy_s(short_term_history[i], COMMAND, short_term_history[i + 1]);
	}
	strcpy_s(short_term_history[index_history], COMMAND, command);
	short_term_history[0] = "";
}

void get_n_command(int show_index, List old_commands, char command[][COMMAND])
{
	ListNode* node = old_commands.head;
	show_index -= 7;
	while (show_index > 0 && node != NULL) {
		show_index--;
		node = node->next;
	}
	if (show_index == 0) {
		strcpy_s(*command, COMMAND, node->data);
	}
	else {
		printf("Error getting the %d command from old commands index\n", show_index);
	}

}

void filter_number_command(char* command, int* var, int command_len) {
	command = command + command_len + 1;
	number_from_string(command, var);
}

void number_from_string(char* str, int* num) {
	int i = 0;
	if (str != NULL) {
		*num = 0;
		while (str[i] >= 9 && str[i] >= 0 && str[i] != '\0') {
			*num = *num * 10 + char_to_int(str[i]);
			i++;
		}
	}
}

void edit_command(char command[][COMMAND], char prev_command[COMMAND]) {//!num^str1^str2 action
	char str1[COMMAND];
	char str2[COMMAND];
	char command_end[COMMAND];
	char* change_point;
	int command_len = strlen(*command), prev_command_len = strlen(prev_command);
	int str1_len = 0, str2_len = 0;
	strcpy_s(str1, COMMAND, (strstr(prev_command, "^")+1));
	strcpy_s(str2, COMMAND, (strstr(str1, "^")+1));
	str2_len = strlen(str2);
	str1_len = strlen(str1) - str2_len - 1;
	strcpy_s(command_end, COMMAND, *command + str2_len + str1_len + 2);
	change_point = strstr(*command, str1);
	for (int i = 0; i < str2_len; i++) {
		change_point[i] = str2[i];
	}
	change_point[str2_len] = '\0';
	strcat_s(*command, COMMAND, command_end);
}


void parse_command(char* command, int* max_price, int* min_num_room, int* max_num_room, struct tm* date) {
	char *max_price_command = "-MaximumPrice"; char *min_num_room_command = "-MinimumNumRooms"; char *max_num_room_command = "-MaximumNumRooms"; char *date_command = "-Date";
	filter_number_command(strstr(command, max_price_command), max_price, strlen(max_price_command));
	filter_number_command(strstr(command, min_num_room_command), min_num_room, strlen(min_num_room_command));
	filter_number_command(strstr(command, max_num_room_command), max_num_room, strlen(max_num_room_command));
	filter_date_command(strstr(command, date_command), date, strlen(date_command));
}


void filter_date_command(char* command, struct tm* date, int command_len) {
	if (command != NULL) {
		command = command + command_len + 1;
		date->tm_mday = date->tm_mon = date->tm_year = 0;
		date->tm_mday = char_to_int(command[0]) * 10 + char_to_int(command[1]);
		date->tm_mon = char_to_int(command[2]) * 10 + char_to_int(command[3]);
		date->tm_year = char_to_int(command[4]) * 100 + char_to_int(command[5]) * 10 + char_to_int(command[3]) - 1900;
	}
}