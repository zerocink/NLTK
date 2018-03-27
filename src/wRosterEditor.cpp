//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//===========================================================================
//---------------------------------------------------------------------------
#include "wRosterEditor.h"
#include "NLTK_common.h"
#include "wIconLists.h"
#include "wAcceptChanges.h"
//---------------------------------------------------------------------------
//===========================================================================


#pragma package(smart_init)
#pragma resource "*.dfm"

TRosterEditorDlg *RosterEditorDlg;

//===========================================================================
// CONSTANTES :
//---------------------------------------------------------------------------
#define COL_RP		    AnsiString( "RP" )
#define COL_NOM         AnsiString( "Nom" )
#define COL_TAILLE      AnsiString( "Taille" )
#define COL_POIDS       AnsiString( "Poids" )
#define COL_POS         AnsiString( "Pos" )
#define COL_OVRL        AnsiString( "Ovrl" )
#define COL_EXP         AnsiString( "Exp" )
#define COL_PTS         AnsiString( "Pts" )
#define COL_RB          AnsiString( "Rb" )
#define COL_AST         AnsiString( "Ast" )
#define COL_BLK         AnsiString( "Blk" )
#define COL_STL         AnsiString( "Stl" )
#define COL_EVAL        AnsiString( "Eval" )
//---------------------------------------------------------------------------
#define RP              (this->_fieldCols->IndexOf(COL_RP))
#define NOM             (this->_fieldCols->IndexOf(COL_NOM))
#define TAILLE          (this->_fieldCols->IndexOf(COL_TAILLE))
#define POIDS           (this->_fieldCols->IndexOf(COL_POIDS))
#define POS             (this->_fieldCols->IndexOf(COL_POS))
#define OVRL            (this->_fieldCols->IndexOf(COL_OVRL))
#define EXP             (this->_fieldCols->IndexOf(COL_EXP))
#define PTS             (this->_fieldCols->IndexOf(COL_PTS))
#define RB              (this->_fieldCols->IndexOf(COL_RB))
#define AST             (this->_fieldCols->IndexOf(COL_AST))
#define BLK             (this->_fieldCols->IndexOf(COL_BLK))
#define STL             (this->_fieldCols->IndexOf(COL_STL))
#define EVAL            (this->_fieldCols->IndexOf(COL_EVAL))
//===========================================================================

//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
__fastcall TRosterEditorDlg::TRosterEditorDlg(TComponent* Owner)
	: TForm(Owner)
{
    this->zero();
    this->init();
}
//---------------------------------------------------------------------------
__fastcall TRosterEditorDlg::~TRosterEditorDlg()
{
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::zero()
{
    this->_sg = NULL;
    this->_rosters = NULL;
    this->_fieldCols = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::init()
{
    if ( !this->_rosters ) this->_rosters = new TList();
    if ( !this->_fieldCols )
    {
    	this->_fieldCols = new TStringList();

        // ordre par défaut des colonnes :
        //--------------------------------
        this->_fieldCols->Add( COL_RP );
        this->_fieldCols->Add( COL_NOM );
        this->_fieldCols->Add( COL_TAILLE );
        this->_fieldCols->Add( COL_POIDS );
        this->_fieldCols->Add( COL_POS );
        this->_fieldCols->Add( COL_OVRL );
        this->_fieldCols->Add( COL_EXP );
        this->_fieldCols->Add( COL_PTS );
        this->_fieldCols->Add( COL_RB );
        this->_fieldCols->Add( COL_AST );
        this->_fieldCols->Add( COL_BLK );
        this->_fieldCols->Add( COL_STL );
        this->_fieldCols->Add( COL_EVAL );
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::deinit()
{
    if ( this->_fieldCols )
    {
        this->_fieldCols->Clear();
        delete this->_fieldCols;
        this->_fieldCols = NULL;
    }

    if ( this->_rosters )
    {
        this->clearRosters();

        delete this->_rosters;
        this->_rosters = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::formInit()
{
    this->Caption = Application->Title;
    this->pnlTeam->ClientHeight = 64;
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::clearRosters()
{
    if ( this->_rosters )
    {
        while ( this->_rosters->Count )
        {
            CNLRoster* r = (CNLRoster*)this->_rosters->Items[ 0 ];
            if ( r )
            {
                ZeroMemory( r , sizeof( CNLRoster ) );
                delete r;
                r = NULL;
            }
            this->_rosters->Delete( 0 );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::updateTeams()
{
    this->cbTeamSel->Items->Clear();

    if ( this->_rosters )
    {
        for ( int i = 0 ; i < this->_rosters->Count ; i++ )
        {
            CNLRoster* r = (CNLRoster*)this->_rosters->Items[ i ];
            if ( r && r->team )
            {
                this->cbTeamSel->Items->AddObject( r->team->CityName , (TObject*)r );
            }
            else
            {
                this->cbTeamSel->Items->AddObject( AnsiString( "NULL" ) , (TObject*)NULL );
            }
        }
    }

    if ( this->cbTeamSel->Items->Count > 0 )
    {
        this->cbTeamSel->ItemIndex = 0;
    }
    else
    {
        this->cbTeamSel->ItemIndex = -1;
    }

    this->updatePlayers();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::updatePlayers()
{
    // vidage de la grille :
    //----------------------
    for ( int i = 0 ; i < this->gridPlayers->ColCount ; i++ )
    {
        for ( int j = 0 ; j < this->gridPlayers->RowCount ; j++ )
        {
            this->gridPlayers->Cells[i][j]	 	= TXT_NULL;
            this->gridPlayers->Objects[i][j]	= NULL;
        }
    }

    // initialisation des lignes et colonnes :
    //----------------------------------------
    this->gridPlayers->RowCount = ROSTER_SIZE + 1;
    this->gridPlayers->ColCount = this->_fieldCols->Count;

    // titres des colonnes :
    //----------------------
    for ( int i = 0 ; i < this->_fieldCols->Count ; i++ )
    {
        AnsiString titre = this->_fieldCols->Strings[ i ];
        this->gridPlayers->Cells[i][0] = titre;
    }

    // récup roster sélectionné dans la liste déroulante :
    //----------------------------------------------------
    CNLRoster* r = (CNLRoster*)this->cbTeamSel->Items->Objects[ this->cbTeamSel->ItemIndex ];
    if ( r )
    {
        for ( int i = 0 ; i < ROSTER_SIZE ; i++ )
        {
            CNLPlayer* p = r->players[ i ];
            this->playerDisplay( p , i+1 );
        }
    }

    // auto size des colonnes de la grille :
    //--------------------------------------
    this->autoSizeCol( -1 );
    this->autoSizeRow( -1 );
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::autoSizeCol( int col )
{
    if ( col < 0 )
    {
        for ( int i = 0 ; i < this->gridPlayers->ColCount ; i++ )
        {
            this->autoSizeCol( i );
        }
    }
    else if ( col >= 0 && col <= this->gridPlayers->ColCount )
    {
        this->gridPlayers->Canvas->Font->Assign( this->gridPlayers->Font );

        int w_max = 0;
        for ( int i = 0 ; i < this->gridPlayers->RowCount ; i++ )
        {
            int w = this->gridPlayers->Canvas->TextWidth( this->gridPlayers->Cells[col][i] );
            if ( w > w_max ) w_max = w;
        }
        this->gridPlayers->ColWidths[ col ] = w_max + 26;
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::autoSizeRow( int row )
{

}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::playerDisplay( CNLPlayer* p , int row )
{
    if ( p && row >= 1 && row < this->gridPlayers->RowCount )
    {
        AnsiString txt;

        CNLPlayerStats ps;
        p->loadSeasonStats( ps );

        this->gridPlayers->Objects[0][row] = (TObject*)p;
        this->gridPlayers->Cells[RP][row] = p->RosterPosText;
        this->gridPlayers->Cells[NOM][row] = txt.sprintf( "%s %s %s" , p->Number , p->FName , p->Name );
        this->gridPlayers->Cells[TAILLE][row] = txt.sprintf( "%01.02f m" , (double)p->Height/100.0 );
        this->gridPlayers->Cells[POIDS][row] = txt.sprintf( "%d kg" , p->Weight );
        this->gridPlayers->Cells[POS][row] = txt.sprintf( "%s / %s " , p->Position1 , p->Position2 );
        this->gridPlayers->Cells[OVRL][row] = txt.sprintf( "%2.01f" , p->OverallRtg );
        this->gridPlayers->Cells[EXP][row] = txt.sprintf( "%d" , p->YearsExp );

        if (  ps.GM > 0  )
        {
            this->gridPlayers->Cells[PTS][row] = txt.sprintf( "%2.01f" , ps.avgPTS );
            this->gridPlayers->Cells[RB][row] = txt.sprintf( "%2.01f" , ps.avgRB );
            this->gridPlayers->Cells[AST][row] = txt.sprintf( "%2.01f" , ps.avgAST );
            this->gridPlayers->Cells[BLK][row] = txt.sprintf( "%2.01f" , ps.avgBLK );
            this->gridPlayers->Cells[STL][row] = txt.sprintf( "%2.01f" , ps.avgSTL );
            this->gridPlayers->Cells[EVAL][row] = txt.sprintf( "%2.01f" , ps.avgEVAL );

        }
        else
        {
            this->gridPlayers->Cells[PTS][row] = TXT_NULL;
            this->gridPlayers->Cells[RB][row] = TXT_NULL;
            this->gridPlayers->Cells[AST][row] = TXT_NULL;
            this->gridPlayers->Cells[BLK][row] = TXT_NULL;
            this->gridPlayers->Cells[STL][row] = TXT_NULL;
            this->gridPlayers->Cells[EVAL][row] = TXT_NULL;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::playerMoveUp()
{
    if ( this->playerSwitch( this->gridPlayers->Row , this->gridPlayers->Row-1 ) )
    {
        this->gridPlayers->Row--;
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::playerMoveDown()
{
    if ( this->playerSwitch( this->gridPlayers->Row , this->gridPlayers->Row+1 ) )
    {
        this->gridPlayers->Row++;
    }
}
//---------------------------------------------------------------------------
bool __fastcall TRosterEditorDlg::playerSwitch( int row1 , int row2 )
{
    int i1 = row1 - 1;
    int i2 = row2 - 1;

    if ( ( i1 >= 0 && i1 < ROSTER_SIZE ) &&
		 ( i2 >= 0 && i2 < ROSTER_SIZE ) &&
         ( i1 != i2 )
       )
    {

	    CNLRoster* r = (CNLRoster*)this->cbTeamSel->Items->Objects[ this->cbTeamSel->ItemIndex ];
        if ( r )
        {
            CNLPlayer* p1 = r->players[ i1 ];
            CNLPlayer* p2 = r->players[ i2 ];
            if ( p1 && p2 )
            {
                r->players[ i1 ] = p2;
                r->players[ i2 ] = p1;
                p1->RosterPos = i2;
                p2->RosterPos = i1;

                this->playerDisplay( r->players[ i1 ] , row1 );
                this->playerDisplay( r->players[ i2 ] , row2 );

                return true;
            }
        }
    }

    return false;
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::rostersAccept()
{
    if ( this->_sg )
    {
	    bool ok = this->_sg->playersAccept();
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::rostersUpdate()
{
    if ( this->_sg )
    {
        bool ok = this->_sg->playersUpdate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::setSg( CNLSavedGame* sg )
{
    this->_sg = sg;
    this->clearRosters();

    if ( sg )
    {
        // récupération de la liste des équipes :
        //---------------------------------------
        for ( int i = 0 ; i < sg->teamCount ; i++ )
        {
            CNLTeam* t = sg->teamByIndex[ i ];
            if ( t && t->TeamCode == TEAMCODE_NBATEAM )
            {
                CNLRoster* r = new CNLRoster;
                ZeroMemory( r , sizeof( CNLRoster ) );
                r->team = t;
                this->_rosters->Add( r );
            }
        }

        // affectation des joueurs dans les rosters :
        //-------------------------------------------
        for ( int i = 0 ; i < sg->playerCount ; i++ )
        {
            CNLPlayer* p = sg->playerByIndex[ i ];
            if ( p && p->InSeason )
            {
                // recherche roster du joueur :
                //-----------------------------
                CNLRoster* r = this->teamRoster[ p->Team ];
                if ( r && p->RosterPos >= 0 && p->RosterPos < ROSTER_SIZE )
                {
                    r->players[ p->RosterPos ] = p;
                }
            }
        }
    }

    this->updateTeams();
}
//---------------------------------------------------------------------------
CNLRoster* __fastcall TRosterEditorDlg::getTeamRoster( WORD teamNum )
{
    if ( this->_rosters )
    {
        for ( int i = 0 ; i < this->_rosters->Count ; i++ )
        {
            CNLRoster* r = (CNLRoster*)this->_rosters->Items[ i ];
            if ( r && r->team && r->team->TeamNum == teamNum ) return r;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
CNLPlayer* __fastcall TRosterEditorDlg::getPlayerAtRow( int row )
{
    if ( row > 0 && row < this->gridPlayers->RowCount )
    {
        CNLRoster* r = (CNLRoster*)this->cbTeamSel->Items->Objects[ this->cbTeamSel->ItemIndex ];
        if ( r )
        {
            return r->players[ row-1 ];
        }
    }
    return NULL;
}
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
void __fastcall TRosterEditorDlg::FormCreate(TObject *Sender)
{
    this->formInit();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::FormDestroy(TObject *Sender)
{
    this->formDeinit();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::cbTeamSelChange(TObject *Sender)
{
    this->updatePlayers();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::btnTeamPrevClick(TObject *Sender)
{
    if ( this->cbTeamSel->ItemIndex > 0 ) this->cbTeamSel->ItemIndex--;
    this->updatePlayers();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::btnTeamNextClick(TObject *Sender)
{
    if ( this->cbTeamSel->ItemIndex < this->cbTeamSel->Items->Count-1 ) this->cbTeamSel->ItemIndex++;
    this->updatePlayers();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::gridPlayersDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State)
{
    if ( !State.Contains( gdFixed ) )
    {

        // collecte infos sur joueur sélectionné :
        //----------------------------------------
        CNLPlayer* p = (CNLPlayer*)this->gridPlayers->Objects[ 0 ][ ARow ];
        if ( p )
        {
            TColor textColor = this->gridPlayers->Font->Color;

            if ( p->InjuryId != 0 )
            {

                if ( p->IsPlayable ) textColor = clWebOrange;
                else textColor = clRed;

                this->gridPlayers->Canvas->Font->Assign( this->gridPlayers->Font );
                this->gridPlayers->Canvas->Font->Color = textColor;

                AnsiString text = this->gridPlayers->Cells[ACol][ARow];
                this->gridPlayers->Canvas->TextRect( Rect , Rect.Left + 2 , Rect.Top + 6 ,  text );
            }

        }

    }

}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::btnMoveUpClick(TObject *Sender)
{
    this->playerMoveUp();
}
//---------------------------------------------------------------------------

void __fastcall TRosterEditorDlg::btnMoveDownClick(TObject *Sender)
{
    this->playerMoveDown();
}
//---------------------------------------------------------------------------

void __fastcall TRosterEditorDlg::btnAcceptClick(TObject *Sender)
{
    this->rostersAccept();
    this->rostersUpdate();
}
//---------------------------------------------------------------------------


void __fastcall TRosterEditorDlg::cbTeamSelMeasureItem(TWinControl *Control, int Index,
          int &Height)
{
    Height = 49;
}
//---------------------------------------------------------------------------

void __fastcall TRosterEditorDlg::cbTeamSelDrawItem(TWinControl *Control, int Index,
          TRect &Rect, TOwnerDrawState State)
{
    TComboBox* box = (TComboBox*)Control;

    if ( box )
    {
        if ( State.Contains( odFocused ) )
        {
            box->Canvas->DrawFocusRect( Rect );
        }
        box->Canvas->FillRect( Rect );

        if ( Index >= 0 && Index < IconListsDlg->ilLogos187x49->Count )
        {
			IconListsDlg->ilLogos187x49->Draw( box->Canvas , Rect.left , Rect.top , Index , true );
        }

        UnicodeString text = box->Items->Strings[ Index ];
        int textHeight = box->Canvas->TextHeight( text );

        TRect textRect = TRect( Rect );
        textRect.left += 187;
    	textRect.top += ( ( textRect.Height() - textHeight ) / 2 );
        textRect.bottom = textRect.top + textHeight;

        TTextFormat textFormat;
        textFormat << tfCenter;

        box->Canvas->TextRect( textRect , text , textFormat );

    }
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::gridPlayersColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex)
{
    if ( this->_fieldCols )
    {
        this->_fieldCols->Move( FromIndex,ToIndex );
    }
}
//---------------------------------------------------------------------------

