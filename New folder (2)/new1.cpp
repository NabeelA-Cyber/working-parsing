#include <iostream>	// define libraries
 #include <fstream>
 using namespace std;
 // Variable definitions:
 ifstream infp;	// file handler
 
enum Tokens {INT_LIT, IDENT, ASSIGN_OP, ADD_OP, SUB_OP, MUL_OP, DIV_OP, LEFT_PAREN, RIGHT_PAREN, LETTER, DIGIT, UNKNOWN, ENDFILE};

 Tokens nextToken;		// nextToken read from the file.

 int charClass;		// char class
 char lexeme [100];  // number of characters per line
 char nextChar;	// next char read from the file
 int lexLen;	// number of characters in lexeme so far.

// function to get the next character from the file
void getChar() {
	if ((nextChar = infp.get()) != EOF) {
		if (isalpha(nextChar)) charClass = LETTER;
		else if (isdigit(nextChar)) charClass = DIGIT;
		else charClass = UNKNOWN;
	}
	else charClass = ENDFILE;
}
// function to skip all white spaces
void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}
// function add the character read from the file into the array lexeme
void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else cout << "Error - lexeme is too long \n";
}
// function to determine the token
int lookup(char ch) {
	switch (ch) {
		case '(': addChar(); nextToken = LEFT_PAREN; break;
		case ')': addChar(); nextToken = RIGHT_PAREN; break;
		case '+': addChar(); nextToken = ADD_OP; break;
		case '-': addChar(); nextToken = SUB_OP; break;
		case '*': addChar(); nextToken = MUL_OP; break;
		case '/': addChar(); nextToken = DIV_OP; break;
		case '=': addChar(); nextToken = ASSIGN_OP; break;
		default: addChar(); nextToken = ENDFILE; break;
	}
	return nextToken;
}
void print(Tokens t) { // print out the token category.
   switch (t) {
	case INT_LIT: cout << "<INT_LIT>"; break;
	case IDENT: cout << "<IDENT>"; break;
	case ASSIGN_OP: cout << "<ASSIGN_OP>"; break;
	case ADD_OP: cout << "<ADD_OP>"; break;
	case SUB_OP: cout << "<SUB_OP>"; break;
	case MUL_OP: cout << "<MUL_OP>"; break;
	case DIV_OP: cout << "<DIV_OP>"; break;
	case LEFT_PAREN: cout << "<LEFT_PAREN>"; break;
	case RIGHT_PAREN: cout << "<RIGHT_PAREN>"; break;
	case LETTER: cout << "<LETTER>"; break;
	case DIGIT: cout << "<DIGIT>"; break;
	case UNKNOWN: cout << "<UNKNOWN>"; break;
	case ENDFILE: cout << "<ENDFILE>"; break;
   } /* End of switch */
} /* End of function print */
int lex() {//function lex() returns a token for each lexeme read from the file
   lexLen = 0; getNonBlank();
   switch (charClass) {
        case LETTER: addChar(); getChar();
		while (charClass == LETTER || charClass == DIGIT) { 
			addChar(); getChar(); }
		nextToken = IDENT; break;
	case DIGIT: addChar(); getChar();
		while (charClass == DIGIT) { addChar(); getChar(); }
		nextToken = INT_LIT; break;
         case UNKNOWN: lookup(nextChar); getChar(); break;
         case ENDFILE: nextToken=ENDFILE; lexeme[0]='E'; lexeme[1]='O'; 
			lexeme[2] = 'F'; lexeme[3] = 0; break;
    } /* End of switch */
    cout << "Next token is: "; print(nextToken);
    cout <<" Next lexeme is " << lexeme << endl;
    return nextToken;
} /* End of function lex */
int main() {
	infp.open("front.in");
	if (!infp) cout << "ERROR - cannot open front.in \n";
	else {
		getChar();
		do { lex(); 
		} while (nextToken != ENDFILE);
	}
	return 0;
}
