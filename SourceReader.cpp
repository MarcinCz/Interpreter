#include "SourceReader.h"


SourceReader::SourceReader(void)
{

}


SourceReader::~SourceReader(void)
{
	if(inputStream.is_open()) inputStream.close();
}

bool SourceReader::openSource(string _source)
{
	
	source = _source;
	row = 0;
	column = 0;

	if(inputStream.is_open()) inputStream.close();
	inputStream.open(source.c_str());
	if(!inputStream)
	{
		cout<<"Nie mo¿na otworzyæ pliku "<<source<<endl;
		return false;
	}
	if(!getNextLine())
	{
		cout<<"Pusty plik "<<source<<endl;
		return false;
	}
	return true;
}

bool SourceReader::getNextLine()
{
	if(inputStream.eof()) return false;

	getline(inputStream, line);
	line.push_back('\n');

	row++;
	column = 0;
	while(line[column]==' ' || line[column]=='\t') column++;
	return true;
}

char SourceReader::getNextChar()
{
	
	if(column == line.size())		//end of line
	{
		if(getNextLine())			//if there is next line
		{
			return line[column++];
		}
		else
			return EOF;				//end of file
	}

	return line[column++];

}

pair<int,int> SourceReader::getPosition()
{
	return make_pair(column, row);
}