object DraftReviewDlg: TDraftReviewDlg
  Left = 0
  Top = 0
  Caption = 'DraftReviewDlg'
  ClientHeight = 491
  ClientWidth = 645
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
  object pnlDrafts: TPanel
    Left = 0
    Top = 0
    Width = 645
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object cbDraftSel: TComboBox
      Left = 0
      Top = 0
      Width = 645
      Height = 21
      Align = alClient
      Style = csDropDownList
      TabOrder = 0
      OnChange = cbDraftSelChange
    end
  end
  object gridPlayers: TStringGrid
    Left = 0
    Top = 49
    Width = 645
    Height = 442
    Align = alClient
    DoubleBuffered = True
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColMoving, goRowSelect]
    ParentDoubleBuffered = False
    TabOrder = 1
    OnColumnMoved = gridPlayersColumnMoved
  end
end
