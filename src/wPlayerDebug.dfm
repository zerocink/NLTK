object PlayerDebugDlg: TPlayerDebugDlg
  Left = 0
  Top = 0
  Caption = 'PlayerDebugDlg'
  ClientHeight = 456
  ClientWidth = 647
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
  object pnlCmds: TPanel
    Left = 0
    Top = 0
    Width = 647
    Height = 25
    Align = alTop
    BevelOuter = bvLowered
    TabOrder = 0
    object btnFirst: TButton
      Left = 1
      Top = 1
      Width = 72
      Height = 23
      Align = alLeft
      Caption = '|<'
      TabOrder = 0
      OnClick = btnFirstClick
    end
    object btnPrior: TButton
      Left = 73
      Top = 1
      Width = 72
      Height = 23
      Align = alLeft
      Caption = '<'
      TabOrder = 1
      OnClick = btnPriorClick
    end
    object btnNext: TButton
      Left = 145
      Top = 1
      Width = 72
      Height = 23
      Align = alLeft
      Caption = '>'
      TabOrder = 2
      OnClick = btnNextClick
    end
    object btnLast: TButton
      Left = 217
      Top = 1
      Width = 72
      Height = 23
      Align = alLeft
      Caption = '>|'
      TabOrder = 3
      OnClick = btnLastClick
    end
    object edtRecordIndex: TEdit
      Left = 289
      Top = 1
      Width = 282
      Height = 23
      Align = alClient
      Alignment = taCenter
      BevelInner = bvNone
      BevelOuter = bvNone
      ReadOnly = True
      TabOrder = 4
      Text = '? / ?'
      ExplicitHeight = 21
    end
    object btnTest: TButton
      Left = 571
      Top = 1
      Width = 75
      Height = 23
      Align = alRight
      Caption = 'Test'
      TabOrder = 5
      OnClick = btnTestClick
    end
  end
  object txtLog: TMemo
    Left = 0
    Top = 25
    Width = 647
    Height = 431
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Liberation Mono'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 1
    WordWrap = False
  end
end
