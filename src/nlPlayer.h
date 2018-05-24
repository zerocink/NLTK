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
// CONSTANTES : liste des positions
//---------------------------------------------------------------------------
#define POS_PG           4
#define POS_SG           3
#define POS_SF           2
#define POS_PF           1
#define POS_C            0
#define POS_NONE	  	-1
#define POS_UNDEF       -2
//---------------------------------------------------------------------------
#define POS_PG_TXT          AnsiString( "PG" )
#define POS_SG_TXT          AnsiString( "SG" )
#define POS_SF_TXT          AnsiString( "SF" )
#define POS_PF_TXT          AnsiString( "PF" )
#define POS_C_TXT           AnsiString( "C"  )
#define POS_NONE_TXT        AnsiString( "-"  )
//===========================================================================

//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
class CNLPlayerStats;
class CNLPlayer;
//===========================================================================


//===========================================================================
class CNLPlayerStats
{
    friend class CNLPlayer;

    public	:

        // constructeurs & destructeur :
        //------------------------------
        		__fastcall CNLPlayerStats();
                __fastcall CNLPlayerStats( const CNLPlayerStats& ps );
        virtual __fastcall ~CNLPlayerStats();

        // propriétés publiques :
        //-----------------------
        __property WORD       GM	  = { read = _GM	};
        __property WORD       GMS	  = { read = _GMS	};
        __property WORD       FGM     = { read = _FGM	};
        __property WORD       FGA     = { read = _FGA	};
        __property WORD       TPM     = { read = _TPM	};
        __property WORD       TPA     = { read = _TPA	};
        __property WORD       FTM     = { read = _FTM	};
        __property WORD       FTA     = { read = _FTA	};
        __property WORD       ORB     = { read = _ORB	};
        __property WORD       DRB     = { read = _DRB	};
        __property WORD       RB      = { read = getRB  };
        __property WORD       AST     = { read = _AST	};
        __property WORD       STL     = { read = _STL	};
        __property WORD       BLK     = { read = _BLK	};
        __property WORD       TO      = { read = _TO	};
        __property WORD       FLS     = { read = _FLS	};
        __property WORD       MIN     = { read = _MIN	};
        __property WORD       EJT     = { read = _EJT  	};
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
        void __fastcall loadSeasonStats( CNLPlayerStats& ps );
        void __fastcall loadPlayoffsStats( CNLPlayerStats& ps );

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
        __property AnsiString Position2 	= { read = getPosition2 	, write = setPosition2 };
        __property WORD       Team          = { read = getTeam          };
        __property WORD       RosterPos	 	= { read = getRosterPos	 	, write = setRosterPos };
        __property AnsiString RosterPosText = { read = getRosterPosText };
        __property bool       InSeason      = { read = getInSeason      };
        __property double     OverallRtg    = { read = getOverallRtg    };
        __property WORD       YearsExp      = { read = getYearsExp      };
        __property WORD       InjuryId      = { read = getInjuryId      };
        __property bool       IsPlayable    = { read = getIsPlayable	};

        __property WORD       weeklyMvp     = { read = getWeeklyMvp 		};
        __property WORD       monthlyMvp    = { read = getMonthlyMvp 		};
        __property WORD       allStarMvp    = { read = getAllStarMvp 		};

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

        __property WORD       skillLuciditeOffensive	= { read = getSkillLuciditeOffensive	};
        __property WORD       skillLuciditeDefensive    = { read = getSkillLuciditeDefensive    };
        __property WORD       skillDribble		        = { read = getSkillDribble           	};
        __property WORD       skillPasse			    = { read = getSkillPasse        		};
        __property WORD       skillAdresse		        = { read = getSkillAdresse          	};
        __property WORD       skill2Pts			        = { read = getSkill2Pts           		};
        __property WORD       skill3Pts				    = { read = getSkill3Pts       			};
        __property WORD       skillLf			        = { read = getSkillLf           		};
        __property WORD       skillRebondOffensif	    = { read = getSkillRebondOffensif      	};
        __property WORD       skillRebondDefensif       = { read = getSkillRebondDefensif		};
        __property WORD       skillInterception         = { read = getSkillInterception 		};
        __property WORD       skillContre               = { read = getSkillContre           	};
        __property WORD       skillAgilite              = { read = getSkillAgilite          	};
        __property WORD       skillEndurance            = { read = getSkillEndurance        	};
        __property WORD       skillDetente              = { read = getSkillDetente          	};
        __property WORD       skillPuissance            = { read = getSkillPuissance			};
        __property WORD       skillVitesse              = { read = getSkillVitesse          	};

        __property WORD       skillDistanceTir          = { read = getSkillDistanceTir          };

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
        void        __fastcall setPosition2( AnsiString position2 );
        WORD        __fastcall getTeam();
        WORD        __fastcall getRosterPos();
        void        __fastcall setRosterPos( WORD rosterPos );
        AnsiString  __fastcall getRosterPosText();
        bool        __fastcall getInSeason();
        double      __fastcall getOverallRtg();
        WORD        __fastcall getYearsExp();
        WORD        __fastcall getInjuryId();
        bool        __fastcall getIsPlayable();

        WORD        __fastcall getWeeklyMvp();
        WORD        __fastcall getMonthlyMvp();
        WORD        __fastcall getAllStarMvp();

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
        SHORT      __fastcall getSeasonEval();

        WORD       __fastcall getDraftPlace();
        WORD       __fastcall getDraftRound();
        WORD       __fastcall getDraftOverall();
        WORD       __fastcall getDraftYear();
        AnsiString __fastcall getDraftTeam();

        WORD       __fastcall getSkillLuciditeOffensive();
        WORD       __fastcall getSkillLuciditeDefensive();
        WORD       __fastcall getSkillDribble();
        WORD       __fastcall getSkillPasse();
        WORD       __fastcall getSkillAdresse();
        WORD       __fastcall getSkill2Pts();
        WORD       __fastcall getSkill3Pts();
        WORD       __fastcall getSkillLf();
        WORD       __fastcall getSkillRebondOffensif();
        WORD       __fastcall getSkillRebondDefensif();
        WORD       __fastcall getSkillInterception();
        WORD       __fastcall getSkillContre();
        WORD       __fastcall getSkillAgilite();
        WORD       __fastcall getSkillEndurance();
        WORD       __fastcall getSkillDetente();
        WORD       __fastcall getSkillPuissance();
        WORD       __fastcall getSkillVitesse();

        WORD       __fastcall getSkillDistanceTir();


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
