/* 
	ASSIGNMENT 1 - LEXICAL ANALYSIS 
	WRITTEN BY: KHALEN STENSBY      
	SUBMITTED 2/25/20
	VERSION: FINAL VERSION
	FOR: CPSC 323-03 TTH 5:30-6:45 
*/



#include "Lexer.h"

int main(int argc, char **argv){

	std::ifstream fin;
	bool appInput = false;

	if (argc > 1) {
		appInput = true;
		int i = 0;
		std::vector<Lexer> lexers;
		while (i < argc) {
			fin.open(argv[i+1]);
			std::stringstream tempBuffer;
			tempBuffer << fin.rdbuf();
			std::string sample = tempBuffer.str();
			Lexer tempLexer = Lexer(sample);
			fin.close();
			lexers.push_back(tempLexer);
			lexers[i].analyze();
			std::string tempOutputFile = "commandLineOutput" + std::to_string(i) + ".txt";
			lexers[i].output(tempOutputFile);
			++i;
		}
	}
	else if(argc == 1){
		int num = 0;
		std::cout << "Enter the number of files you wish to parse (Press 0 to run base sample files): ";
		std::cin >> num;
		if (num > 0) {
			appInput = true;
			std::vector<Lexer> lexers;
			for(int i = 0; i < num; ++i) {
				std::string tempFile;
				std::cout << "Enter file name: ";
				std::cin >> tempFile;
				fin.open(tempFile);
				std::stringstream tempBuffer;
				tempBuffer << fin.rdbuf();
				std::string sample = tempBuffer.str();
				Lexer tempLexer = Lexer(sample);
				fin.close();
				lexers.push_back(tempLexer);
				lexers[i].analyze();
				std::string tempOutputFile = "inExecutionOutput" + std::to_string(i) + ".txt";
				lexers[i].output(tempOutputFile);
			}
		}
	}
	else if(!appInput){
		fin.open("sample1.txt");
		std::stringstream buffer1, buffer2, buffer3;
		buffer1 << fin.rdbuf();
		std::string sample;
		sample = buffer1.str();
		fin.close();
		Lexer lex1 = Lexer(sample);
		lex1.analyze();
		lex1.output("output1.txt");

		fin.open("sample2.txt");
		buffer2 << fin.rdbuf();
		sample = buffer2.str();
		Lexer lex2 = Lexer(sample);
		lex2.analyze();
		lex2.output("output2.txt");
		fin.close();

		fin.open("sample3.txt");
		buffer3 << fin.rdbuf();
		sample = buffer3.str();
		Lexer lex3 = Lexer(sample);
		lex3.analyze();
		lex3.output("output3.txt");
		fin.close();
	}
	return 0;
}