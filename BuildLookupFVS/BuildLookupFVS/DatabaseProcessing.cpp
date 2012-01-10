
#include <afxdb.h>
#include <iostream>
#include "DatabaseProcessing.h"

using namespace std;

DBase::DBase()
{
	LPCTSTR lpszConnect = 
		_T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=N:\\FireProject_Part2\\BuildLookupFVS\\FVSInputFiles\\outputs.mdb;");
		
	BOOL result = TRUE;
	// Create object name for the database
	CDatabase outputs;
	//WORK IN PROGRESS 11/1/2011

	TRY
	{ 
		result = outputs.OpenEx(lpszConnect, 
			CDatabase::openReadOnly | 
			CDatabase::noOdbcDialog);
		if(FALSE == result)
		{
			printf_s("MFC ODBC: Unable to connect to data source");
		}
		
	    // Query the data file and pull out the stand characteristics for processing
		LPCTSTR query = _T("SELECT FVS_Compute.[StandID], FVS_Compute.[FML], FVS_Compute.[HTT], FVS_Compute.HTLIVE, FVS_Compute.[CBD];");
	}
	CATCH_ALL(e)
	{
		TCHAR errMsg[255];
		e->GetErrorMessage(errMsg, 255);
		printf_s("MFC ODBC: CException%s", errMsg);
	}
	END_CATCH_ALL

	outputs.Close();
}

/**
* Destructor
*/

DBase::~DBase()
{
	
}