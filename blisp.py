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


def apply_(env, closure, args):
    cenv, params, body = closure
    if len(params) != len(args):
        raise RuntimeError("error: eval: expected {} args, received {} args".format(
            len(params), len(args)))
    env2 = {}
    env2.update(env)
    env2.update(cenv)
    for param, arg in zip(params, args):
        # # TODO: move this when lambda is read in
        # if not isinstance(param, Symbol):
        #     raise RuntimeError("error: eval: parameters must be symbols")
        env2[param] = arg
    result = eval_(body, env2)
    return result


def eval_args(env, es):
    args = []
    for arg in es:
        args.append(eval_(arg, env))
    return args


def eval_(e, env):
    if isinstance(e, float):
        result = e
    elif isinstance(e, Symbol):
        result = env[e]
    elif isinstance(e, list):
        meth = eval_(e[0], env)
        if isinstance(meth, Symbol):
            if meth.name == 'begin':
                for x in e[1:]:
                    result = eval_(x, env)
            elif meth.name == 'define':
                if len(e) != 3:
                    raise RuntimeError("error: eval: malformed define")
                sym = e[1]
                if not isinstance(sym, Symbol):
                    raise RuntimeError("error: eval: symbol must be defined: {}".format(sym))
                value = eval_(e[2], env)
                env[sym] = value
                result = None
            elif meth.name == 'lambda':
                # (env, params, body)
                # ('define' (<params>) <body>)
                if len(e) != 3:
                    raise RuntimeError("error: eval: malformed lambda")
                if not isinstance(e[1], list):
                    raise RuntimeError("error: eval: parameters must be a list")
                for x in e[1]:
                    if not isinstance(x, Symbol):
                        raise RuntimeError("error: eval: parameter must be symbol: {}".format(x))
                closure = {}
                closure.update(env)
                result = (closure, e[1], e[2])
            else:
                args = eval_args(env, e[1:])
                meth = _builtins[meth]
                result = meth(env, args)
        else:
            args = eval_args(env, e[1:])
            result = apply_(env, meth, args)
    return result


if __name__ == '__main__':
    import pprint
    # source = "(+ (+ x (+ x x) (+ x x)) (+ x (+ x x x x)))"
    # source = "(begin (+ 1 1) (+ 1 2))"
    # source = "((lambda (x) 1) 42)"
    # source = "((lambda (y x) x) 42 27)"
    # source = "(begin (define x 1) x)"
    # source = "(begin (define add (lambda (x y) )))"
    # source = "((lambda (x y) (+ x y)) 3 4)"
    source = "(begin (define add (lambda (x y) (+ x y))) (add 3 4))"
    tokens = Tokens(source)
    result = read_sexpr(tokens)
    pprint.pprint(result)
    builtins = ('+', '-', 'begin', 'lambda', 'define')
    env = {}
    for b in builtins:
        env[mksymbol(b)] = mksymbol(b)
    r = eval_(result, env)
    print("{}: {}".format(type(r), r))
