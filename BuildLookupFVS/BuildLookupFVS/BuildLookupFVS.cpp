// BuildLookupFVS.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include "stdafx.h"
#include "buildInputFile.h"
#include "DatabaseProcessing.h"


	


int _tmain(int argc, _TCHAR* argv[])
{

	char fvs[100]; 
	int standNumber = 49;
	//FILE* standlist;

	// File containing stands to be simulated.
	//fopen_s(&standlist, "N:\\FireProject_Part2\\BuildLookupFVS\\standList.txt", "r");

	// For each stand do this loop.
	//while(!feof(standlist))
	//{
	//	fscanf_s(standlist, "%d\n", &standNumber);
		InputFile* fileCreator = new InputFile(standNumber);

		sprintf_s(fvs, "..\\..\\FVSInputFiles\\%d.bat", standNumber);

		// Call FVS in command line
		system(fvs);

		fileCreator->~InputFile();
	//}

	//fclose(standlist);
	DBase openMDB;

	return 0;
}

