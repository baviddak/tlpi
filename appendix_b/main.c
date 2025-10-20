#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 256

#endif // BUF_SIZE 


#define ELEM_SIZE 32

struct dict_node {
	char key[ELEM_SIZE];
	char value[ELEM_SIZE];
	struct dict_node *next;
};

struct dict {
	struct dict_node *top;
};


struct dict *new_dict() {
	return (struct dict *)malloc(sizeof(struct dict));
}


void add(struct dict *dct, const char *key, const char *value){


	/* Create the new node */
	struct dict_node *new_node = (struct dict_node *)malloc(sizeof(struct dict_node));

	snprintf(new_node->key, strlen(key) + 1, key);
	snprintf(new_node->value, strlen(value) + 1, value);

	new_node->next = NULL;

	/* Add the new node to the dictionary */
	if (dct->top == NULL ){
		dct->top = new_node;
		return;
	}

	struct dict_node *p = dct->top;

	/* This is awful but it might work */
	while (p != NULL){
		if (p->next == NULL) {
			p->next = new_node;
			return;
		}
		p = p->next;
	}

	return;

}

#define TOKEN_MAX 256

struct token_node {
	char token_str[TOKEN_MAX];
	struct token_node *next;
};

struct token_buf {
	struct token_node *top;
};

struct token_buf *new_token_buf() {
	return (struct token_buf *)malloc(sizeof(token_buf));
}

void add_token(const char *tok) {
	struct token_node *nd = (struct token_node *)malloc(sizeof(struct token_node));

	snprintf(nd->token_str, TOKEN_MAX, tok);
	nd->next = NULL;

	return nd;
}

void print_token_buf(struct token_buf *tb) {

	struct token_node *tn = tb->top;

	while(tn != NULL) {
		puts(tn->token_str);
		tn = tn->next;
	}
}

int main (int argc, char *argv[]) {

	FILE *kvp;
	size_t num_read;
	char buf[BUF_SIZE];
	char *token;
	char *new_line = "\n";
	char *equals = "=";

	if (argc != 2) {
		fprintf(stderr, "Please enter a filename");
		return -1;
	}
	if ((kvp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Cannot fopen!!\n");
		return -1;
	}


	/* Write the business logic here */
	while (fread(buf, sizeof(char), BUF_SIZE, kvp) > 0) {
		fprintf(stdout, "Read some data into the buffer\n");
	}

	/* Split the buffer by new lines */
	if ((token = strtok(buf, new_line)) == NULL){
		printf("No tokens found.\n");
		return -1;
	}
	// printf("First token..\n");
	// puts(token);
	
	struct token_buf *tb = new_token_buf();

	while((token = strtok(NULL, new_line)) != NULL) {

		if (strlen(token) > 2) {
			// printf("Another token..\n");
			// puts(token);
			add_token(tb, token);
		}
	}

	print_token_buf(tb);

	if (fclose(kvp) != 0) {
		fprintf(stderr, "Error in closing the file stream\n");
		return -1;
	}

	return 0;
}
