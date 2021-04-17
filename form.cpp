//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

void TForm1::connect()
{
IBDatabase1->Connected = false;
AnsiString serv = serverEdit->Text;

IBDatabase1->DatabaseName = serv + "/" + portEdit->Text + ":"+pathToDBEdit->Text;
//IBDatabase1->Params->SaveToFile("d:\\db\\123.txt");
IBDatabase1->Params->Clear();
IBDatabase1->Params->Add("user_name="+userEdit->Text);
IBDatabase1->Params->Add("password="+passwordEdit->Text);
IBDatabase1->Params->Add("lc_ctype=WIN1251");
//IBDatabase1->Params->SaveToFile("d:\\db\\1234.txt");

//IBDatabase1->Connected = true;
Shape1->Brush->Color = clLime;
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


