
// Build the input files for FVS. 

#include <stdlib.h>
#include <stdio.h>
#include "buildInputFile.h"
#include <iostream>

/**
* Constructor to create input files for simulating FVS
**/

InputFile::InputFile(int stand)
{
	char name[50];
	char inPath[128];
	char outPath[128];
	sprintf_s(inPath, "..\\..\\FVSInputFiles\\");
	// This must be updated for each computer or FVS will not run.
	sprintf_s(outPath, "..\\..\\FVSOutputFiles\\");


	for(int i = 0; i < 3; i++)
	{
		if(i == 0)
			sprintf_s(name, "%d.key", stand);
		else if(i == 1)
			sprintf_s(name, "%d.in", stand);
		else if(i == 2)
			sprintf_s(name, "%d.bat", stand);

		sprintf_s(pathway, "..\\..\\FVSInputFiles\\%s", name);
		fopen_s(&input, pathway, "w");

		if(i == 0)// Create the Keyword file
		{
			// Basic input
			fprintf(input, "STDIDENT\n"
						   "%d\nSTANDCN\n"
						   "%d\nMGMTID\n"
						   "\nINVYEAR      2007\n"
						   "NUMCYCLE        20\n"
						   "TIMEINT         0         5\n"
						   "SCREEN\n"
						   , stand, stand);

			//Open and read stands and treelists
			fprintf(input, "DATABASE\n"
						     "DSNIN\n"
						     "%s\RealSAStands.mdb\n"
						     "StandSQL\n"
						     "SELECT * FROM StandsSAReal\n"
						     "WHERE tree_cn = '%%stand_cn%%'\n"
						   "EndSQL\n"
						   "DSNIN\n"
						     "%s\RealSAStands.mdb\n"
						     "TreeSQL\nSELECT * FROM TreesSAReal\n"
						     "WHERE tree_cn = (SELECT tree_cn FROM StandsSAReal\n"
						     "WHERE tree_cn = '%%stand_cn%%')\n"
						    "EndSQL\n"
						   "END\n", inPath, inPath);

			fprintf(input, "TREELIST         0        50         0\n"
							"COMPUTE            0\n"
						    "canopy = acancov\n"
						    "fml = fuelmods(1,1)\n"
						    "htt = ATOPHT\n"
						    "htlive = crbaseht\n"
						    "cbd = crbulkdn\n"
						    "yr = year\n"
							"sdi = BSDI\n"
							"ba = BBA\n"
							"tpa = BTPA\n"
						  "END\n");

			fprintf(input, "FMIN\n"
						     "FUELOUT\n"
						     "BURNREPT\n"
						     "FIRECALC         0        1        1\n"
						     "SOILHEAT\n"
						   "END\n"
						   "STRCLASS         1     30.00        5.       16.      20.00       50.      35.00\n"
						   "ECHOSUM\n"
						   "DATABASE\n"
						   "DSNOUT\n"
						     "%s\outputs.mdb\n"
							 "SUMMARY\n"
						     "COMPUTE\n"
							 "TREELIST\n"							 
							 "END\n"
						   "PROCESS\n"
						   "STOP\n", outPath);
		}
		if(i == 1)// Write the in file.
		{
			fprintf(input, "%s%d.key\n%s%d.fvs\n%s%d.out\n%s%d.trl\n%s%d.sum", 
				inPath, stand, inPath, stand, inPath, stand, inPath, stand, inPath, stand);
		}
		if(i == 2)// Write the batch file
		{
			fprintf(input, "C:\\FVSbin\\FVSsox.exe < %s%d.in", inPath, stand);
		}
		fclose(input);
	}
}

/**
* Destructor for InputFile
**/

InputFile::~InputFile()
{
	delete[] pathway;
}
