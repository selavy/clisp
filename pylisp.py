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
            self.val = c
            while self.pos < self.mlen and self.text[self.pos].isdigit():
                self.val += self.text[self.pos]
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
    
    
if __name__ == '__main__':
    prog = "(+ x 1)"
    tokens = Tokens(prog)
    while not tokens.match(TK_EOF):
        print "[{}]: {}".format(TokenString[tokens.ttyp], tokens.tval)
        tokens.advance()