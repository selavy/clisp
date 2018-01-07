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
    NUMBER = auto()
    IDENT = auto()
    EOF = auto()


class Token(object):
    def __init__(self, ttype, lexeme):
        # TODO: add linum
        self.ttype = TokenType(ttype)
        self.lexeme = str(lexeme)

    def __str__(self):
        return '{ttype!s}({lexeme!s})'.format(
                ttype=self.ttype, lexeme=self.lexeme)


class Tokens(object):
    def __init__(self, source):
        self.src = source
        self.cur = 0
        self.end = len(source)
        self.endtok = Token(TokenType.EOF, lexeme='EOF')
        self.tok = self._next()

    def peek(self):
        return self.tok.ttype

    def expect(self, ttype, msg=None):
        if self.peek() != ttype:
            if msg is None:
                msg = "Expected {!s}, instead received {!s}".format(
                        ttype, self.peek())
            raise ValueError(msg)
        self.tok = self._next()

    def match(self, ttype):
        if self.peek() == ttype:
            self.tok = self._next()
            return True
        else:
            return False

    def _next(self):
        i = self.cur
        end = self.end
        src = self.src
        while i < end and src[i].isspace():
            i += 1
        if not i < end:
            self.cur = i
            return self.endtok
        c = src[i]
        i += 1
        if c == '(':
            result = Token(TokenType.LPAREN, c)
        elif c == ')':
            result = Token(TokenType.RPAREN, c)
        elif c == '+':
            result = Token(TokenType.PLUS, c)
        elif c == '-':
            result = Token(TokenType.MINUS, c)
        elif c == '*':
            result = Token(TokenType.STAR, c)
        elif c == '/':
            result = Token(TokenType.SLASH, c)
        elif c == '"':
            while i < end and src[i] != '"':
                c += src[i]
                i += 1
            if src[i] != '"':
                raise ValueError("Expect '\"' to close string.")
            result = Token(TokenType.STRING, c)
        elif c.isdigit():
            while i < end and src[i].isdigit():
                c += src[i]
                i += 1
            result = Token(TokenType.NUMBER, c)
        elif c.isalpha():
            # TODO: allow '_'?  maybe this should be "while not src[i].isspace()"?
            while i < end and src[i].isalnum():
                c += src[i]
                i += 1
            result = Token(TokenType.IDENT, c)
        else:
            raise ValueError("Unexpected character: '{}'".format(c))
        self.cur = i
        return result


if __name__ == '__main__':
    # tok = Token(TokenType.IDENT, "HelloWorld")
    # print(str(tok))
    source = "(+ 1 2)"
    tokens = Tokens(source)
    i = 0
    while not tokens.match(TokenType.EOF) and i < 10:
        print(tokens.tok)
        tokens.tok = tokens._next()
        i += 1
    print(tokens.tok)

