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
        elif c == '-':
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
        result = mksymbol(tokens.previous()[1])
    elif tokens.match(TOPEN):
        result = read_list(tokens)
    else:
        lparse("read: error: unexpected token: {!s}".format(tokens.cur()))
    return result


def env_get(env, name):
    import pprint
    print("env_get({})".format(name))
    pprint.pprint(env)
    return env[name]


def _builtin_add(env, xs):
    result = 0
    for x in xs:
        if not isinstance(x, float):
            raise RuntimeError("<builtin::+> arguments must be floats")
        result += x
    return result


def _builtin_sub(env, xs):
    for x in xs:
        if not isinstance(x, float):
            raise RuntimeError("<builtin::-> arguments must be floats")
    if len(xs) == 1:
        result = -1. * xs[0]
    else:
        result = xs[0]
        for x in xs[1:]:
            result -= x
    return result

symtab = {}

def mksymbol(name):
    global symtab
    try:
        return symtab[name]
    except KeyError:
        symtab[name] = Symbol(name)
        return symtab[name]


_builtins = {
    mksymbol('+'): _builtin_add,
    mksymbol('-'): _builtin_sub,
}


def apply_(env, meth, args):
    pass


def eval_(e, env):
    if isinstance(e, float):
        result = e
    elif isinstance(e, Symbol):
        result = env_get(env, e)
    elif isinstance(e, list):
        meth = eval_(e[0], env)
        args = []
        for arg in e[1:]:
            args.append(eval_(arg, env))
        if isinstance(meth, Symbol):
            meth = _builtins[meth]
            result = meth(env, args)
        else:
            result = apply_(env, meth, args)
    return result


if __name__ == '__main__':
    import pprint
    source = "(+ (+ x (+ x x) (+ x x)) (+ x (+ x x x x)))"
    tokens = Tokens(source)
    result = read_sexpr(tokens)
    pprint.pprint(result)
    env = {
        mksymbol('+'): mksymbol('+'),
        mksymbol('-'): mksymbol('-'),
        mksymbol('x'): float(1),
    }
    r = eval_(result, env)
    print("{}: {}".format(type(r), r))
