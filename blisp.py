#!/usr/bin/env python3

TNUM = 0
TSYM = 1
TOPEN = 2
TCLOSE = 3
TEOF = 4


TokenStr = ('Number', 'Symbol', 'LeftParen', 'RightParen', 'EOF')


def lerror(msg):
    raise RuntimeError(msg)


def tokenize(s):
    i = 0
    mlen = len(s)
    result = []
    while i < mlen:
        while i < mlen and s[i].isspace():
            i += 1
        if not i < mlen:
            break
        c = s[i]
        i += 1
        if c == '(':
            result.append((TOPEN, c))
        elif c == ')':
            result.append((TCLOSE, c))
        elif c.isnumeric():
            # TODO: actually parse numbers
            while i < mlen and not s[i].isspace():
                try:
                    float(c + s[i])
                    c += s[i]
                    i += 1
                except ValueError:
                    break
            result.append((TNUM, float(c)))
        elif c == '+':
            result.append((TSYM, c))
        elif c.isalpha():
            while i < mlen and s[i].isalnum():
                c += s[i]
                i += 1
            result.append((TSYM, c))
        else:
            lerror("read: error: unexpected character '{}'".format(c))
    result.append((TEOF, None))
    return result


if __name__ == '__main__':
    import pprint
    source = "(+ 1 2 44.4 5)"
    tokens = tokenize(source)
    pprint.pprint(tokens)
