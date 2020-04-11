#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_LEN 16
#define FILENAME "database.csv"
#define FORMAT "\n\t\t产品型号\t库存数量"

struct Item {
	int n;
	char id[ID_LEN];
	struct Item* next;
};

struct Item* add(char id[], int n);
struct Item** find(char id[]);
void print(struct Item item);
void del(struct Item* item);
void in(char cmd);
void printAll();
void save();
void read();

inline void menu() {
	puts("+-----------------+");
	puts("| 1. 显示存货列表 |");
	puts("| 2. 入库         |");
	puts("| 3. 出库         |");
	puts("| 0. 退出程序     |");
	puts("+-----------------+");
	printf("你选择了: ");
}

const char csv_format[20] = "%s , %d\n";
char format[20] = "\t%16s%16d\n";
struct Item* header = NULL;

int main() {
	system("title warehouse");
	read();
	while (1) {
		menu();
		char cmd[10];
		scanf("%s", cmd);
		if (strlen(cmd) == 1) {
			switch (cmd[0]) {
				case '1': printAll(); break;
				case '2': case '3': in(cmd[0]); break;
				case '0': save(); return 0;
				default: break;
			}
		}
		puts("");
	}
}

struct Item* add(char id[], int n) {
	struct Item* p = (struct Item*) malloc(sizeof(struct Item));
	memcpy(p->id, id, sizeof(char) * ID_LEN);
	p->next = NULL;
	p->n = n;
	return p;
}

void del(struct Item* p) {
	if (header == p) {
		header = p->next;
	}
	else {
		struct Item* prev = header;
		while (prev->next != p) {
			prev = prev->next;
		}
		prev->next = p->next;
		free(p);
	}
}

void in(char cmd) {
	int n;
	char id[32];
	printf("货物型号: "); scanf("%s", id);
	printf("%s库数量: ", cmd == '2' ? "入" : "出"); scanf("%d", &n);
	if (n < 0) {
		puts("\n\t请输入大于0的整数~");
		return;
	}
	if (cmd == '3') {
		n = -n;
	}
	struct Item** p = find(id);
	if (*p == NULL) {
		if (n > 0) {
			*p = add(id, 0);
			puts(FORMAT);
			printf("原");
			print(**p);
			(*p)->n = n;
			printf("现");
			print(**p);
		}
		else {
			puts("\n\t未找到符合的条目:(");
		}
	}
	else {
		puts(FORMAT);
		printf("原");
		print(**p);
		int temp = (*p)->n + n;
		if (temp >= 0) {
			(*p)->n = temp;
			printf("现");
			print(**p);
			if (temp == 0) {
				del(*p);
			}
		}
		else {
			puts("\n\t出库数量>原有储量!");
		}
	}
}

struct Item** find(char id[]) {
	struct Item** p = &header;
	while (*p != NULL) {
		if (!strcmp((*p)->id, id))
			return p;
		p = &((*p)->next);
	}
	return p;
}

void print(struct Item item) {
	printf(format, item.id, item.n);
}

void printAll() {
	struct Item* p = header;
	if (strcmp(format, csv_format)) {
		puts(p == NULL ? "\n\t列表为空" : FORMAT);
	}
	while (p != NULL) {
		print(*p);
		p = p->next;
	}
}

void save() {
	freopen(FILENAME, "w", stdout);
	memcpy(format, csv_format, sizeof(format));
	printAll();
	fclose(stdout);
}

void read() {
	int n;
	char id[ID_LEN];
	struct Item** item = &header;
	freopen(FILENAME, "r", stdin);
	while(scanf(csv_format, id, &n) == 2) {
		*item = add(id, n);
		item = &((*item)->next);
	}
	freopen("con", "r", stdin);
}
