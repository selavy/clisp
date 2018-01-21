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


class Tokens(object):
    def __init__(self, src):
        self.toks = tokenize(src)
        self.i = 0

    def adv(self):
        if self.i < len(self.toks):
            self.i += 1

    def cur(self):
        return self.toks[self.i]

    def previous(self):
        return self.toks[self.i - 1]

    def peek(self):
        return self.toks[self.i]

    def match(self, ttype):
        if self.peek()[0] == ttype:
            self.adv()
            return True
        else:
            return False

    def expect(self, ttype):
        if not self.match(ttype):
            raise RuntimeError("read: error: unexpected token: '{}'".format(
                self.cur()))


def lparse(msg):
    raise RuntimeError(msg)


class Symbol(object):
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return 'Symbol({})'.format(self.name)

    def __repr__(self):
        return self.__str__()


def read_list(tokens):
    result = []
    while not tokens.match(TCLOSE):
        if tokens.match(TEOF):
            lparse("read: error: expected ')' to close '('")
        result.append(read_sexpr(tokens))
    return result


def read_sexpr(tokens):
    if tokens.match(TNUM):
        result = float(tokens.previous()[1])
    elif tokens.match(TSYM):
        result = Symbol(tokens.previous()[1])
    elif tokens.match(TOPEN):
        result = read_list(tokens)
    else:
        lparse("read: error: unexpected token: {!s}".format(tokens.cur()))
    return result


def env_get(env, name):
    return env[name]


def eval_(e, env):
    if isinstance(e, float):
        result = e
    elif isinstance(e, Symbol):
        result = env_get(env, e.name)
    elif isinstance(e, list):
        meth = eval_(e[0], env)
        result = apply_(meth, e[1:])
    return result



if __name__ == '__main__':
    import pprint
    # source = "(+ 44.2 52)"
    source = "42.7"
    tokens = Tokens(source)
    result = read_sexpr(tokens)
    pprint.pprint(result)
    env = {}
    r = eval_(result, env)
    print("{}: {}".format(type(r), r))

    # source = "(+ 1 2 44.4 5)"
    # tokens = Tokens(source)
    # while not tokens.match(TEOF):
    #     print(tokens.cur())
    #     tokens.adv()
    # # tokens = tokenize(source)
    # # pprint.pprint(tokens)
