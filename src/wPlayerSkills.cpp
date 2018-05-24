//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//===========================================================================
//---------------------------------------------------------------------------
#include "NLPlayer.h"
//---------------------------------------------------------------------------
#include "wPlayerSkills.h"
#include "NLTK_common.h"
#include "wIconLists.h"
//---------------------------------------------------------------------------
//===========================================================================

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPlayerSkillsDlg *PlayerSkillsDlg;
//---------------------------------------------------------------------------
__fastcall TPlayerSkillsDlg::TPlayerSkillsDlg(TComponent* Owner)
	: TForm(Owner)
{
    this->zero();
    this->init();
}
//---------------------------------------------------------------------------
__fastcall TPlayerSkillsDlg::~TPlayerSkillsDlg()
{
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
bool __fastcall TPlayerSkillsDlg::showPlayerSkills( CNLPlayer* p )
{
    this->_p = p;
    this->playerDisplay();

    if ( p && this->ShowModal() == mrOk )
    {
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::zero()
{
    this->_p = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::init()
{

}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::deinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::formInit()
{

    this->cbChangePosition2->Items->Clear();
    this->cbChangePosition2->Items->Add( "Pas de changement" );
    this->cbChangePosition2->Items->Add( POS_NONE_TXT );
    this->cbChangePosition2->Items->Add( POS_PG_TXT );
    this->cbChangePosition2->Items->Add( POS_SG_TXT );
    this->cbChangePosition2->Items->Add( POS_SF_TXT );
    this->cbChangePosition2->Items->Add( POS_PF_TXT );
    this->cbChangePosition2->Items->Add( POS_C_TXT );


    gridStats->ColCount = 12;
    gridStats->RowCount = 2;

    gridStats->Cells[0][0] = AnsiString( "MJ" );
    gridStats->Cells[1][0] = AnsiString( "Min" );
    gridStats->Cells[2][0] = AnsiString( "Pts" );
    gridStats->Cells[3][0] = AnsiString( "FG" );
    gridStats->Cells[4][0] = AnsiString( "3Pts" );
    gridStats->Cells[5][0] = AnsiString( "FT" );
    gridStats->Cells[6][0] = AnsiString( "REB" );
    gridStats->Cells[7][0] = AnsiString( "AST" );
    gridStats->Cells[8][0] = AnsiString( "STL" );
    gridStats->Cells[9][0] = AnsiString( "BLK" );
    gridStats->Cells[10][0] = AnsiString( "TO" );
    gridStats->Cells[11][0] = AnsiString( "EVAL" );

    gridSkills->ColCount = 15;
    gridSkills->RowCount = 18;

    gridSkills->Cells[0][0] = AnsiString( "C" );
    gridSkills->Cells[3][0] = AnsiString( "PF" );
    gridSkills->Cells[6][0] = AnsiString( "SF" );
    gridSkills->Cells[9][0] = AnsiString( "SG" );
    gridSkills->Cells[12][0] = AnsiString( "PG" );

   // skills C :
    //-----------
    this->gridSkills->Cells[0][1] = AnsiString( "contre" );
    this->gridSkills->Cells[0][2] = AnsiString( "adresse" );
    this->gridSkills->Cells[0][3] = AnsiString( "reb off" );
    this->gridSkills->Cells[0][4] = AnsiString( "2 pts" );
    this->gridSkills->Cells[0][5] = AnsiString( "reb déf" );
    this->gridSkills->Cells[0][6] = AnsiString( "endurance" );
    this->gridSkills->Cells[0][7] = AnsiString( "lucid déf" );
    this->gridSkills->Cells[0][8] = AnsiString( "lf" );
    this->gridSkills->Cells[0][9] = AnsiString( "lucid off" );
    this->gridSkills->Cells[0][10] = AnsiString( "intercep" );
    this->gridSkills->Cells[0][11] = AnsiString( "agilité" );
    this->gridSkills->Cells[0][12] = AnsiString( "détente" );
    this->gridSkills->Cells[0][13] = AnsiString( "puissance" );
    this->gridSkills->Cells[0][14] = AnsiString( "vitesse" );
    this->gridSkills->Cells[0][15] = AnsiString( "dribble" );
    this->gridSkills->Cells[0][16] = AnsiString( "passe" );
    this->gridSkills->Cells[0][17] = AnsiString( "3 pts" );

    // skills PF :
    //------------
    this->gridSkills->Cells[3][1] = AnsiString( "contre" );
    this->gridSkills->Cells[3][2] = AnsiString( "adresse" );
    this->gridSkills->Cells[3][3] = AnsiString( "2 pts" );
    this->gridSkills->Cells[3][4] = AnsiString( "reb off" );
    this->gridSkills->Cells[3][5] = AnsiString( "lucid déf" );
    this->gridSkills->Cells[3][6] = AnsiString( "reb déf" );
    this->gridSkills->Cells[3][7] = AnsiString( "lf" );
    this->gridSkills->Cells[3][8] = AnsiString( "endurance" );
    this->gridSkills->Cells[3][9] = AnsiString( "intercep" );
    this->gridSkills->Cells[3][10] = AnsiString( "lucid off" );
    this->gridSkills->Cells[3][11] = AnsiString( "dribble" );
    this->gridSkills->Cells[3][12] = AnsiString( "passe" );
    this->gridSkills->Cells[3][13] = AnsiString( "agilité" );
    this->gridSkills->Cells[3][14] = AnsiString( "vitesse" );
    this->gridSkills->Cells[3][15] = AnsiString( "détente" );
    this->gridSkills->Cells[3][16] = AnsiString( "puissance" );
    this->gridSkills->Cells[3][17] = AnsiString( "3 pts" );

    // skills SF :
    //------------
    this->gridSkills->Cells[6][1] = AnsiString( "2 pts" );
    this->gridSkills->Cells[6][2] = AnsiString( "3 pts" );
    this->gridSkills->Cells[6][3] = AnsiString( "reb off" );
    this->gridSkills->Cells[6][4] = AnsiString( "lucid déf" );
    this->gridSkills->Cells[6][5] = AnsiString( "adresse" );
    this->gridSkills->Cells[6][6] = AnsiString( "reb déf" );
    this->gridSkills->Cells[6][7] = AnsiString( "intercep" );
    this->gridSkills->Cells[6][8] = AnsiString( "contre" );
    this->gridSkills->Cells[6][9] = AnsiString( "lf" );
    this->gridSkills->Cells[6][10] = AnsiString( "endurance" );
    this->gridSkills->Cells[6][11] = AnsiString( "lucid off" );
    this->gridSkills->Cells[6][12] = AnsiString( "passe" );
    this->gridSkills->Cells[6][13] = AnsiString( "dribble" );
    this->gridSkills->Cells[6][14] = AnsiString( "agilité" );
    this->gridSkills->Cells[6][15] = AnsiString( "détente" );
    this->gridSkills->Cells[6][16] = AnsiString( "puissance" );
    this->gridSkills->Cells[6][17] = AnsiString( "vitesse" );

    // skills SG :
    //------------
    this->gridSkills->Cells[9][1] = AnsiString( "lucid déf" );
    this->gridSkills->Cells[9][2] = AnsiString( "3 pts" );
    this->gridSkills->Cells[9][3] = AnsiString( "intercep" );
    this->gridSkills->Cells[9][4] = AnsiString( "adresse" );
    this->gridSkills->Cells[9][5] = AnsiString( "2 pts" );
    this->gridSkills->Cells[9][6] = AnsiString( "reb déf" );
    this->gridSkills->Cells[9][7] = AnsiString( "passe" );
    this->gridSkills->Cells[9][8] = AnsiString( "reb off" );
    this->gridSkills->Cells[9][9] = AnsiString( "contre" );
    this->gridSkills->Cells[9][10] = AnsiString( "endurance" );
    this->gridSkills->Cells[9][11] = AnsiString( "lucid off" );
    this->gridSkills->Cells[9][12] = AnsiString( "agilité" );
    this->gridSkills->Cells[9][13] = AnsiString( "dribble" );
    this->gridSkills->Cells[9][14] = AnsiString( "lf" );
    this->gridSkills->Cells[9][15] = AnsiString( "puissance" );
    this->gridSkills->Cells[9][16] = AnsiString( "vitesse" );
    this->gridSkills->Cells[9][17] = AnsiString( "détente" );

    // skills PG :
    //------------
    this->gridSkills->Cells[12][1] = AnsiString( "intercep" );
    this->gridSkills->Cells[12][2] = AnsiString( "2 pts" );
    this->gridSkills->Cells[12][3] = AnsiString( "adresse" );
    this->gridSkills->Cells[12][4] = AnsiString( "3 pts" );
    this->gridSkills->Cells[12][5] = AnsiString( "reb déf" );
    this->gridSkills->Cells[12][6] = AnsiString( "lucid off" );
    this->gridSkills->Cells[12][7] = AnsiString( "lucid déf" );
    this->gridSkills->Cells[12][8] = AnsiString( "passe" );
    this->gridSkills->Cells[12][9] = AnsiString( "lf" );
    this->gridSkills->Cells[12][10] = AnsiString( "endurance" );
    this->gridSkills->Cells[12][11] = AnsiString( "dribble" );
    this->gridSkills->Cells[12][12] = AnsiString( "agilité" );
    this->gridSkills->Cells[12][13] = AnsiString( "reb off" );
    this->gridSkills->Cells[12][14] = AnsiString( "détente" );
    this->gridSkills->Cells[12][15] = AnsiString( "puissance" );
    this->gridSkills->Cells[12][16] = AnsiString( "vitesse" );
    this->gridSkills->Cells[12][17] = AnsiString( "contre" );


}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::playerDisplay()
{
    if ( this->_p )
    {
        IconListsDlg->ilLogos187x49->GetBitmap( this->_p->Team , this->imgTeamLogo->Picture->Bitmap );

        AnsiString txt;
        float taille = ((float)this->_p->Height) / 100.0;
        pnlBio->Caption = txt.sprintf( "%s - %s %s ( %.2f m / %d kg ) Exp. %d" , this->_p->Number , this->_p->FName , this->_p->Name.UpperCase() , taille , this->_p->Weight , this->_p->YearsExp );
        pnlPos1->Caption = txt.sprintf( "%s (%.1f)" , this->_p->Position1 , this->_p->OverallRtg );
        pnlPos2->Caption = this->_p->Position2;

        this->cbChangePosition2->ItemIndex = 0;

        CNLPlayerStats ps;
        this->_p->loadSeasonStats( ps );

        // affichage des stats :
        //----------------------
        this->gridStats->Cells[0][1]	= txt.sprintf( "%d/%d" , ps.GMS , ps.GM );
        if ( ps.GM > 0 )
        {
	        this->gridStats->Cells[1][1]  = txt.sprintf( "%.1f" , ps.avgMIN );
            this->gridStats->Cells[2][1]  = txt.sprintf( "%.1f" , ps.avgPTS );
            this->gridStats->Cells[3][1]  = txt.sprintf( "%d/%d (%.1f %%)" , ps.FGM , ps.FGA , ps.prctFG );
            this->gridStats->Cells[4][1]  = txt.sprintf( "%d/%d (%.1f %%)" , ps.TPM , ps.TPA , ps.prctTP );
            this->gridStats->Cells[5][1]  = txt.sprintf( "%d/%d (%.1f %%)" , ps.FTM , ps.FTA , ps.prctFT );
            this->gridStats->Cells[6][1]  = txt.sprintf( "%.1f (%.1f / %.1f)" , ps.avgRB , ps.avgORB , ps.avgDRB );
            this->gridStats->Cells[7][1]  = txt.sprintf( "%.1f" , ps.avgAST );
            this->gridStats->Cells[8][1]  = txt.sprintf( "%.1f" , ps.avgSTL );
            this->gridStats->Cells[9][1]  = txt.sprintf( "%.1f" , ps.avgBLK );
            this->gridStats->Cells[10][1]  = txt.sprintf( "%.1f" , ps.avgTO );
            this->gridStats->Cells[11][1]  = txt.sprintf( "%.1f" , ps.avgEVAL );
        }
        else
        {
            for ( int i = 1 ; i < this->gridStats->ColCount ; i++ )
            {
                this->gridStats->Cells[i][1] = TXT_NULL;
            }
        }

        // skills C :
        //-----------
        this->gridSkills->Cells[1][1] = IntToStr( this->_p->skillContre );
        this->gridSkills->Cells[1][2] = IntToStr( this->_p->skillAdresse );
        this->gridSkills->Cells[1][3] = IntToStr( this->_p->skillRebondOffensif );
        this->gridSkills->Cells[1][4] = IntToStr( this->_p->skill2Pts );
        this->gridSkills->Cells[1][5] = IntToStr( this->_p->skillRebondDefensif );
        this->gridSkills->Cells[1][6] = IntToStr( this->_p->skillEndurance );
        this->gridSkills->Cells[1][7] = IntToStr( this->_p->skillLuciditeDefensive );
        this->gridSkills->Cells[1][8] = IntToStr( this->_p->skillLf );
        this->gridSkills->Cells[1][9] = IntToStr( this->_p->skillLuciditeOffensive );
        this->gridSkills->Cells[1][10] = IntToStr( this->_p->skillInterception );
        this->gridSkills->Cells[1][11] = IntToStr( this->_p->skillAgilite );
        this->gridSkills->Cells[1][12] = IntToStr( this->_p->skillDetente );
        this->gridSkills->Cells[1][13] = IntToStr( this->_p->skillPuissance );
        this->gridSkills->Cells[1][14] = IntToStr( this->_p->skillVitesse );
        this->gridSkills->Cells[1][15] = IntToStr( this->_p->skillDribble );
        this->gridSkills->Cells[1][16] = IntToStr( this->_p->skillPasse );
        this->gridSkills->Cells[1][17] = IntToStr( this->_p->skill3Pts );

        // skills PF :
        //-----------
        this->gridSkills->Cells[4][1] = IntToStr( this->_p->skillContre );
        this->gridSkills->Cells[4][2] = IntToStr( this->_p->skillAdresse );
        this->gridSkills->Cells[4][3] = IntToStr( this->_p->skill2Pts );
        this->gridSkills->Cells[4][4] = IntToStr( this->_p->skillRebondOffensif );
        this->gridSkills->Cells[4][5] = IntToStr( this->_p->skillLuciditeDefensive );
        this->gridSkills->Cells[4][6] = IntToStr( this->_p->skillRebondDefensif );
        this->gridSkills->Cells[4][7] = IntToStr( this->_p->skillLf);
        this->gridSkills->Cells[4][8] = IntToStr( this->_p->skillEndurance );
        this->gridSkills->Cells[4][9] = IntToStr( this->_p->skillInterception );
        this->gridSkills->Cells[4][10] = IntToStr( this->_p->skillLuciditeOffensive );
        this->gridSkills->Cells[4][11] = IntToStr( this->_p->skillDribble );
        this->gridSkills->Cells[4][12] = IntToStr( this->_p->skillPasse );
        this->gridSkills->Cells[4][13] = IntToStr( this->_p->skillAgilite );
        this->gridSkills->Cells[4][14] = IntToStr( this->_p->skillVitesse );
        this->gridSkills->Cells[4][15] = IntToStr( this->_p->skillDetente );
        this->gridSkills->Cells[4][16] = IntToStr( this->_p->skillPuissance );
        this->gridSkills->Cells[4][17] = IntToStr( this->_p->skill3Pts );

        // skills SF :
        //------------
        this->gridSkills->Cells[7][1] = IntToStr( this->_p->skill2Pts );
        this->gridSkills->Cells[7][2] = IntToStr( this->_p->skill3Pts );
        this->gridSkills->Cells[7][3] = IntToStr( this->_p->skillRebondOffensif );
        this->gridSkills->Cells[7][4] = IntToStr( this->_p->skillLuciditeDefensive );
        this->gridSkills->Cells[7][5] = IntToStr( this->_p->skillAdresse );
        this->gridSkills->Cells[7][6] = IntToStr( this->_p->skillRebondDefensif );
        this->gridSkills->Cells[7][7] = IntToStr( this->_p->skillInterception);
        this->gridSkills->Cells[7][8] = IntToStr( this->_p->skillContre );
        this->gridSkills->Cells[7][9] = IntToStr( this->_p->skillLf );
        this->gridSkills->Cells[7][10] = IntToStr( this->_p->skillEndurance );
        this->gridSkills->Cells[7][11] = IntToStr( this->_p->skillLuciditeOffensive );
        this->gridSkills->Cells[7][12] = IntToStr( this->_p->skillPasse );
        this->gridSkills->Cells[7][13] = IntToStr( this->_p->skillDribble );
        this->gridSkills->Cells[7][14] = IntToStr( this->_p->skillAgilite );
        this->gridSkills->Cells[7][15] = IntToStr( this->_p->skillDetente );
        this->gridSkills->Cells[7][16] = IntToStr( this->_p->skillPuissance );
        this->gridSkills->Cells[7][17] = IntToStr( this->_p->skillVitesse );

        // skills SG :
        //------------
        this->gridSkills->Cells[10][1] = IntToStr( this->_p->skillLuciditeDefensive );
        this->gridSkills->Cells[10][2] = IntToStr( this->_p->skill3Pts );
        this->gridSkills->Cells[10][3] = IntToStr( this->_p->skillInterception );
        this->gridSkills->Cells[10][4] = IntToStr( this->_p->skillAdresse );
        this->gridSkills->Cells[10][5] = IntToStr( this->_p->skill2Pts );
        this->gridSkills->Cells[10][6] = IntToStr( this->_p->skillRebondDefensif );
        this->gridSkills->Cells[10][7] = IntToStr( this->_p->skillPasse);
        this->gridSkills->Cells[10][8] = IntToStr( this->_p->skillRebondOffensif );
        this->gridSkills->Cells[10][9] = IntToStr( this->_p->skillContre );
        this->gridSkills->Cells[10][10] = IntToStr( this->_p->skillEndurance );
        this->gridSkills->Cells[10][11] = IntToStr( this->_p->skillLuciditeOffensive );
        this->gridSkills->Cells[10][12] = IntToStr( this->_p->skillAgilite );
        this->gridSkills->Cells[10][13] = IntToStr( this->_p->skillDribble );
        this->gridSkills->Cells[10][14] = IntToStr( this->_p->skillLf );
        this->gridSkills->Cells[10][15] = IntToStr( this->_p->skillPuissance );
        this->gridSkills->Cells[10][16] = IntToStr( this->_p->skillVitesse );
        this->gridSkills->Cells[10][17] = IntToStr( this->_p->skillDetente );

       // skills PG :
        //------------
        this->gridSkills->Cells[13][1] = IntToStr( this->_p->skillInterception );
        this->gridSkills->Cells[13][2] = IntToStr( this->_p->skill2Pts );
        this->gridSkills->Cells[13][3] = IntToStr( this->_p->skillAdresse );
        this->gridSkills->Cells[13][4] = IntToStr( this->_p->skill3Pts );
        this->gridSkills->Cells[13][5] = IntToStr( this->_p->skillRebondDefensif );
        this->gridSkills->Cells[13][6] = IntToStr( this->_p->skillLuciditeOffensive );
        this->gridSkills->Cells[13][7] = IntToStr( this->_p->skillLuciditeDefensive);
        this->gridSkills->Cells[13][8] = IntToStr( this->_p->skillPasse );
        this->gridSkills->Cells[13][9] = IntToStr( this->_p->skillLf );
        this->gridSkills->Cells[13][10] = IntToStr( this->_p->skillEndurance );
        this->gridSkills->Cells[13][11] = IntToStr( this->_p->skillDribble );
        this->gridSkills->Cells[13][12] = IntToStr( this->_p->skillAgilite );
        this->gridSkills->Cells[13][13] = IntToStr( this->_p->skillRebondOffensif );
        this->gridSkills->Cells[13][14] = IntToStr( this->_p->skillDetente );
        this->gridSkills->Cells[13][15] = IntToStr( this->_p->skillPuissance );
        this->gridSkills->Cells[13][16] = IntToStr( this->_p->skillVitesse );
        this->gridSkills->Cells[13][17] = IntToStr( this->_p->skillContre );

        for ( int i = 1 ; i < this->gridSkills->RowCount ; i++ )
        {
            this->gridSkills->Cells[2][i] = StringOfChar(' ',30);
            this->gridSkills->Cells[5][i] = StringOfChar(' ',30);
            this->gridSkills->Cells[8][i] = StringOfChar(' ',30);
            this->gridSkills->Cells[11][i] = StringOfChar(' ',30);
            this->gridSkills->Cells[14][i] = StringOfChar(' ',30);
        }
    }
    else
    {
        for ( int i = 0 ; i < this->gridStats->ColCount ; i++ )
        {
            this->gridStats->Cells[i][1] = TXT_NULL;
        }

        for ( int i = 1 ; i < this->gridSkills->RowCount ; i++ )
        {
            for ( int j = 0 ; j < this->gridSkills->ColCount ; j++ )
            {
                this->gridSkills->Cells[i][j] = TXT_NULL;
            }
        }
    }

    this->gridAutoSizeCol( this->gridStats , -1);
    this->gridAutoSizeCol( this->gridSkills , -1);
}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::gridAutoSizeCol( TStringGrid* grid , int col )
{
    if ( grid )
    {
        if ( col < 0 )
        {
            for ( int i = 0 ; i < grid->ColCount ; i++ )
            {
                this->gridAutoSizeCol( grid , i );
            }
        }
        else if ( col >= 0 && col <= grid->ColCount )
        {
            grid->Canvas->Font->Assign( grid->Font );

            int w_max = 0;
            for ( int i = 0 ; i < grid->RowCount ; i++ )
            {
                int w = grid->Canvas->TextWidth( grid->Cells[col][i] );
                if ( w > w_max ) w_max = w;
            }
            grid->ColWidths[ col ] = w_max + 26;
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall TPlayerSkillsDlg::getChangePos2()
{
    return ( this->cbChangePosition2->ItemIndex > 0 );
}
//---------------------------------------------------------------------------
AnsiString __fastcall TPlayerSkillsDlg::getNewPos2()
{
    return ( this->cbChangePosition2->Text );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================

void __fastcall TPlayerSkillsDlg::FormCreate(TObject *Sender)
{
    this->formInit();
}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::FormDestroy(TObject *Sender)
{
    this->formDeinit();
}
//---------------------------------------------------------------------------
void __fastcall TPlayerSkillsDlg::gridSkillsDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State)
{
    TStringGrid* grid = (TStringGrid*)Sender;

    if ( grid && ACol % 3 == 2 && ARow >= 1 )
    {
        double val = (double)grid->Cells[ACol-1][ARow].ToIntDef(0);

        double w = (double)Rect.Width() * ( val / 99.0 );

        TRect bargraph;
        bargraph.left = Rect.left;
        bargraph.top = Rect.top;
        bargraph.right = Rect.left + (int)w;
        bargraph.bottom = Rect.bottom;
        grid->Canvas->Pen->Color = clRed;
        grid->Canvas->Brush->Color = clRed;
        //grid->Canvas->FillRect(bargraph);
        grid->Canvas->Rectangle( bargraph.left , bargraph.top , bargraph.right , bargraph.bottom );
    }
}
//---------------------------------------------------------------------------
