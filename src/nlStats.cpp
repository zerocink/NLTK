//---------------------------------------------------------------------------

#pragma hdrstop

//===========================================================================
#include <vcl.h>
#include "NLTK_common.h"
//---------------------------------------------------------------------------
#include "nlStats.h"
//---------------------------------------------------------------------------
//===========================================================================

#pragma package(smart_init)


//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================

//---------------------------------------------------------------------------
__fastcall CNLPlayerStats::CNLPlayerStats()
{
    this->zero();
    this->init();
}
//---------------------------------------------------------------------------
__fastcall CNLPlayerStats::CNLPlayerStats( const CNLPlayerStats& ps )
{
    this->zero();
    this->init();

    this->_GM	= ps._GM;
    this->_GMS	= ps._GMS;
    this->_FGM	= ps._FGM;
    this->_FGA	= ps._FGA;
    this->_TPM	= ps._TPM;
    this->_TPA	= ps._TPA;
    this->_FTM	= ps._FTM;
    this->_FTA	= ps._FTA;
    this->_ORB	= ps._ORB;
    this->_DRB	= ps._DRB;
    this->_AST	= ps._AST;
    this->_STL	= ps._STL;
    this->_BLK	= ps._BLK;
    this->_TO   = ps._TO;
    this->_FLS	= ps._FLS;
    this->_MIN	= ps._MIN;
    this->_EJT	= ps._EJT;
}
//---------------------------------------------------------------------------
__fastcall CNLPlayerStats::~CNLPlayerStats()
{
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
void __fastcall CNLPlayerStats::zero()
{
    this->_GM	=
    this->_GMS	=
    this->_FGM	=
    this->_FGA	=
    this->_TPM	=
    this->_TPA	=
    this->_FTM	=
    this->_FTA	=
    this->_ORB	=
    this->_DRB	=
    this->_AST	=
    this->_STL	=
    this->_BLK	=
    this->_TO   =
    this->_FLS	=
    this->_MIN	=
    this->_EJT	= 0;
}
//---------------------------------------------------------------------------
void __fastcall CNLPlayerStats::init()
{

}
//---------------------------------------------------------------------------
void __fastcall CNLPlayerStats::deinit()
{

}
//---------------------------------------------------------------------------
WORD __fastcall CNLPlayerStats::getRB()
{
    return this->_ORB + this->_DRB;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLPlayerStats::getPTS()
{
    return ( this->_FGM * 2 ) + this->_TPM + this->_FTM;
}
//---------------------------------------------------------------------------
SHORT __fastcall CNLPlayerStats::getEVAL()
{
    return (SHORT)( this->PTS + this->RB + this->AST + this->BLK + this->STL ) - ( (SHORT)this->_FGA - (SHORT)this->_FGM ) - ( (SHORT)this->_FTA - (SHORT)this->_FTM ) - (SHORT)this->_TO;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgFGM()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_FGM / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgFGA()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_FGA / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getPrctFG()
{
    if ( this->_FGA > 0 )
    {
        return ((double)this->_FGM / (double)this->_FGA)*100.0;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgTPM()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_TPM / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgTPA()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_TPA / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getPrctTP()
{
    if ( this->_TPA > 0 )
    {
        return ((double)this->_TPM / (double)this->_TPA)*100.0;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgFTM()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_FTM / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgFTA()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_FTA / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getPrctFT()
{
    if ( this->_FTA > 0 )
    {
        return ((double)this->_FTM / (double)this->_FTA)*100.0;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgORB()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_ORB / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgDRB()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_DRB / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgRB()
{
    if ( this->_GM > 0 )
    {
        return (double)this->RB / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgAST()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_AST / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgSTL()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_STL / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgBLK()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_BLK / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgTO()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_TO / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgFLS()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_FLS / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgMIN()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_MIN / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgEJT()
{
    if ( this->_GM > 0 )
    {
        return (double)this->_EJT / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgPTS()
{
    if ( this->_GM > 0 )
    {
        return (double)this->PTS / (double)this->_GM;
    }

    return 0.0;
}
//---------------------------------------------------------------------------
double __fastcall CNLPlayerStats::getAvgEVAL()
{
    if ( this->_GM > 0 )
    {
        return (double)this->EVAL / (double)this->_GM;
    }

    return 0.0;
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
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
