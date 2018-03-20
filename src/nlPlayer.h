//---------------------------------------------------------------------------

#ifndef nlPlayerH
#define nlPlayerH

//===========================================================================
// fichiers en-tête utilisés
//---------------------------------------------------------------------------
#include "dbEngine.h"
//===========================================================================


//===========================================================================
// CONSTANTES : liste des id blessures
//---------------------------------------------------------------------------
#define INJURYID_UNDEF          ((WORD)-1)
//===========================================================================

//===========================================================================
// CONSTANTES : drafs
//---------------------------------------------------------------------------
#define DRAFT_PLACE_UNDEF           (WORD(0))
#define DRAFT_ROUND_UNDEF           (WORD(0))
#define DRAFT_OVERALL_UNDEF         (WORD(0))
#define DRAFT_YEAR_UNDEF            (WORD(0))
#define DRAFT_TEAM_UNDEF            TXT_NULL
//===========================================================================

//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
class CNLPlayer;
//===========================================================================


//===========================================================================
class CNLPlayer
{
    public	:

    	// constructeurs & destructeur :
        //------------------------------
		        __fastcall CNLPlayer();
                __fastcall CNLPlayer( CDBTable* t );
        virtual __fastcall ~CNLPlayer();

        // méthodes publiques :
        //---------------------
        bool __fastcall loadFromTable( CDBTable* t );
        void __fastcall loadDifs( TStrings* difs );
        bool __fastcall saveToTable( CDBTable* f );

        // propriétés publiques :
        //-----------------------
        __property bool       dif           = { read = getDif			};
        __property int        recordIndex	= { read = getRecordIndex	};
        __property WORD 	  ID			= { read = getID    		};
        __property AnsiString Name 			= { read = getName 			};
        __property AnsiString FName 		= { read = getFName			};
        __property AnsiString Number		= { read = getNumber    	};
        __property WORD	      Weight 		= { read = getWeight		};
        __property WORD 	  Height    	= { read = getHeight		};
        __property AnsiString Position1 	= { read = getPosition1 	};
        __property AnsiString Position2 	= { read = getPosition2 	};
        __property WORD       Team          = { read = getTeam          };
        __property WORD       RosterPos	 	= { read = getRosterPos	 	, write = setRosterPos };
        __property AnsiString RosterPosText = { read = getRosterPosText };
        __property bool       InSeason      = { read = getInSeason      };
        __property double     OverallRtg    = { read = getOverallRtg    };
        __property WORD       YearsExp      = { read = getYearsExp      };
        __property WORD       InjuryId      = { read = getInjuryId      };
        __property bool       IsPlayable    = { read = getIsPlayable	};

        __property WORD       SeasonGM		= { read = getSeasonGM   	 	};
        __property WORD       SeasonGMS		= { read = getSeasonGMS		    };
        __property WORD       SeasonFGM     = { read = getSeasonFGM         };
        __property WORD       SeasonFGA     = { read = getSeasonFGA         };
        __property WORD       Season3PM     = { read = getSeason3PM         };
        __property WORD       Season3PA     = { read = getSeason3PA         };
        __property WORD       SeasonFTM     = { read = getSeasonFTM         };
        __property WORD       SeasonFTA     = { read = getSeasonFTA         };
        __property WORD       SeasonORB     = { read = getSeasonORB         };
        __property WORD       SeasonDRB     = { read = getSeasonDRB         };
        __property WORD       SeasonAST     = { read = getSeasonAST    	 	};
        __property WORD       SeasonSTL     = { read = getSeasonSTL         };
        __property WORD       SeasonBLK     = { read = getSeasonBLK			};
        __property WORD       SeasonTO      = { read = getSeasonTO          };
        __property WORD       SeasonFLS     = { read = getSeasonFLS         };
        __property WORD       SeasonMIN     = { read = getSeasonMIN     	};
        __property WORD       SeasonEJT     = { read = getSeasonEJT         };

        __property WORD       DraftPlace    = { read = getDraftPlace        };
        __property WORD       DraftRound    = { read = getDraftRound        };
        __property WORD       DraftOverall  = { read = getDraftOverall      };
        __property WORD       DraftYear     = { read = getDraftYear         };
        __property AnsiString DraftTeam     = { read = getDraftTeam         };


    private :

    	// méthodes internes :
        //--------------------
        void __fastcall zero();
        void __fastcall init();
        void __fastcall deinit();

        // méthodes internes statiques :
        //------------------------------
        static void __fastcall createFieldNames();
        static void __fastcall deleteFieldNames();

        // méthodes get / set des propriétés :
        //------------------------------------
        bool        __fastcall getDif();
        int         __fastcall getRecordIndex();
        WORD 		__fastcall getID();
        AnsiString 	__fastcall getName();
        AnsiString  __fastcall getFName();
        AnsiString  __fastcall getNumber();
        WORD        __fastcall getWeight();
        WORD        __fastcall getHeight();
        AnsiString  __fastcall getPosition1();
        AnsiString  __fastcall getPosition2();
        WORD        __fastcall getTeam();
        WORD        __fastcall getRosterPos();
        void        __fastcall setRosterPos( WORD rosterPos );
        AnsiString  __fastcall getRosterPosText();
        bool        __fastcall getInSeason();
        double      __fastcall getOverallRtg();
        WORD        __fastcall getYearsExp();
        WORD        __fastcall getInjuryId();
        bool        __fastcall getIsPlayable();

        WORD       __fastcall getSeasonGM();
        WORD       __fastcall getSeasonGMS();
        WORD       __fastcall getSeasonFGM();
        WORD       __fastcall getSeasonFGA();
        WORD       __fastcall getSeason3PM();
        WORD       __fastcall getSeason3PA();
        WORD       __fastcall getSeasonFTM();
        WORD       __fastcall getSeasonFTA();
        WORD       __fastcall getSeasonORB();
        WORD       __fastcall getSeasonDRB();
        WORD       __fastcall getSeasonAST();
        WORD       __fastcall getSeasonSTL();
        WORD       __fastcall getSeasonBLK();
        WORD       __fastcall getSeasonTO();
        WORD       __fastcall getSeasonFLS();
        WORD       __fastcall getSeasonMIN();
        WORD       __fastcall getSeasonEJT();

        WORD       __fastcall getDraftPlace();
        WORD       __fastcall getDraftRound();
        WORD       __fastcall getDraftOverall();
        WORD       __fastcall getDraftYear();
        AnsiString __fastcall getDraftTeam();

        // variables internes :
        //---------------------
        CDBRecord* _record;

        // variables internes statiques :
        //-------------------------------
        static DWORD 		_instanceCount;
        static TStrings*    _fieldNames;
};
//===========================================================================
#endif
