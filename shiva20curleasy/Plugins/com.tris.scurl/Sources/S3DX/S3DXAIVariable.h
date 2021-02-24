//-----------------------------------------------------------------------------
#ifndef __S3DXAIVariable_h__
#define __S3DXAIVariable_h__
//-----------------------------------------------------------------------------
#include "S3DXTypes.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace S3DX
//-----------------------------------------------------------------------------
{
    // Forward declaration for conversion operators
    //
    template < uint8 _iCount > class AIVariables ;

    //-------------------------------------------------------------------------

    class S3DX_API AIVariable
    {
    public :

        //---------------------------------------------------------------------
        //  Constants
        //---------------------------------------------------------------------
        enum Type
        {
            eTypeNil        = 0x00,
            eTypeNumber     = 0x01,
            eTypeString     = 0x02,
            eTypeBoolean    = 0x03,
            eTypeHandle     = 0x80
        } ;

        //---------------------------------------------------------------------
        //  Constructor / Destructor
        //---------------------------------------------------------------------
        inline                      AIVariable              ( ) ;
        //inline                     ~AIVariable              ( ) ;

        inline                      AIVariable              ( const int8                    _iValue ) ;
        inline                      AIVariable              ( const uint8                   _iValue ) ;
        inline                      AIVariable              ( const int16                   _iValue ) ;
        inline                      AIVariable              ( const uint16                  _iValue ) ;
        inline                      AIVariable              ( const int32                   _iValue ) ;
        inline                      AIVariable              ( const uint32                  _iValue ) ;
        inline                      AIVariable              ( const float32                 _nValue ) ;
        inline                      AIVariable              ( const float64                 _nValue ) ;
        inline                      AIVariable              ( const bool                    _bValue ) ;
        inline                      AIVariable              ( const char                   *_pValue ) ;
        inline                      AIVariable              ( const void                   *_pValue ) ;
        template< uint8 _iCount >
        inline                      AIVariable              ( const AIVariables< _iCount > &_oValue ) ;

        //---------------------------------------------------------------------
        //  Accessors
        //---------------------------------------------------------------------
        inline          bool        CheckType               ( const Type    _eType  ) const ;

        inline          bool        IsNil                   ( ) const ;
        inline          bool        IsBoolean               ( ) const ;
        inline          bool        IsNumber                ( ) const ;
        inline          bool        IsString                ( ) const ;
        inline          bool        IsHandle                ( ) const ;

        inline          bool        CanConvertToNumber      ( ) const ;
        inline          bool        CanConvertToString      ( ) const ;

        inline          Type        GetType                 ( ) const ;
        inline          bool        GetBooleanValue         ( ) const ;
        inline          number      GetNumberValue          ( ) const ;
        inline  const   char       *GetStringValue          ( ) const ;
        inline  const   void       *GetHandleValue          ( ) const ;

        inline          void        SetNil                  ( ) ;
        inline          void        SetBooleanValue         ( const bool    _bValue ) ;
        inline          void        SetNumberValue          ( const number  _nValue ) ;
        inline          void        SetStringValue          ( const char   *_pValue ) ;
        inline          void        SetHandleValue          ( const void   *_pValue ) ;

        //---------------------------------------------------------------------
        //  Misc
        //---------------------------------------------------------------------
        inline  static  AIVariable  Concat                  ( const AIVariable &_v0, const AIVariable &_v1 ) ;

        //---------------------------------------------------------------------
        //  Operators
        //---------------------------------------------------------------------
        inline                  operator int8               ( ) const ;
        inline                  operator uint8              ( ) const ;
        inline                  operator int16              ( ) const ;
        inline                  operator uint16             ( ) const ;
        inline                  operator int32              ( ) const ;
        inline                  operator uint32             ( ) const ;
        inline                  operator float32            ( ) const ;
        inline                  operator float64            ( ) const ;
        inline                  operator bool               ( ) const ;
        //???inline                  operator const char *   ( ) const ;
        //???inline                  operator const void *   ( ) const ;

        inline  bool            operator !                  ( ) const ;

        inline  AIVariable      operator +                  ( ) const ;
        inline  AIVariable      operator -                  ( ) const ;

        inline  AIVariable     &operator =                  ( const int8        _iValue ) ;
        inline  AIVariable     &operator =                  ( const uint8       _iValue ) ;
        inline  AIVariable     &operator =                  ( const int16       _iValue ) ;
        inline  AIVariable     &operator =                  ( const uint16      _iValue ) ;
        inline  AIVariable     &operator =                  ( const int32       _iValue ) ;
        inline  AIVariable     &operator =                  ( const uint32      _iValue ) ;
        inline  AIVariable     &operator =                  ( const float32     _nValue ) ;
        inline  AIVariable     &operator =                  ( const float64     _nValue ) ;
        inline  AIVariable     &operator =                  ( const bool        _bValue ) ;
        inline  AIVariable     &operator =                  ( const char       *_pValue ) ;
        inline  AIVariable     &operator =                  ( const void       *_pValue ) ;
        inline  AIVariable     &operator =                  ( const AIVariable &_vValue ) ;
        template< uint8 _iCount >
        inline  AIVariable     &operator =                  ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable      operator +                  ( const int8        _iValue ) const ;
        inline  AIVariable      operator +                  ( const uint8       _iValue ) const ;
        inline  AIVariable      operator +                  ( const int16       _iValue ) const ;
        inline  AIVariable      operator +                  ( const uint16      _iValue ) const ;
        inline  AIVariable      operator +                  ( const int32       _iValue ) const ;
        inline  AIVariable      operator +                  ( const uint32      _iValue ) const ;
        inline  AIVariable      operator +                  ( const float32     _nValue ) const ;
        inline  AIVariable      operator +                  ( const float64     _nValue ) const ;
        inline  AIVariable      operator +                  ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  AIVariable      operator +                  ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable     &operator +=                 ( const int8        _iValue ) ;
        inline  AIVariable     &operator +=                 ( const uint8       _iValue ) ;
        inline  AIVariable     &operator +=                 ( const int16       _iValue ) ;
        inline  AIVariable     &operator +=                 ( const uint16      _iValue ) ;
        inline  AIVariable     &operator +=                 ( const int32       _iValue ) ;
        inline  AIVariable     &operator +=                 ( const uint32      _iValue ) ;
        inline  AIVariable     &operator +=                 ( const float32     _nValue ) ;
        inline  AIVariable     &operator +=                 ( const float64     _nValue ) ;
        inline  AIVariable     &operator +=                 ( const AIVariable &_vValue ) ;
        template< uint8 _iCount >
        inline  AIVariable     &operator +=                 ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable      operator -                  ( const int8        _iValue ) const ;
        inline  AIVariable      operator -                  ( const uint8       _iValue ) const ;
        inline  AIVariable      operator -                  ( const int16       _iValue ) const ;
        inline  AIVariable      operator -                  ( const uint16      _iValue ) const ;
        inline  AIVariable      operator -                  ( const int32       _iValue ) const ;
        inline  AIVariable      operator -                  ( const uint32      _iValue ) const ;
        inline  AIVariable      operator -                  ( const float32     _nValue ) const ;
        inline  AIVariable      operator -                  ( const float64     _nValue ) const ;
        inline  AIVariable      operator -                  ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  AIVariable      operator -                  ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable     &operator -=                 ( const int8        _iValue ) ;
        inline  AIVariable     &operator -=                 ( const uint8       _iValue ) ;
        inline  AIVariable     &operator -=                 ( const int16       _iValue ) ;
        inline  AIVariable     &operator -=                 ( const uint16      _iValue ) ;
        inline  AIVariable     &operator -=                 ( const int32       _iValue ) ;
        inline  AIVariable     &operator -=                 ( const uint32      _iValue ) ;
        inline  AIVariable     &operator -=                 ( const float32     _nValue ) ;
        inline  AIVariable     &operator -=                 ( const float64     _nValue ) ;
        inline  AIVariable     &operator -=                 ( const AIVariable &_vValue ) ;
        template< uint8 _iCount >
        inline  AIVariable     &operator -=                 ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable      operator *                  ( const int8        _iValue ) const ;
        inline  AIVariable      operator *                  ( const uint8       _iValue ) const ;
        inline  AIVariable      operator *                  ( const int16       _iValue ) const ;
        inline  AIVariable      operator *                  ( const uint16      _iValue ) const ;
        inline  AIVariable      operator *                  ( const int32       _iValue ) const ;
        inline  AIVariable      operator *                  ( const uint32      _iValue ) const ;
        inline  AIVariable      operator *                  ( const float32     _nValue ) const ;
        inline  AIVariable      operator *                  ( const float64     _nValue ) const ;
        inline  AIVariable      operator *                  ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  AIVariable      operator *                  ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable     &operator *=                 ( const int8        _iValue ) ;
        inline  AIVariable     &operator *=                 ( const uint8       _iValue ) ;
        inline  AIVariable     &operator *=                 ( const int16       _iValue ) ;
        inline  AIVariable     &operator *=                 ( const uint16      _iValue ) ;
        inline  AIVariable     &operator *=                 ( const int32       _iValue ) ;
        inline  AIVariable     &operator *=                 ( const uint32      _iValue ) ;
        inline  AIVariable     &operator *=                 ( const float32     _nValue ) ;
        inline  AIVariable     &operator *=                 ( const float64     _nValue ) ;
        inline  AIVariable     &operator *=                 ( const AIVariable &_vValue ) ;
        template< uint8 _iCount >
        inline  AIVariable     &operator *=                 ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable      operator /                  ( const int8        _iValue ) const ;
        inline  AIVariable      operator /                  ( const uint8       _iValue ) const ;
        inline  AIVariable      operator /                  ( const int16       _iValue ) const ;
        inline  AIVariable      operator /                  ( const uint16      _iValue ) const ;
        inline  AIVariable      operator /                  ( const int32       _iValue ) const ;
        inline  AIVariable      operator /                  ( const uint32      _iValue ) const ;
        inline  AIVariable      operator /                  ( const float32     _nValue ) const ;
        inline  AIVariable      operator /                  ( const float64     _nValue ) const ;
        inline  AIVariable      operator /                  ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  AIVariable      operator /                  ( const AIVariables< _iCount > &_oValue ) ;

        inline  AIVariable     &operator /=                 ( const int8        _iValue ) ;
        inline  AIVariable     &operator /=                 ( const uint8       _iValue ) ;
        inline  AIVariable     &operator /=                 ( const int16       _iValue ) ;
        inline  AIVariable     &operator /=                 ( const uint16      _iValue ) ;
        inline  AIVariable     &operator /=                 ( const int32       _iValue ) ;
        inline  AIVariable     &operator /=                 ( const uint32      _iValue ) ;
        inline  AIVariable     &operator /=                 ( const float32     _nValue ) ;
        inline  AIVariable     &operator /=                 ( const float64     _nValue ) ;
        inline  AIVariable     &operator /=                 ( const AIVariable &_vValue ) ;
        template< uint8 _iCount >
        inline  AIVariable     &operator /=                 ( const AIVariables< _iCount > &_oValue ) ;

        inline  bool            operator <                  ( const int8        _iValue ) const ;
        inline  bool            operator <                  ( const uint8       _iValue ) const ;
        inline  bool            operator <                  ( const int16       _iValue ) const ;
        inline  bool            operator <                  ( const uint16      _iValue ) const ;
        inline  bool            operator <                  ( const int32       _iValue ) const ;
        inline  bool            operator <                  ( const uint32      _iValue ) const ;
        inline  bool            operator <                  ( const float32     _nValue ) const ;
        inline  bool            operator <                  ( const float64     _nValue ) const ;
        inline  bool            operator <                  ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  bool            operator <                  ( const AIVariables< _iCount > &_oValue ) ;

        inline  bool            operator >                  ( const int8        _iValue ) const ;
        inline  bool            operator >                  ( const uint8       _iValue ) const ;
        inline  bool            operator >                  ( const int16       _iValue ) const ;
        inline  bool            operator >                  ( const uint16      _iValue ) const ;
        inline  bool            operator >                  ( const int32       _iValue ) const ;
        inline  bool            operator >                  ( const uint32      _iValue ) const ;
        inline  bool            operator >                  ( const float32     _nValue ) const ;
        inline  bool            operator >                  ( const float64     _nValue ) const ;
        inline  bool            operator >                  ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  bool            operator >                  ( const AIVariables< _iCount > &_oValue ) ;

        inline  bool            operator <=                 ( const int8        _iValue ) const ;
        inline  bool            operator <=                 ( const uint8       _iValue ) const ;
        inline  bool            operator <=                 ( const int16       _iValue ) const ;
        inline  bool            operator <=                 ( const uint16      _iValue ) const ;
        inline  bool            operator <=                 ( const int32       _iValue ) const ;
        inline  bool            operator <=                 ( const uint32      _iValue ) const ;
        inline  bool            operator <=                 ( const float32     _nValue ) const ;
        inline  bool            operator <=                 ( const float64     _nValue ) const ;
        inline  bool            operator <=                 ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  bool            operator <=                 ( const AIVariables< _iCount > &_oValue ) ;

        inline  bool            operator >=                 ( const int8        _iValue ) const ;
        inline  bool            operator >=                 ( const uint8       _iValue ) const ;
        inline  bool            operator >=                 ( const int16       _iValue ) const ;
        inline  bool            operator >=                 ( const uint16      _iValue ) const ;
        inline  bool            operator >=                 ( const int32       _iValue ) const ;
        inline  bool            operator >=                 ( const uint32      _iValue ) const ;
        inline  bool            operator >=                 ( const float32     _nValue ) const ;
        inline  bool            operator >=                 ( const float64     _nValue ) const ;
        inline  bool            operator >=                 ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  bool            operator >=                 ( const AIVariables< _iCount > &_oValue ) ;

        inline  bool            operator ==                 ( const int8        _iValue ) const ;
        inline  bool            operator ==                 ( const uint8       _iValue ) const ;
        inline  bool            operator ==                 ( const int16       _iValue ) const ;
        inline  bool            operator ==                 ( const uint16      _iValue ) const ;
        inline  bool            operator ==                 ( const int32       _iValue ) const ;
        inline  bool            operator ==                 ( const uint32      _iValue ) const ;
        inline  bool            operator ==                 ( const float32     _nValue ) const ;
        inline  bool            operator ==                 ( const float64     _nValue ) const ;
        inline  bool            operator ==                 ( const bool        _bValue ) const ;
        inline  bool            operator ==                 ( const char       *_pValue ) const ;
        inline  bool            operator ==                 ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  bool            operator ==                 ( const AIVariables< _iCount > &_oValue ) ;

        inline  bool            operator !=                 ( const int8        _iValue ) const ;
        inline  bool            operator !=                 ( const uint8       _iValue ) const ;
        inline  bool            operator !=                 ( const int16       _iValue ) const ;
        inline  bool            operator !=                 ( const uint16      _iValue ) const ;
        inline  bool            operator !=                 ( const int32       _iValue ) const ;
        inline  bool            operator !=                 ( const uint32      _iValue ) const ;
        inline  bool            operator !=                 ( const float32     _nValue ) const ;
        inline  bool            operator !=                 ( const float64     _nValue ) const ;
        inline  bool            operator !=                 ( const bool        _bValue ) const ;
        inline  bool            operator !=                 ( const char       *_pValue ) const ;
        inline  bool            operator !=                 ( const AIVariable &_vValue ) const ;
        template< uint8 _iCount >
        inline  bool            operator !=                 ( const AIVariables< _iCount > &_oValue ) ;

        //---------------------------------------------------------------------
        //  "Special" operators
        //---------------------------------------------------------------------

        // Bitwise left shift, replacing '..' in Lua
        //
        inline  AIVariable      operator <<                 ( const int8        _iValue ) const ;
        inline  AIVariable      operator <<                 ( const uint8       _iValue ) const ;
        inline  AIVariable      operator <<                 ( const int16       _iValue ) const ;
        inline  AIVariable      operator <<                 ( const uint16      _iValue ) const ;
        inline  AIVariable      operator <<                 ( const int32       _iValue ) const ;
        inline  AIVariable      operator <<                 ( const uint32      _iValue ) const ;
        inline  AIVariable      operator <<                 ( const float32     _nValue ) const ;
        inline  AIVariable      operator <<                 ( const float64     _nValue ) const ;
        inline  AIVariable      operator <<                 ( const AIVariable &_vValue ) const ;

        // Bitwise AND replacing 'and' in Lua (DEPRECATED)
        //
        inline  AIVariable      operator &                  ( const int8        _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const uint8       _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const int16       _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const uint16      _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const int32       _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const uint32      _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const float32     _nValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const float64     _nValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const bool        _bValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator &                  ( const AIVariable &_vValue ) const ; // DEPRECATED, PLEASE DO NOT USE

        // Bitwise OR replacing 'or' in Lua (DEPRECATED)
        //
        inline  AIVariable      operator |                  ( const int8        _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const uint8       _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const int16       _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const uint16      _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const int32       _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const uint32      _iValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const float32     _nValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const float64     _nValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const bool        _bValue ) const ; // DEPRECATED, PLEASE DO NOT USE
        inline  AIVariable      operator |                  ( const AIVariable &_vValue ) const ; // DEPRECATED, PLEASE DO NOT USE

        //---------------------------------------------------------------------
        //  Temporary string buffer access
        //  Public for some reasons but do *not* use it!!!
        //---------------------------------------------------------------------
        static  char           *GetStringPoolBuffer         ( const uint32      _iSize   ) ;
        static  char           *GetStringPoolBufferAndCopy  ( const char       *_pString ) ;
        static  char           *GetStringPoolBufferAndCopy  ( const uint32      _iSize,
                                                              const char       *_pString ) ;
        static  bool            ResetStringPool             ( const uint32      _iSize   ) ;

    private :

        //---------------------------------------------------------------------
        //  Functions
        //---------------------------------------------------------------------
        inline  void            SetType                     ( const Type  _eType ) ;
        inline  bool            StringToNumber              ( const char *_pString, number *_pNumber ) const ;
        inline  number          StringToNumber              ( const char *_pString ) const ;
        inline  const char     *NumberToString              ( number      _nNumber ) const ;

        //---------------------------------------------------------------------
        //  Variables
        //---------------------------------------------------------------------
        uint8   iType       ;
        uint8   iUnused0    ; // For alignment, not actually used
        uint16  iUnused1    ; // For alignment, not actually used
        union
        {
            uintptr       iUnknownValue   ;
            bool          bBooleanValue   ;
            number        nNumberValue    ;
            const char   *pStringValue    ;
            const void   *pHandleValue    ;
        } ;

        //---------------------------------------------------------------------
        //  Static variables
        //---------------------------------------------------------------------
        static  uint32  iStringPoolCursor ;
        static  uint32  iStringPoolSize   ;
        static  char   *pStringPool       ;
    } ;

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
    //-------------------------------------------------------------------------

    inline AIVariable::AIVariable ( )
    {
        iType           = (uint8)eTypeNil ;
        iUnknownValue   = 0 ;
    }

    //-------------------------------------------------------------------------
    /*
    inline AIVariable::~AIVariable ( )
    {
        iType           = (uint8)eTypeNil ;
        iUnknownValue   = 0 ;
    }
    */

    //-------------------------------------------------------------------------

    inline  AIVariable::AIVariable ( const int8        _iValue ) { SetNumberValue  ( (number)  _iValue ) ; }
    inline  AIVariable::AIVariable ( const uint8       _iValue ) { SetNumberValue  ( (number)  _iValue ) ; }
    inline  AIVariable::AIVariable ( const int16       _iValue ) { SetNumberValue  ( (number)  _iValue ) ; }
    inline  AIVariable::AIVariable ( const uint16      _iValue ) { SetNumberValue  ( (number)  _iValue ) ; }
    inline  AIVariable::AIVariable ( const int32       _iValue ) { SetNumberValue  ( (number)  _iValue ) ; }
    inline  AIVariable::AIVariable ( const uint32      _iValue ) { SetNumberValue  ( (number)  _iValue ) ; }
    inline  AIVariable::AIVariable ( const float32     _nValue ) { SetNumberValue  ( (number)  _nValue ) ; }
    inline  AIVariable::AIVariable ( const float64     _nValue ) { SetNumberValue  ( (number)  _nValue ) ; }
    inline  AIVariable::AIVariable ( const bool        _bValue ) { SetBooleanValue (           _bValue ) ; }
    inline  AIVariable::AIVariable ( const char       *_pValue ) { SetStringValue  (           _pValue ) ; }
    inline  AIVariable::AIVariable ( const void       *_pValue ) { SetHandleValue  (           _pValue ) ; }

    template< uint8 _iCount >
    inline  AIVariable::AIVariable ( const AIVariables< _iCount > &_oValue ) { *this = (const AIVariable &)_oValue ; }


    //-------------------------------------------------------------------------
    //  Misc functions
    //-------------------------------------------------------------------------

    inline AIVariable AIVariable::Concat ( const AIVariable &_v0, const AIVariable &_v1 )
    {
        // FIXME: to verify/optimize/...
        //
        const char *p0 = _v0.GetStringValue ( ) ;
        const char *p1 = _v1.GetStringValue ( ) ;

        if ( p0 && ! p1 ) return p0 ; // FIXME: return a copy?
        if ( p1 && ! p0 ) return p1 ; // FIXME: return a copy?
        if ( p0 &&   p1 )
        {
            const uint32 iLen0 = S3DX_STRLEN( p0 ) ;
            const uint32 iLen1 = S3DX_STRLEN( p1 ) ;

            char *pNewStr = GetStringPoolBuffer ( iLen0 + iLen1 + 1 ) ;
            if  ( pNewStr )
            {
                S3DX_MEMCPY ( pNewStr,         p0, iLen0     ) ;
                S3DX_MEMCPY ( pNewStr + iLen0, p1, iLen1 + 1 ) ;

                return AIVariable ( pNewStr ) ;
            }
        }
        return AIVariable ( "" ) ;
    }

    //-------------------------------------------------------------------------
    //  Private functions
    //-------------------------------------------------------------------------

    inline bool AIVariable::StringToNumber ( const char *_pString, number *_pNumber ) const
    {
        char   *pEndPtr ;
        number  nResult = S3DX_STRTOF( _pString, &pEndPtr ) ;
        if    ( pEndPtr == _pString ) return false ;  // no conversion
        while ( S3DX_ISSPACE((unsigned char)(*pEndPtr))) pEndPtr++ ;
        if    ( *pEndPtr != '\0'    ) return false ;  // invalid trailing characters
        *_pNumber = nResult ;
        return true ;
    }

    //-------------------------------------------------------------------------

    inline number AIVariable::StringToNumber ( const char *_pString ) const
    {
        number nRet = 0.0f ; StringToNumber ( _pString, &nRet ) ;
        return nRet ;
    }

    //-------------------------------------------------------------------------

    inline const char *AIVariable::NumberToString ( number _nNumber ) const
    {
        char *pNewStr = GetStringPoolBuffer ( 32 ) ;
        if  ( pNewStr )
        {
            S3DX_SPRINTF( pNewStr, "%g", _nNumber ) ;
            return        pNewStr;
        }
        return "" ;
    }

    //-------------------------------------------------------------------------
    //  Accessors
    //-------------------------------------------------------------------------

    inline bool AIVariable::CheckType ( const Type _eType ) const
    {
        return ( iType == _eType ) ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::IsNil ( ) const
    {
        return CheckType ( eTypeNil ) ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::IsBoolean ( ) const
    {
        return CheckType ( eTypeBoolean ) ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::IsNumber ( ) const
    {
        return CheckType ( eTypeNumber ) ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::IsString ( ) const
    {
        return CheckType ( eTypeString ) ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::IsHandle ( ) const
    {
        return CheckType ( eTypeHandle ) ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::CanConvertToNumber ( ) const
    {
        if ( IsNumber ( ) ) return true ;
        if ( IsString ( ) && pStringValue )
        {
            number nDummy ;
            return StringToNumber ( pStringValue, &nDummy ) ;
        }
        return false ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::CanConvertToString ( ) const
    {
        return IsString ( ) || IsNumber ( ) ;
    }

    //-------------------------------------------------------------------------

    inline AIVariable::Type AIVariable::GetType ( ) const
    {
        return (Type)iType ;
    }

    //-------------------------------------------------------------------------

    inline bool AIVariable::GetBooleanValue ( ) const
    {
        return IsBoolean ( ) ? bBooleanValue : ( ! IsNil ( ) ) ;
    }

    //-------------------------------------------------------------------------

    inline number AIVariable::GetNumberValue ( ) const
    {
        return IsNumber ( ) ? nNumberValue : ( ( IsString ( ) && pStringValue ) ? StringToNumber ( pStringValue ) : 0.0f ) ;
    }

    //-------------------------------------------------------------------------

    inline const char *AIVariable::GetStringValue ( ) const
    {
        return IsString ( ) ? ( pStringValue ? pStringValue : "" ) : ( IsNumber ( ) ? NumberToString ( nNumberValue ) : NULL ) ;
    }

    //-------------------------------------------------------------------------

    inline const void *AIVariable::GetHandleValue ( ) const
    {
        return IsHandle ( ) ? pHandleValue : NULL ;
    }

    //-------------------------------------------------------------------------

    inline void AIVariable::SetType ( const Type _eType )
    {
        iType           = (uint8)_eType ;
        iUnknownValue   = 0 ;
    }

    //-------------------------------------------------------------------------

    inline void AIVariable::SetNil ( )
    {
        SetType       ( eTypeNil ) ;
    }

    //-------------------------------------------------------------------------

    inline void AIVariable::SetBooleanValue ( const bool _bValue )
    {
        SetType       ( eTypeBoolean ) ;
        bBooleanValue = _bValue ;
    }

    //-------------------------------------------------------------------------

    inline void AIVariable::SetNumberValue ( const number _nValue )
    {
        SetType       ( eTypeNumber ) ;
        nNumberValue = _nValue ;
    }

    //-------------------------------------------------------------------------

    inline void AIVariable::SetStringValue ( const char *_pValue )
    {
        SetType       ( eTypeString ) ;
        pStringValue = _pValue ;
    }

    //-------------------------------------------------------------------------

    inline void AIVariable::SetHandleValue ( const void *_pValue )
    {
        SetType       ( eTypeHandle ) ;
        pHandleValue  = _pValue ;
    }

    //-------------------------------------------------------------------------
    //  Operators
    //-------------------------------------------------------------------------

    inline              AIVariable::operator int8           ( ) const { return (int8)    GetNumberValue  ( ) ; }
    inline              AIVariable::operator uint8          ( ) const { return (uint8)   GetNumberValue  ( ) ; }
    inline              AIVariable::operator int16          ( ) const { return (int16)   GetNumberValue  ( ) ; }
    inline              AIVariable::operator uint16         ( ) const { return (uint16)  GetNumberValue  ( ) ; }
    inline              AIVariable::operator int32          ( ) const { return (int32)   GetNumberValue  ( ) ; }
    inline              AIVariable::operator uint32         ( ) const { return (uint32)  GetNumberValue  ( ) ; }
    inline              AIVariable::operator float32        ( ) const { return (float32) GetNumberValue  ( ) ; }
    inline              AIVariable::operator float64        ( ) const { return (float64) GetNumberValue  ( ) ; }
    inline              AIVariable::operator bool           ( ) const { return           GetBooleanValue ( ) ; }
    //???inline              AIVariable::operator const char *   ( ) const { return           GetStringValue  ( ) ; }
    //???inline              AIVariable::operator const void *   ( ) const { return           GetHandleValue  ( ) ; }

    inline  bool        AIVariable::operator !              ( ) const { return ! GetBooleanValue ( ) ; }

    inline  AIVariable  AIVariable::operator +              ( ) const { return *this ; }
    inline  AIVariable  AIVariable::operator -              ( ) const { AIVariable v ; v.SetNumberValue ( - GetNumberValue ( ) ) ; return v ; } // FIXME?

    inline  AIVariable &AIVariable::operator =              ( const int8                    _iValue ) { SetNumberValue  ( (number)  _iValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const uint8                   _iValue ) { SetNumberValue  ( (number)  _iValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const int16                   _iValue ) { SetNumberValue  ( (number)  _iValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const uint16                  _iValue ) { SetNumberValue  ( (number)  _iValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const int32                   _iValue ) { SetNumberValue  ( (number)  _iValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const uint32                  _iValue ) { SetNumberValue  ( (number)  _iValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const float32                 _nValue ) { SetNumberValue  ( (number)  _nValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const float64                 _nValue ) { SetNumberValue  ( (number)  _nValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const bool                    _bValue ) { SetBooleanValue (           _bValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const char                   *_pValue ) { SetStringValue  (           _pValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const void                   *_pValue ) { SetHandleValue  (           _pValue ) ; return *this ; }
    inline  AIVariable &AIVariable::operator =              ( const AIVariable             &_vValue ) { iType =_vValue.iType ; iUnknownValue = _vValue.iUnknownValue ; return *this ; }
    template< uint8 _iCount >
    inline  AIVariable &AIVariable::operator =              ( const AIVariables< _iCount > &_oValue ) { return *this = (const AIVariable &)_oValue ; }

    inline  AIVariable  AIVariable::operator +              ( const int8                    _iValue ) const { return GetNumberValue ( ) + (number)_iValue ; }
    inline  AIVariable  AIVariable::operator +              ( const uint8                   _iValue ) const { return GetNumberValue ( ) + (number)_iValue ; }
    inline  AIVariable  AIVariable::operator +              ( const int16                   _iValue ) const { return GetNumberValue ( ) + (number)_iValue ; }
    inline  AIVariable  AIVariable::operator +              ( const uint16                  _iValue ) const { return GetNumberValue ( ) + (number)_iValue ; }
    inline  AIVariable  AIVariable::operator +              ( const int32                   _iValue ) const { return GetNumberValue ( ) + (number)_iValue ; }
    inline  AIVariable  AIVariable::operator +              ( const uint32                  _iValue ) const { return GetNumberValue ( ) + (number)_iValue ; }
    inline  AIVariable  AIVariable::operator +              ( const float32                 _nValue ) const { return GetNumberValue ( ) + (number)_nValue ; }
    inline  AIVariable  AIVariable::operator +              ( const float64                 _nValue ) const { return GetNumberValue ( ) + (number)_nValue ; }
    inline  AIVariable  AIVariable::operator +              ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) + _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  AIVariable  AIVariable::operator +              ( const AIVariables< _iCount > &_oValue ) { return *this + (const AIVariable &)_oValue ; }

    inline  AIVariable              operator +              ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue + _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator +              ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue + _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator +              ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue + _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator +              ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue + _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator +              ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue + _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator +              ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue + _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator +              ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue + _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator +              ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue + _vVariable.GetNumberValue ( ) ; }

    inline  AIVariable &AIVariable::operator +=             ( const int8                    _iValue ) { *this = *this + _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const uint8                   _iValue ) { *this = *this + _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const int16                   _iValue ) { *this = *this + _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const uint16                  _iValue ) { *this = *this + _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const int32                   _iValue ) { *this = *this + _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const uint32                  _iValue ) { *this = *this + _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const float32                 _nValue ) { *this = *this + _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const float64                 _nValue ) { *this = *this + _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator +=             ( const AIVariable             &_vValue ) { *this = *this + _vValue ; return *this ; }
    template< uint8 _iCount >
    inline  AIVariable &AIVariable::operator +=             ( const AIVariables< _iCount > &_oValue ) { return *this += (const AIVariable &)_oValue ; }

    inline  AIVariable  AIVariable::operator -              ( const int8                    _iValue ) const { return GetNumberValue ( ) - (number)_iValue ; }
    inline  AIVariable  AIVariable::operator -              ( const uint8                   _iValue ) const { return GetNumberValue ( ) - (number)_iValue ; }
    inline  AIVariable  AIVariable::operator -              ( const int16                   _iValue ) const { return GetNumberValue ( ) - (number)_iValue ; }
    inline  AIVariable  AIVariable::operator -              ( const uint16                  _iValue ) const { return GetNumberValue ( ) - (number)_iValue ; }
    inline  AIVariable  AIVariable::operator -              ( const int32                   _iValue ) const { return GetNumberValue ( ) - (number)_iValue ; }
    inline  AIVariable  AIVariable::operator -              ( const uint32                  _iValue ) const { return GetNumberValue ( ) - (number)_iValue ; }
    inline  AIVariable  AIVariable::operator -              ( const float32                 _nValue ) const { return GetNumberValue ( ) - (number)_nValue ; }
    inline  AIVariable  AIVariable::operator -              ( const float64                 _nValue ) const { return GetNumberValue ( ) - (number)_nValue ; }
    inline  AIVariable  AIVariable::operator -              ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) - _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  AIVariable  AIVariable::operator -              ( const AIVariables< _iCount > &_oValue ) { return *this - (const AIVariable &)_oValue ; }

    inline  AIVariable              operator -              ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue - _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator -              ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue - _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator -              ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue - _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator -              ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue - _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator -              ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue - _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator -              ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue - _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator -              ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue - _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator -              ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue - _vVariable.GetNumberValue ( ) ; }

    inline  AIVariable &AIVariable::operator -=             ( const int8                    _iValue ) { *this = *this - _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const uint8                   _iValue ) { *this = *this - _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const int16                   _iValue ) { *this = *this - _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const uint16                  _iValue ) { *this = *this - _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const int32                   _iValue ) { *this = *this - _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const uint32                  _iValue ) { *this = *this - _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const float32                 _nValue ) { *this = *this - _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const float64                 _nValue ) { *this = *this - _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator -=             ( const AIVariable             &_vValue ) { *this = *this - _vValue ; return *this ; }
    template< uint8 _iCount >
    inline  AIVariable &AIVariable::operator -=             ( const AIVariables< _iCount > &_oValue ) { return *this -= (const AIVariable &)_oValue ; }

    inline  AIVariable  AIVariable::operator *              ( const int8                    _iValue ) const { return GetNumberValue ( ) * (number)_iValue ; }
    inline  AIVariable  AIVariable::operator *              ( const uint8                   _iValue ) const { return GetNumberValue ( ) * (number)_iValue ; }
    inline  AIVariable  AIVariable::operator *              ( const int16                   _iValue ) const { return GetNumberValue ( ) * (number)_iValue ; }
    inline  AIVariable  AIVariable::operator *              ( const uint16                  _iValue ) const { return GetNumberValue ( ) * (number)_iValue ; }
    inline  AIVariable  AIVariable::operator *              ( const int32                   _iValue ) const { return GetNumberValue ( ) * (number)_iValue ; }
    inline  AIVariable  AIVariable::operator *              ( const uint32                  _iValue ) const { return GetNumberValue ( ) * (number)_iValue ; }
    inline  AIVariable  AIVariable::operator *              ( const float32                 _nValue ) const { return GetNumberValue ( ) * (number)_nValue ; }
    inline  AIVariable  AIVariable::operator *              ( const float64                 _nValue ) const { return GetNumberValue ( ) * (number)_nValue ; }
    inline  AIVariable  AIVariable::operator *              ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) * _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  AIVariable  AIVariable::operator *              ( const AIVariables< _iCount > &_oValue ) { return *this * (const AIVariable &)_oValue ; }

    inline  AIVariable              operator *              ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue * _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator *              ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue * _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator *              ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue * _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator *              ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue * _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator *              ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue * _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator *              ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue * _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator *              ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue * _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator *              ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue * _vVariable.GetNumberValue ( ) ; }

    inline  AIVariable &AIVariable::operator *=             ( const int8                    _iValue ) { *this = *this * _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const uint8                   _iValue ) { *this = *this * _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const int16                   _iValue ) { *this = *this * _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const uint16                  _iValue ) { *this = *this * _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const int32                   _iValue ) { *this = *this * _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const uint32                  _iValue ) { *this = *this * _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const float32                 _nValue ) { *this = *this * _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const float64                 _nValue ) { *this = *this * _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator *=             ( const AIVariable             &_vValue ) { *this = *this * _vValue ; return *this ; }
    template< uint8 _iCount >
    inline  AIVariable &AIVariable::operator *=             ( const AIVariables< _iCount > &_oValue ) { return *this *= (const AIVariable &)_oValue ; }

    inline  AIVariable  AIVariable::operator /              ( const int8                    _iValue ) const { return GetNumberValue ( ) / (number)_iValue ; }
    inline  AIVariable  AIVariable::operator /              ( const uint8                   _iValue ) const { return GetNumberValue ( ) / (number)_iValue ; }
    inline  AIVariable  AIVariable::operator /              ( const int16                   _iValue ) const { return GetNumberValue ( ) / (number)_iValue ; }
    inline  AIVariable  AIVariable::operator /              ( const uint16                  _iValue ) const { return GetNumberValue ( ) / (number)_iValue ; }
    inline  AIVariable  AIVariable::operator /              ( const int32                   _iValue ) const { return GetNumberValue ( ) / (number)_iValue ; }
    inline  AIVariable  AIVariable::operator /              ( const uint32                  _iValue ) const { return GetNumberValue ( ) / (number)_iValue ; }
    inline  AIVariable  AIVariable::operator /              ( const float32                 _nValue ) const { return GetNumberValue ( ) / (number)_nValue ; }
    inline  AIVariable  AIVariable::operator /              ( const float64                 _nValue ) const { return GetNumberValue ( ) / (number)_nValue ; }
    inline  AIVariable  AIVariable::operator /              ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) / _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  AIVariable  AIVariable::operator /              ( const AIVariables< _iCount > &_oValue ) { return *this / (const AIVariable &)_oValue ; }

    inline  AIVariable              operator /              ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue / _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator /              ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue / _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator /              ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue / _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator /              ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue / _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator /              ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue / _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator /              ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue / _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator /              ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue / _vVariable.GetNumberValue ( ) ; }
    inline  AIVariable              operator /              ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue / _vVariable.GetNumberValue ( ) ; }

    inline  AIVariable &AIVariable::operator /=             ( const int8                    _iValue ) { *this = *this / _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const uint8                   _iValue ) { *this = *this / _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const int16                   _iValue ) { *this = *this / _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const uint16                  _iValue ) { *this = *this / _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const int32                   _iValue ) { *this = *this / _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const uint32                  _iValue ) { *this = *this / _iValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const float32                 _nValue ) { *this = *this / _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const float64                 _nValue ) { *this = *this / _nValue ; return *this ; }
    inline  AIVariable &AIVariable::operator /=             ( const AIVariable             &_vValue ) { *this = *this / _vValue ; return *this ; }
    template< uint8 _iCount >
    inline  AIVariable &AIVariable::operator /=             ( const AIVariables< _iCount > &_oValue ) { return *this /= (const AIVariable &)_oValue ; }

    inline  bool        AIVariable::operator <              ( const int8                    _iValue ) const { return GetNumberValue ( ) < (number)_iValue ; }
    inline  bool        AIVariable::operator <              ( const uint8                   _iValue ) const { return GetNumberValue ( ) < (number)_iValue ; }
    inline  bool        AIVariable::operator <              ( const int16                   _iValue ) const { return GetNumberValue ( ) < (number)_iValue ; }
    inline  bool        AIVariable::operator <              ( const uint16                  _iValue ) const { return GetNumberValue ( ) < (number)_iValue ; }
    inline  bool        AIVariable::operator <              ( const int32                   _iValue ) const { return GetNumberValue ( ) < (number)_iValue ; }
    inline  bool        AIVariable::operator <              ( const uint32                  _iValue ) const { return GetNumberValue ( ) < (number)_iValue ; }
    inline  bool        AIVariable::operator <              ( const float32                 _nValue ) const { return GetNumberValue ( ) < (number)_nValue ; }
    inline  bool        AIVariable::operator <              ( const float64                 _nValue ) const { return GetNumberValue ( ) < (number)_nValue ; }
    inline  bool        AIVariable::operator <              ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) < _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  bool        AIVariable::operator <              ( const AIVariables< _iCount > &_oValue ) { return *this < (const AIVariable &)_oValue ; }

    inline  bool                    operator <              ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue < _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <              ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue < _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <              ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue < _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <              ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue < _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <              ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue < _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <              ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue < _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <              ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue < _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <              ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue < _vVariable.GetNumberValue ( ) ; }

    inline  bool        AIVariable::operator >              ( const int8                    _iValue ) const { return GetNumberValue ( ) > (number)_iValue ; }
    inline  bool        AIVariable::operator >              ( const uint8                   _iValue ) const { return GetNumberValue ( ) > (number)_iValue ; }
    inline  bool        AIVariable::operator >              ( const int16                   _iValue ) const { return GetNumberValue ( ) > (number)_iValue ; }
    inline  bool        AIVariable::operator >              ( const uint16                  _iValue ) const { return GetNumberValue ( ) > (number)_iValue ; }
    inline  bool        AIVariable::operator >              ( const int32                   _iValue ) const { return GetNumberValue ( ) > (number)_iValue ; }
    inline  bool        AIVariable::operator >              ( const uint32                  _iValue ) const { return GetNumberValue ( ) > (number)_iValue ; }
    inline  bool        AIVariable::operator >              ( const float32                 _nValue ) const { return GetNumberValue ( ) > (number)_nValue ; }
    inline  bool        AIVariable::operator >              ( const float64                 _nValue ) const { return GetNumberValue ( ) > (number)_nValue ; }
    inline  bool        AIVariable::operator >              ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) > _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  bool        AIVariable::operator >              ( const AIVariables< _iCount > &_oValue ) { return *this > (const AIVariable &)_oValue ; }

    inline  bool                    operator >              ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue > _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >              ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue > _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >              ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue > _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >              ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue > _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >              ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue > _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >              ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue > _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >              ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue > _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >              ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue > _vVariable.GetNumberValue ( ) ; }

    inline  bool        AIVariable::operator <=             ( const int8                    _iValue ) const { return GetNumberValue ( ) <= (number)_iValue ; }
    inline  bool        AIVariable::operator <=             ( const uint8                   _iValue ) const { return GetNumberValue ( ) <= (number)_iValue ; }
    inline  bool        AIVariable::operator <=             ( const int16                   _iValue ) const { return GetNumberValue ( ) <= (number)_iValue ; }
    inline  bool        AIVariable::operator <=             ( const uint16                  _iValue ) const { return GetNumberValue ( ) <= (number)_iValue ; }
    inline  bool        AIVariable::operator <=             ( const int32                   _iValue ) const { return GetNumberValue ( ) <= (number)_iValue ; }
    inline  bool        AIVariable::operator <=             ( const uint32                  _iValue ) const { return GetNumberValue ( ) <= (number)_iValue ; }
    inline  bool        AIVariable::operator <=             ( const float32                 _nValue ) const { return GetNumberValue ( ) <= (number)_nValue ; }
    inline  bool        AIVariable::operator <=             ( const float64                 _nValue ) const { return GetNumberValue ( ) <= (number)_nValue ; }
    inline  bool        AIVariable::operator <=             ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) <= _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  bool        AIVariable::operator <=             ( const AIVariables< _iCount > &_oValue ) { return *this <= (const AIVariable &)_oValue ; }

    inline  bool                    operator <=             ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue <= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <=             ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue <= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <=             ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue <= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <=             ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue <= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <=             ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue <= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <=             ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue <= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <=             ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue <= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator <=             ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue <= _vVariable.GetNumberValue ( ) ; }

    inline  bool        AIVariable::operator >=             ( const int8                    _iValue ) const { return GetNumberValue ( ) >= (number)_iValue ; }
    inline  bool        AIVariable::operator >=             ( const uint8                   _iValue ) const { return GetNumberValue ( ) >= (number)_iValue ; }
    inline  bool        AIVariable::operator >=             ( const int16                   _iValue ) const { return GetNumberValue ( ) >= (number)_iValue ; }
    inline  bool        AIVariable::operator >=             ( const uint16                  _iValue ) const { return GetNumberValue ( ) >= (number)_iValue ; }
    inline  bool        AIVariable::operator >=             ( const int32                   _iValue ) const { return GetNumberValue ( ) >= (number)_iValue ; }
    inline  bool        AIVariable::operator >=             ( const uint32                  _iValue ) const { return GetNumberValue ( ) >= (number)_iValue ; }
    inline  bool        AIVariable::operator >=             ( const float32                 _nValue ) const { return GetNumberValue ( ) >= (number)_nValue ; }
    inline  bool        AIVariable::operator >=             ( const float64                 _nValue ) const { return GetNumberValue ( ) >= (number)_nValue ; }
    inline  bool        AIVariable::operator >=             ( const AIVariable             &_vValue ) const { return GetNumberValue ( ) >= _vValue.GetNumberValue ( ) ; }
    template< uint8 _iCount >
    inline  bool        AIVariable::operator >=             ( const AIVariables< _iCount > &_oValue ) { return *this >= (const AIVariable &)_oValue ; }

    inline  bool                    operator >=             ( const int8                    _iValue, const AIVariable &_vVariable ) { return (number)_iValue >= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >=             ( const uint8                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue >= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >=             ( const int16                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue >= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >=             ( const uint16                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue >= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >=             ( const int32                   _iValue, const AIVariable &_vVariable ) { return (number)_iValue >= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >=             ( const uint32                  _iValue, const AIVariable &_vVariable ) { return (number)_iValue >= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >=             ( const float32                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue >= _vVariable.GetNumberValue ( ) ; }
    inline  bool                    operator >=             ( const float64                 _nValue, const AIVariable &_vVariable ) { return (number)_nValue >= _vVariable.GetNumberValue ( ) ; }

    inline  bool        AIVariable::operator ==             ( const int8                    _iValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_iValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const uint8                   _iValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_iValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const int16                   _iValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_iValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const uint16                  _iValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_iValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const int32                   _iValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_iValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const uint32                  _iValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_iValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const float32                 _nValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_nValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const float64                 _nValue ) const { return IsNumber  ( ) ? ( GetNumberValue  ( ) == (number)_nValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const bool                    _bValue ) const { return IsBoolean ( ) ? ( GetBooleanValue ( ) ==         _bValue ) : false ; }
    inline  bool        AIVariable::operator ==             ( const char                   *_pValue ) const { return CanConvertToString ( ) ? ( S3DX_STREQ( GetStringValue ( ), _pValue ) ) : false ; }
    inline  bool        AIVariable::operator ==             ( const AIVariable             &_vValue ) const { return ( iType == _vValue.iType ) && ( IsString ( ) ? ( S3DX_STREQ( GetStringValue ( ), _vValue.GetStringValue ( ) ) ) : ( iUnknownValue == _vValue.iUnknownValue ) ) ; }
    template< uint8 _iCount >
    inline  bool        AIVariable::operator ==             ( const AIVariables< _iCount > &_oValue ) { return *this == (const AIVariable &)_oValue ; }

    inline  bool                    operator ==             ( const int8                    _iValue, const AIVariable &_vVariable ) { return _vVariable == _iValue ; }
    inline  bool                    operator ==             ( const uint8                   _iValue, const AIVariable &_vVariable ) { return _vVariable == _iValue ; }
    inline  bool                    operator ==             ( const int16                   _iValue, const AIVariable &_vVariable ) { return _vVariable == _iValue ; }
    inline  bool                    operator ==             ( const uint16                  _iValue, const AIVariable &_vVariable ) { return _vVariable == _iValue ; }
    inline  bool                    operator ==             ( const int32                   _iValue, const AIVariable &_vVariable ) { return _vVariable == _iValue ; }
    inline  bool                    operator ==             ( const uint32                  _iValue, const AIVariable &_vVariable ) { return _vVariable == _iValue ; }
    inline  bool                    operator ==             ( const float32                 _nValue, const AIVariable &_vVariable ) { return _vVariable == _nValue ; }
    inline  bool                    operator ==             ( const float64                 _nValue, const AIVariable &_vVariable ) { return _vVariable == _nValue ; }
    inline  bool                    operator ==             ( const bool                    _bValue, const AIVariable &_vVariable ) { return _vVariable == _bValue ; }
    inline  bool                    operator ==             ( const char                   *_pValue, const AIVariable &_vVariable ) { return _vVariable == _pValue ; }

    inline  bool        AIVariable::operator !=             ( const int8                    _iValue ) const { return ! ( *this == _iValue ) ; }
    inline  bool        AIVariable::operator !=             ( const uint8                   _iValue ) const { return ! ( *this == _iValue ) ; }
    inline  bool        AIVariable::operator !=             ( const int16                   _iValue ) const { return ! ( *this == _iValue ) ; }
    inline  bool        AIVariable::operator !=             ( const uint16                  _iValue ) const { return ! ( *this == _iValue ) ; }
    inline  bool        AIVariable::operator !=             ( const int32                   _iValue ) const { return ! ( *this == _iValue ) ; }
    inline  bool        AIVariable::operator !=             ( const uint32                  _iValue ) const { return ! ( *this == _iValue ) ; }
    inline  bool        AIVariable::operator !=             ( const float32                 _nValue ) const { return ! ( *this == _nValue ) ; }
    inline  bool        AIVariable::operator !=             ( const float64                 _nValue ) const { return ! ( *this == _nValue ) ; }
    inline  bool        AIVariable::operator !=             ( const bool                    _bValue ) const { return ! ( *this == _bValue ) ; }
    inline  bool        AIVariable::operator !=             ( const char                   *_pValue ) const { return ! ( *this == _pValue ) ; }
    inline  bool        AIVariable::operator !=             ( const AIVariable             &_vValue ) const { return ! ( *this == _vValue ) ; }
    template< uint8 _iCount >
    inline  bool        AIVariable::operator !=             ( const AIVariables< _iCount > &_oValue ) { return *this != (const AIVariable &)_oValue ; }

    inline  bool                    operator !=             ( const int8                    _iValue, const AIVariable &_vVariable ) { return _vVariable != _iValue ; }
    inline  bool                    operator !=             ( const uint8                   _iValue, const AIVariable &_vVariable ) { return _vVariable != _iValue ; }
    inline  bool                    operator !=             ( const int16                   _iValue, const AIVariable &_vVariable ) { return _vVariable != _iValue ; }
    inline  bool                    operator !=             ( const uint16                  _iValue, const AIVariable &_vVariable ) { return _vVariable != _iValue ; }
    inline  bool                    operator !=             ( const int32                   _iValue, const AIVariable &_vVariable ) { return _vVariable != _iValue ; }
    inline  bool                    operator !=             ( const uint32                  _iValue, const AIVariable &_vVariable ) { return _vVariable != _iValue ; }
    inline  bool                    operator !=             ( const float32                 _nValue, const AIVariable &_vVariable ) { return _vVariable != _nValue ; }
    inline  bool                    operator !=             ( const float64                 _nValue, const AIVariable &_vVariable ) { return _vVariable != _nValue ; }
    inline  bool                    operator !=             ( const bool                    _bValue, const AIVariable &_vVariable ) { return _vVariable != _bValue ; }
    inline  bool                    operator !=             ( const char                   *_pValue, const AIVariable &_vVariable ) { return _vVariable != _pValue ; }

    //-------------------------------------------------------------------------
    //  "Special" operators
    //-------------------------------------------------------------------------

    inline  AIVariable              AIVariable::operator << ( const int8        _iValue ) const { return Concat( *this, AIVariable( _iValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const uint8       _iValue ) const { return Concat( *this, AIVariable( _iValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const int16       _iValue ) const { return Concat( *this, AIVariable( _iValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const uint16      _iValue ) const { return Concat( *this, AIVariable( _iValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const int32       _iValue ) const { return Concat( *this, AIVariable( _iValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const uint32      _iValue ) const { return Concat( *this, AIVariable( _iValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const float32     _nValue ) const { return Concat( *this, AIVariable( _nValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const float64     _nValue ) const { return Concat( *this, AIVariable( _nValue ) ) ; }
    inline  AIVariable              AIVariable::operator << ( const AIVariable &_vValue ) const { return Concat( *this,             _vValue   ) ; }
    inline  AIVariable                          operator << ( const char       *_pValue,
                                                              const AIVariable &_vValue )       { return AIVariable::Concat( _pValue, _vValue ) ; }

    // DEPRECATED. Code kept for emergency cases ;)
    /*
    inline  AIVariable              AIVariable::operator &  ( const int8        _iValue ) const { return bool(*this) ? AIVariable( _iValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const uint8       _iValue ) const { return bool(*this) ? AIVariable( _iValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const int16       _iValue ) const { return bool(*this) ? AIVariable( _iValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const uint16      _iValue ) const { return bool(*this) ? AIVariable( _iValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const int32       _iValue ) const { return bool(*this) ? AIVariable( _iValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const uint32      _iValue ) const { return bool(*this) ? AIVariable( _iValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const number      _nValue ) const { return bool(*this) ? AIVariable( _nValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const bool        _bValue ) const { return bool(*this) ? AIVariable( _bValue ) : *this ; }
    inline  AIVariable              AIVariable::operator &  ( const AIVariable &_vValue ) const { return bool(*this) ?             _vValue   : *this ; }

    inline  AIVariable              AIVariable::operator |  ( const int8        _iValue ) const { return bool(*this) ? *this : AIVariable( _iValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const uint8       _iValue ) const { return bool(*this) ? *this : AIVariable( _iValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const int16       _iValue ) const { return bool(*this) ? *this : AIVariable( _iValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const uint16      _iValue ) const { return bool(*this) ? *this : AIVariable( _iValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const int32       _iValue ) const { return bool(*this) ? *this : AIVariable( _iValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const uint32      _iValue ) const { return bool(*this) ? *this : AIVariable( _iValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const number      _nValue ) const { return bool(*this) ? *this : AIVariable( _nValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const bool        _bValue ) const { return bool(*this) ? *this : AIVariable( _bValue ) ; }
    inline  AIVariable              AIVariable::operator |  ( const AIVariable &_vValue ) const { return bool(*this) ? *this :             _vValue   ; }
    */

    //-------------------------------------------------------------------------
    // "nil" constant definition
    //
    #ifdef nil
    #undef nil
    #endif

    const AIVariable nil = AIVariable ( ) ;

    //-------------------------------------------------------------------------
    // Macro to call when developing a plugin that needs string operations.
    // Note that this implementation is trivial but sufficient in most if not
    // all cases. The main advantage is that there is nothing faster :)
    // Increase __size value if you encounter problems while manipulating long
    // strings. A value of 524288 should largely be enough.
    //
    #if (defined S3DX_DLL) || (defined S3DX_DISCRETE_STRING_POOL)
        #define S3DX_IMPLEMENT_AIVARIABLE_STRING_POOL( __size )                                 \
                                                                                                \
            static char                  __aStringPool [__size] = "" ;                          \
            S3DX::uint32    S3DX::AIVariable::iStringPoolCursor = 0 ;                           \
            S3DX::uint32    S3DX::AIVariable::iStringPoolSize   = __size ;                      \
            char           *S3DX::AIVariable::pStringPool       = __aStringPool ;               \
                                                                                                \
            char *S3DX::AIVariable::GetStringPoolBuffer ( const S3DX::uint32 _iSize )           \
            {                                                                                   \
                if ( iStringPoolCursor + _iSize > iStringPoolSize )                             \
                {                                                                               \
                    if ( _iSize > iStringPoolSize )                                             \
                    {                                                                           \
                        return NULL ;                                                           \
                    }                                                                           \
                    iStringPoolCursor = 0 ;                                                     \
                }                                                                               \
                char  *pRet = pStringPool + iStringPoolCursor ; iStringPoolCursor += _iSize ;   \
                return pRet ;                                                                   \
            }
    #else
        #define S3DX_IMPLEMENT_AIVARIABLE_STRING_POOL( __size )
    #endif

    //-------------------------------------------------------------------------
    // Macros defining the Lua compliant 'and' and 'or' operators.
    // They are provided for C++ AIModels, and cannot be used in dynamically linked plug-ins,
    // unless you define S3DX::__lua_and_helper and/or S3DX::__lua_or_helper in your code.
    // Anyways it is better to use C++ '&&' and '||' operators whenever possible for speed.
    //
	extern  S3DX_API S3DX::AIVariable __lua_and_helper ;
	extern  S3DX_API S3DX::AIVariable __lua_or_helper  ;
    #define S3DX_LUA_AND( __a__, __b__ ) ((S3DX::__lua_and_helper=(__a__)).GetBooleanValue()?S3DX::AIVariable(__b__):S3DX::__lua_and_helper)
	#define S3DX_LUA_OR(  __a__, __b__ ) ((S3DX::__lua_or_helper =(__a__)).GetBooleanValue()?S3DX::__lua_or_helper:S3DX::AIVariable(__b__))
    #define S3DX_CPP_AND( __a__, __b__ ) ((S3DX::AIVariable(__a__)).GetBooleanValue() && (S3DX::AIVariable(__b__)).GetBooleanValue())
    #define S3DX_CPP_OR( __a__,  __b__ ) ((S3DX::AIVariable(__a__)).GetBooleanValue() || (S3DX::AIVariable(__b__)).GetBooleanValue())
    #define S3DX_DEFAULT_AND    S3DX_LUA_AND
	#define S3DX_DEFAULT_OR     S3DX_LUA_OR
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
