//Header file for FVS input file functions


class InputFile
{
public: 
	InputFile(int standNumber);
	char pathway[128];
	FILE * input;
	~InputFile(void);

};