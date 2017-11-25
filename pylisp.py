#!/usr/bin/env python


TK_UNK = 0
TK_LPAREN = 1
TK_RPAREN = 2
TK_PLUS = 3
TK_NUMBER = 4
TK_IDENT = 5
TK_EOF = 6
    

TokenString = {
        TK_UNK: 'Unknown',
        TK_LPAREN: 'LParen',
        TK_RPAREN: 'RParen',
        TK_PLUS: 'Plus',
        TK_NUMBER: 'Number',
        TK_IDENT: 'Ident',
        TK_EOF: 'EOF',
}


class Tokens(object):
    def __init__(self, text):
        self.text = text
        self.mlen = len(self.text)
        self.pos = 0
        self.ttyp = TK_UNK
        self.tval = ''
        self.advance()
        
    def advance(self):
        while self.pos < self.mlen and self.text[self.pos].isspace():
            self.pos += 1
        if not self.pos < self.mlen:
            self.ttyp = TK_EOF
            self.tval = ''
            return
        c = self.text[self.pos]
        self.pos += 1
        if c == '(':
            self.ttyp = TK_LPAREN
            self.tval = c
        elif c == ')':
            self.ttyp = TK_RPAREN
            self.tval = c
        elif c == '+':
            self.ttyp = TK_PLUS
            self.tval = c
        elif c.isdigit():
            self.ttyp = TK_NUMBER
            self.tval = c
            while self.pos < self.mlen and self.text[self.pos].isdigit():
                self.tval += self.text[self.pos]
                self.pos += 1
        else:
            self.ttyp = TK_IDENT
            self.tval = c
            while self.pos < self.mlen:
                c = self.text[self.pos]
                if not (c.isdigit() or c.isalpha() or c == '_'):
                    break
                self.tval += c 
                self.pos += 1

    def match(self, typ):
        if self.ttyp == typ:
            self.advance()
            return True
        return False
    
    def expect(self, typ):
        if self.ttyp != typ:
            raise ValueError("Expected token of type {}, received {}".format(
                    TokenString[typ], TokenString[self.ttyp]))
        self.match(typ)
    
    
class Number(object):
    def __init__(self, val):
        self.val = float(val)
    
    def __str__(self):
        return str(self.val)
        
    
class Plus(object):
    def __init__(self, args):
        self.args = args
        
    def __str__(self):
        args = [str(x) for x in self.args]
        return 'Plus({})'.format(' '.join(args))
    
    
def expr(tokens):
    tval = tokens.tval
    if tokens.match(TK_LPAREN):
        result = expr(tokens)
        tokens.expect(TK_RPAREN)
    elif tokens.match(TK_NUMBER):
        result = Number(tval)
    elif tokens.match(TK_PLUS):
        args = []
        while tokens.ttyp != TK_RPAREN:
            args.append(expr(tokens))
        result = Plus(args)
    else:
        raise ValueError("Invalid token: [{}] -> {}".format(
                TokenString[tokens.ttyp], tokens.tval))
    return result


def parse(prog):
    tokens = Tokens(prog)
    while not tokens.match(TK_EOF):
        result = expr(tokens)
    return result
    

_Debug = False
def classname(x):
    if _Debug:
        return str(type(x))
    else:
        return str(type(x)).split('.')[1][:-2] 


if __name__ == '__main__':
    prog = "(+ 1 25 3)"
    result = parse(prog)
    print "{} -> {}".format(classname(result), result)