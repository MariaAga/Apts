#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"

void readingFromFiles(AptList* appList, char* apparatmentFile, int code, char commandFile, List* long_term_history, char** short_term_history, int* countCommand);
AptList readFromFile(char* str);
AptNode* getNode(FILE* file);
void getEnterDate(FILE* file, struct tm* date);
void getDateAndNumRooms(int* numRooms, struct tm* date, FILE* file);
void readFromCommandFile(char* str, List* long_term_history, char **short_term_history, int *countCommands);
void organizeShortTermHistoryArray(char** short_term);
void readCommandForStorage(List* long_term, char** short_term, char* str, int countCmd);
char* getCommandFromFile(FILE *p);




void readingFromFiles(AptList* appList, char* apparatmentFile, int code, char commandFile, List* long_term_history, char** short_term_history, int* countCommand)
{
	(*appList) = readFromFile(apparatmentFile);
	readFromCommandFile(commandFile, long_term_history, short_term_history, countCommand);

}


AptList readFromFile(char* str)
{
	FILE* file;
	AptList appList;
	makeEmptyList(&appList);
	AptNode* curr;

	int sizeOfFile = 0;

	file = fopen(str, "rb");

	if (file == NULL)
		return appList;

	fseek(file, 0, SEEK_END);
	sizeOfFile = ftell(file);
	fseek(file, 0, SEEK_SET);


	if (sizeOfFile == 0)
		return appList;

	curr = getNode(file);

	while (curr != NULL)
	{

		insertNodeTotail(curr, &appList);

		curr = getNode(file);

	}
	appList.tail->next = NULL;

	fclose(file);

	return appList;
}

// reading the info from the file to new node 
AptNode* getNode(FILE* file)
{
	int flag = 0;
	short int code = 0;
	short int len_address;
	AptNode* newNode = malloc(sizeof(AptNode));

	flag = fread(&code, sizeof(short int), 1, file);

	if (flag == 0)
		return NULL;

	fread(&newNode->apt->id, sizeof(short int), 1, file);
	fread(&len_address, sizeof(short int), 1, file);
	newNode->apt->address = (char*)calloc(len_address + 1, sizeof(char));
	fread(newNode->apt->address, sizeof(char), len_address, file);
	newNode->apt->address[len_address] = '\0';

	fread(&newNode->apt->price, sizeof(int), 1, file);

	getDateAndNumRooms(&newNode->apt->rooms, &newNode->apt->rooms, file);

	getEnterDate(file, &newNode->apt->rooms);

	return newNode;
}

void getEnterDate(FILE* file, struct tm* date)
{
	BYTE bytes[2];
	BYTE month1, month2, day, year;

	fread(bytes, sizeof(BYTE), 2, file);
	day = bytes[0];
	day >>= 3;

	date->tm_mday = day;

	month1 = bytes[0];
	month1 <<= 5;
	month1 >>= 4;

	month2 = bytes[1];
	month2 >>= 7;


	date->tm_mon = month1 | month2;

	year = bytes[1];
	year <<= 1;
	year >>= 1;

	date->tm_year = year;
	date->tm_year += 2000;
}

void getDateAndNumRooms(int* numRooms, struct tm* date, FILE* file)
{
	BYTE bytes[3];
	BYTE day1, day2, year1, year2, month;

	fread(bytes, sizeof(BYTE), 3, file);

	*numRooms = bytes[0] >> 4;

	day1 = bytes[0];
	day1 <<= 4;
	day1 >>= 3;

	day2 = bytes[1];
	day2 >>= 7;

	month = (bytes[1]);
	month <<= 1;
	month >>= 4;
	date->tm_mon = month;

	year1 = (bytes[1] << 5) >> 1;
	year2 = (bytes[2] >> 4);

	date->tm_mday = day1 | day2;
	date->tm_year = year1 | year2;
}

void readFromCommandFile(char* str, List* long_term_history, char **short_term_history, int *countCommands)
{
	char ch;
	char *currCommand;
	int phSize = 2;
	int logiSize = 0;
	int numCommands = 0;

	makeArrayNull(short_term_history);
	makeEmptyListCmd(long_term_history);

	FILE * commandFile = fopen(str, "rt");
	//check if the file is exist but not read well .

	if (commandFile == NULL)
	{
		printMenu();
		return;
	}

	currCommand = getCommandFromFile(commandFile);

	while (currCommand != NULL)
	{
		readCommandForStorage(long_term_history, short_term_history, currCommand, ++numCommands);

		//updateCommands(long_term_history, short_term_history, currCommand, ++numCommands);

		currCommand = getCommandFromFile(commandFile);
	}

	*countCommands = numCommands;

	organizeShortTermHistoryArray(short_term_history);

	printMenu();
}

// In case of that short_term is not full the function will set all strings into the begining 
void organizeShortTermHistoryArray(char** short_term)
{
	if (short_term[0] != NULL)
		return;

	int writeInd = 0;
	int readInd = 0;

	char*temp[N];

	for (int i = 0; i < N; i++)
	{
		if (short_term[i] != NULL)
			temp[writeInd++] = short_term[i];
	}

	makeArrayNull(short_term);

	for (int i = 0; i < writeInd; i++)
		short_term[i] = temp[readInd++];
}

// get a command(Str) and allocate it to the fit place short_term or long_term following the countCmd 
void readCommandForStorage(List* long_term, char** short_term, char* str, int countCmd)
{
	if (isFull(short_term))
		insertDataToHeadList(long_term, str);
	else
		readToArr(str, countCmd, short_term);

}

// read a command from the specific place in file till arrive to '/n' 
char*  getCommandFromFile(FILE *p)
{
	int phSize = 2;
	int logicSize = 0;

	char ch = fgetc(p);

	if (ch == EOF)
		return NULL;

	char* str = (char*)malloc(sizeof(char)*phSize + 1);

	while (ch != '\n')
	{
		if (phSize == logicSize)
		{
			phSize *= 2;
			str = (char *)realloc(str, sizeof(char)*phSize + 1);
		}
		str[logicSize++] = ch;

		ch = fgetc(p);
	}

	if (phSize > logicSize)
	{
		str = (char *)realloc(str, sizeof(char)*logicSize + 1);
	}
	str[logicSize] = '\0';

	return str;
}