//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
//-----------------------------------------------------------------------------
#include <string.h>
//-----------------------------------------------------------------------------
S3DX_IMPLEMENT_AIVARIABLE_STRING_POOL   ( 524288 ) ;
S3DX_IMPLEMENT_AIENGINEAPI              ( ScURL2 ) ;
S3DX_IMPLEMENT_PLUGIN                   ( ScURL2 ) ;

//-----------------------------------------------------------------------------
//  AI Packages
//-----------------------------------------------------------------------------
//@@Begin of AI Package include@@
#include "scurl.h"
//@@End of AI Package include@@
//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

ScURL2::ScURL2 ( )
{
    S3DX_REGISTER_PLUGIN  ( "com.tris.scurl" ) ;
    aContentsDirectory[0] = '\0' ;
	
	//Instanciate AI Packages
    S3DX::uint32 iAIPackageIndex = 0 ;
    
    //@@Begin of AI Package declaration@@
	if ( iAIPackageIndex < PLUGIN_AIPACKAGES_COUNT ) aAIPackages [iAIPackageIndex++] = new scurlPackage ( ) ;
    //@@End of AI Package declaration@@

	for ( ; iAIPackageIndex < PLUGIN_AIPACKAGES_COUNT; iAIPackageIndex ++ )
	{
        aAIPackages[iAIPackageIndex] = NULL  ;		
	}

}

//-----------------------------------------------------------------------------

ScURL2::~ScURL2 ( )
{
	for ( S3DX::uint32 iAIPackageIndex = 0 ; iAIPackageIndex < PLUGIN_AIPACKAGES_COUNT; iAIPackageIndex ++ )
	{
		if ( aAIPackages [iAIPackageIndex] )
		{
			delete aAIPackages [iAIPackageIndex] ; 
			aAIPackages[iAIPackageIndex] = NULL  ;
		}
	}
}


//-----------------------------------------------------------------------------
//  Plugin content directory
//-----------------------------------------------------------------------------

        void                    ScURL2::SetContentsDirectory  ( const char *_pDirectory ) { strcpy ( aContentsDirectory, _pDirectory ) ; }

//-----------------------------------------------------------------------------
//  AI packages
//-----------------------------------------------------------------------------

        S3DX::uint32            ScURL2::GetAIPackageCount     ( )                      const { return PLUGIN_AIPACKAGES_COUNT ; }
const   S3DX::AIPackage        *ScURL2::GetAIPackageAt        ( S3DX::uint32 _iIndex ) const { return (_iIndex < PLUGIN_AIPACKAGES_COUNT) ? aAIPackages[_iIndex] : NULL ; }


//-----------------------------------------------------------------------------
//  Engine Events
//-----------------------------------------------------------------------------


void ScURL2::OnEngineEvent ( S3DX::uint32 _iEventCode, S3DX::uint32 _iArgumentCount, S3DX::AIVariable *_pArguments )
{
    switch ( _iEventCode )
    {
    case eEngineEventApplicationStart  : break ;
    case eEngineEventApplicationPause  : break ;
    case eEngineEventApplicationResume : break ;
    case eEngineEventApplicationStop   : break ;
    case eEngineEventFrameUpdateBegin  : break ;
    case eEngineEventFrameUpdateEnd    : break ;
    case eEngineEventFrameRenderBegin  : break ;
    case eEngineEventFrameRenderEnd    : break ;
    }
}
