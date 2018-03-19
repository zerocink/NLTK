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
    this->_rosters = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::init()
{
    if ( !this->_rosters ) this->_rosters = new TList();
}
//---------------------------------------------------------------------------
void __fastcall TRosterEditorDlg::deinit()
{
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
    // visage de la grille :
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
    this->gridPlayers->ColCount = 12;

    // titres des colonnes :
    //----------------------
    this->gridPlayers->Cells[0][0] = AnsiString( "RP" );    // roster position
    this->gridPlayers->Cells[1][0] = AnsiString( "Nom" );
    this->gridPlayers->Cells[2][0] = AnsiString( "Taille" );
    this->gridPlayers->Cells[3][0] = AnsiString( "Poids" );
    this->gridPlayers->Cells[4][0] = AnsiString( "Pos" );
    this->gridPlayers->Cells[5][0] = AnsiString( "Ovrl" );
    this->gridPlayers->Cells[6][0] = AnsiString( "Exp" );
    this->gridPlayers->Cells[7][0] = AnsiString( "Pts" );
    this->gridPlayers->Cells[8][0] = AnsiString( "Rb" );
    this->gridPlayers->Cells[9][0] = AnsiString( "Ast" );
    this->gridPlayers->Cells[10][0] = AnsiString( "Blk" );
    this->gridPlayers->Cells[11][0] = AnsiString( "Stl" );

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

        this->gridPlayers->Objects[0][row] = (TObject*)p;
        this->gridPlayers->Cells[0][row] = p->RosterPosText;
        this->gridPlayers->Cells[1][row] = txt.sprintf( "%s %s %s" , p->Number , p->FName , p->Name );
        this->gridPlayers->Cells[2][row] = txt.sprintf( "%01.02f m" , (double)p->Height/100.0 );
        this->gridPlayers->Cells[3][row] = txt.sprintf( "%d kg" , p->Weight );
        this->gridPlayers->Cells[4][row] = txt.sprintf( "%s / %s " , p->Position1 , p->Position2 );
        this->gridPlayers->Cells[5][row] = txt.sprintf( "%2.01f" , p->OverallRtg );
        this->gridPlayers->Cells[6][row] = txt.sprintf( "%d" , p->YearsExp );

        WORD g = p->SeasonGM;
        if ( g > 0 )
        {
            double pts = ( ( (double)p->SeasonFGM * 2.0 ) + (double)p->Season3PM + (double)p->SeasonFTM ) / (double)g;
            double reb = ( (double)p->SeasonORB + (double)p->SeasonDRB ) / (double)g;
            double ast = ( (double)p->SeasonAST ) / (double)g;
            double blk = ( (double)p->SeasonBLK ) / (double)g;
            double stl = ( (double)p->SeasonSTL ) / (double)g;

            this->gridPlayers->Cells[7][row] = txt.sprintf( "%2.01f" , pts );
            this->gridPlayers->Cells[8][row] = txt.sprintf( "%2.01f" , reb );
            this->gridPlayers->Cells[9][row] = txt.sprintf( "%2.01f" , ast );
            this->gridPlayers->Cells[10][row] = txt.sprintf( "%2.01f" , blk );
            this->gridPlayers->Cells[11][row] = txt.sprintf( "%2.01f" , stl );
        }
        else
        {
            this->gridPlayers->Cells[7][row] = TXT_NULL;
            this->gridPlayers->Cells[8][row] = TXT_NULL;
            this->gridPlayers->Cells[9][row] = TXT_NULL;
            this->gridPlayers->Cells[10][row] = TXT_NULL;
            this->gridPlayers->Cells[11][row] = TXT_NULL;
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

