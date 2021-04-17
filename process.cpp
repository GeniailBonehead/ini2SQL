//---------------------------------------------------------------------------

#pragma hdrstop

#include "process.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void process::getDataType(byte exType)
{
	switch(exType)
	{
	case RAW:
		{	typeStr = dataTypeStr;
			break;};
	case INI:
		{	typeStr = "ini";
			break;}
	case JSON:
		{	typeStr = "json";
			break; }
	case XML:
		{	typeStr = "xml";
			break; }
		}
}

unsigned char process::halfByteReverse(unsigned char d) {     //при необходимости
   d = (d & 0x55) << 1 | (d & 0xAA) >> 1;
   d = (d & 0x33) << 2 | (d & 0xCC) >> 2;
   return d;
}

void process::writeLog(AnsiString errorText)
{
if (!DirectoryExists(PATH_TO_ERRORS))
{
	MkDir(PATH_TO_ERRORS);
}
AnsiString filename = PATH_TO_ERRORS+"SQL.txt";
	FILE *logFile = fopen(filename.c_str(), "a");
	errorText += DateTimeToStr(Now());
	if (logFile != NULL)
		fwrite(errorText.c_str(),1,errorText.Length(),logFile);
	fclose(logFile);
}

void process::writeLog(TStringList *SQLList)
{
if (!DirectoryExists(PATH_TO_ERRORS))
{
	MkDir(PATH_TO_ERRORS);
}
	AnsiString datetime = DateTimeToStr(Now());
	AnsiString filename = PATH_TO_ERRORS+datetime;
	for (int j = 4; j<filename.Length(); j++) {
		if (filename[j] == 58) filename[j] = '_';
	}
	filename+= "_metaSQL.txt";
	//SQLList->SaveToFile(filename);
}

int process::proc(int maxFiles)
{
int filesProcessed = 0;

	TSearchRec searchResult;
	if (path == "") {
		return false;
	}
	if (!(path[path.Length()-1] == '\\')) {
		path = path + "\\";
	}
	if (FindFirst(path+"*"+typeStr, faAnyFile-faDirectory, searchResult) == 0) {
		do
		{
			AnsiString filename = searchResult.Name;
			TStringList *SQLList = metaSQL(path+filename);
			if (!SQLList) {
				int x = 0;
			}
			execSQL(SQLList);
			delete SQLList;
			if (type != RAW) {
				remove((path+filename).c_str());
			}

			execDataSQL(path+filename);

			filesProcessed++;
		}	while
			((FindNext(searchResult) == 0) && (maxFiles>filesProcessed));
		FindClose(searchResult);

		transCommit();
	}
return filesProcessed;
}

bool process::transCommit()
{
	if (transaction->Active) {
		transaction->Commit();
	}
	return true;
}

jsonBlock process::parser(char *data, unsigned int length, AnsiString blockToFind)
{
//AnsiString data;

TStringList * Columns = new TStringList();
TStringList * Values = new TStringList();

bool element_started = false;
bool colval = false;
AnsiString current_element = "";
AnsiString current_column = "";
char x = data[1];
jsonBlock res;
res.Columns = Columns;
res.Values = Values;

	for (int iter = 1; iter <= length; iter++) {
		if (data[iter] == '{') {
			///////////Открыть блок
			jsonBlock innerBlock = parser(data+iter, length-iter, blockToFind); //Тут получается вложенный контейнер. Но непонятно, что с ним делать =)
				if (current_column == blockToFind) {
					return innerBlock;
				}
				if (innerBlock.Columns->Count != 0) {
					if (innerBlock.Columns->Strings[0] == blockToFind) {
                        return innerBlock;
					}
				}
			iter += innerBlock.length;
		}
		else if (data[iter] == '}') {
			if (current_element != "") {
				if (current_column == blockToFind) {
					Columns->Clear();
					Columns->Add(current_column);
					Values->Clear();
					Values->Add(current_column);
					res.length = iter;
					return res;
				}
				Values->Add(current_element);
				current_element = "";
			}
			jsonBlock block = {Columns, Values, iter};
			return block;
		}
		else if (data[iter] == '\n' || data[iter] == '\r' || data[iter] == '\t') {

        }
		else if (data[iter] == ':') {
				if (colval && (current_element != "")) {
                    current_element += data[iter];
				}
				/////////Переход к значению
                 colval = true;
			 }
		else if (data[iter] == '\"' || data[iter] == '\'') {
			//
			if (element_started) {
				///////записать значение или колонку
				if (colval) {
					if (current_element != "")
						if (current_element[current_element.Length()] == '\\') {
							current_element += data[iter];
							continue;
							}
					if (current_column == blockToFind) {
						Columns->Clear();
						Columns->Add(current_column);
						Values->Clear();
						Values->Add(current_element);
						res.length = iter;
						return res;
					}
					Values->Add(current_element);
					current_element = "";
				}
				else
				{
					current_column = current_element;
					Columns->Add(current_element);
					current_element = "";
				}
			}
			element_started = !element_started;
		}
		else if (data[iter] == ',') {
			if (current_element != "") {
				if (current_column == blockToFind) {
					Columns->Clear();
					Columns->Add(current_column);
					Values->Clear();
					Values->Add(current_column);
					res.length = iter;
					return res;
				}
				Values->Add(current_element);
				current_element = "";
			}
				 colval = false;
				 element_started = false;
				 current_element = "";
			 }
		else if (data[iter] == ' ' && current_element == "") {
				continue;
			 }
		else
		{
				current_element += data[iter];
        }
	}

return res;
delete Columns;
delete Values;

}

TStringList * processIni::metaSQL(AnsiString fullFilename)
{

TStringList * presetColumns = new TStringList();
TStringList * presetValues = new TStringList();
presetColumns->Add("s_sourceid");     presetValues->Add("0");
presetColumns->Add("s_type");     	  presetValues->Add("0");
presetColumns->Add("s_priority");     presetValues->Add("0");
presetColumns->Add("s_prelooked");    presetValues->Add("0");
presetColumns->Add("s_replicated");   presetValues->Add("0");
presetColumns->Add("s_selstatus");    presetValues->Add("-1");
presetColumns->Add("s_dchannel");     presetValues->Add("-1");
presetColumns->Add("s_rchannel");     presetValues->Add("-1");
presetColumns->Add("s_status");       presetValues->Add("0");
presetColumns->Add("s_event");        presetValues->Add("-1");
presetColumns->Add("s_deviceid");     presetValues->Add("");

	TIniFile *fileID = new TIniFile(fullFilename);
	if (fileID == NULL) {
		delete presetColumns;
		delete presetValues;
		return false;          ///
	}

TStringList * SQL = new TStringList();
SQL->Add("INSERT INTO "+META_SECTION+ "(");
	if (fileID->SectionExists(META_SECTION)) {

		TStringList *iniColumns = new TStringList();
		TStringList *iniValues = new TStringList();
		fileID->ReadSection("META_SECTION",iniColumns);
		fileID->ReadSectionValues("META_SECTION",iniValues);
		s_eventcode = fileID->ReadString("Spr_sp_data_1_table", "s_eventcode", "ANY");   //Опять какие-то костыли

		AnsiString SQL_keys = "";
		AnsiString SQL_values = "";

		for (int i = 0; i < presetColumns->Count; i++) {
			if (iniColumns->IndexOf(presetColumns->Strings[i]) == -1) {
				iniColumns->Add(presetColumns->Strings[i]);
				iniValues->Add(presetValues->Strings[i]);
			}
		}
		if (iniColumns->IndexOf("s_eventcode") == -1)
		{
			iniColumns->Add("s_eventcode");
			iniValues->Add(s_eventcode);
        }

		for (int i = 0; i < iniColumns->Count; i++) {
			AnsiString key = iniColumns->Strings[i];
			AnsiString value = fileID->ReadString(META_SECTION,iniColumns->Strings[i],"0");
			if (i<iniColumns->Count-1) {
				SQL_keys += key+", ";
				SQL_values += "\'"+value.SubString(0,20) + "\', ";
			}
			else {
				SQL_keys += key;
				SQL_values += "\'"+value+"\'";
			}
		}
		SQL->Add(SQL_keys+") VALUES (");
		SQL->Add(SQL_values+")");

		delete iniColumns;
		delete iniValues;
	}
	delete presetColumns;
	delete presetValues;
	delete fileID;
	SQL->SaveToFile("d:\\temp\\meta.txt");
	return SQL;
}

TStringList * processJSON::metaSQL(AnsiString fullFilename)
{
	///Чтение файла
	int iFileHandle;
	int iFileLength;
	int iBytesRead;
	PAnsiChar pszBuffer = 0;
	iFileHandle = FileOpen(fullFilename, fmOpenRead);
	if (iFileHandle > 0) {
	  iFileLength = FileSeek(iFileHandle, 0, 2);
	  FileSeek(iFileHandle,0,0);
	  pszBuffer = new char[iFileLength+1];
	  iBytesRead = FileRead(iFileHandle, pszBuffer, iFileLength);
	  FileClose(iFileHandle);
    }

//	  for (int bufferIter = 0; bufferIter < iBytesRead; bufferIter++)
//	  {
//		pszBuffer[bufferIter];
//	  }

TStringList * presetColumns = new TStringList();
TStringList * presetValues = new TStringList();
presetColumns->Add("s_sourceid");     presetValues->Add("0");
presetColumns->Add("s_type");     	  presetValues->Add("0");
presetColumns->Add("s_priority");     presetValues->Add("0");
presetColumns->Add("s_prelooked");    presetValues->Add("0");
presetColumns->Add("s_replicated");   presetValues->Add("0");
presetColumns->Add("s_selstatus");    presetValues->Add("-1");
presetColumns->Add("s_dchannel");     presetValues->Add("-1");
presetColumns->Add("s_rchannel");     presetValues->Add("-1");
presetColumns->Add("s_status");       presetValues->Add("0");
presetColumns->Add("s_event");        presetValues->Add("-1");
presetColumns->Add("s_deviceid");     presetValues->Add("");


TStringList * SQL = new TStringList();
SQL->Add("INSERT INTO "+META_SECTION+ "(");

		jsonBlock metaData = parser(pszBuffer, iFileLength, META_SECTION);
		TStringList *iniColumns = metaData.Columns;
		TStringList *iniValues = metaData.Values;
		AnsiString s_eventcode = "";
		TStringList *s_eventcode_list = parser(pszBuffer, iFileLength, "s_eventcode").Values;   //Опять какие-то костыли
		if (s_eventcode_list->Count != 0) {
			s_eventcode = s_eventcode_list->Strings[0];
		}
		else
			s_eventcode = "ANY";
		AnsiString SQL_keys = "";
		AnsiString SQL_values = "";

		for (int i = 0; i < presetColumns->Count; i++) {
			if (iniColumns->IndexOf(presetColumns->Strings[i]) == -1) {
				iniColumns->Add(presetColumns->Strings[i]);
				iniValues->Add(presetValues->Strings[i]);
			}
		}
		if (iniColumns->IndexOf("s_eventcode") == -1)
		{
			iniColumns->Add("s_eventcode");
			iniValues->Add(s_eventcode);
        }

		for (int i = 0; i < iniColumns->Count; i++) {
			AnsiString key = iniColumns->Strings[i];
			if (iniValues->Count < i) {
                break;
			}
			AnsiString value = iniValues->Strings[i];
			if (i < iniColumns->Count-1) {
				SQL_keys += key+", ";
				SQL_values += "\'"+value.SubString(0,20) + "\', ";
			}
			else {
				SQL_keys += key;
				SQL_values += "\'"+value+"\'";
			}
		}
		SQL->Add(SQL_keys+") VALUES (");
		SQL->Add(SQL_values+")");

		delete iniColumns;
		delete iniValues;
	delete [] pszBuffer;
	delete presetColumns;
	delete presetValues;
	SQL->SaveToFile("d:\\temp\\meta.txt");
	return SQL;
}

void process::execSQL(TStringList *SQLList)
{
	SQLList->SaveToFile(path+"metaSQL.txt");
	query->SQL = SQLList;
	try {
		query->ExecSQL();
	} catch (...) {
		writeLog("Ошибка выполнения мета-запроса");
		writeLog(SQLList);
	}
}

bool process::execDataSQL(AnsiString exFilename)
{
	AnsiString filename = exFilename.SubString(0,exFilename.Length()-this->typeStr.Length())+dataTypeStr;

	FILE *fileToDB = fopen(filename.c_str(), "rb");
	if (fileToDB == NULL) {
    	return false;
	}
	else
	{
		fseek(fileToDB,0,SEEK_END);
		int lSize = ftell(fileToDB);
		rewind(fileToDB);
		unsigned char* buffer = (char*) malloc(sizeof(char) * lSize);
		size_t result = fread(buffer, sizeof(char), lSize, fileToDB);

		if (this->ToHalfByteReverse) {
			for (int i = 0; i < lSize; i++) {
				buffer[i] = halfByteReverse(buffer[i]);
			}
		}

		TStringList *SQL = new TStringList();
		if (result>5) {
			try {
				query->SQL->Clear();
				query->SQL->Add("INSERT INTO DATA_TABLE (s_key, s_order, s_type, s_f) VALUES ");
				query->SQL->Add("((Select max(s_inckey) from Main_table), 0, '"+s_eventcode+"', :s_f)");
				query->ParamByName("s_f")->SetBlobData(buffer, result);
				query->ExecSQL();
				query->SQL->Clear();
			} catch (...) {
				writeLog("Ошибка выполнения внесения данных");
				//writeLog(query->SQL);
			}
		}
		delete SQL;
		fclose(fileToDB);
		delete buffer;
		remove(filename.c_str());
	}
}

TStringList * processRaw::metaSQL(AnsiString fullFilename)
{
String	s_datetime, s_sysnumbertype2, s_duration;

	FILE *file = fopen(fullFilename.c_str(), "rb");      //Проверку открытия файла
	fseek(file,0,SEEK_END);
	int lSize = ftell(file);

s_datetime = "'"+StrToDateTime(FileDateToDateTime(FileAge(fullFilename)))+"'";

int dur_int = ceil(lSize/1024);
int dur_int2;
dur_int2 = floor(dur_int/60);
String dur_str;
int dur_int3 =  floor(dur_int2/60);
dur_int2 -= 60*dur_int3;
if (dur_int3 <10) {	dur_str = "0";}
dur_str += IntToStr(dur_int3)+":";
if (dur_int2 <10) {	dur_str += "0";}
dur_str += IntToStr(dur_int2)+":";
dur_int2 = ceil(dur_int % 60);
if (dur_int2 <10) {	dur_str += "0";}
dur_str += IntToStr(dur_int2)+"'";

fclose(file);
//	delete file2;

s_duration = "'"+dur_str;

//s_eventcode = ;

TStringList * SQL = new TStringList();

SQL->Clear();

SQL->Add("INSERT INTO "+META_SECTION+ " (s_type, s_datetime, s_type, s_sourceid, s_priority, ");
SQL->Add("s_prelooked,");
SQL->Add("s_eventcode, s_replicated, s_dur, s_selstatus, s_dchannel, s_rchannel, s_status, ");
SQL->Add("s_event, s_st");

SQL->Add(") VALUES ");
SQL->Add("(0, "+s_datetime+", 2, 0, ");
SQL->Add("0, 0,'"+s_eventcode+"', 0," +s_duration+", -1, -1, -1, 0,-1, '"+path.SubString(0,100)+"'"); //path or full name?

SQL->Add(");");

return SQL;

}
