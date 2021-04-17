//---------------------------------------------------------------------------

#ifndef processH
#define processH
//---------------------------------------------------------------------------
#endif
//#include <cstring>   // for memset()
//#include <cstdlib>
//#include <cstdio>
#include <System.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "form.h"
#include <cstdio>
#include "IniFiles.hpp"

const byte INI = 1;
const byte RAW = 0;
const byte JSON = 2;
const byte XML = 3;
const AnsiString PATH_TO_ERRORS = "d:\\temp\\";

struct record
{
	bool enabled;
	byte metaType;
	AnsiString dataExt;
	AnsiString path;
	AnsiString eventCode;
	bool HalfByte;
};

struct jsonBlock {
	TStringList *Columns;
	TStringList *Values;
	unsigned int length;
};

class process
{
public:

	~process() {}
	process(AnsiString exPath = "D://temp", byte exType=1)
	{
		META_SECTION = "Main_table";
		path = exPath;
		getDataType(exType);
		ToHalfByteReverse = False;
	}
	process(record exParams)
	{
		META_SECTION = "Main_table";
		path = exParams.path;
		dataTypeStr = exParams.dataExt;
		getDataType(exParams.metaType);
		s_eventcode = exParams.eventCode;
		type = exParams.metaType;
		ToHalfByteReverse = exParams.HalfByte;
	}
	int proc(int maxFiles);
	virtual TStringList * metaSQL(AnsiString fullFilename) {}
	virtual bool execDataSQL(AnsiString exFilename);
	virtual void execSQL(TStringList *SQLList);
	unsigned char halfByteReverse(unsigned char d);

	void setDBParams(TIBDatabase* DB,TIBQuery* quer, TIBTransaction *trans)
	{
		database = DB;	query = quer; transaction = trans;
	}
	void getDataType(byte exType);

	void writeLog(AnsiString errorText);
	void writeLog(TStringList *SQLList);
	AnsiString path;
	byte type;
	AnsiString typeStr;
	AnsiString dataTypeStr;
	bool transCommit();
	bool ToHalfByteReverse;

	jsonBlock parser(char *data, unsigned int length, AnsiString blockToFind);

protected:
	TIBDatabase *database;
	TIBQuery *query;
	TIBTransaction *transaction;
	AnsiString META_SECTION;
	AnsiString s_eventcode;
};

class processIni : public process
{
public:
	processIni(AnsiString exPath, int exType) : process(exPath, exType)
	{}
	processIni(record exParams) : process(exParams)
	{}
	TStringList * metaSQL(AnsiString fullFilename);
};

class processRaw : public process
{
public:
	processRaw(AnsiString exPath, int exType) : process(exPath, exType)
	{}
	processRaw(record exParams) : process(exParams)
	{}
	TStringList * metaSQL(AnsiString fullFilename);
};

class processJSON : public process
{
public:
	processJSON(AnsiString exPath, int exType) : process(exPath, exType)
	{}
	processJSON(record exParams) : process(exParams)
	{}
	TStringList * metaSQL(AnsiString fullFilename);
};
