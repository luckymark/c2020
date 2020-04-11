#include <stdlib.h>
#include <stdio.h>

struct Node {
	int value;
	struct Node *next;
};

struct Node *add(int value);
void print(struct Node *ptr);
void inverse(struct Node **header);
void append(struct Node *ptr, int value);
int find(struct Node *from, const int value, struct Node **pos);
inline int find_next(int from_n, struct Node *from, const int value) {
	int index;
	struct Node *pos = NULL;
	return (from != NULL && (index = find(from->next, value, &pos)) != -1) ? from_n + index : -1;
}

int main() {
	system("title linkedList");
	puts("在main函数中创建一个单向链表");
	struct Node *header = NULL;
	header = add(5);
	for(int i = 9; i >= 1; i--) {
		append(header, i);
	}
	puts("done");
	puts("遍历该链表，依次现实各节点的value");
	print(header);
	puts("将该链表所有节点反序");
	inverse(&header);
	print(header);
	puts("在该链表中查找第一个值为5的节点，如果找到则返回该节点的序号，否则返回-1");
	struct Node *p_five;
	int index = find(header, 5, &p_five);
	printf("%d\n", index);
	puts("查找下一个值为5的节点，返回值同上");
	printf("%d\n", find_next(index, p_five, 5));
	system("pause");
	return 0;
}

struct Node *add(int value) {
	struct Node *p_node = (struct Node*) malloc(sizeof(struct Node));
	p_node->value = value;
	p_node->next = NULL;
	return p_node;
}

void append(struct Node *ptr, int value) {
	if (ptr == NULL)
		return;
	while (ptr->next != NULL) {
		ptr = ptr->next;
	}
	ptr->next = add(value);
}

void inverse(struct Node **header) {
	struct Node *pointer = *header;
	struct Node *prev = NULL;
	while (pointer != NULL) {
		struct Node *next = pointer->next;
		pointer->next = prev;
		prev = pointer;
		pointer = next;
	}
	*header = prev;
}

int find(struct Node *ptr, int value, struct Node **pos) {
	int counter = 0;
	while (ptr != NULL) {
		counter++;
		if (ptr->value == value) {
			*pos = ptr;
			return counter;
		}
		ptr = ptr->next;
	}
	*pos = NULL;
	return -1;
}

void print(struct Node *ptr) {
	if(ptr == NULL) {
		printf("empty");
	}
	while (ptr != NULL) {
		printf("%d ", ptr->value);
		ptr = ptr->next;
	}
	putchar('\n');
}
