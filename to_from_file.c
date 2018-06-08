#include "functions.h"

void upload_commands_to_file(List commands) {

}

List load_commands_from_file()
{
	//return List();
}


void upload_apts_to_file(AptList* apts) {
	AptNode* node = apts->head;
	FILE* file;
	errno_t err;
	err = fopen_s(&file, "apt.bin", "wb");

	while (node != NULL) {
		fwrite(&node->apt->id, sizeof(short int), 1, file);
		fwrite(&node->apt->address_len, sizeof(short int), 1, file);
		fwrite(node->apt->address, sizeof(char), node->apt->address_len, file);
		fwrite(&node->apt->price, sizeof(int), 1, file);
		//bits_to_file(file, *node->apt);
		node = node->next;
	}

	free_apt_list(apts);
	fclose(file);
}


AptList* load_apts_from_file()
{
	AptList* apts = (AptList*)malloc(sizeof(AptList));;
	AptNode* node = (AptNode*)malloc(sizeof(AptNode));
	FILE* file;

	fopen_s(&file, "apt.bin", "rb");

	if (file == NULL) {
		apts->head = apts->tail = NULL;
	}
	else {
		apts->head = node;
		node->apt = (Apt*)malloc(sizeof(Apt));
		while (fread(&node->apt->id, sizeof(short int), 1, file) == 1) {
			fread(&node->apt->address_len, sizeof(short int), 1, file);

			node->apt->address = (char*)malloc(sizeof(char)*(node->apt->address_len) + 1);
			fread(node->apt->address, sizeof(char), node->apt->address_len, file);
			node->apt->address[node->apt->address_len] = '\0';

			fread(&node->apt->price, sizeof(int), 1, file);
			file_to_bits(file, node->apt);
		}
	}
	
	return apts;
	fclose(file);
}

void db_date_to_file(FILE* file, Apt apt) {
	/*byte[0] - 5 bits day + 3 bits from month,
	byte[1] - 1 from month, 7 from year*/
	char byte[2];
	char tmp;
	for (int i = 0; i < 2; i++) {
		byte[0] = 0;
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

	fwrite(byte, sizeof(char), 2, file);
}

void bits_to_file(FILE* file, Apt apt) {
	/*byte[0] - 4 bits rooms + 4 bits from day,
	byte[1] - 1 bit from days, 4 from month, 3 from year
	byte[2] - 4 from year, 4 zeros*/
	char byte[3];
	char tmp;
	for (int i = 0; i < 3; i++) {
		byte[0] = 0;
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
	byte[1] = byte[0] | tmp;

	tmp = apt.entry_date.tm_year;
	tmp = tmp << 3;
	byte[2] = byte[1] | tmp;

	fwrite(byte, sizeof(char), 3, file);

}


void file_to_bits(FILE* file, Apt* apt) {
	/*byte[0] - 4 bits rooms + 4 bits from day,
	byte[1] - 1 bit from days, 4 from month, 3 from year
	byte[2] - 4 from year, 4 zeros*/
	char byte[3];
	char tmp;

	fread(byte,sizeof(char), 3, file);

	apt->rooms = byte[0] >> 4;
	apt->entry_date.tm_mday = byte[0] & 15; //mask 00001111
	apt->entry_date.tm_mday = apt->entry_date.tm_mday << 1;
	apt->entry_date.tm_mday = apt->entry_date.tm_mday | (byte[1] >> 7);
	apt->entry_date.tm_mon = byte[1] & 120; //maks 01111000
	apt->entry_date.tm_year = byte[1] & 7; //mask 00000111
	apt->entry_date.tm_year = apt->entry_date.tm_mon << 3;

	tmp = byte[2];
	tmp = tmp >> 3;
	apt->entry_date.tm_year = apt->entry_date.tm_year | tmp;

}