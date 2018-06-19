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
      Width = 111
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
      Left = 127
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
    object cbChangePosition2: TComboBox
      Left = 220
      Top = 63
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 4
      Text = 'Pas de changement'
      Items.Strings = (
        'Pas de changement'
        'Aucun'
        'C'
        'PF'
        'SF'
        'SG'
        'PG')
    end
  end
  object gridSkills: TStringGrid
    Left = 0
    Top = 193
    Width = 768
    Height = 255
    Align = alClient
    DoubleBuffered = True
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
    ParentDoubleBuffered = False
    TabOrder = 1
    OnDrawCell = gridSkillsDrawCell
    ColWidths = (
      64
      64
      64
      64
      64)
  end
  object pnlCmd: TPanel
    Left = 0
    Top = 448
    Width = 768
    Height = 60
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object btnAccept: TButton
      Left = 679
      Top = 0
      Width = 89
      Height = 60
      Align = alRight
      ImageAlignment = iaCenter
      ImageIndex = 191
      Images = IconListsDlg.ilIconSet48x48_green
      ModalResult = 1
      TabOrder = 0
    end
  end
end
