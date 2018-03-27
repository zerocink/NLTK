//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//===========================================================================
//---------------------------------------------------------------------------
#include "wDraftReview.h"
#include "NLTK_common.h"
//---------------------------------------------------------------------------
//===========================================================================


//===========================================================================
// CONSTANTES :
//---------------------------------------------------------------------------
#define TITRE_ROUND AnsiString( "Round" )
#define TITRE_PLACE AnsiString( "Place" )
#define TITRE_BY    AnsiString( "By" )
#define TITRE_TEAM  AnsiString( "Team" )
#define TITRE_NOM   AnsiString( "Nom" )
#define TITRE_POS   AnsiString( "Pos" )
#define TITRE_OVRL  AnsiString( "Ovrl" )
#define TITRE_PTS   AnsiString( "Pts" )
#define TITRE_RB    AnsiString( "Rb" )
#define TITRE_AST   AnsiString( "Ast" )
#define TITRE_BLK   AnsiString( "Blk" )
#define TITRE_STL   AnsiString( "Stl" )
#define TITRE_EVAL  AnsiString( "Eval" )
//---------------------------------------------------------------------------
#define ROUND       (this->_fieldCols->IndexOf(TITRE_ROUND))
#define PLACE       (this->_fieldCols->IndexOf(TITRE_PLACE))
#define BY       	(this->_fieldCols->IndexOf(TITRE_BY))
#define TEAM       	(this->_fieldCols->IndexOf(TITRE_TEAM))
#define NOM       	(this->_fieldCols->IndexOf(TITRE_NOM))
#define POS       	(this->_fieldCols->IndexOf(TITRE_POS))
#define OVRL       	(this->_fieldCols->IndexOf(TITRE_OVRL))
#define PTS       	(this->_fieldCols->IndexOf(TITRE_PTS))
#define RB       	(this->_fieldCols->IndexOf(TITRE_RB))
#define AST       	(this->_fieldCols->IndexOf(TITRE_AST))
#define BLK       	(this->_fieldCols->IndexOf(TITRE_BLK))
#define STL       	(this->_fieldCols->IndexOf(TITRE_STL))
#define EVAL       	(this->_fieldCols->IndexOf(TITRE_EVAL))
//===========================================================================

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDraftReviewDlg *DraftReviewDlg;
//===========================================================================
//---------------------------------------------------------------------------
__fastcall TDraftReviewDlg::TDraftReviewDlg(TComponent* Owner)
	: TForm(Owner)
{
    this->zero();
    this->init();
}
//---------------------------------------------------------------------------
__fastcall TDraftReviewDlg::~TDraftReviewDlg()
{
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::zero()
{
    this->_sg 		= NULL;
    this->_drafts 	= NULL;
    this->_fieldCols = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::init()
{
    if ( !this->_drafts ) this->_drafts = new TList();

    if ( !this->_fieldCols )
    {
        this->_fieldCols = new TStringList();

        this->_fieldCols->Add( TITRE_ROUND );
        this->_fieldCols->Add( TITRE_PLACE );
        this->_fieldCols->Add( TITRE_BY );
        this->_fieldCols->Add( TITRE_TEAM );
        this->_fieldCols->Add( TITRE_NOM );
        this->_fieldCols->Add( TITRE_POS );
        this->_fieldCols->Add( TITRE_OVRL );
        this->_fieldCols->Add( TITRE_PTS );
        this->_fieldCols->Add( TITRE_RB );
        this->_fieldCols->Add( TITRE_AST );
        this->_fieldCols->Add( TITRE_BLK );
        this->_fieldCols->Add( TITRE_STL );
        this->_fieldCols->Add( TITRE_EVAL );
    }
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::deinit()
{
    if ( this->_fieldCols )
    {
        this->_fieldCols->Clear();

        delete this->_fieldCols;
        this->_fieldCols = NULL;
    }

    if ( this->_drafts )
    {
        this->clearDrafts();

        delete this->_drafts;
        this->_drafts = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::formInit()
{
    this->Caption = Application->Title;
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::setSg( CNLSavedGame* sg )
{
    this->_sg = sg;
    this->clearDrafts();

    if ( sg && this->_drafts )
    {
    	// affectation des joueurs dans les drafts :
        //------------------------------------------
        for ( int i = 0 ; i < sg->playerCount ; i++ )
        {
            CNLPlayer* p = sg->playerByIndex[ i ];
            if ( p )
            {
                WORD y = p->DraftYear;
                if ( y != DRAFT_YEAR_UNDEF )
                {
                    CNLDraft* d = this->draftByYear[ y ];
                    if ( !d )
                    {
                        d = new CNLDraft;
                        ZeroMemory( d , sizeof(CNLDraft) );
                        d->year = y;

                        this->_drafts->Add( d );
                    }

                    WORD round = p->DraftRound;
                    WORD place = p->DraftPlace;
                    if ( round > 0 && round <= DRAFT_ROUND_COUNT && place > 0 && place <= DRAFT_PLACE_COUNT )
                    {
	                    d->players[ round-1 ][ place-1 ] = p;
                    }
                }
            }
        }

        // tri des drafts dans l'ordre décroissant d'années :
        //---------------------------------------------------
        for ( int i = 0 ; i < this->draftCount-1 ; i++ )
        {
            CNLDraft* d1 = this->draftByIndex[ i ];
            CNLDraft* d2 = this->draftByIndex[ i + 1 ];

            if ( d1 && d2 && d1->year < d2->year )
            {
                this->_drafts->Exchange( i , i+1 );

                for ( int j = i ; j > 0 ; j-- )
                {
                    CNLDraft* d3 = this->draftByIndex[ j ];
                    CNLDraft* d4 = this->draftByIndex[ j-1 ];

                    if ( d3 && d4 && d3->year > d4->year )
                    {
                        this->_drafts->Exchange( j , j-1 );
                    }
                }
            }
        }
    }

    // mise a jour affichage :
    //------------------------
    this->updateDrafts();
}
//---------------------------------------------------------------------------
CNLDraft* __fastcall TDraftReviewDlg::getDraftByYear( WORD year )
{
    for ( int i = 0 ; i < this->draftCount ; i++ )
    {
        CNLDraft* d = this->draftByIndex[ i ];
        if ( d && d->year == year ) return d;
    }

    return NULL;
}
//---------------------------------------------------------------------------
CNLDraft* __fastcall TDraftReviewDlg::getDraftByIndex( int index )
{
    if ( this->_drafts && index >= 0 && index < this->_drafts->Count )
    {
        return (CNLDraft*)this->_drafts->Items[ index ];
    }

    return NULL;
}
//---------------------------------------------------------------------------
int __fastcall TDraftReviewDlg::getDraftCount()
{
    if ( this->_drafts )
    {
        return this->_drafts->Count;
    }

    return 0;
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::clearDrafts()
{
    if ( this->_drafts )
    {
        while ( this->_drafts->Count )
        {
            CNLDraft* d = (CNLDraft*)this->_drafts->Items[ 0 ];
            if ( d )
            {
                ZeroMemory( d , sizeof( CNLDraft ) );
                delete d;
                d = NULL;
            }
            this->_drafts->Delete( 0 );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::updateDrafts()
{
    this->cbDraftSel->Items->Clear();

	for ( int i = 0 ; i < this->draftCount ; i++ )
    {
        CNLDraft* d = this->draftByIndex[ i ];
        if ( d )
        {
            this->cbDraftSel->Items->AddObject( IntToStr( d->year ) , (TObject*)d );
        }
    }

    if ( this->cbDraftSel->Items->Count > 0 )
    {
        this->cbDraftSel->ItemIndex = 0;
    }
    else
    {
        this->cbDraftSel->ItemIndex = -1;
    }

    this->updatePlayers();

}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::updatePlayers()
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
    this->gridPlayers->RowCount = DRAFT_PLACE_COUNT * DRAFT_ROUND_COUNT + 1;
    this->gridPlayers->ColCount = this->_fieldCols->Count;

    // titre des colonnes :
    //---------------------
    for ( int i = 0 ; i < this->_fieldCols->Count ; i++ )
    {
        this->gridPlayers->Cells[ i ][ 0 ] = this->_fieldCols->Strings[ i ];
    }

    // récup draft sélectionnée dans la liste déroulante :
    //----------------------------------------------------
    CNLDraft* d = (CNLDraft*)this->cbDraftSel->Items->Objects[ this->cbDraftSel->ItemIndex ];
    if ( d )
    {
        for ( int i = 0 ; i < DRAFT_ROUND_COUNT ; i++ )
        {
            for ( int j = 0 ; j < DRAFT_PLACE_COUNT ; j++ )
            {
                int row = 1 + ( i*DRAFT_PLACE_COUNT + j );

	            CNLPlayer* p = d->players[ i ][ j ];
    	        this->playerDisplay( p , row );
            }
        }
    }

    // auto size des colonnes de la grille :
    //--------------------------------------
    this->autoSizeCol( -1 );
    this->autoSizeRow( -1 );
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::playerDisplay( CNLPlayer* p , int row )
{
    if ( p && row >= 1 && row < this->gridPlayers->RowCount )
    {
        AnsiString txt;

        CNLPlayerStats ps;
        p->loadSeasonStats( ps );

        // recherche équipe actuel du joueur :
        //------------------------------------
        CNLTeam* t = NULL;
        AnsiString team = TXT_NULL;
        if ( this->sg )
        {
            t = this->sg->teamByNum[ p->Team ];
            if ( t ) team = t->Abrev.UpperCase();
        }

        this->gridPlayers->Objects[0][row] = (TObject*)p;
        this->gridPlayers->Cells[ROUND][row] = txt.sprintf( "%d" , p->DraftRound );
        this->gridPlayers->Cells[PLACE][row] = txt.sprintf( "%d" , p->DraftPlace );
        this->gridPlayers->Cells[BY][row] = p->DraftTeam.UpperCase();
        this->gridPlayers->Cells[TEAM][row] = team;
        this->gridPlayers->Cells[NOM][row] = txt.sprintf( "%s %s" , p->FName , p->Name );
        this->gridPlayers->Cells[POS][row] = txt.sprintf( "%s / %s " , p->Position1 , p->Position2 );
        this->gridPlayers->Cells[OVRL][row] = txt.sprintf( "%2.01f" , p->OverallRtg );

        if ( ps.GM > 0 )
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
void __fastcall TDraftReviewDlg::autoSizeCol( int col )
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
void __fastcall TDraftReviewDlg::autoSizeRow( int row )
{

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
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
void __fastcall TDraftReviewDlg::cbDraftSelChange(TObject *Sender)
{
    this->updatePlayers();
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::gridPlayersColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex)
{
    if ( this->_fieldCols )
    {
        this->_fieldCols->Move( FromIndex , ToIndex );
    }
}
//---------------------------------------------------------------------------

void __fastcall TDraftReviewDlg::FormCreate(TObject *Sender)
{
    this->formInit();
}
//---------------------------------------------------------------------------

void __fastcall TDraftReviewDlg::FormDestroy(TObject *Sender)
{
    this->formDeinit();
}
//---------------------------------------------------------------------------

