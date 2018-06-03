#include "functions.h"

void shift_command(char *short_term_history[N], char* command, int* index_history, List* old_commands) {

	*index_history = (*index_history + 1) % 9;
	if (*index_history > N) { //cut the oldest command from the array to the linked list and update the history array with the new command
		insertDataToEndList(old_commands, short_term_history[N-1], strlen(short_term_history[N-1]));
		*index_history=*index_history-1;
	}
	if (*index_history > 1) {
		for (int i = N - 1; i > 0; i--) { //shift the shrt history array left
			copy_string(short_term_history[i], COMMAND, short_term_history[i - 1]);
		}

		copy_string(short_term_history[0], COMMAND, command);
	}
}

void copy_string(char* dest, int len, char* source) {
	free(dest);
	dest = (char*)malloc(sizeof(char)*len+1);
	if (strlen(source)<len) {
		strcpy_s(dest, len, source);
	}

}

void get_n_command(int show_index, List old_commands, char** command)
{
	ListNode* node = old_commands.head;
	
	while (show_index > 0 && node != NULL) {
		show_index--;
		node = node->next;
	}
	if (show_index == 0) {
		node->data = (char*)malloc(sizeof(char) * (COMMAND + 1));
		copy_string(*command, COMMAND, node->data);
	}
	else {
		printf("Error getting the %d command from old commands index\n", show_index);
	}

}

void filter_number_command(char* command, int* var, int command_len) {
	if (command != NULL) {
		command = command + command_len + 1;
		number_from_string(command, var);
	}
}

void number_from_string(char* str, int* num) {
	int i = 0;
	if (str != NULL) {
		*num = 0;
		while (str[i] == ' ') {
			i++;
		}
		while (str[i] <= '9' && str[i] >= '0' && str[i] != '\0') {
			*num = *num * 10 + char_to_int(str[i]);
			i++;
		}
	}
}

void edit_command(char** command, char* prev_command) {//!num^str1^str2 action
	char str1[COMMAND];
	char str2[COMMAND];
	char command_end[COMMAND];
	char* change_point;
	int command_len = strlen(*command), prev_command_len = strlen(prev_command);
	int str1_len = 0, str2_len = 0;
	strcpy_s(str1, COMMAND , (strstr(prev_command, "^")+1));
	strcpy_s(str2, COMMAND , (strstr(str1, "^")+1));
	str2_len = strlen(str2);
	str1_len = strlen(str1) - str2_len - 1;
	str1[str1_len ] = '\0';
	str2[str2_len-1] = '\0';

	change_point = strstr(*command, str1);
	strcpy_s(command_end, COMMAND,  change_point+str1_len);
	for (int i = 0; i < str2_len; i++) {
		change_point[i] = str2[i];
	}
	change_point[str2_len] = '\0';
	strcat_s(*command, COMMAND-1, command_end);
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

