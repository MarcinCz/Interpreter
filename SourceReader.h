#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class SourceReader
{
public:
	SourceReader(void);
	~SourceReader(void);

	bool openSource(string Source);
	char getNextChar();
	bool getNextLine();
	pair<int,int> getPosition();

private:
	string source;
	string line;
	int row;
	int column;
	ifstream inputStream;

};

