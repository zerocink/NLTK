//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//===========================================================================
//---------------------------------------------------------------------------
#include "wDraftReview.h"
#include "NLTK_common.h"
//---------------------------------------------------------------------------
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
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::init()
{
    if ( !this->_drafts ) this->_drafts = new TList();
}
//---------------------------------------------------------------------------
void __fastcall TDraftReviewDlg::deinit()
{
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
    this->gridPlayers->ColCount = 13;

    // titre des colonnes :
    //---------------------
    this->gridPlayers->Cells[ 0 ][ 0 ] = AnsiString( "Round" );
    this->gridPlayers->Cells[ 1 ][ 0 ] = AnsiString( "Place" );
    this->gridPlayers->Cells[ 2 ][ 0 ] = AnsiString( "By" );
    this->gridPlayers->Cells[ 3 ][ 0 ] = AnsiString( "Team" );
    this->gridPlayers->Cells[ 4 ][ 0 ] = AnsiString( "Nom" );
    this->gridPlayers->Cells[ 5 ][ 0 ] = AnsiString( "Pos" );
    this->gridPlayers->Cells[ 6 ][ 0 ] = AnsiString( "Ovrl" );
    this->gridPlayers->Cells[ 7 ][ 0 ] = AnsiString( "Pts" );
    this->gridPlayers->Cells[ 8 ][ 0 ] = AnsiString( "Rb" );
    this->gridPlayers->Cells[ 9 ][ 0 ] = AnsiString( "Ast" );
    this->gridPlayers->Cells[ 10 ][ 0 ] = AnsiString( "Blk" );
    this->gridPlayers->Cells[ 11 ][ 0 ] = AnsiString( "Stl" );
    this->gridPlayers->Cells[ 12 ][ 0 ] = AnsiString( "Eval" );

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
        this->gridPlayers->Cells[0][row] = txt.sprintf( "%d" , p->DraftRound );
        this->gridPlayers->Cells[1][row] = txt.sprintf( "%d" , p->DraftPlace );
        this->gridPlayers->Cells[2][row] = p->DraftTeam.UpperCase();
        this->gridPlayers->Cells[3][row] = team;
        this->gridPlayers->Cells[4][row] = txt.sprintf( "%s %s" , p->FName , p->Name );
        this->gridPlayers->Cells[5][row] = txt.sprintf( "%s / %s " , p->Position1 , p->Position2 );
        this->gridPlayers->Cells[6][row] = txt.sprintf( "%2.01f" , p->OverallRtg );

        if ( ps.GM > 0 )
        {

            this->gridPlayers->Cells[7][row] = txt.sprintf( "%2.01f" , ps.avgPTS );
            this->gridPlayers->Cells[8][row] = txt.sprintf( "%2.01f" , ps.avgRB );
            this->gridPlayers->Cells[9][row] = txt.sprintf( "%2.01f" , ps.avgAST );
            this->gridPlayers->Cells[10][row] = txt.sprintf( "%2.01f" , ps.avgBLK );
            this->gridPlayers->Cells[11][row] = txt.sprintf( "%2.01f" , ps.avgSTL );
            this->gridPlayers->Cells[12][row] = txt.sprintf( "%2.01f" , ps.avgEVAL );
        }
        else
        {
            this->gridPlayers->Cells[7][row] = TXT_NULL;
            this->gridPlayers->Cells[8][row] = TXT_NULL;
            this->gridPlayers->Cells[9][row] = TXT_NULL;
            this->gridPlayers->Cells[10][row] = TXT_NULL;
            this->gridPlayers->Cells[11][row] = TXT_NULL;
            this->gridPlayers->Cells[12][row] = TXT_NULL;
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
