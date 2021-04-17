object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 517
  ClientWidth = 387
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 224
    Top = 91
    Width = 33
    Height = 30
    Brush.Color = clRed
    Pen.Style = psClear
    Shape = stCircle
  end
  object serverEdit: TLabeledEdit
    Left = 8
    Top = 24
    Width = 177
    Height = 21
    EditLabel.Width = 37
    EditLabel.Height = 13
    EditLabel.Caption = #1057#1077#1088#1074#1077#1088
    TabOrder = 0
    Text = '127.0.0.1'
  end
  object portEdit: TLabeledEdit
    Left = 191
    Top = 24
    Width = 66
    Height = 21
    EditLabel.Width = 25
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1086#1088#1090
    TabOrder = 1
    Text = 'gds_db'
  end
  object pathToDBEdit: TLabeledEdit
    Left = 8
    Top = 64
    Width = 249
    Height = 21
    EditLabel.Width = 51
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1091#1090#1100' '#1082' '#1041#1044
    TabOrder = 2
    Text = 'd:\db\123.ibs'
  end
  object MaskEdit1: TMaskEdit
    Left = 8
    Top = 91
    Width = 113
    Height = 21
    EditMask = '!9999;1;_'
    MaxLength = 4
    TabOrder = 3
    Text = '  50'
  end
  object userEdit: TLabeledEdit
    Left = 8
    Top = 133
    Width = 121
    Height = 21
    EditLabel.Width = 93
    EditLabel.Height = 13
    EditLabel.Caption = #1048#1084#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
    TabOrder = 4
    Text = 'SYSDBA'
  end
  object passwordEdit: TLabeledEdit
    Left = 8
    Top = 176
    Width = 121
    Height = 21
    EditLabel.Width = 37
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1072#1088#1086#1083#1100
    PasswordChar = '*'
    TabOrder = 5
    Text = 'masterkey'
  end
  object Panel1: TPanel
    Left = 0
    Top = 213
    Width = 387
    Height = 304
    Align = alBottom
    TabOrder = 6
    object CheckBox1: TCheckBox
      Left = 8
      Top = 8
      Width = 17
      Height = 17
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 8
      Top = 35
      Width = 17
      Height = 17
      TabOrder = 1
    end
    object ComboBox1: TComboBox
      Left = 31
      Top = 8
      Width = 50
      Height = 21
      TabOrder = 2
      Text = 'INI'
      Items.Strings = (
        'RAW'
        'INI'
        'JSON')
    end
    object CheckBox3: TCheckBox
      Left = 8
      Top = 62
      Width = 17
      Height = 17
      TabOrder = 3
    end
    object CheckBox4: TCheckBox
      Left = 8
      Top = 89
      Width = 17
      Height = 17
      TabOrder = 4
    end
    object CheckBox5: TCheckBox
      Left = 8
      Top = 116
      Width = 17
      Height = 17
      TabOrder = 5
    end
    object ComboBox2: TComboBox
      Left = 31
      Top = 35
      Width = 50
      Height = 21
      TabOrder = 6
      Text = 'RAW'
      Items.Strings = (
        'RAW'
        'INI'
        'JSON')
    end
    object ComboBox3: TComboBox
      Left = 31
      Top = 62
      Width = 50
      Height = 21
      TabOrder = 7
      Text = 'RAW'
      Items.Strings = (
        'RAW'
        'INI'
        'JSON')
    end
    object ComboBox4: TComboBox
      Left = 31
      Top = 89
      Width = 50
      Height = 21
      TabOrder = 8
      Text = 'RAW'
      Items.Strings = (
        'RAW'
        'INI'
        'JSON')
    end
    object ComboBox5: TComboBox
      Left = 31
      Top = 116
      Width = 50
      Height = 21
      TabOrder = 9
      Text = 'RAW'
      Items.Strings = (
        'RAW'
        'INI'
        'JSON')
    end
    object Edit1: TEdit
      Left = 87
      Top = 8
      Width = 42
      Height = 21
      TabOrder = 10
      Text = 'bin'
    end
    object Edit2: TEdit
      Left = 87
      Top = 35
      Width = 42
      Height = 21
      TabOrder = 11
      Text = 'bin'
    end
    object Edit3: TEdit
      Left = 87
      Top = 62
      Width = 42
      Height = 21
      TabOrder = 12
      Text = 'bin'
    end
    object Edit4: TEdit
      Left = 87
      Top = 89
      Width = 42
      Height = 21
      TabOrder = 13
      Text = 'bin'
    end
    object Edit5: TEdit
      Left = 87
      Top = 116
      Width = 42
      Height = 21
      TabOrder = 14
      Text = 'bin'
    end
    object Edit6: TEdit
      Left = 135
      Top = 8
      Width = 121
      Height = 21
      TabOrder = 15
      Text = 'd:\\temp\\'
    end
    object Edit7: TEdit
      Left = 135
      Top = 35
      Width = 121
      Height = 21
      TabOrder = 16
      Text = 'd:\\temp\\'
    end
    object Edit8: TEdit
      Left = 135
      Top = 62
      Width = 121
      Height = 21
      TabOrder = 17
      Text = 'd:\\temp\\'
    end
    object Edit9: TEdit
      Left = 135
      Top = 89
      Width = 121
      Height = 21
      TabOrder = 18
      Text = 'd:\\temp\\'
    end
    object Edit10: TEdit
      Left = 135
      Top = 116
      Width = 121
      Height = 21
      TabOrder = 19
      Text = 'd:\\temp\\'
    end
    object Edit11: TEdit
      Left = 262
      Top = 8
      Width = 67
      Height = 21
      TabOrder = 20
      Text = 'ANY'
    end
    object Edit12: TEdit
      Left = 262
      Top = 35
      Width = 67
      Height = 21
      TabOrder = 21
      Text = 'ANY'
    end
    object Edit13: TEdit
      Left = 262
      Top = 62
      Width = 67
      Height = 21
      TabOrder = 22
      Text = 'ANY'
    end
    object Edit14: TEdit
      Left = 262
      Top = 89
      Width = 67
      Height = 21
      TabOrder = 23
      Text = 'ANY'
    end
    object Edit15: TEdit
      Left = 262
      Top = 116
      Width = 67
      Height = 21
      TabOrder = 24
      Text = 'ANY'
    end
    object HalfByte1: TCheckBox
      Left = 335
      Top = 8
      Width = 122
      Height = 17
      Caption = #1056#1072#1079#1074#1086#1088#1086#1090' '#1087#1086#1083#1091#1073#1072#1081#1090
      TabOrder = 25
    end
    object HalfByte2: TCheckBox
      Left = 335
      Top = 35
      Width = 121
      Height = 17
      Caption = #1056#1072#1079#1074#1086#1088#1086#1090' '#1087#1086#1083#1091#1073#1072#1081#1090
      TabOrder = 26
    end
    object HalfByte3: TCheckBox
      Left = 335
      Top = 61
      Width = 121
      Height = 17
      Caption = #1056#1072#1079#1074#1086#1088#1086#1090' '#1087#1086#1083#1091#1073#1072#1081#1090
      TabOrder = 27
    end
    object CheckBox8: TCheckBox
      Left = -216
      Top = 384
      Width = 97
      Height = 17
      Caption = 'CheckBox8'
      TabOrder = 28
    end
    object HalfByte4: TCheckBox
      Left = 335
      Top = 89
      Width = 121
      Height = 17
      Caption = #1056#1072#1079#1074#1086#1088#1086#1090' '#1087#1086#1083#1091#1073#1072#1081#1090
      TabOrder = 29
    end
    object HalfByte5: TCheckBox
      Left = 335
      Top = 115
      Width = 129
      Height = 17
      Caption = #1056#1072#1079#1074#1086#1088#1086#1090' '#1087#1086#1083#1091#1073#1072#1081#1090
      TabOrder = 30
    end
  end
  object counterEdit: TEdit
    Left = 144
    Top = 133
    Width = 113
    Height = 21
    TabOrder = 7
    Text = '10'
  end
  object IBDatabase1: TIBDatabase
    DatabaseName = '127.0.0.1/gds_db:d:\db\123.IBS'
    Params.Strings = (
      'user_name=sysdba'
      'password=masterkey')
    LoginPrompt = False
    DefaultTransaction = IBTransaction1
    ServerType = 'IBServer'
    Left = 152
    Top = 192
  end
  object IBQuery1: TIBQuery
    Database = IBDatabase1
    Transaction = IBTransaction1
    BufferChunks = 1000
    CachedUpdates = False
    ParamCheck = True
    Left = 208
    Top = 192
  end
  object IBTransaction1: TIBTransaction
    DefaultDatabase = IBDatabase1
    Left = 272
    Top = 184
  end
end
