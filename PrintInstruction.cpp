#include "PrintInstruction.h"


PrintInstruction::PrintInstruction(void)
{
}

PrintInstruction::PrintInstruction(string _toPrint, bool _isText)
{
	toPrint =_toPrint;
	isText = _isText;
}
PrintInstruction::~PrintInstruction(void)
{
}

bool PrintInstruction::execute()
{
		cout<<"print"<<endl;
	return true;
}