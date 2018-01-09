#!/usr/bin/env python3

from enum import Enum, auto


class TokenType(Enum):
    LPAREN = auto()
    RPAREN = auto()
    LBRACE = auto()
    RBRACE = auto()
    PLUS = auto()
    MINUS = auto()
    STAR = auto()
    SLASH = auto()
    STRING = auto()
    GT = auto(),
    GTE = auto(),
    LT = auto(),
    LTE = auto(),
    NUMBER = auto()
    DEFINE = auto()
    IF = auto()
    IDENT = auto()
    EOF = auto()


KEYWORDS = {
    'define': TokenType.DEFINE,
    'if': TokenType.IF,
}

class Token(object):
    def __init__(self, linum, ttype, lexeme):
        self.linum = int(linum)
        self.ttype = TokenType(ttype)
        self.lexeme = str(lexeme)

    def __str__(self):
        return '{ttype!s}({lexeme!s})'.format(
                ttype=self.ttype, lexeme=self.lexeme, i=self.linum)

    def __repr__(self):
        return self.__str__()


class Tokens(object):
    def __init__(self, source):
        self.src = source
        self.linum = 0
        self.cur = 0
        self.end = len(source)
        self.endtok = Token(-1, TokenType.EOF, lexeme='EOF')
        self.tok = self._next()
        self.previous = None

    def peek(self):
        return self.tok.ttype

    def advance(self):
        self.previous = self.tok
        self.tok = self._next()

    def expect(self, ttype, msg=None):
        if self.peek() != ttype:
            if msg is None:
                msg = "Expected {!s}, instead received {!s}".format(
                        ttype, self.peek())
            raise ValueError(msg)
        self.advance()

    def match(self, ttype):
        if self.peek() == ttype:
            self.advance()
            return True
        else:
            return False

    def _next(self):
        i = self.cur
        end = self.end
        src = self.src
        while i < end and src[i].isspace():
            if src[i] == '\n':
                self.linum += 1
            i += 1
        if not i < end:
            self.cur = i
            return self.endtok
        # TODO: support ';' comment
        c = src[i]
        i += 1
        if c == '(':
            result = Token(self.linum, TokenType.LPAREN, c)
        elif c == ')':
            result = Token(self.linum, TokenType.RPAREN, c)
        elif c == '+':
            result = Token(self.linum, TokenType.PLUS, c)
        elif c == '-':
            result = Token(self.linum, TokenType.MINUS, c)
        elif c == '*':
            result = Token(self.linum, TokenType.STAR, c)
        elif c == '/':
            result = Token(self.linum, TokenType.SLASH, c)
        elif c == '<':
            if i < end and src[i] == '=':
                c += src[i]
                i += 1
                result = Token(self.linum, TokenType.LTE, c)
            else:
                result = Token(self.linum, TokenType.LT, c)
        elif c == '>':
            if i < end and src[i] == '=':
                c += src[i]
                i += 1
                result = Token(self.linum, TokenType.GTE, c)
            else:
                result = Token(self.linum, TokenType.GT, c)
        elif c == '"':
            while i < end and src[i] != '"' and src[i] != '\n':
                c += src[i]
                i += 1
            if not (i < end and src[i] == '"'):
                raise ValueError("Expect '\"' to close string.")
            c += src[i]
            i += 1
            result = Token(self.linum, TokenType.STRING, c)
        elif c.isdigit():
            while i < end and src[i].isdigit():
                c += src[i]
                i += 1
            result = Token(self.linum, TokenType.NUMBER, c)
        elif c.isalpha():
            # TODO: allow '_'?  maybe this should be "while not src[i].isspace()"?
            while i < end and src[i].isalnum():
                c += src[i]
                i += 1
            ttype = KEYWORDS.get(c, TokenType.IDENT)
            result = Token(self.linum, ttype, c)
        else:
            raise ValueError("Unexpected character: '{}'".format(c))
        self.cur = i
        return result


def parse_error(token, msg=None):
    if not msg:
        msg = "Unexpected token {}".format(token.lexeme)
    raise RuntimeError("[line {}] {}.".format(
        token.linum, msg))


def parse_list(tokens):
    results = []
    while not tokens.match(TokenType.RPAREN):
        if tokens.match(TokenType.EOF):
            parse_error(tokens.previous, "Expected ')' to close list.")
        if tokens.match(TokenType.DEFINE):
            results.append(tokens.previous)
        elif tokens.match(TokenType.IF):
            results.append(tokens.previous)
        else:
            results.append(parse(tokens))
    return results


def parse(tokens):
    result = None
    if tokens.match(TokenType.NUMBER):
        result = tokens.previous
    elif tokens.match(TokenType.STRING):
        result = tokens.previous
    elif tokens.match(TokenType.IDENT):
        result = tokens.previous
    elif tokens.match(TokenType.LPAREN):
        result = parse_list(tokens)
    else:
        parse_error(tokens.tok)
    return result


if __name__ == '__main__':
    import pprint
    sources = (
            "1234",
            '"Hello, World"',
            "(1 2 3 4)",
            "(define foo 22)"
    )
    for source in sources:
    # source = "(1 2 3 4)"
    # if True:
        tokens = Tokens(source)
        print("Source = '{}'".format(source))
        ast = parse(tokens)
        pprint.pprint(ast)
        print()

