#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define IF_NO_KEY if(!key_len){puts("input key first");continue;}
#define MAX_STR_LEN 10000
#define MAX_KEY_LEN 100
#define bool int
#define false 0
#define true 1

struct Key{
	char ch;
	int num;
};

struct Key key[MAX_KEY_LEN];
char str[MAX_STR_LEN];
int key_len, str_len;

int cmp(const void *a, const void *b) {
	return (*(struct Key *)a).ch - (*(struct Key *)b).ch;
}

void savekey();
void encrypt();
void decrypt();
char get_cmd();

int main(){
	system("title encrypt_decrypt");
	puts("# key KEY_STRING");
	puts("# encrypt STRING");
	puts("# decrypt STRING");
	puts("# halt (kill me)");
	puts("# Simply k/e/d/h");
	puts("");
	while(true) {
		// get command
		char cmd = get_cmd();
		if (cmd == 0)
			continue;
		if (cmd == 'h')
			return 0;
		// get string
		bool skip = false;
		int len = 0;
		while(true) {
			char ch = getchar();
			if (ch == '\r')
				continue;
			if (ch == '\n') {
				if (cmd > 0 && !len) {
					puts("param is needed");
					skip = true;
				}
				break;
			}
			if (ch != ' ') {
				str[len++] = ch;
			}
		}
		if (skip)
			continue;
		// execute
		switch (cmd) {
			case 'k': {
				key_len = len;
				savekey();
				break;
			}
			case 'e': {
				IF_NO_KEY;
				str_len = len;
				encrypt();
				break;
			}
			case 'd': {
				IF_NO_KEY;
				str_len = len;
				decrypt();
				break;
			}
			default: {
				break;
			}
		}
	}
}

/*
INPUT ACTION
| if press enter then skip
| if input wrong then echo "no such command"
| if press enter then echo "param is needed"
| if there nokey then echo "input key first"
*/

char get_cmd() {
	char cmd[8] = {0};
	bool endl = false;
	int p_cmd = 0;
	printf("> ");
	while(true) {
		char ch = getchar();
		if (ch == ' ') {
			if (p_cmd)
				break;
			else
				continue;
		}
		if (ch == '\r')
			continue;
		if (ch == '\n') {
			endl = true;
			break;
		}
		if (p_cmd < 7) {
			cmd[p_cmd++] = tolower(ch);
		}
		else {
			cmd[0] = -1;
		}
	}
	if (!strcmp(cmd, "h") || !strcmp(cmd, "halt")) {
		endl = false;
	}
	if (
		strcmp(cmd, "k") && strcmp(cmd,     "key") &&
		strcmp(cmd, "e") && strcmp(cmd, "encrypt") &&
		strcmp(cmd, "d") && strcmp(cmd, "decrypt") &&
		strcmp(cmd, "h") && strcmp(cmd,    "halt")
	) {
		puts("no such command");
		cmd[0] = -1;
	}
	if (endl && cmd[0] > 0) {
		puts("param is needed");
	}
	return endl ? 0 : cmd[0];
	//   0: unexpectedly receive enter and skip
	//  -1: wrong command but try to absorb string
	// 'a': successfully get one of the legel commands
}

void savekey() {
	for (int i = 0; i < key_len; i++) {
		key[i].ch = str[i];
		key[i].num = i;
	}
	qsort(key, key_len, sizeof(struct Key), cmp);
}

void encrypt() {
	int end = (str_len - 1) / key_len + 1;
	for (int i = 0; i < key_len; i++) {
		for (int j = 0; j < end; j++) {
			int t = j * key_len + key[i].num;
			putchar(toupper(t < str_len ? str[t] : 'e'));
		}
	}
	putchar('\n');
}

void decrypt() {
	char ans[MAX_STR_LEN] = {0};
	int end = str_len / key_len;
	for (int i = 0; i < key_len; i++) {
		for (int j = 0; j < end; j++) {
			ans[j * key_len + key[i].num] = str[i * end + j];
		}
	}
	puts(ans);
}
