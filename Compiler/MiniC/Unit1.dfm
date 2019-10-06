object Form1: TForm1
  Left = 233
  Top = 95
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MiniC'
  ClientHeight = 530
  ClientWidth = 721
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 3
    Top = 8
    Width = 3
    Height = 13
  end
  object Label2: TLabel
    Left = 192
    Top = 8
    Width = 3
    Height = 13
  end
  object Memo1: TMemo
    Left = -8
    Top = 24
    Width = 721
    Height = 401
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'Memo1')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 0
  end
  object Memo2: TMemo
    Left = 0
    Top = 440
    Width = 721
    Height = 97
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'Memo2')
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object MainMenu1: TMainMenu
    Left = 448
    object N1: TMenuItem
      Caption = #25991#20214
      object N2: TMenuItem
        Caption = #25171#24320
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #20445#23384
      end
      object N4: TMenuItem
        Caption = #36864#20986
        OnClick = N4Click
      end
    end
    object N5: TMenuItem
      Caption = #35789#27861#20998#26512
      object N6: TMenuItem
        Caption = #24320#22987#20998#26512
        OnClick = N6Click
      end
      object Token1: TMenuItem
        Caption = #26174#31034'Token'#34920
        OnClick = Token1Click
      end
    end
    object N7: TMenuItem
      Caption = #35821#27861#21046#23548#32763#35793
      object N8: TMenuItem
        Caption = #35821#27861#35821#20041#20998#26512
        OnClick = N8Click
      end
      object N9: TMenuItem
        Caption = #26174#31034#35821#27861#26632
        OnClick = N9Click
      end
      object N10: TMenuItem
        Caption = #26174#31034#20013#38388#20195#30721
        OnClick = N10Click
      end
    end
    object N11: TMenuItem
      Caption = #30446#26631#20195#30721
      object N12: TMenuItem
        Caption = #29983#25104#30446#26631#20195#30721
        OnClick = N12Click
      end
      object N13: TMenuItem
        Caption = #26174#31034#30446#26631#20195#30721
        OnClick = N13Click
      end
    end
    object N14: TMenuItem
      Caption = #31995#32479
      object N15: TMenuItem
        Caption = #26174#31034#26085#24535#25991#20214
        OnClick = N15Click
      end
      object N17: TMenuItem
        Caption = #26174#31034#28304#25991#20214
        OnClick = N17Click
      end
      object N18: TMenuItem
        Caption = #36816#34892
        OnClick = N18Click
      end
    end
    object N16: TMenuItem
      Caption = #24110#21161
    end
  end
  object OpenDialog1: TOpenDialog
    FileName = 'C:\Documents and Settings\Administrator\'#26700#38754'\bcb\'#27979#35797'\mytest2.asm'
    FilterIndex = 0
    Left = 496
  end
  object SaveDialog1: TSaveDialog
    Left = 544
  end
end
