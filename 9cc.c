#include "./9cc.h"

void error(char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

struct Token *token;

bool consume(char op)
{
	if (TK_RESERVED != token->kind || op != token->str[0]) {
		return false;
	}

	token = token->next;
	return true;
}

void expect(char op)
{
	if (TK_RESERVED != token->kind || op != token->str[0])
		error("'%c'ではありません", op);

	token = token->next;
}

int expect_number(void)
{
	if (TK_NUM != token->kind) {
		error("数ではありません");
	}

	int val = token->val;
	token = token->next;

	return val;
}

bool at_eof(void)
{
	return TK_EOF == token->kind;
}

struct Token *new_token(TokenKind kind, struct Token *cur, char *str)
{
	struct Token *tok = calloc(1, sizeof(struct Token));

	tok->kind = kind;
	tok->str = str;
	cur->next = tok;

	return tok;
}

struct Token *tokenize(char *p)
{
	struct Token head; /* dummy head */
	head.next = NULL;
	struct Token *curr = &head;

	while (*p) {
		if (isspace(*p)) {
			p++;
			continue;
		}

		if ('+' == *p || '-' == *p) {
			curr = new_token(TK_RESERVED, curr, p++);
			continue;
		}

		if (isdigit(*p)) {
			curr = new_token(TK_NUM, curr, p);
			/* converts p char into long */
			/* offsets p address to the next non-digit char */
			curr->val = strtol(p, &p, 10);
			continue;
		}

		error("トークナイズできません");
	}

	new_token(TK_EOF, curr, p);
	return head.next;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		error("引数の個数が正しくありません");
		return 1;
	}

	token = tokenize(argv[1]);

	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");

	printf("\tmov rax, %d\n", expect_number());

	while (!at_eof()) {
		if (consume('+')) {
			printf("\tadd rax, %d\n", expect_number());
			continue;
		}

		expect('-');
		printf("\tsub rax, %d\n", expect_number());
	}

	printf("\tret\n");

	return 0;
}
