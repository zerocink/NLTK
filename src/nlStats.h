//---------------------------------------------------------------------------

#ifndef nlStatsH
#define nlStatsH

//===========================================================================
// fichiers en-tête utilisés
//---------------------------------------------------------------------------
//===========================================================================


//===========================================================================
// CONSTANTES :
//---------------------------------------------------------------------------
//===========================================================================

//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
//===========================================================================


//===========================================================================
class CNLPlayerStats
{
	public	:

        // constructeurs & destructeur :
        //------------------------------
        		__fastcall CNLPlayerStats();
                __fastcall CNLPlayerStats( const CNLPlayerStats& ps );
        virtual __fastcall ~CNLPlayerStats();

        // propriétés publiques :
		//-----------------------
		__property WORD       GM	  = { read = _GM	, write = _GM	};
		__property WORD       GMS	  = { read = _GMS	, write = _GMS	};
		__property WORD       FGM     = { read = _FGM	, write = _FGM	};
		__property WORD       FGA     = { read = _FGA	, write = _FGA	};
		__property WORD       TPM     = { read = _TPM	, write = _TPM	};
		__property WORD       TPA     = { read = _TPA	, write = _TPA	};
		__property WORD       FTM     = { read = _FTM	, write = _FTM	};
		__property WORD       FTA     = { read = _FTA	, write = _FTA	};
		__property WORD       ORB     = { read = _ORB	, write = _ORB	};
		__property WORD       DRB     = { read = _DRB	, write = _DRB	};
		__property WORD       RB      = { read = getRB  };
		__property WORD       AST     = { read = _AST	, write = _AST	};
		__property WORD       STL     = { read = _STL	, write = _STL	};
		__property WORD       BLK     = { read = _BLK	, write = _BLK	};
		__property WORD       TO      = { read = _TO	, write = _TO	};
		__property WORD       FLS     = { read = _FLS	, write = _FLS	};
		__property WORD       MIN     = { read = _MIN	, write = _MIN	};
		__property WORD       EJT     = { read = _EJT  	, write = _EJT	};
        __property WORD       PTS     = { read = getPTS  };
        __property SHORT      EVAL    = { read = getEVAL };

        __property double 	  avgFGM  = { read = getAvgFGM  };
        __property double     avgFGA  = { read = getAvgFGA  };
        __property double     prctFG  = { read = getPrctFG  };
        __property double     avgTPM  = { read = getAvgTPM  };
        __property double     avgTPA  = { read = getAvgTPA  };
        __property double     prctTP  = { read = getPrctTP  };
        __property double     avgFTM  = { read = getAvgFTM  };
        __property double     avgFTA  = { read = getAvgFTA  };
        __property double     prctFT  = { read = getPrctFT  };
        __property double     avgORB  = { read = getAvgORB  };
        __property double     avgDRB  = { read = getAvgDRB  };
        __property double     avgRB   = { read = getAvgRB   };
        __property double     avgAST  = { read = getAvgAST  };
        __property double     avgSTL  = { read = getAvgSTL  };
        __property double     avgBLK  = { read = getAvgBLK  };
        __property double     avgTO   = { read = getAvgTO   };
        __property double     avgFLS  = { read = getAvgFLS  };
        __property double     avgMIN  = { read = getAvgMIN  };
        __property double     avgEJT  = { read = getAvgEJT  };
        __property double     avgPTS  = { read = getAvgPTS  };
        __property double     avgEVAL = { read = getAvgEVAL };


    private	:

        // méthodes internes :
        //--------------------
        void __fastcall zero();
        void __fastcall init();
        void __fastcall deinit();

        // variables internes :
        //---------------------
        WORD _GM;
        WORD _GMS;
        WORD _FGM;
        WORD _FGA;
        WORD _TPM;
        WORD _TPA;
        WORD _FTM;
        WORD _FTA;
        WORD _ORB;
        WORD _DRB;
        WORD _AST;
        WORD _STL;
        WORD _BLK;
        WORD _TO;
        WORD _FLS;
        WORD _MIN;
        WORD _EJT;

        // méthodes get / set des propriétés :
        //------------------------------------
        WORD       __fastcall getRB();
        WORD       __fastcall getPTS();
        SHORT      __fastcall getEVAL();
        double 	   __fastcall getAvgFGM();
        double     __fastcall getAvgFGA();
        double     __fastcall getPrctFG();
        double     __fastcall getAvgTPM();
        double     __fastcall getAvgTPA();
        double     __fastcall getPrctTP();
        double     __fastcall getAvgFTM();
        double     __fastcall getAvgFTA();
        double     __fastcall getPrctFT();
        double     __fastcall getAvgORB();
        double     __fastcall getAvgDRB();
        double     __fastcall getAvgRB();
        double     __fastcall getAvgAST();
        double     __fastcall getAvgSTL();
        double     __fastcall getAvgBLK();
        double     __fastcall getAvgTO();
        double     __fastcall getAvgFLS();
        double     __fastcall getAvgMIN();
        double     __fastcall getAvgEJT();
        double     __fastcall getAvgPTS();
        double     __fastcall getAvgEVAL();

};
//===========================================================================

#endif
