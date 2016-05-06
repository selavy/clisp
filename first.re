#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

bool adddgt(unsigned long *u, unsigned int d, int base)
{
    if (*u > (ULONG_MAX - d) / base) {
        return false;
    }
    *u = *u * base + d;
    return true;
}

bool lex(const char *s, unsigned long *u)
{
    const char *YYMARKER;
    const char *YYCTXMARKER;
    *u = 0;

    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:define:YYCTYPE = char;
        re2c:define:YYCURSOR = s;

        end = "\x00";
    */

    /*!re2c
        *                  { return false; }
        '0b' / [01]        { goto bin; }
        "0"                { goto oct; }
        "" / [1-9]         { goto dec; }
        '0x' / [0-9a-fA-F] { goto hex; }
    */

bin:
    /*!re2c
        *     { return false; }
        end   { return true; }
        [01]  { if (!adddgt(u, s[-1] - '0', 2)) return false; goto bin; }
    */

oct:
    /*!re2c
        *     { return false; }
        end   { return true; }
        [0-7] { if (!adddgt(u, s[-1] - '0', 8)) return false; goto oct; }
    */

dec:
    /*!re2c
        *     { return false; }
        end   { return true; }
        [0-9] { if (!adddgt(u, s[-1] - '0', 10)) return false; goto dec; }
    */

hex:
    /*!re2c
        *     { return false; }
        end   { return true; }
        [0-9] { if (!adddgt(u, s[-1] - '0', 16))      return false; goto hex; }
        [a-f] { if (!adddgt(u, s[-1] - 'a' + 10, 16)) return false; goto hex; }
        [A-F] { if (!adddgt(u, s[-1] - 'A' + 10, 16)) return false; goto hex; }
    */
}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        unsigned long u;
        if (lex(argv[i], &u)) {
            printf("%lu\n", u);
        } else {
            printf("error\n");
        }
    }
    return 0;
}
