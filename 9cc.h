#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

// トークンの種類
typedef enum {
	TK_RESERVED,
	TK_NUM,
	TK_EOF,
} TokenKind;

// トークン型
struct Token {
	TokenKind kind;
	struct Token *next;
	char *str;
	int val;
};

// エラーを報告するための関数
// printfと同じ引数を取る
void error(char *fmt, ...);

// 次のトークンが期待している記号のときには、トークンを1つ読み進めて
// 真を返す。それ以外の場合には偽を返す。
bool consume(char op);

// 次のトークンが期待している記号のときには、トークンを1つ読み進める。
// それ以外の場合にはエラーを報告する。
void expect(char op);

// 次のトークンが数値の場合、トークンを1つ読み進めてその数値を返す。
// それ以外の場合にはエラーを報告する。
int expect_number(void);

bool at_eof(void);

// 新しいトークンを作成してcurに繋げる
struct Token *new_token(TokenKind kind, struct Token *cur, char *str);

// 入力文字列pをトークナイズしてそれを返す
struct Token *tokenize(char *p);
