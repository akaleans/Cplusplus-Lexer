#pragma once

/*
	ASSIGNMENT 1 - LEXICAL ANALYSIS
	WRITTEN BY: KHALEN STENSBY
	SUBMITTED 2/25/20
	VERSION: FINAL VERSION
	FOR: CPSC 323-03 TTH 5:30-6:45
*/


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>


class Lexer
{
public:
	Lexer();
	Lexer(std::string code);
	~Lexer();

	void analyze();
	void output(std::string foutName);

	bool separator(char c);
	bool digit(char c);
	bool space(char c);
	bool identifier(char c);
	bool keyword(std::string str);
	bool operators(char c);
	bool comment(char c);

	int getSize();
	std::string getLexeme(int n);
	std::string getToken(int n);

	//FSM (input, states, initstate, final states, table)
private:
	std::string ptr;
	int input = 0;
	int states[9] = { 0, 1, 2, 3, 4, 5, 6};
	int initState = 1;
	int finalStates[4] = { 2, 4, 5, 6 };
	int table[7][4] = {
		{ 1, 3, 5, 6 },
		{ 1, 1, 2, 2 },
		{ 0, 0, 0, 0 },
		{ 4, 3, 4, 4 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
	};
	std::string keywords[20] = { "int", "float", "bool", "true",
								"false", "if", "else", "then",
								"endif", "while", "whileend", "do",
								"doend", "for", "forend", "input",
								"output", "and", "or", "not" };

	std::vector<std::string> tokens;
	std::vector<std::string> lexemes;
};

