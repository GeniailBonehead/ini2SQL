//---------------------------------------------------------------------------


#include "module.h"

char* module_name        = "SQL";
char* module_description = "Пихалка в БДшку";
char* module_group       = "Утилиты";
char* module_version     = "0.0.1";
bool  module_generator   = true;

void __stdcall Module::createModule()
{
	//создать экземпляр модуля
	settings_form = new TForm1(NULL);
	h_SettingsForm = settings_form->Handle;
}


void __stdcall Module::showForm()
{
	//показать форму, если она есть
	 settings_form->Visible = true;
	 
}

Module::~Module()
{

}

bool __stdcall  Module::initResources()
{
	//старт схемы - инициализация модуля
	//pathToFiles = settings_form->pathToFilesEdit->Text;
	AnsiString mask = settings_form->MaskEdit1->Text;
	char *maskChar = mask.c_str();
	for (int i = 0; i < mask.Length(); i++) {
		if (maskChar[i] == ' ') {
			maskChar[i] = '0';
		}
	}
	maxFiles = StrToInt(maskChar);
	allProceed = 0;

	settings_form->connect();
	countMax = StrToInt(settings_form->counterEdit->Text);
	if (!kernel)
		return false;

	return true;
}

bool Module::exec(record oneRec)
{
switch (oneRec.metaType) {
	case INI:
		{
			processIni firstPr(oneRec);
			firstPr.setDBParams(settings_form->IBDatabase1,settings_form->IBQuery1,settings_form->IBTransaction1);
			firstPr.proc(maxFiles);
			break;
		}
	case RAW:
		{
			processRaw firstPr(oneRec);
			firstPr.setDBParams(settings_form->IBDatabase1,settings_form->IBQuery1,settings_form->IBTransaction1);
			firstPr.proc(maxFiles);
			break;
		}
	case JSON:
		{
			processJSON firstPr(oneRec);
			firstPr.setDBParams(settings_form->IBDatabase1,settings_form->IBQuery1,settings_form->IBTransaction1);
			firstPr.proc(maxFiles);
			break;
		}

default:
	kernel->logError("Не, так не работает");
	break;
}
}

bool __stdcall Module::processTimeout()
{
if (counter++ < countMax) {
	return true;
}
	counter = 0;

if (settings_form->CheckBox1->Checked) {
	record oneRec;
	oneRec.enabled = settings_form->CheckBox1->Checked;
	oneRec.metaType = settings_form->ComboBox1->ItemIndex;
	oneRec.dataExt = settings_form->Edit1->Text;
	oneRec.path = settings_form->Edit6->Text;
	oneRec.eventCode = settings_form->Edit11->Text;
	oneRec.HalfByte = settings_form->HalfByte1->Checked;

	exec(oneRec);
}

if (settings_form->CheckBox2->Checked) {
	record oneRec;
	oneRec.enabled = settings_form->CheckBox2->Checked;
	oneRec.metaType = settings_form->ComboBox2->ItemIndex;
	oneRec.dataExt = settings_form->Edit2->Text;
	oneRec.path = settings_form->Edit7->Text;
	oneRec.eventCode = settings_form->Edit12->Text;
	oneRec.HalfByte = settings_form->HalfByte2->Checked;

	exec(oneRec);
}

if (settings_form->CheckBox3->Checked) {
	record oneRec;
	oneRec.enabled = settings_form->CheckBox3->Checked;
	oneRec.metaType = settings_form->ComboBox3->ItemIndex;
	oneRec.dataExt = settings_form->Edit3->Text;
	oneRec.path = settings_form->Edit8->Text;
	oneRec.eventCode = settings_form->Edit13->Text;
	oneRec.HalfByte = settings_form->HalfByte3->Checked;

	exec(oneRec);
	}

if (settings_form->CheckBox4->Checked) {
	record oneRec;
	oneRec.enabled = settings_form->CheckBox4->Checked;
	oneRec.metaType = settings_form->ComboBox4->ItemIndex;
	oneRec.dataExt = settings_form->Edit4->Text;
	oneRec.path = settings_form->Edit9->Text;
	oneRec.eventCode = settings_form->Edit14->Text;
	oneRec.HalfByte = settings_form->HalfByte4->Checked;

	exec(oneRec);
}

if (settings_form->CheckBox5->Checked) {
	record oneRec;
	oneRec.enabled = settings_form->CheckBox5->Checked;
	oneRec.metaType = settings_form->ComboBox5->ItemIndex;
	oneRec.dataExt = settings_form->Edit5->Text;
	oneRec.path = settings_form->Edit10->Text;
	oneRec.eventCode = settings_form->Edit15->Text;
	oneRec.HalfByte = settings_form->HalfByte5->Checked;

	exec(oneRec);
}
	//таймаут, приблизительно 1 секунда
	return true;
}

void __stdcall Module::tellParams()
{
AnsiString server = settings_form->serverEdit->Text;
	kernel->defineParameterStr("Сервер", server.c_str());
AnsiString port = settings_form->portEdit->Text;
	kernel->defineParameterStr("Порт", port.c_str());
AnsiString pathToDB = settings_form->pathToDBEdit->Text;
	kernel->defineParameterStr("Путь_к_БД", pathToDB.c_str());
AnsiString maxFiles = settings_form->MaskEdit1->Text;
	kernel->defineParameterStr("Файлов_в_цикле", maxFiles.c_str());
AnsiString user = settings_form->userEdit->Text;
	kernel->defineParameterStr("Пользователь", user.c_str());
AnsiString password = settings_form->passwordEdit->Text;
	kernel->defineParameterStr("Пароль", password.c_str());

bool enable1 = settings_form->CheckBox1->Checked;
	kernel->defineParameterBool("enable1", enable1);
bool enable2 = settings_form->CheckBox2->Checked;
	kernel->defineParameterBool("enable2", enable2);
bool enable3 = settings_form->CheckBox3->Checked;
	kernel->defineParameterBool("enable3", enable3);
bool enable4 = settings_form->CheckBox4->Checked;
	kernel->defineParameterBool("enable4", enable4);
bool enable5 = settings_form->CheckBox5->Checked;
	kernel->defineParameterBool("enable5", enable5);

bool HalfByte1 = settings_form->HalfByte1->Checked;
	kernel->defineParameterBool("HalfByte1", HalfByte1);
bool HalfByte2 = settings_form->HalfByte2->Checked;
	kernel->defineParameterBool("HalfByte2", HalfByte2);
bool HalfByte3 = settings_form->HalfByte3->Checked;
	kernel->defineParameterBool("HalfByte3", HalfByte3);
bool HalfByte4 = settings_form->HalfByte4->Checked;
	kernel->defineParameterBool("HalfByte4", HalfByte4);
bool HalfByte5 = settings_form->HalfByte5->Checked;
	kernel->defineParameterBool("HalfByte5", HalfByte5);

int  type1   = settings_form->ComboBox1->ItemIndex;
	kernel->defineParameterInt("type1", type1);
int  type2   = settings_form->ComboBox1->ItemIndex;
	kernel->defineParameterInt("type2", type2);
int  type3   = settings_form->ComboBox1->ItemIndex;
	kernel->defineParameterInt("type3", type3);
int  type4   = settings_form->ComboBox1->ItemIndex;
	kernel->defineParameterInt("type4", type4);
int  type5   = settings_form->ComboBox1->ItemIndex;
	kernel->defineParameterInt("type5", type5);

AnsiString dataExt1 = settings_form->Edit1->Text;
	kernel->defineParameterStr("ТипДанных1", dataExt1.c_str());
AnsiString dataExt2 = settings_form->Edit2->Text;
	kernel->defineParameterStr("ТипДанных2", dataExt2.c_str());
AnsiString dataExt3 = settings_form->Edit3->Text;
	kernel->defineParameterStr("ТипДанных3", dataExt3.c_str());
AnsiString dataExt4 = settings_form->Edit4->Text;
	kernel->defineParameterStr("ТипДанных4", dataExt4.c_str());
AnsiString dataExt5 = settings_form->Edit5->Text;
	kernel->defineParameterStr("ТипДанных5", dataExt5.c_str());

AnsiString path1 = settings_form->Edit6->Text;
	kernel->defineParameterStr("path1", path1.c_str());
AnsiString path2 = settings_form->Edit7->Text;
	kernel->defineParameterStr("path2", path2.c_str());
AnsiString path3 = settings_form->Edit8->Text;
	kernel->defineParameterStr("path3", path3.c_str());
AnsiString path4 = settings_form->Edit9->Text;
	kernel->defineParameterStr("path4", path4.c_str());
AnsiString path5 = settings_form->Edit10->Text;
	kernel->defineParameterStr("path5", path5.c_str());

AnsiString data1 = settings_form->Edit11->Text;
	kernel->defineParameterStr("data1", data1.c_str());
AnsiString data2 = settings_form->Edit12->Text;
	kernel->defineParameterStr("data2", data2.c_str());
AnsiString data3 = settings_form->Edit13->Text;
	kernel->defineParameterStr("data3", data3.c_str());
AnsiString data4 = settings_form->Edit14->Text;
	kernel->defineParameterStr("data4", data4.c_str());
AnsiString data5 = settings_form->Edit15->Text;
	kernel->defineParameterStr("data5", data5.c_str());
	//перечислить параметры для их сохранения
}

bool __stdcall Module::setParameter(const char* _name, const char* _value, int _type)
{
if (AnsiString(_name) == "Сервер")
	settings_form->serverEdit->Text = _value;
if (AnsiString(_name) == "Порт")
	settings_form->portEdit->Text = _value;
if (AnsiString(_name) == "Путь_к_БД")
	settings_form->pathToDBEdit->Text = _value;
if (AnsiString(_name) == "Файлов_в_цикле")
	settings_form->MaskEdit1->Text = _value;
if (_name == "Пользователь")
	settings_form->userEdit->Text = _value;
if (AnsiString(_name) == "Пароль")
	settings_form->passwordEdit->Text = _value;

if (AnsiString(_name) == "enable1")
	settings_form->CheckBox1->Checked = StrToBool(_value);
if (AnsiString(_name) == "enable2")
	settings_form->CheckBox2->Checked = StrToBool(_value);
if (AnsiString(_name) == "enable3")
	settings_form->CheckBox3->Checked = StrToBool(_value);
if (AnsiString(_name) == "enable4")
	settings_form->CheckBox4->Checked = StrToBool(_value);
if (AnsiString(_name) == "enable5")
	settings_form->CheckBox5->Checked = StrToBool(_value);

if (AnsiString(_name) == "HalfByte1")
	settings_form->HalfByte1->Checked = StrToBool(_value);
if (AnsiString(_name) == "HalfByte2")
	settings_form->HalfByte2->Checked = StrToBool(_value);
if (AnsiString(_name) == "HalfByte3")
	settings_form->HalfByte3->Checked = StrToBool(_value);
if (AnsiString(_name) == "HalfByte4")
	settings_form->HalfByte4->Checked = StrToBool(_value);
if (AnsiString(_name) == "HalfByte5")
	settings_form->HalfByte5->Checked = StrToBool(_value);

if (AnsiString(_name) == "type1")
	settings_form->ComboBox1->ItemIndex = StrToInt(_value);
if (AnsiString(_name) == "type2")
	settings_form->ComboBox2->ItemIndex = StrToInt(_value);
if (AnsiString(_name) == "type3")
	settings_form->ComboBox3->ItemIndex = StrToInt(_value);
if (AnsiString(_name) == "type4")
	settings_form->ComboBox4->ItemIndex = StrToInt(_value);
if (AnsiString(_name) == "type5")
	settings_form->ComboBox5->ItemIndex = StrToInt(_value);

if (AnsiString(_name) == "ТипДанных1")
	settings_form->Edit1->Text = _value;
if (AnsiString(_name) == "ТипДанных2")
	settings_form->Edit2->Text = _value;
if (AnsiString(_name) == "ТипДанных3")
	settings_form->Edit3->Text = _value;
if (AnsiString(_name) == "ТипДанных4")
	settings_form->Edit4->Text = _value;
if (AnsiString(_name) == "ТипДанных5")
	settings_form->Edit5->Text = _value;

if (AnsiString(_name) == "path1")
	settings_form->Edit6->Text = _value;
if (AnsiString(_name) == "path2")
	settings_form->Edit7->Text = _value;
if (AnsiString(_name) == "path3")
	settings_form->Edit8->Text = _value;
if (AnsiString(_name) == "path4")
	settings_form->Edit9->Text = _value;
if (AnsiString(_name) == "path5")
	settings_form->Edit10->Text = _value;

if (AnsiString(_name) == "data1")
	settings_form->Edit11->Text = _value;
if (AnsiString(_name) == "data2")
	settings_form->Edit12->Text = _value;
if (AnsiString(_name) == "data3")
	settings_form->Edit13->Text = _value;
if (AnsiString(_name) == "data4")
	settings_form->Edit14->Text = _value;
if (AnsiString(_name) == "data5")
	settings_form->Edit15->Text = _value;

	if (AnsiString(_name) == "Временная папка") {
		settings_form->Edit2->Text = _value;
	}
	//установить параметр (после загрузки схемы)

	return true;
}

//DLL export functions

extern "C" __declspec(dllexport) IModule*  __stdcall getModuleInstance()
{
	return reinterpret_cast<IModule*>(new Module());;
}

extern "C" __declspec(dllexport) void  __stdcall removeModuleInstance(IModule* aVal)
{
	//call our destructor
	if ( aVal != NULL )
	{
		delete (Module*)aVal;
	}
}

