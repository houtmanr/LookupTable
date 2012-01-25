
#include <afxdb.h>
#include <cstring>
#include <iostream>
#include <vector>
#include "DatabaseProcessing.h"

using std::vector;
using namespace std;




DBase::DBase()
{
  const char* DAM = "MFC ODBC";

  LPCTSTR lpszConnect = 
  _T("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DSN='';DBQ=..\\..\\FVSOutputFiles\\outputs.mdb;");
		
  BOOL result = TRUE;

  // Create object name for the database
  CDatabase inputs;

  TRY
  { 
    result = inputs.OpenEx(lpszConnect, 
      CDatabase::openReadOnly | 
      CDatabase::noOdbcDialog);

    if(FALSE == result)
    {
      printf_s("MFC ODBC: Unable to connect to data source");
    }

    cout<<DAM<<": Successfully connected to database. Data source name:\n  "<<inputs.GetDatabaseName()<<endl; 

    // Query the data file and pull out the stand characteristics for processing
    LPCTSTR query = _T("SELECT FVS_Compute.[StandID], FVS_Compute.[FML], FVS_Compute.[HTT], FVS_Compute.HTLIVE, FVS_Compute.[CBD] FROM FVS_Compute;");

    cout<<DAM<<": SQL query:\n"<<CStringA(query)<<endl;

    CRecordset rs(&inputs);
    result = rs.Open(CRecordset::dynaset, query, CRecordset::none);
    if (result == TRUE)
    {
      cout<<DAM<<": Retrieve schema infor for the given result set:"<<endl;
      CODBCFieldInfo fInfo;
      short sFieldCount = rs.GetODBCFieldCount();
      if (sFieldCount>0)
      {
        for(short nIndex=0; nIndex < sFieldCount; nIndex++)
        {
          CODBCFieldInfo fInfo;
          rs.GetODBCFieldInfo(nIndex, fInfo);
          cout<<" | "<<CStringA(fInfo.m_strName);
        }
        cout<<endl;
      }
      else
      {
        cout<<DAM<<": ERROR: Number of fields in the result set is 0."<<endl;
      }
      cout<<DAM<<": Fetch the actual data: "<<endl;
      CDBVariant var;
      CString value;
	  vector<charicteristic> charicterVector;
	  charicteristic charicter;

      int rowCount = 0;
      while (!rs.IsEOF())
      {
        for (short nIndex=0; nIndex < sFieldCount; nIndex++)
        {
          rs.GetFieldValue(nIndex, var);
          switch (var.m_dwType)
          {
            case DBVT_WSTRING:
              value.Format(_T("%s"), var.m_pstringW->GetBuffer(var.m_pstringW->GetLength()));
              break;
            case DBVT_DOUBLE:
              value.Format(_T("%lf"), var.m_dblVal);
              break;
            default:
              value = "";
          }
          cout<<" | "<<CStringA(value);
		  if(nIndex = 0)
			  charicter.treeCn = _wtoi(value);
		  if(nIndex = 1)
			  charicter.fml = _wtoi(value);
		  if(nIndex = 2)
			  charicter.height = _wtof(value);
		  if(nIndex = 3)
			  charicter.heightLive = _wtof(value);
		  if(nIndex = 4)
			  charicter.cbd = _wtof(value);
        }
        cout<<endl;
        rowCount++;
        rs.MoveNext();
        charicterVector.push_back(charicter);
      }
      cout<<DAM<<": Total Row Count: "<<rowCount<<endl;
    }
  }
  CATCH_ALL(e)
  {
    TCHAR errMsg[255];
    e->GetErrorMessage(errMsg, 255);
    printf_s("MFC ODBC: CException%s", errMsg);
  }
  END_CATCH_ALL

  inputs.Close();
};

int DBase::getYear(){
  return year;
};




void DBase::Charicteristics(int standId){




};

/**
* Destructor
*/

DBase::~DBase()
{	
};