object MainDlg: TMainDlg
  Left = 0
  Top = 0
  Caption = 'MainDlg'
  ClientHeight = 263
  ClientWidth = 613
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object brnPlayerDebug: TButton
    Left = 8
    Top = 27
    Width = 129
    Height = 41
    Caption = 'Player Debug'
    TabOrder = 0
    OnClick = brnPlayerDebugClick
  end
  object btnRosters: TButton
    Left = 8
    Top = 67
    Width = 129
    Height = 41
    Caption = 'Rosters'
    TabOrder = 1
    OnClick = btnRostersClick
  end
  object cbSavedGamesPaths: TComboBox
    Left = 0
    Top = 0
    Width = 613
    Height = 21
    Align = alTop
    Style = csDropDownList
    TabOrder = 2
  end
end
