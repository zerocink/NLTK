//---------------------------------------------------------------------------

#pragma hdrstop

//===========================================================================
// fihiers en-têtes :
//---------------------------------------------------------------------------
#include "NLTK_Common.h"
//---------------------------------------------------------------------------
#include "dbEngine.h"
//---------------------------------------------------------------------------
//===========================================================================


#pragma package(smart_init)


//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
// CLASSE CDBField
//---------------------------------------------------------------------------
__fastcall CDBField::CDBField( AnsiString name )
{
	this->zero();
	this->init();

	this->_name = name;
}
//---------------------------------------------------------------------------
__fastcall CDBField::~CDBField()
{
	this->deinit();
	this->zero();
}
//---------------------------------------------------------------------------
void __fastcall CDBField::zero()
{
	this->_name = TXT_NULL;
	this->_rom  = TXT_NULL;
	this->_ram 	= TXT_NULL;
}
//---------------------------------------------------------------------------
void __fastcall CDBField::init()
{

}
//---------------------------------------------------------------------------
void __fastcall CDBField::deinit()
{

}
//---------------------------------------------------------------------------
bool __fastcall CDBField::readFromTable( CDBTable* t )
{
	bool ok = false;

	if ( t && t->isOpen )
	{
		AnsiString rom;
		ok = t->getFieldValueString( this->_name.Trim() , rom );
		if ( ok )
		{
			this->_rom = rom;
			this->_ram = rom;
		}

	}


	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBField::writeToTable( CDBTable* t )
{
	bool ok = true;

	if ( t && t->isOpen )
	{
		/*TField* dsField = ds->FieldByName( this->_name.Trim() );
		if ( dsField )
		{
			dsField->AsString = this->_ram;
			this->_rom = this->_ram;
		}
		else
		{
			ok = false;
		}*/
	}
	else
	{
		ok = false;
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBField::getDif()
{
	return this->_rom.Trim() != this->_ram.Trim();
}
//---------------------------------------------------------------------------
// CLASSE CDBField
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
// CLASSE CDBRecord
//---------------------------------------------------------------------------
__fastcall CDBRecord::CDBRecord( )
{
	this->zero();
	this->init();
}
//---------------------------------------------------------------------------
__fastcall CDBRecord::~CDBRecord()
{
	this->deleteAllFields();
	this->deinit();
	this->zero();
}
//---------------------------------------------------------------------------
void __fastcall CDBRecord::zero()
{
	this->_fields = NULL;
}
//---------------------------------------------------------------------------
void __fastcall CDBRecord::init()
{
	this->_fields = new TList();
}
//---------------------------------------------------------------------------
void __fastcall CDBRecord::deinit()
{
	if ( this->_fields ) delete this->_fields;
	this->_fields = NULL;
}
//---------------------------------------------------------------------------
bool __fastcall CDBRecord::createFields( TStrings* names )
{
	bool ok = true;

	if ( names )
	{
		ok = this->deleteAllFields();

		if ( ok )
		{
			for ( int i = 0 ; i < names->Count ; i++ )
			{
				AnsiString name = names->Strings[i].Trim();
				if ( name != TXT_NULL && this->indexOfField[ name ] < 0 )
				{
					this->_fields->Add( new CDBField(name) );
				}
				else
				{
					ok = false;
				}
			}
        }
	}
	else
	{
		ok = false;
    }



	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBRecord::deleteFields( TStrings* names )
{
	bool ok = true;

	if ( names )
	{
		for ( int i = 0 ; i < names->Count ; i++ )
		{
			AnsiString name = names->Strings[i].Trim();
			if ( !this->deleteFieldByIndex( this->indexOfField[ name ] ) )
			{
				ok = false;
			}
		}
	}
	else
	{
		ok = false;
    }


	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBRecord::deleteAllFields()
{
	bool ok = true;

	while ( this->_fields->Count )
	{
		if ( !this->deleteFieldByIndex( 0 ) )
		{
			ok = false;
        }
    }

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBRecord::deleteFieldByIndex( int index )
{
	bool ok = true;

	if ( index >= 0 && index < this->_fields->Count )
	{
		CDBField* field = (CDBField*)this->_fields->Items[ index ];
		if ( field )
        {	delete field;
			field = NULL;
            this->_fields->Delete( index );
        }
	}
	else
	{
		ok = false;
    }


	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBRecord::readFromTable( CDBTable* t )
{
	bool ok = true;

	if ( t && t->isOpen )
	{
		for ( int i = 0 ; i < this->_fields->Count ; i++ )
		{
			CDBField* field = this->fields[ i ];
			if ( field && !field->readFromTable( t ) )
			{
				ok = false;
			}
		}
	}
	else
	{
		ok = false;
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBRecord::writeToTable( CDBTable* t )
{
	bool ok = true;

	if ( t && t->isOpen )
	{
		for ( int i = 0 ; i < this->_fields->Count ; i++ )
		{
			CDBField* field = this->fields[ i ];
			if ( field && !field->writeToTable( t ) )
			{
				ok = false;
			}
		}
	}
	else
	{
		ok = false;
	}

	return ok;
}
//---------------------------------------------------------------------------
CDBField* __fastcall CDBRecord::getFields( int index )
{
	return (CDBField*)this->_fields->Items[ index ];
}
//---------------------------------------------------------------------------
int __fastcall CDBRecord::getFieldsCount()
{
	return this->_fields->Count;
}
//---------------------------------------------------------------------------
int __fastcall CDBRecord::getIndexOfField( AnsiString name )
{
	for ( int i = 0 ; i < this->_fields->Count ; i++ )
	{
		CDBField* field = this->fields[i];
		if ( field && ( field->name == name.Trim() ) )
		{
			return i;
        }
	}

	return -1;
}
//---------------------------------------------------------------------------
bool __fastcall CDBRecord::getDif()
{
	for ( int i=0 ; i < this->_fields->Count ; i++ )
	{
		CDBField* field = this->fields[ i ];
		if ( field && field->dif ) return true;
	}

	return false;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CDBRecord::getRam( AnsiString fieldName )
{
    AnsiString ram = TXT_NULL;

    CDBField* f = this->fields[ this->getIndexOfField( fieldName ) ];
    if ( f ) ram = f->ram;

    return ram;
}
//---------------------------------------------------------------------------
void __fastcall CDBRecord::setRam( AnsiString fieldName , AnsiString ram )
{
    CDBField* f = this->fields[ this->getIndexOfField( fieldName ) ];
    if ( f ) f->ram = ram;
}
//---------------------------------------------------------------------------
// CLASSE CDBField
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
// CLASSE CDBTable
//---------------------------------------------------------------------------
__fastcall CDBTable::CDBTable( AnsiString filename )
{
	this->zero();
	this->init();

	this->_filename = filename;
}
//---------------------------------------------------------------------------
__fastcall CDBTable::~CDBTable()
{
	this->deinit();
	this->zero();
}
//---------------------------------------------------------------------------
void __fastcall CDBTable::zero()
{
	this->_filename = AnsiString( "" );
	this->_h = 0;
	this->_recordIndex = 0;
	this->_recordCount = 0;
	this->_bofMarker = 0;
	this->_eofMarker = 0;
	this->_fieldCount = 0;
	this->_fields = NULL;

	ZeroMemory( &this->_info , sizeof( this->_info ) );
}
//---------------------------------------------------------------------------
void __fastcall CDBTable::init()
{
	if ( !this->_fields )
	{
		this->_fields = new TStringList();
    }
}
//---------------------------------------------------------------------------
void __fastcall CDBTable::deinit()
{
	if ( this->_fields )
	{
		delete this->_fields;
		this->_fields = NULL;
    }
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::open()
{
	if ( !this->isOpen )
	{
		DBF_OPEN openCfg;
		ZeroMemory( &openCfg , sizeof( DBF_OPEN ));

		openCfg.api = NULL;
		openCfg.charconv = dbf_charconv_default;
		openCfg.memo = TRUE;
		openCfg.tablename = NULL;
		openCfg.editmode = dbf_editmode_editable;

		this->_h = dbf_open( this->_filename.c_str() , &openCfg );
		if ( this->_h )
		{
			dbf_getinfo( this->_h , &this->_info );
			this->_recordCount 	= this->_info.recordcount;
			this->_bofMarker 	= -1;
			this->_eofMarker 	= this->_recordCount;
			this->_recordIndex 	= dbf_getposition( this->_h );
            this->_fieldCount	= this->_info.fieldcount;

			this->_fields->Clear();

			for ( int i = 0 ; i < this->_info.fieldcount ; i++ )
			{
				DBF_FIELD_INFO fieldInfo;
				ZeroMemory( &fieldInfo , sizeof( fieldInfo ) );

				AnsiString fieldName;

				if ( dbf_getfield_info( this->_h , i , &fieldInfo ) )
				{
					this->_fields->Add( AnsiString( fieldInfo.name ) );
				}
				else
				{
					fieldName = AnsiString( "FIELD" ) + IntToStr( i ) + AnsiString( "_NULL" );
                }
			}

		}
		else
		{
			this->_recordCount 	= 0;
			this->_bofMarker 	= -1;
			this->_eofMarker 	= -1;
			this->_recordIndex	= -1;

			this->_fields->Clear();
		}
    }

	return this->isOpen;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::close()
{
	if ( this->isOpen )
	{
		dbf_close( &this->_h );
	}

	return !this->isOpen;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::first()
{
	bool ok = false;

	if ( this->isOpen )
	{
		ok = dbf_setposition( this->_h , 0 );
		this->_recordIndex = dbf_getposition( this->_h );
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::last()
{
	bool ok = false;

	if ( this->isOpen )
	{
		ok = dbf_setposition( this->_h , this->_recordCount - 1 );
		this->_recordIndex = dbf_getposition( this->_h );
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::next()
{
	bool ok = false;

	if ( this->isOpen )
	{
		ok = dbf_setposition( this->_h , this->recordIndex + 1 );
		this->_recordIndex = dbf_getposition( this->_h );
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::prior()
{
	bool ok = false;

	if ( this->isOpen )
	{
		ok = dbf_setposition( this->_h , this->recordIndex - 1 );
		this->_recordIndex = dbf_getposition( this->_h );
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::loadFieldNames( TStrings* names )
{
	bool ok = false;

	if ( names && this->_fields )
	{
		ok = true;

		names->AddStrings( this->_fields );
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::getFieldValueString( AnsiString fieldName , AnsiString& fieldValue )
{
	bool ok = false;

	if ( this->isOpen )
	{
		const DBF_FIELD* field = dbf_getfieldptr_name( this->_h , fieldName.c_str() );
		if ( field )
		{
			dbf_data_type fieldType = dbf_getfield_type( this->_h , field );
			size_t fieldSize = dbf_getfield( this->_h , field , NULL , 0 , fieldType );

			if ( fieldSize > 0 )
			{
				char* buf = new char[ fieldSize + 1 ];
				ZeroMemory( buf , sizeof( char ) * (fieldSize+1) );

				dbf_getfield( this->_h , field , buf , fieldSize , fieldType );
				fieldValue = AnsiString( buf );

				ZeroMemory( buf , sizeof( char ) * (fieldSize+1) );
				delete[] buf;
				buf = NULL;
			}
            ok = true;
		}
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::setFieldValueString( AnsiString fieldName , AnsiString fieldValue )
{
	bool ok = false;

	if ( this->isOpen )
	{
		const DBF_FIELD* field = dbf_getfieldptr_name( this->_h , fieldName.c_str() );
		if ( field )
		{
			ok = dbf_putfield( this->_h , field , fieldValue.c_str() );
        }
	}

	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::post()
{
	bool ok = false;

	if ( this->isOpen )
	{
		ok = dbf_putrecord( this->_h , this->recordIndex );
    }


	return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CDBTable::getIsOpen()
{
	return ( this->_h!=0 );
}
//---------------------------------------------------------------------------
// CLASSE CDBTable
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
