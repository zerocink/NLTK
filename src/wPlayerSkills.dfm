object PlayerSkillsDlg: TPlayerSkillsDlg
  Left = 0
  Top = 0
  Caption = 'PlayerSkillsDlg'
  ClientHeight = 508
  ClientWidth = 768
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
  object pnlGeneral: TPanel
    Left = 0
    Top = 0
    Width = 768
    Height = 193
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object imgTeamLogo: TImage
      Left = 575
      Top = 8
      Width = 187
      Height = 49
      Center = True
    end
    object gridStats: TStringGrid
      Left = 0
      Top = 120
      Width = 768
      Height = 73
      Align = alBottom
      DoubleBuffered = True
      FixedCols = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
      ParentDoubleBuffered = False
      TabOrder = 0
      ExplicitTop = 104
      ExplicitWidth = 662
      ColWidths = (
        64
        64
        64
        64
        64)
    end
    object pnlBio: TPanel
      Left = 10
      Top = 8
      Width = 559
      Height = 49
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object pnlPos1: TPanel
      Left = 10
      Top = 63
      Width = 87
      Height = 49
      BevelOuter = bvLowered
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object pnlPos2: TPanel
      Left = 103
      Top = 63
      Width = 87
      Height = 49
      BevelOuter = bvLowered
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
  end
  object gridSkills: TStringGrid
    Left = 0
    Top = 193
    Width = 768
    Height = 263
    Align = alClient
    DoubleBuffered = True
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
    ParentDoubleBuffered = False
    TabOrder = 1
    ExplicitLeft = -40
    ExplicitTop = 245
    ColWidths = (
      64
      64
      64
      64
      64)
  end
  object pnlCmd: TPanel
    Left = 0
    Top = 456
    Width = 768
    Height = 52
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
  end
end
