/*
ASSIGNMENT 1 - LEXICAL ANALYSIS
WRITTEN BY: KHALEN STENSBY
SUBMITTED 2/16/20
VERSION: WORKING ITERATION FOR EXTRA CREDIT
FOR: CPSC 323-03 TTH 5:30-6:45
*/


#include "Lexer.h"



Lexer::Lexer()
{
}

Lexer::Lexer(std::string code) 
{
	ptr = code;
}

Lexer::~Lexer()
{
}

bool Lexer::keyword(std::string str)
{
	for (int i = 0; i < 20; ++i) {
		if (str == keywords[i])
			return true;
	}
	return false;
}

/*                             TABLE                        		//
					0	1	2	3
Curr state:			l	d	sep	op
start			0 |	1	3	5	6
in id			1 |	1	1	2	2
end id			2 |	0	0	0	0
in #			3 |	4	3	4	4
end #			4 |	0	0	0	0	
separat			5 |	0	0	0	0	
operato			6 |	0	0	0	0	


//                                                                  */


void Lexer::analyze()
{
	int i = 0;
	std::string lexeme = "";
	int currState = initState;
	while (i < ptr.length()) {
		if (digit(ptr.at(i))) {
			lexeme += ptr.at(i);
			input = 1;
			currState = table[currState][input];
			++i;
		}
		else if (operators(ptr.at(i))) {
			lexeme += ptr.at(i);
			input = 3;
			currState = table[currState][input];
		}
		else if (identifier(ptr.at(i))) {
			lexeme += ptr.at(i);
			input = 0;
			currState = table[currState][input];
			++i;
		}
		else if (separator(ptr.at(i)) || space(ptr.at(i))) {
			input = 2;
			currState = table[currState][input];
		}
		else if (comment(ptr.at(i))) {
			++i;
			while (!comment(ptr.at(i))) {
				++i;
			}
			++i;
			lexeme = "";
			currState = 0;
		}
		if (currState == 2 || currState == 4 || currState == 5 || currState == 6) {
			if (currState == 2) {
				if (keyword(lexeme)) {
					lexemes.push_back(lexeme);
					tokens.push_back("KEYWORD");
				}
				else {
					lexemes.push_back(lexeme);
					tokens.push_back("IDENTIFIER");
				}
			}
			else if (currState == 4) {
				lexemes.push_back(lexeme);
				tokens.push_back("REAL");
			}
			else if (currState == 5) {
				if (separator(ptr.at(i))) {
					lexeme = ptr.at(i);
					lexemes.push_back(lexeme);
					tokens.push_back("SEPARATOR");
					++i;
				}
				else {
					++i;
				}
			}
			else if (currState == 6) {
				lexemes.push_back(lexeme);
				tokens.push_back("OPERATOR");
				++i;
			}
			lexeme = "";
			currState = 0;
		}
	}
}

void Lexer::output(std::string foutName)
{
	std::ofstream fout;
	fout.open(foutName);
	fout << "TOKENS" << std::setw(40) << "LEXEMES\n\n";
	for (int i = 0; i < lexemes.size(); ++i) {
		fout << std::left << std::setw(20) << tokens.at(i) << std::setw(20) << "=" << lexemes.at(i) << "\n";
	}
}

int Lexer::getSize() {
	return lexemes.size();
}

std::string Lexer::getLexeme(int n)
{
	return lexemes.at(n);
}

std::string Lexer::getToken(int n)
{
	return tokens.at(n);
}

bool Lexer::operators(char c)
{
	switch (c) {
	case '*':
	case '+':
	case '-':
	case '=':
	case '/':
	case '<':
	case '>':
	case '%':
		return true;
	default:
		return false;
	}
}

bool Lexer::comment(char c)
{
	if (c == '!') {
		return true;
	}
	return false;
}

bool Lexer::space(char c) {
	switch (c) {
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return true;
	default:
		return false;
	}
}

bool Lexer::separator(char c) 
{
	switch (c) { 
	case '\'':
	case '(':
	case ')':
	case '{':
	case '}':
	case '[':
	case ']':
	case ',':
	case '.':
	case ':':
	case ';':
		return true;
	default:
		return false;
	}
}

bool Lexer::digit(char c) 
{
	switch (c) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
	default:
		return false;
	}
}
	
bool Lexer::identifier(char c) 
{
	switch (c) {
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '_':
	case '$':
		return true;
	default:
		return false;
	}
}
