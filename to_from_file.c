#include "functions.h"

void upload_commands_to_file(List* commands, int total_commands,char *short_term_history[N]){
	ListNode* node = commands->head;
	FILE* file;
	int i;
	fopen_s(&file, "command.txt", "w");
	if (file != NULL) {
		if (total_commands > 7) {
			for (i = 0; i < 7; i++) {
				fprintf(file, short_term_history[i]);
			}
			while (node != NULL) {
				fprintf(file, node->data);
				node = node->next;
			}
			free_old_commands(commands);
		}
		else {
			for (i = 0; i < total_commands - 1; i++) {
				fprintf(file, short_term_history[i]);
			}
		}
		fclose(file);
	}
	else {
		printf("error opening the file");
	}
	free_commands(short_term_history);

}


int load_commands_from_file(List* commands, char *short_term_history[N],int*show_index){
	FILE* file;
	int i, total = 0;
	char* command = (char*)malloc(sizeof(char) * (COMMAND + 1));
	fopen_s(&file, "command.txt", "r");
	commands->head = commands->tail = NULL;
	for (i = 0; i < N; i++) { // init the short term history
		short_term_history[i] = (char*)malloc(sizeof(char) * (COMMAND + 1));
	}
	if (file != NULL) {
		while (fgets(command, COMMAND + 1, file)) {
			;
			if (total < 7) {
				strcpy_s(short_term_history[total], (COMMAND + 1),command);
			}
			else {
				insertDataToEndList(commands, command, strlen(command));
			}
			total++;
		}
		fclose(file);
	}
	
	*show_index = total;
	free(command);
	return total;
}


void upload_apts_to_file(AptList* apts) {
	AptNode* node = apts->head;
	FILE* file;
	fopen_s(&file, "apt.bin", "wb");
	if (file != NULL) {
		while (node != NULL) {
			fwrite(&node->apt->id, sizeof(short int), 1, file);
			fwrite(&node->apt->address_len, sizeof(short int), 1, file);
			fwrite(node->apt->address, sizeof(char), node->apt->address_len, file);
			fwrite(&node->apt->price, sizeof(int), 1, file);
			bits_to_file(file, *node->apt);
			node = node->next;
		}
		fclose(file);
	}
	else {
		printf("error opening the file");
	}
	free_apt_list(apts);

}


AptList* load_apts_from_file()
{
	AptList* apts = (AptList*)malloc(sizeof(AptList));
	AptNode* node=NULL;
	AptNode* node_prev=NULL;
	FILE* file;
	int id;

	fopen_s(&file, "apt.bin", "rb");
	apts->head = apts->tail = NULL;
	if (file != NULL) {
		while (fread(&id, sizeof(short int), 1, file) == 1) {
			node = (AptNode*)malloc(sizeof(AptNode));
			node->apt = (Apt*)malloc(sizeof(Apt));
			node->apt->id = id;
			fread(&node->apt->address_len, sizeof(short int), 1, file);

			node->apt->address = (char*)malloc(sizeof(char)*(node->apt->address_len) + 1);
			fread(node->apt->address, sizeof(char), node->apt->address_len, file);
			node->apt->address[node->apt->address_len] = '\0';

			fread(&node->apt->price, sizeof(int), 1, file);
			file_to_bits(file, node->apt);
			
			if (apts->head == NULL) {
				apts->head = node;
				node->prev = NULL;
			}
			else {
				node->prev = node_prev;
				node_prev->next = node;
				node->next = NULL;
			}
			node_prev = node;
		}
		apts->tail = node;
		
		fclose(file);
	}
	
	return apts;
	
}

void db_date_to_file(FILE* file, Apt apt) {
	/*byte[0] - 5 bits day + 3 bits from month,
	byte[1] - 1 from month, 7 from year*/
	unsigned char byte[2];
	unsigned char tmp;
	for (int i = 0; i < 2; i++) {
		byte[i] = 0;
	}

	byte[0] = apt.db_entry_date.tm_mday;
	byte[0] = byte[0] << 4;

	tmp = apt.db_entry_date.tm_mon;
	tmp = tmp >> 1;
	byte[0] = byte[0] | tmp;
	
	tmp = apt.db_entry_date.tm_mon;
	tmp = tmp << 7;
	byte[1] = byte[1] | tmp;

	tmp = apt.db_entry_date.tm_year;
	byte[1] = byte[1] | tmp;

	fwrite(byte, sizeof(unsigned char), 2, file);
}

void bits_to_file(FILE* file, Apt apt) {
	/*byte[0] - 4 bits rooms + 4 bits from day,
	byte[1] - 1 bit from days, 4 from month, 3 from year
	byte[2] - 4 from year, 4 zeros*/
	unsigned char byte[3];
	unsigned char tmp;
	for (int i = 0; i < 3; i++) {
		byte[i] = 0;
	}

	byte[0] = apt.rooms;
	byte[0] = byte[0] << 4;

	tmp = apt.entry_date.tm_mday;
	tmp = tmp >> 1;
	byte[0] = byte[0] | tmp;

	tmp = apt.entry_date.tm_mday;
	tmp = tmp << 7;
	byte[1] = byte[1] | tmp;

	tmp = apt.entry_date.tm_mon;
	tmp = tmp << 3;
	byte[1] = byte[1] | tmp;

	tmp = apt.entry_date.tm_year;
	tmp = tmp >> 4;
	byte[1] = byte[1] | tmp;

	tmp = apt.entry_date.tm_year;
	tmp = tmp << 3;
	byte[2] = byte[2] | tmp;

	fwrite(byte, sizeof(unsigned char), 3, file);
	db_date_to_file(file, apt);
}


void file_to_bits(FILE* file, Apt* apt) {
	/*byte[0] - 4 bits rooms + 4 bits from day,
	byte[1] - 1 bit from days, 4 from month, 3 from year
	byte[2] - 4 from year, 4 zeros*/
	unsigned char byte[3];
	unsigned char tmp;

	fread(byte,sizeof(unsigned char), 3, file);

	apt->rooms = byte[0] >> 4;
	apt->entry_date.tm_mday = byte[0] & 15; //mask 00001111
	apt->entry_date.tm_mday = apt->entry_date.tm_mday << 1;
	apt->entry_date.tm_mday = apt->entry_date.tm_mday | (byte[1] >> 7);
	apt->entry_date.tm_mon = byte[1] & 120; //maks 01111000
	apt->entry_date.tm_mon = apt->entry_date.tm_mon >> 3;
	apt->entry_date.tm_year = byte[1] & 7; //mask 00000111
	apt->entry_date.tm_year = apt->entry_date.tm_year << 4;
	tmp = byte[2];
	tmp = tmp >> 3;
	apt->entry_date.tm_year = apt->entry_date.tm_year | tmp;
	file_to_db_date(file, apt);

}

void file_to_db_date(FILE* file, Apt* apt) {
	/*byte[0] - 5 bits day + 3 bits from month,
	byte[1] - 1 from month, 7 from year*/
	unsigned char byte[3];

	fread(byte, sizeof(unsigned char), 2, file);
	apt->db_entry_date.tm_mday = byte[0] >> 3;

	apt->db_entry_date.tm_mon = byte[0] & 7; //mask 00000111
	apt->db_entry_date.tm_mon = apt->db_entry_date.tm_mon << 1;
	apt->db_entry_date.tm_mon = apt->db_entry_date.tm_mon | (byte[1] >> 7);

	apt->db_entry_date.tm_year = byte[1] & 127; // maks 01111111
}