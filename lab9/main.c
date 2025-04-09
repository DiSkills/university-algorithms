#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define NOCOLOR "\x1b[0m"

#define DIGITS_SET "0123456789"

enum statuses {
    unexpected_eol = 1,
    unexpected_char = 2,
};

struct parser {
    const char *s;
    int pos;
    jmp_buf env;
};

static int check_char(const struct parser *pars, char c)
{
    return pars->s[pars->pos] == c;
}

static void parse_char(struct parser *pars, char c)
{
    if (!pars->s[pars->pos]) {
        longjmp(pars->env, unexpected_eol);
    }

    if (!check_char(pars, c)) {
        longjmp(pars->env, unexpected_char);
    }
    pars->pos++;
}

static int check_char_set(const struct parser *pars, const char *set)
{
    char c = pars->s[pars->pos];
    return c && strchr(set, c) ? 1 : 0;
}

static void parse_char_set(struct parser *pars, const char *set)
{
    if (!pars->s[pars->pos]) {
        longjmp(pars->env, unexpected_eol);
    }

    if (!check_char_set(pars, set)) {
        longjmp(pars->env, unexpected_char);
    }
    pars->pos++;
}

static void parse_unsigned(struct parser *pars)
{
    do {
        parse_char_set(pars, DIGITS_SET);
    } while (check_char_set(pars, DIGITS_SET));
}

static void parse_int(struct parser *pars)
{
    if (check_char(pars, '-')) {
        parse_char(pars, '-');
    }
    parse_unsigned(pars);
}

static void parse_inversion(struct parser *pars)
{
    if (check_char(pars, '(')) {
        parse_char(pars, '(');
        parse_unsigned(pars);
        parse_char(pars, '+');
        parse_inversion(pars);
        parse_char(pars, ')');
    } else {
        parse_unsigned(pars);
    }
    parse_char(pars, '~');
}

static void parse_fraction(struct parser *pars)
{
    parse_int(pars);
    if (check_char(pars, '+')) {
        parse_char(pars, '+');
        parse_inversion(pars);
    }
}

static int parser_run(const char *s)
{
    int res;
    struct parser pars;

    pars.s = s;
    pars.pos = 0;

    res = setjmp(pars.env);
    switch (res) {
    case 0:
        parse_fraction(&pars);
        if (strlen(s) == pars.pos) {
            return 0;
        }
        fprintf(stderr, "The line contains extra characters:\n"
                "%.*s" COLOR_YELLOW "%c" "%s" NOCOLOR "\n",
                pars.pos, s, s[pars.pos], s + pars.pos + 1);
        break;
    case unexpected_eol:
        fprintf(stderr, "Unexpected end of line\n");
        break;
    case unexpected_char:
        fprintf(stderr, "%.*s" COLOR_RED "%c" NOCOLOR "%s\n",
                pars.pos, s, s[pars.pos], s + pars.pos + 1);
        break;
    }
    return 2;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Expected: %s <string>\n", argv[0]);
        return 1;
    }
    return parser_run(argv[1]);
}
