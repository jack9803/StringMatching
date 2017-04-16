#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
using namespace std;


#define MAX 100
#define SKIP_TABLE_SIZE 500 


void skipTable(int *skip, char* key);
int stringMatch(char* key, int keyLen, char* input, int* skip);
void subString(char* input, char* sub, int start, int keyLen);

int main(void){
	int skip[500];
	char input[100];
	char key[100];

	printf("Input string : \n");
	cin >> input;
	printf("Search string : \n");
	cin >> key;

	skipTable(skip, key);

	int inputLen = strlen(input);
	int keyLen = strlen(key);

	/*
		if key size = 3
		index = *

		[Search Range]
		ABCDEFGHIJKLMN
		--*
		 --*
		  --*
		   --*..........
	*/
	int ans = stringMatch(key, keyLen-1, input, skip);
	while(ans != -1){
		printf("%d\n", ans);
		ans = stringMatch(key, ans + keyLen, input, skip);
	}

	system("pause");
	//return 0;
}
/*
construct the skip table
EX : key = just
	j u s t  | other
	3 2 1 4  |  4
*/
void skipTable(int *skip, char* key){
	int keyLen = strlen(key);
	int i;
	for(i = 0; i < SKIP_TABLE_SIZE; i++){
		skip[i] = keyLen;
	}
	for(i = 0; i < keyLen-1; i++){
		skip[key[i]] = (keyLen-1) - i;
	}
}

int stringMatch(char* key, int from, char* input, int* skip){
	char sub[MAX] = {'\0'};
	int inputLen = strlen(input);
	int keyLen = strlen(key);
	int index = from;
	while(index < inputLen){
		subString(input, sub, index-keyLen+1, index);
		//printf("index : %d   sub : %s   s : %d\n", index, sub, index-keyLen+1);
		if(!strcmp(sub, key)){
			return index-keyLen+1;
		}
		index += skip[input[index]];
	}

	return -1;
}

void subString(char* input, char* sub, int start, int end){
	int j = 0;
	int i;
	for(i = start; i <= end; i++){
		sub[j] = input[i];
		j++;
	}
	sub[j] = '\0';
}