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
	struct Token head;
	head.next = NULL;
	struct Token *curr = &head;

	while (*p) {
	}
}

int main(void)
{
	return 0;
}
