#pragma once
#include "../Common/StringUtils.h"
#include "Basic.h"
#include "Utils.h"
#include "../Common/ATLDefine.h"
#include "RtfDefine.h"

#define MERGE_PROPERTY(propName, propObj)\
	if( PROP_DEF != ##propObj##.##propName## )\
		propName = ##propObj##.##propName##;

#define MERGE_PROPERTY_DEF(propName, propObj, defval)\
	if( defval != ##propObj##.##propName## )\
		propName = ##propObj##.##propName##;

#define DEFAULT_PROPERTY(propName)\
		propName= PROP_DEF;

#define DEFAULT_PROPERTY_DEF(propName, defval)\
		propName = defval;

#define RENDER_OOX_BOOL( prop, sResult, sName)\
		if( 0 == prop )\
			sResult.AppendFormat( _T("<%s w:val=\"false\"/>"), sName );\
		else if(  PROP_DEF != prop  )\
			sResult.AppendFormat( _T("<%s w:val=\"true\"/>"), sName );

#define RENDER_OOX_BOOL_ATTRIBUTE( prop, sResult, sName)\
		if( 0 == prop )\
			sResult.AppendFormat( _T(" %s=\"0\""), sName );\
		else if(  PROP_DEF != prop  )\
			sResult.AppendFormat( _T(" %s=\"1\""), sName );

#define RENDER_OOX_INT( prop, sResult, sName)\
		if( PROP_DEF != prop )\
			sResult.AppendFormat( _T("<%s w:val=\"%d\"/>"), sName, prop );

#define RENDER_OOX_INT_ATTRIBUTE( prop, sResult, sName)\
		if( PROP_DEF != prop )\
		sResult.AppendFormat( _T(" %s=\"%d\""), sName, prop );

#define RENDER_OOX_STRING( prop, sResult, sName)\
		if( false == prop.IsEmpty() )\
			sResult.AppendFormat( _T("<%s w:val=\"%s\"/>"), sName, prop );


#define RENDER_RTF_BOOL( prop, sResult, sName)\
		if( 0 == prop )\
			sResult.AppendFormat( _T("\\%s0"), sName );\
		else if(  PROP_DEF != prop  )\
			sResult.AppendFormat( _T("\\%s"), sName );

#define RENDER_RTF_INT( prop, sResult, sName)\
		if( PROP_DEF != prop )\
			sResult.AppendFormat( _T("\\%s%d"), sName, prop );



class RtfFont : public IRenderableProperty
{
public: typedef enum {ft_none,ft_flomajor , ft_fhimajor ,ft_fdbmajor ,ft_fbimajor ,ft_flominor ,ft_fhiminor ,ft_fdbminor ,ft_fbiminor}FontTheme;
public: typedef enum {ff_none, ff_fnil ,ff_froman ,ff_fswiss ,ff_fmodern ,ff_fscript ,ff_fdecor ,ff_ftech ,ff_fbidi} FontFamily;
public: FontTheme m_eFontTheme;
public: FontFamily m_eFontFamily;
public: CString m_sPanose;
public: int m_nID;
public: CString m_sName;
public: CString m_sAltName;
public: int m_nCharset;
public: int m_nCodePage;
public: int m_nPitch;

public: RtfFont()
		{
			SetDefault();
		}
public: int GetType()
		{
			return TYPE_RTF_FONT;
		}
public: bool operator==( const RtfFont& oFont)
		{
			return m_eFontTheme == oFont.m_eFontTheme && m_eFontFamily == oFont.m_eFontFamily && 
					m_sPanose == oFont.m_sPanose && m_nID == oFont.m_nID && 
					m_sName == oFont.m_sName && m_sAltName == oFont.m_sAltName && 
					m_nCharset == oFont.m_nCharset && m_nCodePage == oFont.m_nCodePage && 
					m_nPitch == oFont.m_nPitch;
		}
public: bool IsValid()
		{
			//return PROP_DEF != m_nID && _T("") != m_sName && ff_fnil == m_eFontFamily;
			//return PROP_DEF != m_nID && _T("") != m_sName; //wordpad не всегда пишет m_sName
			return PROP_DEF != m_nID;
		}
public: void SetDefaultRtf()
		{
			SetDefault();
			m_nPitch = 0;
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY_DEF( m_eFontTheme, ft_none )
			DEFAULT_PROPERTY_DEF( m_eFontFamily, ff_fnil )
			DEFAULT_PROPERTY_DEF( m_sPanose, _T("") )
			DEFAULT_PROPERTY( m_nID )
			DEFAULT_PROPERTY_DEF( m_sName, _T("") )
			DEFAULT_PROPERTY_DEF( m_sAltName, _T("") )
			DEFAULT_PROPERTY( m_nCharset )
			DEFAULT_PROPERTY( m_nCodePage )
			DEFAULT_PROPERTY_DEF( m_nPitch, 2 )
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfColor : public IRenderableProperty
{
public: typedef enum {TC_NONE,cmaindarkone ,cmainlightone ,cmaindarktwo ,cmainlighttwo ,caccentone ,caccenttwo ,caccentthree ,caccentfour ,caccentfive ,caccentsix ,chyperlink ,cfollowedhyperlink ,cbackgroundone ,ctextone ,cbackgroundtwo ,ctexttwo} ThemeColor;
public: ThemeColor m_eTheme;
public: byte m_byteRed;
public: byte m_byteGreen;
public: byte m_byteBlue;
public: byte m_byteTint;
public: byte m_byteShade;
public: RtfColor()
	{
		SetDefault();
	}
public: RtfColor(int nHex)
	{
		SetHEX( nHex );
	}
public: RtfColor(byte r, byte g, byte b)
	{
		SetRGB( r, g, b );
	}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			m_byteRed = 0;
			m_byteGreen = 0;
			m_byteBlue = 0;
			m_byteTint = 255;
			m_byteShade = 0;
			m_eTheme = TC_NONE;
		}
public: byte GetR()
		{
			byte byteRed = SetShade( m_byteRed );
			byteRed = SetTint( byteRed );
			return byteRed;
		}
public: byte GetG()
		{
			byte byteGreen = SetShade( m_byteGreen );
			byteGreen = SetTint( byteGreen );
			return byteGreen;
		}
public: byte GetB()
		{
			byte byteBlue = SetShade( m_byteBlue );
			byteBlue = SetTint( byteBlue );
			return byteBlue;
		}
public: bool operator==(const RtfColor& oColor)
	{
		return  m_byteRed == oColor.m_byteRed && m_byteGreen == oColor.m_byteGreen && m_byteBlue == oColor.m_byteBlue &&
				m_byteTint == oColor.m_byteTint && m_byteShade == oColor.m_byteShade && m_eTheme == oColor.m_eTheme;
	}
public: void SetHEX(int color)
	{
		SetDefault();
		m_byteRed= (color&0xFF0000) >>16;
		m_byteGreen = (color&0xFF00) >>4;
		m_byteBlue =  (color&0xFF);
	}
public: void SetRGB(byte red, byte green, byte blue)
	{
		SetDefault();
		m_byteRed = red;
		m_byteGreen = green;
		m_byteBlue = blue;
	}
public: void SetHSL(double nHue, double nSat, double nLum)
		{
      //// Given H,S,L in range of 0-1
      //// Returns a Color (RGB struct) in range of 0-255
      //public static ColorRGB HSL2RGB(double nHue, double nSat, double nLum)
            double v;
            double r,g,b;
            r = nLum;   // default to gray
            g = nLum;
            b = nLum;
            v = (nLum <= 0.5) ? (nLum * (1.0 + nSat)) : (nLum + nSat - nLum * nSat);

            if (v > 0)
			{
                  double m;
                  double sv;
                  int sextant;
                  double fract, vsf, mid1, mid2;

                  m = nLum + nLum - v;
                  sv = (v - m ) / v;
                  nHue *= 6.0;
                  sextant = (int)nHue;
                  fract = nHue - sextant;
                  vsf = v * sv * fract;
                  mid1 = m + vsf;
                  mid2 = v - vsf;
                  switch (sextant)
                  {
                        case 0:
                              r = v;
                              g = mid1;
                              b = m;
                              break;
                        case 1:
                              r = mid2;
                              g = v;
                              b = m;
                              break;
                        case 2:
                              r = m;
                              g = v;
                              b = mid1;
                              break;
                        case 3:
                              r = m;
                              g = mid2;
                              b = v;
                              break;
                        case 4:
                              r = mid1;
                              g = m;
                              b = v;
                              break;
                        case 5:
                              r = v;
                              g = m;
                              b = mid2;
                              break;
                  }
            }
			m_byteRed = (byte)(r * 255.0f);
            m_byteGreen = (byte)(g * 255.0f);
            m_byteBlue = (byte)(b * 255.0f);
		m_byteRed = (byte)(r * 255);
		m_byteGreen = (byte)(g * 255);
		m_byteBlue = (byte)(b * 255);

      }
public: void SetRGBPercent(int nRedPer, int nGreenPer, int nBluePer)
		{
			m_byteRed = (BYTE)(nRedPer * 255 / 100);
			m_byteGreen = (BYTE)(nGreenPer * 255/ 100);
			m_byteBlue = (BYTE)(nBluePer * 255 / 100);
		}
public: void SetHEXString(CString hex)
	{
		if( _T("auto") != hex )
		{
			SetDefault();
			int color = Strings::ToColor(hex);
			m_byteRed = (color&0xFF);
			m_byteGreen = (color&0xFF00) >>8;
			m_byteBlue =  (color&0xFF0000) >>16;
		}
		else
			SetDefault();
	}
public: CString ToHexColor()
	{
		byte byteRed = SetShade( m_byteRed );
		byteRed = SetTint( byteRed );
		CString sRed;
		if( byteRed < 0x10 )
			sRed.AppendFormat( _T("0%x"), byteRed );
		else
			sRed.AppendFormat( _T("%x"), byteRed );
		byte byteGreen = SetShade( m_byteGreen );
		byteGreen = SetTint( byteGreen );
		CString sGreen;
		if( byteGreen < 0x10 )
			sGreen.AppendFormat( _T("0%x"), byteGreen );
		else
			sGreen.AppendFormat( _T("%x"), byteGreen );
		byte byteBlue = SetShade( m_byteBlue );
		byteBlue = SetTint( byteBlue );
		CString sBlue;
		if( byteBlue < 0x10 )
			sBlue.AppendFormat( _T("0%x"), byteBlue );
		else
			sBlue.AppendFormat( _T("%x"), byteBlue );
		return sRed + sGreen + sBlue;
	}
public: int ToInt()const
	{
		CString sResult;
		byte byteRed = SetShade( m_byteRed );
		byteRed = SetTint( byteRed );
		byte byteGreen = SetShade( m_byteGreen );
		byteGreen = SetTint( byteGreen );
		byte byteBlue = SetShade( m_byteBlue );
		byteBlue = SetTint( byteBlue );

		int nColor = (byteRed << 16) | (byteGreen << 8) | byteBlue;
		return nColor;
	}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
public: byte SetShade(byte bColor)const
		{
			//return (byte)( ( 1.0 - m_byteShade / 255 ) * bColor );
			return bColor;
		}
public: byte SetTint(byte bColor)const
		 {
			//return (byte)( ( 1.0 - m_byteTint / 255 ) * ( 255 - bColor ) + bColor );
			return bColor;
		 }
private: CString WriteOOXAttribute( CString sParam )
		 {
			 CString sResult;
				if( m_eTheme == TC_NONE )
					if( _T("") == sParam )
						sResult.AppendFormat(_T("color = \"%s\""),ToHexColor());
					else if( _T("Fill") == sParam )
						sResult.AppendFormat(_T("fill = \"%s\""),ToHexColor());
				else
				{
					CString sTheme;
					if( true == GetStringByTheme( sTheme, m_eTheme ) )
					{
						sResult.AppendFormat(_T("theme%sColor = \"%s\" theme%sShade = \"%d\" theme%sTint = \"%d\""),sParam,sTheme,sParam,m_byteShade ,sParam,m_byteTint);
					}
				}
			return sResult;
		 }
public: static bool GetHighlightByColor( RtfColor oOutputColor,CString& oStr ) //todo
		{
			if( oOutputColor ==  RtfColor(0x000000) ) {oStr = _T("black");return true;}
			else if( oOutputColor ==  RtfColor(0x0000FF) ) {oStr = _T("blue");return true;}
			else if( oOutputColor ==  RtfColor(0x00FFFF) ) {oStr = _T("cyan");return true;}
			else if( oOutputColor ==  RtfColor(0x00008B) ) {oStr = _T("darkBlue");return true;}
			else if( oOutputColor ==  RtfColor(0x008B8B) ) {oStr = _T("darkCyan");return true;}
			else if( oOutputColor ==  RtfColor(0xA9A9A9) ) {oStr = _T("darkGray");return true;}
			else if( oOutputColor ==  RtfColor(0x006400) ) {oStr = _T("darkGreen");return true;}
			else if( oOutputColor ==  RtfColor(0x800080) ) {oStr = _T("darkMagenta");return true;}
			else if( oOutputColor ==  RtfColor(0x8B0000) ) {oStr = _T("darkRed");return true;}
			else if( oOutputColor ==  RtfColor(0x808000) ) {oStr = _T("darkYellow");return true;}
			else if( oOutputColor ==  RtfColor(0x00FF00) ) {oStr = _T("green");return true;}
			else if( oOutputColor ==  RtfColor(0xD3D3D3) ) {oStr = _T("lightGray");return true;}
			else if( oOutputColor ==  RtfColor(0xFF00FF) ) {oStr = _T("magenta");return true;}
			else if( oOutputColor ==  RtfColor(0xFF0000) ) {oStr = _T("red");return true;}
			else if( oOutputColor ==  RtfColor(0xFFFFFF) ) {oStr = _T("white");return true;}
			else if( oOutputColor ==  RtfColor(0xFFFF00) ) {oStr = _T("yellow");return true;}
			return false;
		}
public: static RtfColor GetColorByPreset( CString oStr )
		{
			if( oStr == _T("aliceBlue") ) return RtfColor(240,248,255);
			else if( oStr == _T("aniqueWhite") ) return RtfColor(250,235,215);
			else if( oStr == _T("aqua") ) return RtfColor(0,255,255);
			else if( oStr == _T("aquamarine") ) return RtfColor(127,255,212);
			else if( oStr == _T("azure") ) return RtfColor(240,255,255);
			else if( oStr == _T("beige") ) return RtfColor(245,245,220);
			else if( oStr == _T("bisque") ) return RtfColor(255,228,196);
			else if( oStr == _T("black") ) return RtfColor(0,0,0);
			else if( oStr == _T("blanchedAlmond") ) return RtfColor(255,235,205);
			else if( oStr == _T("blueViolet") ) return RtfColor(138,43,226);
			else if( oStr == _T("brown") ) return RtfColor(165,42,42);
			else if( oStr == _T("burlyWood") ) return RtfColor(222,184,135);

			else if( oStr == _T("cyan") ) return RtfColor(0,255,255);
			else if( oStr == _T("gold") ) return RtfColor(255,215,0);
			else if( oStr == _T("green") ) return RtfColor(0,128,0);
			else if( oStr == _T("grey") ) return RtfColor(128,128,128);
			else if( oStr == _T("red") ) return RtfColor(255,0,0);
			else if( oStr == _T("yellow") ) return RtfColor(255,255,0);

			return RtfColor(0,0,0);
		}
public: static CString GetPresetByColor( RtfColor oCol ) //стр. 3320
		{
			if( oCol == RtfColor(240,248,255)) return _T("aliceBlue");
			else if( oCol ==  RtfColor(250,235,215)) return _T("aniqueWhite");
			else if( oCol ==  RtfColor(0,255,255)) return _T("aqua");
			else if( oCol ==  RtfColor(127,255,212)) return _T("aquamarine");
			else if( oCol ==  RtfColor(240,255,255)) return _T("azure");
			else if( oCol ==  RtfColor(245,245,220)) return _T("beige");
			else if( oCol ==  RtfColor(255,228,196)) return _T("bisque");
			else if( oCol ==  RtfColor(0,0,0)) return _T("black");
			else if( oCol ==  RtfColor(255,235,205)) return _T("blanchedAlmond");
			else if( oCol ==  RtfColor(138,43,226)) return _T("blueViolet");
			else if( oCol ==  RtfColor(165,42,42)) return _T("brown");
			else if( oCol ==  RtfColor(222,184,135)) return _T("burlyWood");

			else if( oCol ==  RtfColor(0,255,255)) return _T("cyan");
			else if( oCol ==  RtfColor(255,215,0)) return _T("gold");
			else if( oCol ==  RtfColor(0,128,0)) return _T("green");
			else if( oCol ==  RtfColor(128,128,128)) return _T("grey");
			else if( oCol ==  RtfColor(255,0,0)) return _T("red");
			else if( oCol ==  RtfColor(255,255,0)) return _T("yellow");

			return _T("black");
		}
public: static bool GetThemeByString( CString sTheme ,ThemeColor & oOutTheme )
		{
			if( sTheme == _T("accent1") )
			{oOutTheme = caccentone; return true;}
			else if( sTheme ==  _T("accent2") )
				{oOutTheme = caccenttwo;  return true;}
			else if( sTheme == _T("accent3") )
				{oOutTheme = caccentthree;  return true;}
			else if( sTheme == _T("accent4"))
				{oOutTheme = caccentfour;  return true;}
			else if( sTheme == _T("accent5") )
				{oOutTheme = caccentfive;  return true;}
			else if( sTheme == _T("accent6") )
				{oOutTheme = caccentsix;  return true;}
			else if( sTheme == _T("bg1") )
				{oOutTheme = cbackgroundone;  return true;}
			else if( sTheme == _T("bg2"))
				{oOutTheme = cbackgroundtwo;  return true;}
			else if( sTheme == _T("dk1"))
				{oOutTheme = cmaindarkone;  return true;}
			else if( sTheme == _T("dk2"))
				{oOutTheme = cmaindarktwo;  return true;}
			else if( sTheme == _T("folHlink") )
				{oOutTheme = cfollowedhyperlink;  return true;}
			else if( sTheme == _T("hlink") )
				{oOutTheme = chyperlink;  return true;}
			else if( sTheme == _T("lt1") )
				{oOutTheme = cmainlightone;  return true;}
			else if( sTheme == _T("lt2") )
				{oOutTheme = cmainlighttwo;  return true;}
			else if( sTheme == _T("phClr") )
				{oOutTheme = cmainlighttwo;  return true;}
			else if( sTheme ==  _T("tx1") )
				{oOutTheme = ctextone;  return true;}
			else if( sTheme =  _T("tx2") )
				{oOutTheme = ctexttwo;  return true;}
			return false;
		}
public: static bool GetStringByTheme( CString sTheme , ThemeColor& oOutTheme )
		{
			if( _T("accent1") == sTheme )
			{oOutTheme = caccentone; return true;}
			else if( _T("accent2") == sTheme )
				{oOutTheme =  caccenttwo; return true;}
			else if( _T("accent3") == sTheme )
				{oOutTheme =  caccentthree; return true;}
			else if( _T("accent4") == sTheme )
				{oOutTheme =  caccentfour; return true;}
			else if( _T("accent5") == sTheme )
				{oOutTheme =  caccentfive; return true;}
			else if( _T("accent6") == sTheme )
				{oOutTheme =  caccentsix; return true;}
			else if( _T("bg1") == sTheme )
				{oOutTheme =  cbackgroundone; return true;}
			else if( _T("bg2") == sTheme )
				{oOutTheme =  cbackgroundtwo; return true;}
			else if( _T("dk1") == sTheme )
				{oOutTheme =  cmaindarkone; return true;}
			else if( _T("dk2") == sTheme )
				{oOutTheme =  cmaindarktwo; return true;}
			else if( _T("folHlink") == sTheme )
				{oOutTheme =  cfollowedhyperlink; return true;}
			else if( _T("hlink") == sTheme )
				{oOutTheme =  chyperlink; return true;}
			else if( _T("lt1") == sTheme )
				{oOutTheme =  cmainlightone; return true;}
			else if( _T("lt2") == sTheme )
				{oOutTheme =  cmainlighttwo; return true;}
			else if( _T("phClr") == sTheme )
				{oOutTheme =  cmainlighttwo; return true;}
			else if( _T("tx1") == sTheme )
				{oOutTheme =  ctextone; return true;}
			else if( _T("tx2") == sTheme )
				{oOutTheme =  ctexttwo; return true;}
			return false;
		}
public: CString GetHighLight()
		{
			//CString sBlack = _T("000000");
			//CString blue = _T("0000FF");
			//CString cyan = _T("00FFFF");
			//CString darkBlue = _T("00008B");
			//CString darkCyan = _T("008B8B");
			//CString darkGray = _T("A9A9A9");
			//CString darkGreen = _T("006400");
			//CString darkMagenta = _T("800080");
			//CString darkRed = _T("8B0000");
			//CString darkYellow = _T("808000");
			//CString green = _T("00FF00");
			//CString lightGray = _T("D3D3D3");
			//CString magenta = _T("FF00FF");
			//CString red = _T("FF0000");
			//CString white = _T("FFFFFF");
			//CString yellow = _T("FFFF00");

			CAtlArray< RtfColor > sColors;
			//sColors.Add( RtfColor(sBlack) );
			//sColors.Add( RtfColor(blue) );
			//sColors.Add( RtfColor(cyan) );
			//sColors.Add( RtfColor(darkBlue) );
			//sColors.Add( RtfColor(darkCyan) );
			//sColors.Add( RtfColor(darkGray) );
			//sColors.Add( RtfColor(darkMagenta) );
			//sColors.Add( RtfColor(darkRed) );
			//sColors.Add( RtfColor(darkYellow) );
			//sColors.Add( RtfColor(green) );
			//sColors.Add( RtfColor(lightGray) );
			//sColors.Add( RtfColor(magenta) );
			//sColors.Add( RtfColor(red) );
			//sColors.Add( RtfColor(white) );
			//sColors.Add( RtfColor(yellow) );

			sColors.Add( RtfColor( 0x000000 ) );
			sColors.Add( RtfColor( 0x0000FF ) );
			sColors.Add( RtfColor( 0x00FFFF ) );
			sColors.Add( RtfColor( 0x00008B ) );
			sColors.Add( RtfColor( 0x008B8B ) );
			sColors.Add( RtfColor( 0xA9A9A9 ) );
			sColors.Add( RtfColor( 0x006400 ) );
			sColors.Add( RtfColor( 0x800080 ) );
			sColors.Add( RtfColor( 0x8B0000 ) );
			sColors.Add( RtfColor( 0x808000 ) );
			sColors.Add( RtfColor( 0x00FF00 ) );
			sColors.Add( RtfColor( 0xD3D3D3 ) );
			sColors.Add( RtfColor( 0xFF00FF ) );
			sColors.Add( RtfColor( 0xFF0000 ) );
			sColors.Add( RtfColor( 0xFFFFFF ) );
			sColors.Add( RtfColor( 0xFFFF00 ) );

			//CString sBlack = _T("000000");
			//CString blue = _T("0000FF");
			//CString cyan = _T("00FFFF");
			//CString darkBlue = _T("00008B");
			//CString darkCyan = _T("008B8B");
			//CString darkGray = _T("A9A9A9");
			//CString darkGreen = _T("006400");
			//CString darkMagenta = _T("800080");
			//CString darkRed = _T("8B0000");
			//CString darkYellow = _T("808000");
			//CString green = _T("00FF00");
			//CString lightGray = _T("D3D3D3");
			//CString magenta = _T("FF00FF");
			//CString red = _T("FF0000");
			//CString white = _T("FFFFFF");
			//CString yellow = _T("FFFF00");

			long nMinDelta = MAXLONG;
			int nIndex = -1;
			for( int i = 0; i < (int)sColors.GetCount(); i++ )
			{
				int nCurDelta = ( sColors[i].GetR() - GetR() ) * ( sColors[i].GetR() - GetR() ) + 
								( sColors[i].GetG() - GetG() ) * ( sColors[i].GetG() - GetG() ) + 
								( sColors[i].GetB() - GetB() ) * ( sColors[i].GetB() - GetB() );
				if( nCurDelta < nMinDelta )
				{
					nIndex = i;
					nMinDelta = nCurDelta;
				}
			}
			switch ( nIndex )
			{
				case 0: return _T("black");
				case 1: return _T("blue");
				case 2: return _T("cyan");
				case 3: return _T("darkBlue");
				case 4: return _T("darkCyan");
				case 5: return _T("darkGray");
				case 6: return _T("darkGreen");
				case 7: return _T("darkMagenta");
				case 8: return _T("darkRed");
				case 9: return _T("darkYellow");
				case 10: return _T("green");
				case 11: return _T("lightGray");
				case 12: return _T("magenta");
				case 13: return _T("red");
				case 14: return _T("white");
				case 15: return _T("yellow");
			}
			return _T("none");
		}
};
class RtfShading
{
public: typedef enum { st_none, 
						st_chbghoriz, //\bghoriz	Specifies a horizontal background pattern for the paragraph.
						st_chbgvert, //\bgvert	Specifies a vertical background pattern for the paragraph.
						st_chbgfdiag, //\bgfdiag	Specifies a forward diagonal background pattern for the paragraph (\\\\).
						st_chbgbdiag, //\bgbdiag	Specifies a backward diagonal background pattern for the paragraph (////).
						st_chbgcross, //\bgcross	Specifies a cross background pattern for the paragraph.
						st_chbgdcross, //\bgdcross	Specifies a diagonal cross background pattern for the paragraph.
						st_chbgdkhoriz, //\bgdkhoriz	Specifies a dark horizontal background pattern for the paragraph.
						st_chbgdkvert, //\bgdkvert	Specifies a dark vertical background pattern for the paragraph.
						st_chbgdkfdiag, //\bgdkfdiag	Specifies a dark forward diagonal background pattern for the paragraph (\\\\).
						st_chbgdkbdiag, //\bgdkbdiag	Specifies a dark backward diagonal background pattern for the paragraph (////).
						st_chbgdkcross, //\bgdkcross	Specifies a dark cross background pattern for the paragraph.
						st_chbgdkdcross, //\bgdkdcross	Specifies a dark diagonal cross background pattern for the paragraph.
						st_clshdrawnil, //\clshdrawnil	Specifies a dark diagonal cross background pattern for the paragraph.
							}ShadingType;
public: ShadingType m_eType;
public: int m_nValue;
public: int m_nForeColor;
public: int m_nBackColor;

public: RtfShading()
		{
			SetDefault();
		}
public: bool operator==( const RtfShading& oChar )
		{
			return m_eType == oChar.m_eType && m_nValue == oChar.m_nValue && m_nForeColor == oChar.m_nForeColor && m_nBackColor == oChar.m_nBackColor;
		}
public: bool IsValid()
		{
			return true;
		}
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_SHADING;
		}
public: void SetDefaultRtf( )
		{
			SetDefault();
		}
public: void SetDefaultOOX( )
		{
			SetDefault();
		}
public: void SetDefault( )
		{
			DEFAULT_PROPERTY_DEF( m_eType, st_none )
			DEFAULT_PROPERTY( m_nValue )
			DEFAULT_PROPERTY( m_nForeColor )
			DEFAULT_PROPERTY( m_nBackColor )
		}
public: void Merge( RtfShading& oParPr )
		{
			//свойство должно быть как единое целое, поэтому если oBorPr задано, то переписыватся целиком
			if( st_none != oParPr.m_eType || PROP_DEF != oParPr.m_nValue || PROP_DEF != oParPr.m_nForeColor || PROP_DEF != oParPr.m_nBackColor )
			{
				m_eType = oParPr.m_eType;
				m_nValue = oParPr.m_nValue;
				m_nForeColor = oParPr.m_nForeColor;
				m_nBackColor = oParPr.m_nBackColor;
			}
		}
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfShadingPar : public RtfShading
{
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_SHADING_PARAGRAPH;
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
};
class RtfShadingChar : public RtfShading
{
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_SHADING_CHAR;
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
};
class RtfShadingCell : public RtfShading
{
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_SHADING_CELL;
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
};
class RtfShadingRow : public RtfShading
{
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_SHADING_CELL;
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
};
class RtfShadingTableStyle : public RtfShading
{
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_SHADING_TABLESTYLE;
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
};
class RtfBorder
{
public: typedef enum { bt_none,
						bt_brdrs, //\brdrs	Single-thickness border.
						bt_brdrth, //\brdrth	Double-thickness border.
						bt_brdrsh, //\brdrsh	Shadowed border.
						bt_brdrdb, //\brdrdb	Double border.
						bt_brdrdot, //\brdrdot	Dotted border.
						bt_brdrdash, //\brdrdash	Dashed border.
						bt_brdrhair, //\brdrhair	Hairline border.
						bt_brdrdashsm, //\brdrdashsm	Dashed border (small).
						bt_brdrdashd, //\brdrdashd	Dot-dashed border.
						bt_brdrdashdd, //\brdrdashdd	Dot-dot-dashed border.
						bt_brdrdashdot, //\brdrdashdot	Dot-dashed border (alias for \brdrdashd read but not written by Word)
						bt_brdrinset, //\brdrinset	Inset border.
						bt_brdrnone, //\brdrnone	No border.
						bt_brdroutset, //\brdroutset	Outset border.
						bt_brdrtriple, //\brdrtriple	Triple border.
						bt_brdrtnthsg, //\brdrtnthsg	Thick-thin border (small).
						bt_brdrthtnsg, //\brdrthtnsg	Thin-thick border (small).
						bt_brdrtnthtnsg, //\brdrtnthtnsg	Thin-thick thin border (small).
						bt_brdrtnthmg, //\brdrtnthmg	Thick-thin border (medium).
						bt_brdrthtnmg, //\brdrthtnmg	Thin-thick border (medium).
						bt_brdrtnthtnmg, //\brdrtnthtnmg	Thin-thick thin border (medium).
						bt_brdrtnthlg, //\brdrtnthlg	Thick-thin border (large).
						bt_brdrthtnlg, //\brdrthtnlg	Thin-thick border (large).
						bt_brdrtnthtnlg, //\brdrtnthtnlg	Thin-thick-thin border (large).
						bt_brdrwavy, //\brdrwavy	Wavy border.
						bt_brdrwavydb, //\brdrwavydb	Double wavy border.
						bt_brdrdashdotstr, //\brdrdashdotstr	Striped border.
						bt_brdremboss, //\brdremboss	Embossed border.
						bt_brdrengrave, //\brdrengrave	Engraved border.
							} BorderType;

public: BorderType m_eType;
public: int m_nWidth;
public: int m_nSpace;
public: int m_nColor;

public: RtfBorder()
		{
			SetDefault();
		}
public: bool operator==( const RtfBorder& oChar )
		{
			return m_eType == oChar.m_eType && m_nWidth == oChar.m_nWidth && m_nSpace == oChar.m_nSpace && m_nColor == oChar.m_nColor;
		}
public: bool IsValid()
		{
			return bt_none != m_eType;
		}
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_BORDER;
		}
public: void SetDefaultRtf( )
		{
			SetDefault();
		}
public: void SetDefaultOOX( )
		{
			SetDefault();
		}
public: void SetDefault( )
		{
			DEFAULT_PROPERTY_DEF( m_eType, bt_none )
			DEFAULT_PROPERTY( m_nWidth )
			DEFAULT_PROPERTY( m_nSpace )
			DEFAULT_PROPERTY( m_nColor )
		}
public: void SetEmpty( )
		{
			m_eType = bt_brdrnone;
			m_nWidth = 0;
			m_nSpace = 0;
			m_nColor = PROP_DEF;
		}
public: void Merge( RtfBorder& oBorPr )
		{
			//свойство должно быть как единое целое, поэтому если oBorPr задано, то переписыватся целиком
			if( bt_none != oBorPr.m_eType || PROP_DEF != oBorPr.m_nWidth || PROP_DEF != oBorPr.m_nSpace || PROP_DEF != oBorPr.m_nColor )
			{
				m_eType = oBorPr.m_eType;
				m_nWidth = oBorPr.m_nWidth;
				m_nSpace = oBorPr.m_nSpace;
				m_nColor = oBorPr.m_nColor;
			}
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
public: static bool GetStringRtfByType( BorderType nValue, CString& sValue )
		{
			sValue = _T("\\brdrs");
			//switch( nValue )
			//{
			//default: sResult = _T("\\brdrs"); break;
			////}
			return false;
		}
public: static CString GetStringOOXByType( BorderType nValue, CString& sValue )
		{
			CString sResult;
			sResult = _T("single");
			//switch( nValue )
			//{
			//default: sResult = _T("single"); break;
			//}
			return sResult;
		}
};
class RtfTab : public IRenderableProperty
{
public: typedef enum { tl_none,
						tl_dot , //\tldot 	Absolute position tab with a leading that uses period symbols (.....).
						tl_mdot , //\tlmdot 	Absolute position tab with a leading that uses middle dot symbols (•••••).
						tl_hyph , //\tlhyph 	Absolute position tab with a leading that uses minus symbols (-----).
						tl_ul , //\tlul 	Absolute position tab with a leading that uses underscore symbols (_____).
							}TabLeader;
public: typedef enum { tk_none,
						tk_tql,
						tk_tqr, //\tqr	Flush-right tab.
						tk_tqc, //\tqc	Centered tab.
						tk_tqdec, //\tqdec	Decimal tab.
						tk_tqbar //\tbN	Bar tab position in twips from the left margin.
							}TabKind;
public: int m_nTab; //\tbN or \txN	Tab position in twips from the left margin.
public: TabLeader m_eLeader;
public: TabKind m_eKind;
public: RtfTab()
		{
			SetDefault();
		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_nTab );
			DEFAULT_PROPERTY_DEF( m_eLeader, tl_none );
			DEFAULT_PROPERTY_DEF( m_eKind, tk_tql );
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfTabs: public IRenderableProperty
{
public: CAtlArray<RtfTab> m_aTabs;
public: RtfTabs()
		{
			SetDefault();
		}
public: RtfTabs( const RtfTabs& oTabs )
		{
			SetDefault();
		}
public: const RtfTabs& operator=( const RtfTabs& oTabs )
		{
			Merge( oTabs );
			return (*this);
		}
public: void Merge( const RtfTabs& oTabs )
		{
			m_aTabs.RemoveAll();
			m_aTabs.Append( oTabs.m_aTabs );
		}
public: void SetDefault()
		{
			m_aTabs.RemoveAll();
		}
public: CString RenderToRtf(RenderParameter oRenderParameter)
		{
			CString sResult;
			for( int i = 0; i < (int)m_aTabs.GetCount(); i++ )
				sResult.Append( m_aTabs[i].RenderToRtf( oRenderParameter ) );
			return sResult;
		}
public: CString RenderToOOX(RenderParameter oRenderParameter)
		{
			CString sResult;
			CString sTabs;
			for( int i = 0; i < (int)m_aTabs.GetCount(); i++ )
				sTabs.Append( m_aTabs[i].RenderToOOX( oRenderParameter ) );
			if( false == sTabs.IsEmpty() )
				sResult.AppendFormat( _T("<w:tabs>%s</w:tabs>"), sTabs ); 
			return sResult;
		}
};
class RtfCharProperty: public IRenderableProperty
{
public: typedef enum {uls_none, uls_Single, uls_Dotted,uls_Dashed ,uls_Dash_dotted,uls_Dash_dot_dotted,uls_Double,uls_Heavy_wave,uls_Long_dashe,uls_Stops_all,uls_Thick,uls_Thick_dotted,uls_Thick_dashed,uls_Thick_dash_dotted,uls_Thick_dash_dot_dotted,uls_Thick_long_dashed,uls_Double_wave,uls_Word,uls_Wave} UnderlineStyle;

public: int m_nAnimated; //\animtextN	Animated text properties (note: Word 2007 ignores this control word):

public: int m_bBold; //\b*	Bold.
public: int m_bCaps; //\caps*	All capitals.
public: int m_nScalex; //\charscalexN 	Character scaling value. The N argument is a value representing a percentage (default is 100).
public: int m_nCharStyle; //\csN	Designates character style. If a character style is specified, style properties must be specified with the character run. N refers to an entry in the style table.
public: int m_nDown; //\dnN	Move down N half-points (default is 6).
public: int m_bEmbo; //\embo*	Emboss.
public: int m_nCharacterSpacing; //\expndtwN	Expansion or compression of the space between characters in twips; a negative value compresses. For backward compatibility, both \expndtwN and \expndN should be emitted.		
public: int m_nFitText; //\fittextN	Fit the text in the current group in N twips. When N is set to -1 (\fittext-1), it indicates a continuation of the previous \fittextN run. In other words, {\fittext1000 Fit this} {\fittext-1 text} fits the string “Fit this text” in 1000 twips.
public: int m_nFont; //\fN	Font number. N refers to an entry in the font table.
public: int m_nFont2; //
public: int m_nFont3; //
public: int m_nFontSize; //\fsN	Font size in half-points (default is 24).
public: int m_bItalic; //\i*	Italic.
public: int m_bImprint; //\impr*	Engrave (imprint).
public: int m_nKerning; //\kerningN	Point size (in half-points) above which to kern character pairs. \kerning0 turns off kerning.
public: int m_bRightToLeft; //\rtlch	Character data following this control word is treated as a right-to-left run.
public: int m_nComplexScript;
public: int m_bOutline; //\outl*	Outline.
public: int m_bScaps; //\scaps*	Small capitals.
public: int m_bShadow; //\shad*	Shadow.
public: int m_bStrike; //\strike*	Strikethrough.
public: int m_nStriked; //\striked1	Double strikethrough. \striked0 turns it off.
public: int m_bSub; //\sub	Subscripts text and shrinks point size according to font information.
public: int m_bSuper; //\super	Superscripts text and shrinks point size according to font information.
public: int m_bHidden; //\v*	Hidden text.
public: int m_nHightlited; //

public: int m_nForeColor; //

//public: int m_bUnderline; //\ul*	Continuous underline. \ul0 turns off all underlining.
public: UnderlineStyle m_eUnderStyle; //
public: int m_nUnderlineColor; //
public: int m_nUp; //\upN	Move up N half-points (default is 6).


public: RtfBorder m_poBorder;
public: RtfShadingChar m_poShading;
public: bool operator==( const RtfCharProperty& oChar )
		{
			return m_nAnimated == oChar.m_nAnimated && m_bBold == oChar.m_bBold && m_bCaps == oChar.m_bCaps && m_nScalex == oChar.m_nScalex && 
					m_nCharStyle == oChar.m_nCharStyle && m_nDown == oChar.m_nDown && m_bEmbo == oChar.m_bEmbo && m_nCharacterSpacing == oChar.m_nCharacterSpacing && 
					m_nFitText == oChar.m_nFitText && m_nFont == oChar.m_nFont && m_nFont2 == oChar.m_nFont2 && m_nFont3 == oChar.m_nFont3 && 
					m_nFontSize == oChar.m_nFontSize && m_bItalic == oChar.m_bItalic && m_bImprint == oChar.m_bImprint && m_nKerning == oChar.m_nKerning && 
					m_bRightToLeft == oChar.m_bRightToLeft && m_nComplexScript == oChar.m_nComplexScript && m_bOutline == oChar.m_bOutline && m_bScaps == oChar.m_bScaps && 
					m_bShadow == oChar.m_bShadow && m_bStrike == oChar.m_bStrike && m_bSub == oChar.m_bSub && m_bSuper == oChar.m_bSuper && 
					m_bHidden == oChar.m_bHidden && m_nHightlited == oChar.m_nHightlited && m_nForeColor == oChar.m_nForeColor && 
					m_eUnderStyle == oChar.m_eUnderStyle && m_nUnderlineColor == oChar.m_nUnderlineColor && m_nUp == oChar.m_nUp &&
					m_poBorder == oChar.m_poBorder && m_poShading == oChar.m_poShading;
		}

public: RtfCharProperty()
		{
			SetDefault();
		}
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_CHAR;
		}
public: void SetDefaultRtf()
		{
			SetDefault();
			m_nFontSize = 24;
			m_poShading.SetDefaultRtf();
			m_poBorder.SetDefaultRtf();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
			m_poShading.SetDefaultOOX();
			m_poBorder.SetDefaultOOX();
			m_nFontSize = 20;
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_nAnimated )
			DEFAULT_PROPERTY( m_bBold )
			DEFAULT_PROPERTY( m_bCaps )
			DEFAULT_PROPERTY( m_nScalex )
			DEFAULT_PROPERTY( m_nCharStyle )
			DEFAULT_PROPERTY( m_nDown )
			DEFAULT_PROPERTY( m_bEmbo )
			DEFAULT_PROPERTY( m_nCharacterSpacing )
			DEFAULT_PROPERTY( m_nFitText )
			DEFAULT_PROPERTY( m_nFont )
			DEFAULT_PROPERTY( m_nFont2 )
			DEFAULT_PROPERTY( m_nFont3 )
			DEFAULT_PROPERTY( m_nFontSize )
			DEFAULT_PROPERTY( m_bItalic )
			DEFAULT_PROPERTY( m_bImprint )
			DEFAULT_PROPERTY( m_nKerning )
			DEFAULT_PROPERTY( m_bRightToLeft )
			DEFAULT_PROPERTY( m_bOutline )
			DEFAULT_PROPERTY( m_bScaps )
			DEFAULT_PROPERTY( m_bShadow )
			DEFAULT_PROPERTY( m_bStrike )
			DEFAULT_PROPERTY( m_nStriked )
			DEFAULT_PROPERTY( m_bSub )
			DEFAULT_PROPERTY( m_bSuper )
			DEFAULT_PROPERTY( m_bHidden )
			DEFAULT_PROPERTY( m_nHightlited )
			DEFAULT_PROPERTY( m_nForeColor )
			DEFAULT_PROPERTY_DEF( m_eUnderStyle, uls_none )
			DEFAULT_PROPERTY( m_nUnderlineColor )
			DEFAULT_PROPERTY( m_nUp )
			m_poShading.SetDefault();
			m_poBorder.SetDefault();
			DEFAULT_PROPERTY( m_nComplexScript )
		}
public: void Merge( RtfCharProperty& oCharPr )
		{
			MERGE_PROPERTY( m_nAnimated, oCharPr )
			MERGE_PROPERTY( m_bBold, oCharPr )
			MERGE_PROPERTY( m_bCaps, oCharPr )
			MERGE_PROPERTY( m_nScalex, oCharPr )
			MERGE_PROPERTY( m_nCharStyle, oCharPr )
			MERGE_PROPERTY( m_nDown, oCharPr )
			MERGE_PROPERTY( m_bEmbo, oCharPr )
			MERGE_PROPERTY( m_nCharacterSpacing, oCharPr )
			MERGE_PROPERTY( m_nFitText, oCharPr )
			MERGE_PROPERTY( m_nFont, oCharPr )
			MERGE_PROPERTY( m_nFont2, oCharPr )
			MERGE_PROPERTY( m_nFont3, oCharPr )
			MERGE_PROPERTY( m_nFontSize, oCharPr )
			MERGE_PROPERTY( m_bItalic, oCharPr )
			MERGE_PROPERTY( m_bImprint, oCharPr )
			MERGE_PROPERTY( m_nKerning, oCharPr )
			MERGE_PROPERTY( m_bRightToLeft, oCharPr )
			MERGE_PROPERTY( m_bOutline, oCharPr )
			MERGE_PROPERTY( m_bScaps, oCharPr )
			MERGE_PROPERTY( m_bShadow, oCharPr )
			MERGE_PROPERTY( m_bStrike, oCharPr )
			MERGE_PROPERTY( m_nStriked, oCharPr )
			MERGE_PROPERTY( m_bSub, oCharPr )
			MERGE_PROPERTY( m_bSuper, oCharPr )
			MERGE_PROPERTY( m_bHidden, oCharPr )
			MERGE_PROPERTY( m_nHightlited, oCharPr )
			MERGE_PROPERTY( m_nForeColor, oCharPr )
			//свойство должно быть как единое целое, поэтому если oBorPr задано, то переписыватся целиком
			if( uls_none != oCharPr.m_eUnderStyle || PROP_DEF != oCharPr.m_nUnderlineColor )
			{
				m_eUnderStyle = oCharPr.m_eUnderStyle;
				m_nUnderlineColor = oCharPr.m_nUnderlineColor;
			}
			MERGE_PROPERTY_DEF( m_bSub, oCharPr, uls_none )
			MERGE_PROPERTY( m_nUp, oCharPr )
			MERGE_PROPERTY( m_nComplexScript, oCharPr )
			m_poBorder.Merge( oCharPr.m_poBorder );
			m_poShading.Merge( oCharPr.m_poShading );
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfListLevelProperty : IRenderableProperty
{
public: int m_nLevel; //OOX
public: int m_nNumberType; //\levelnfcN \levelnfcnN Specifies the number type for the level
public: int m_bTentative; //\lvltentative 	Specifies that a given numbering level was been saved by a producer but was not used in the parent document. This means that this numbering level may be redefined by a future consumer without changing the actual content of the document.
public: int m_nJustification; //\leveljcN \leveljcnN	0	Left justified 1	Center justified 2	Right justified
public: int m_nFollow; //\levelfollowN
public: int m_nStart; //\levelstartatN	N specifies the start-at value for the level.
public: CString m_sText; //как в rtf текст, но сдвинут от нуля на 1 // \'03\'00.\'01 -> ("%d%d%d",4,1,2)
public: CString m_sNumber;
public: int m_nNoRestart; //\levelnorestartN	1 if this level does not restart its count each time a super ordinate level is incremented; 0 if this level does restart its count each time a super ordinate level is incremented.
public: int m_nLegal; //\levellegalN	1 if any list numbers from previous levels should be converted to Arabic numbers; 0 if they should be left with the format specified by their own level’s definition.
public: int m_nPictureIndex; //\levelpictureN	Determines which picture bullet from the \listpicture destination should be applied.

public: RtfTabs m_oTabs; //ParagraphProp
public: int m_nFirstIndent;
public: int m_nIndent;
public: int m_nIndentStart;
public: RtfCharProperty m_oCharProp; //Char

public: RtfListLevelProperty()
	{
		SetDefault();
	}
public: bool IsValid()
		{
			//return -1 != m_nFollow && -1 != m_nStart && -1 != m_nNumberType && -1 != m_nJustification &&
			//	false == m_sText.IsEmpty() && false == m_sNumber.IsEmpty();
			return  PROP_DEF != m_nNumberType && false == m_sText.IsEmpty();
		}
public: CString GenerateListText()
		 {//заменяем на булеты
			CString sResult;

			CStringA sBullet;
			char cBullet = (char)149;
			sBullet.AppendChar( cBullet );
			CString swBullet;
			swBullet = sBullet;

			sResult.Append( swBullet );
			//CString sOOXNumber = GetLevelTextOOX();
			//for( int i = 0; i < sOOXNumber.GetLength(); i++ )
			//	if( sOOXNumber[i] == '%' && i != sOOXNumber.GetLength() - 1 )
			//	{
			//		sResult.Append( swBullet );
			//		i++;
			//	}
			//	else
			//		sResult.AppendChar( sOOXNumber[i] );
			return sResult;
		 }
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_nLevel )
			DEFAULT_PROPERTY( m_nNumberType )
			DEFAULT_PROPERTY( m_bTentative )
			DEFAULT_PROPERTY( m_nJustification )
			DEFAULT_PROPERTY( m_nFollow )
			DEFAULT_PROPERTY( m_nStart )
			DEFAULT_PROPERTY_DEF( m_sText, _T("") )
			DEFAULT_PROPERTY_DEF( m_sNumber, _T("") )
			DEFAULT_PROPERTY( m_nNoRestart )
			DEFAULT_PROPERTY( m_nLegal )
			DEFAULT_PROPERTY( m_nPictureIndex )
			m_oTabs.SetDefault();
			DEFAULT_PROPERTY( m_nFirstIndent )
			DEFAULT_PROPERTY( m_nIndent )
			DEFAULT_PROPERTY( m_nIndentStart )

			m_oCharProp.SetDefault();
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);

public: static CString GetFormat( int nNumFormat)
		{
			CString sResult;
			switch(nNumFormat)
			{
				case 0: sResult = _T("decimal");break;
				case 1: sResult = _T("upperRoman");break;
				case 2: sResult = _T("lowerRoman");break;
				case 3: sResult = _T("upperLetter");break;
				case 4: sResult = _T("lowerLetter");break;
				case 5: sResult = _T("ordinal");break;
				case 6: sResult = _T("cardinalText");break;
				case 7: sResult = _T("ordinalText");break;
				case 8: sResult = _T("hex");break;
				case 9: sResult = _T("chicago");break;
				case 10: sResult = _T("ideographDigital");break;
				case 11: sResult = _T("japaneseCounting");break;
				case 12: sResult = _T("aiueo");break;
				case 13: sResult = _T("iroha");break;
				case 14: sResult = _T("decimalFullWidth");break;
				case 15: sResult = _T("decimalHalfWidth");break;
				case 16: sResult = _T("japaneseLegal");break;
				case 17: sResult = _T("japaneseDigitalTenThousand");break;
				case 18: sResult = _T("decimalEnclosedCircle");break;
				case 19: sResult = _T("decimalFullWidth2");break;
				case 20: sResult = _T("aiueoFullWidth");break;
				case 21: sResult = _T("irohaFullWidth");break;
				case 22: sResult = _T("decimalZero");break;
				case 23: sResult = _T("bullet");break;
				case 24: sResult = _T("ganada");break;
				case 25: sResult = _T("chosung");break;
				case 26: sResult = _T("decimalEnclosedFullstop");break;
				case 27: sResult = _T("decimalEnclosedParen");break;
				case 28: sResult = _T("decimalEnclosedCircleChinese");break;
				case 29: sResult = _T("ideographEnclosedCircle");break;
				case 30: sResult = _T("ideographTraditional");break;
				case 31: sResult = _T("ideographZodiac");break;
				case 32: sResult = _T("ideographZodiacTraditional");break;
				case 33: sResult = _T("taiwaneseCounting");break;
				case 34: sResult = _T("ideographLegalTraditional");break;
				case 35: sResult = _T("taiwaneseCountingThousand");break;
				case 36: sResult = _T("taiwaneseDigital");break;
				case 37: sResult = _T("chineseCounting");break;
				case 38: sResult = _T("chineseLegalSimplified");break;
				case 39: sResult = _T("chineseCountingThousand");break;
				case 40: sResult = _T("chineseCounting");break;
				case 41: sResult = _T("koreanDigital");break;
				case 42: sResult = _T("koreanCounting");break;
				case 43: sResult = _T("koreanLegal");break;
				case 44: sResult = _T("koreanDigital2");break;
				case 45: sResult = _T("hebrew1");break;
				case 46: sResult = _T("arabicAlpha");break;
				case 47: sResult = _T("hebrew2");break;
				case 48: sResult = _T("arabicAbjad");break;
				case 49: sResult = _T("hindiVowels");break;
				case 50: sResult = _T("hindiConsonants");break;
				case 51: sResult = _T("hindiNumbers");break;
				case 52: sResult = _T("hindiCounting");break;
				case 53: sResult = _T("thaiLetters");break;
				case 54: sResult = _T("thaiNumbers");break;
				case 55: sResult = _T("thaiCounting");break;
				case 56: sResult = _T("vietnameseCounting");break;
				case 57: sResult = _T("numberInDash");break;
				case 58: sResult = _T("russianLower");break;
				case 59: sResult = _T("russianUpper");break;

				case 70: sResult = _T("chicago");break;

				case 255: sResult = _T("none");break;
				default: sResult = _T("decimal");
			}
			return sResult;
		}
public: static int GetFormat( CString sFormat)
		{
			if( _T("aiueo") == sFormat )
				return 12;
			else if( _T("aiueoFullWidth") == sFormat )
				return 20;
			else if( _T("arabicAbjad") == sFormat )
				return 48;
			else if( _T("arabicAlpha") == sFormat )
				return 46;
			else if( _T("bahtText") == sFormat )
				return 0;
			else if( _T("bullet") == sFormat )
				return 23;
			else if( _T("cardinalText") == sFormat )
				return 6;
			else if( _T("chicago") == sFormat )
				return 9;
			else if( _T("chineseCounting") == sFormat )
				return 37;
			else if( _T("chineseCountingThousand") == sFormat )
				return 39;
			else if( _T("chineseLegalSimplified") == sFormat )
				return 38;
			else if( _T("chosung") == sFormat )
				return 25;
			else if( _T("custom") == sFormat )
				return 0;
			else if( _T("decimal") == sFormat )
				return 0;
			else if( _T("decimalEnclosedCircle") == sFormat )
				return 18;
			else if( _T("decimalEnclosedCircleChinese") == sFormat )
				return 28;
			else if( _T("decimalEnclosedFullstop") == sFormat )
				return 26;
			else if( _T("decimalEnclosedParen") == sFormat )
				return 27;
			else if( _T("decimalFullWidth") == sFormat )
				return 14;
			else if( _T("decimalFullWidth2") == sFormat )
				return 19;
			else if( _T("decimalHalfWidth") == sFormat )
				return 15;
			else if( _T("decimalZero") == sFormat )
				return 22;
			else if( _T("dollarText") == sFormat )
				return 0;
			else if( _T("ganada") == sFormat )
				return 24;
			else if( _T("hebrew1") == sFormat )
				return 45;
			else if( _T("hebrew1") == sFormat )
				return 45;
			else if( _T("hebrew2") == sFormat )
				return 47;
			else if( _T("hex") == sFormat )
				return 8;
			else if( _T("hindiConsonants") == sFormat )
				return 50;
			else if( _T("hindiCounting") == sFormat )
				return 52;
			else if( _T("hindiNumbers") == sFormat )
				return 51;
			else if( _T("hindiVowels") == sFormat )
				return 49;
			else if( _T("ideographDigital") == sFormat )
				return 10;
			else if( _T("ideographEnclosedCircle") == sFormat )
				return 29;
			else if( _T("ideographLegalTraditional") == sFormat )
				return 34;
			else if( _T("ideographTraditional") == sFormat )
				return 30;
			else if( _T("ideographZodiac") == sFormat )
				return 31;
			else if( _T("ideographZodiacTraditional") == sFormat )
				return 32;
			else if( _T("iroha") == sFormat )
				return 13;
			else if( _T("irohaFullWidth") == sFormat )
				return 21;
			else if( _T("japaneseCounting") == sFormat )
				return 11;
			else if( _T("japaneseDigitalTenThousand") == sFormat )
				return 17;
			else if( _T("japaneseLegal") == sFormat )
				return 16;
			else if( _T("koreanCounting") == sFormat )
				return 42;
			else if( _T("koreanDigital") == sFormat )
				return 41;
			else if( _T("koreanDigital2") == sFormat )
				return 44;
			else if( _T("koreanLegal") == sFormat )
				return 43;
			else if( _T("lowerLetter") == sFormat )
				return 4;
			else if( _T("lowerRoman") == sFormat )
				return 2;
			else if( _T("none") == sFormat )
				return 255;
			else if( _T("numberInDash") == sFormat )
				return 57;
			else if( _T("ordinal") == sFormat )
				return 5;
			else if( _T("ordinalText") == sFormat )
				return 7;
			else if( _T("russianLower") == sFormat )
				return 58;
			else if( _T("russianUpper") == sFormat )
				return 59;
			else if( _T("taiwaneseCounting") == sFormat )
				return 33;
			else if( _T("taiwaneseCountingThousand") == sFormat )
				return 35;
			else if( _T("taiwaneseDigital") == sFormat )
				return 36;
			else if( _T("thaiCounting") == sFormat )
				return 55;
			else if( _T("thaiLetters") == sFormat )
				return 53;
			else if( _T("thaiNumbers") == sFormat )
				return 54;
			else if( _T("upperLetter") == sFormat )
				return 3;
			else if( _T("upperRoman") == sFormat )
				return 1;
			else if( _T("vietnameseCounting") == sFormat )
				return 56;
			else if( _T("chicago") == sFormat )
				return 70;
			return 0; //decimal
		}
public: CString GetLevelTextOOX()
		{
			CString sResult = m_sText;
			if( sResult.GetLength() > 0 )
			{
				int nLevelTextLength = sResult[0];
				nLevelTextLength--;
				for( int i = m_sNumber.GetLength() - 1; i >= 0; i-- )
				{
					int nReplaceNumber = m_sNumber[i];
					nReplaceNumber--;
					if( nReplaceNumber >= 0 && nReplaceNumber < sResult.GetLength() )
					{
						int nLevel = sResult[ nReplaceNumber ];
						CString sExt;
						sExt.AppendFormat( _T("%%%d"), nLevel );
						sResult.Delete( nReplaceNumber );
						sResult.Insert(nReplaceNumber, sExt);
						nLevelTextLength += sExt.GetLength() - 1;
					}
				}
				sResult = sResult.Right( sResult.GetLength() - 1 );
				if( nLevelTextLength < sResult.GetLength() )
					sResult = sResult.Left( nLevelTextLength );

			}
			return Utils::PrepareToXML( sResult );
		}
public: void SetLevelTextOOX(CString sText)
		{
			m_sText = _T("");
			m_sNumber = _T("");
			 int nNumberIndex = 0; //индекс символа который отвечает за уровень символа
			 for( int i = 0; i < sText.GetLength() ; i++ )
			 {
				 if( sText[i] == '%' && i + 1 < sText.GetLength() && isdigit( sText[ i + 1 ] ))
				 {
					 int nLevel = RtfUtility::ToByte( sText[ i + 1 ] );
					 m_sText.AppendChar( nLevel );
					 m_sNumber.AppendChar( nNumberIndex + 2 );
					 i++; //т.к. следующий симовл уже учли
				 }
				 else
					 m_sText.AppendChar( sText[i] );
				 nNumberIndex++;
			 }
			 CString sLength;sLength.AppendChar( nNumberIndex + 1 ); // 1 - учитывает то что мы сдвигаем на на единицу вниз при записи
			 m_sText.Insert(0, sLength );
		}
};

class RtfListProperty : public IRenderableProperty, public ItemContainer<RtfListLevelProperty>
{
public: int m_nID; //\listidN	Each list must have a unique list ID that should be randomly generated. N is a long integer. The list ID cannot be between –1 and –5. 
public: int m_nTemplateId; //\listtemplateidN	Each list should have a unique template ID as well, which also should be randomly generated. The template ID –1 means the template ID is undefined. N is a long integer. 
public: int m_nListSimple; //\listsimpleN	1 if the list has one level; 0 (default) if the list has nine levels.
public: int m_bListHybrid; //\listhybrid	Present if the list has 9 levels, each of which is the equivalent of a simple list. Only one of \listsimpleN and \listhybrid should be present. Word 2000 and newer versions will write lists with the \listhybrid property.
public: CString m_sName; //\listname	The argument for \listname is a string that is the name of this list. Names allow ListNum fields to specify the list to which they belong. This is a destination control word.

public: RtfListProperty()
	{
		SetDefault();
	}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_nID )
			DEFAULT_PROPERTY( m_nTemplateId )
			DEFAULT_PROPERTY( m_nListSimple )
			DEFAULT_PROPERTY( m_bListHybrid )
			DEFAULT_PROPERTY_DEF( m_sName, _T("") )

			m_aArray.RemoveAll();
		}
public: bool IsValid()
		{
			return (PROP_DEF != m_nID) ;//&& (_T("") != m_sName);
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfListOverrideProperty : IRenderableProperty
{
public: class ListOverrideLevels : IRenderableProperty
		{
		public: class ListOverrideLevel
				{
				public: int m_nLevelIndex; //\listoverrideformat	Number of list format override levels within this list override (should be either 1, 9, or missing, which means 0).
				public: int m_nStart; //\listoverridestartat	Indicates an override of the start-at value.
				public: RtfListLevelProperty m_oLevel;
				public: ListOverrideLevel()
						{
							m_nLevelIndex = 0;
							m_nStart = PROP_DEF;
						}
				};
		public: CAtlArray<ListOverrideLevel> m_aOverrideLevels;
		public: ListOverrideLevels()
				{
				}
		public: ListOverrideLevels( const ListOverrideLevels& oOverLevel )
				{
					(*this) = oOverLevel;
				}
		public: ListOverrideLevels& operator=( const ListOverrideLevels& oOverLevel )
				{
					m_aOverrideLevels.RemoveAll();
					m_aOverrideLevels.Append( oOverLevel.m_aOverrideLevels );
					return (*this);
				}
		public: void SetDefault()
				{
					m_aOverrideLevels.RemoveAll();
				}
		public: CString RenderToRtf(RenderParameter oRenderParameter)
				{
					CString sResult;
					int nOverrideCount = (int)m_aOverrideLevels.GetCount();
					for( int i = 0; i < nOverrideCount; i++ )
						if( PROP_DEF == m_aOverrideLevels[i].m_nLevelIndex )
							nOverrideCount--;
					sResult.AppendFormat( _T("\\listoverridecount%d"), nOverrideCount );
					for( int i = 0; i < nOverrideCount; i++ )
					{
						if( PROP_DEF != m_aOverrideLevels[i].m_nLevelIndex )
						{
							sResult.Append( _T("{\\lfolevel") );
							if( PROP_DEF != m_aOverrideLevels[i].m_nLevelIndex )
								sResult.AppendFormat( _T("\\listoverrideformat%d"), m_aOverrideLevels[i].m_nLevelIndex );
							if( PROP_DEF != m_aOverrideLevels[i].m_nStart )
								sResult.AppendFormat( _T("\\listoverridestartat%d"), m_aOverrideLevels[i].m_nStart );
							sResult.Append( m_aOverrideLevels[i].m_oLevel.RenderToRtf(oRenderParameter) );
							sResult.Append( _T("}") );
						}
					}
					return sResult;
				}
		public: CString RenderToOOX(RenderParameter oRenderParameter)
				{
					CString sResult;
					for( int i = 0; i < (int)m_aOverrideLevels.GetCount(); i++ )
					{
						if( PROP_DEF != m_aOverrideLevels[i].m_nLevelIndex )
						{
							sResult.AppendFormat( _T("<w:lvlOverride w:ilvl=\"%d\">"), m_aOverrideLevels[i].m_nLevelIndex );
							if( PROP_DEF != m_aOverrideLevels[i].m_nStart )
								sResult.AppendFormat( _T("<w:startOverride w:val=\"%d\"/>"), m_aOverrideLevels[i].m_nStart );
							sResult.Append( m_aOverrideLevels[i].m_oLevel.RenderToOOX(oRenderParameter) );
							sResult.Append( _T("</w:lvlOverride>") );
						}
					}
					return sResult;
				}
		};
public: int m_nListID; //\listidN	Should exactly match the \listid of one of the lists in the List table. The value N is a long integer.
public: int m_nIndex; //\lsN	The (1-based) index of this \listoverride in the \listoverride table. This value should never be zero inside a \listoverride and must be unique for all \listoverride’s within a document. The valid values are from 1 to 2000. The value 0 means no list.
public: ListOverrideLevels m_oOverrideLevels;

public: RtfListOverrideProperty()
		{
			SetDefault();
		}
public: bool IsValid()
		{
			return PROP_DEF != m_nListID && PROP_DEF != m_nIndex;
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_nListID )
			DEFAULT_PROPERTY( m_nIndex )
			m_oOverrideLevels.SetDefault();
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfStyle;
typedef boost::shared_ptr<RtfStyle> RtfStylePtr;
class RtfStyle: public IRenderableProperty
{
	public: typedef enum { st_none, stParagraph, stCharacter, stSection, stTable, stNumbering} StyleType;
	public: StyleType m_eType;
	public: CString m_sName;
	public: int m_nID;
	public: CString m_sID;

	public: int m_bAdditive;
	public: int m_nBasedOn;
	public: int m_nNext;
	public: int m_bHidden;
	public: int m_nLink;
	public: int m_bLocked;
	public: int m_bPersonal;
	public: int m_bCompose;
	public: int m_bReply;
	public: int m_nSemiHidden;
	public: int m_bQFormat;
	public: int m_nPriority;
	public: int m_bUnhiddenWhenUse;
public: RtfStyle()
		{
			SetDefault();
		}
public: bool IsValid()
		{
			return PROP_DEF != m_nID;
		}
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_STYLE;
		}
public: void SetDefaultRtf()
		{
			SetDefault();
			m_eType = stParagraph;
			m_nID = 0;
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY_DEF( m_eType, st_none )
			DEFAULT_PROPERTY_DEF( m_sName, _T("") )
			DEFAULT_PROPERTY_DEF( m_sID, _T("") )
			DEFAULT_PROPERTY( m_nID )
			DEFAULT_PROPERTY( m_bAdditive )
			DEFAULT_PROPERTY( m_nBasedOn )
			DEFAULT_PROPERTY( m_nNext )
			DEFAULT_PROPERTY( m_bHidden )
			DEFAULT_PROPERTY( m_nLink )
			DEFAULT_PROPERTY( m_bLocked )
			DEFAULT_PROPERTY( m_bPersonal )
			DEFAULT_PROPERTY( m_bCompose )
			DEFAULT_PROPERTY( m_bReply )
			DEFAULT_PROPERTY( m_nSemiHidden )
			DEFAULT_PROPERTY( m_bQFormat )
			DEFAULT_PROPERTY( m_nPriority )
			DEFAULT_PROPERTY( m_bUnhiddenWhenUse )
		}

public: virtual void Merge( RtfStylePtr oStyle )
		{
			RtfStyle& oCurStyle = *oStyle;
			MERGE_PROPERTY_DEF( m_eType, oCurStyle, st_none )
			MERGE_PROPERTY_DEF( m_sName, oCurStyle, _T("") )
			MERGE_PROPERTY( m_nID, oCurStyle )
			MERGE_PROPERTY_DEF( m_sID, oCurStyle, _T("") )

			MERGE_PROPERTY( m_bAdditive, oCurStyle )
			MERGE_PROPERTY( m_nBasedOn, oCurStyle )
			MERGE_PROPERTY( m_nNext, oCurStyle )
			MERGE_PROPERTY( m_bHidden, oCurStyle )
			MERGE_PROPERTY( m_nLink, oCurStyle )
			MERGE_PROPERTY( m_bLocked, oCurStyle )
			MERGE_PROPERTY( m_bPersonal, oCurStyle )
			MERGE_PROPERTY( m_bCompose, oCurStyle )
			MERGE_PROPERTY( m_bReply, oCurStyle )
			MERGE_PROPERTY( m_nSemiHidden, oCurStyle )
			MERGE_PROPERTY( m_bQFormat, oCurStyle )
			MERGE_PROPERTY( m_nPriority, oCurStyle )
			MERGE_PROPERTY( m_bUnhiddenWhenUse, oCurStyle )
		}

public: bool operator==( const RtfStyle& oProperty )
		{
			return m_eType == oProperty.m_eType && m_nID == oProperty.m_nID && m_nBasedOn == oProperty.m_nBasedOn && 
				m_nNext == oProperty.m_nNext && m_bHidden == oProperty.m_bHidden && m_nLink == oProperty.m_nLink && 
				m_bLocked == oProperty.m_bLocked && m_bPersonal == oProperty.m_bPersonal && m_bCompose == oProperty.m_bCompose && 
				m_bReply == oProperty.m_bReply && m_nSemiHidden == oProperty.m_nSemiHidden && m_bQFormat == oProperty.m_bQFormat && 
				m_nPriority == oProperty.m_nPriority && m_bUnhiddenWhenUse == oProperty.m_bUnhiddenWhenUse;
		}
public: CString RenderToRtfBegin( RenderParameter oRenderParameter )
		{
			if( false == IsValid() )
				return false;

			CString sResult;
			switch( m_eType )
			{
			case stParagraph : sResult.AppendFormat(_T("{\\s%d"), m_nID);break;
			case stCharacter : sResult.AppendFormat(_T("{\\*\\cs%d"), m_nID);break;
			case stSection : sResult.AppendFormat(_T("{\\*\\ds%d"), m_nID);break;
			case stTable : sResult.AppendFormat(_T("{\\*\\ts%d\\tsrowd"), m_nID);break;
			}
			return sResult;
		}
public: CString RenderToRtfEnd( RenderParameter oRenderParameter );
public: CString RenderToOOXBegin(RenderParameter oRenderParameter);
public: CString RenderToOOXEnd(RenderParameter oRenderParameter);
public: CString RenderToRtf(RenderParameter oRenderParameter)
		{
			return _T("");
		}
public: CString RenderToOOX(RenderParameter oRenderParameter)
		{
			return _T("");
		}
};

class RtfTableProperty: public IRenderableProperty
{
public: typedef enum{hr_none,
					hr_phmrg,//\tphmrg	Use margin as horizontal reference frame.
					hr_phpg, //\tphpg	Use page as horizontal reference frame.
					hr_phcol //\tphcol	Use column as horizontal reference frame. This is the default if no horizontal table positioning information is given.
						} HRef;
public: typedef enum{vr_none,
					vr_pvmrg, //\tpvmrg	Position table vertically relative to the top margin. This is the default if no vertical table positioning information is given.
					vr_pvpg,  //\tpvpg	Position table vertically relative to the top of the page.
					vr_pvpara //\tpvpara	Position table vertically relative to the upper left corner of the next unframed paragraph in the stream.
						} VRef;
public: typedef enum{hp_none, 
					hp_posxc, //\tposxc	Center table within the horizontal reference frame.
					hp_posxi, //\tposxi	Position table inside the horizontal reference frame.
					hp_posxo, //\tposxo	Position table outside the horizontal reference frame.
					hp_posxl, //\tposxl	Position table at the left of the horizontal reference frame.
					hp_posxr  //\tposxr	Position table at the right of the horizontal reference frame.
						} HPos;
public: typedef enum{vp_none,
					vp_posyt,  //\tposyt	Position table at the top of the vertical reference frame.
					vp_posyil, //\tposyil	Position table to be inline.
					vp_posyb,  //\tposyb	Position table at the bottom of the vertical reference frame.
					vp_posyc,  //\tposyc	Center table within the vertical reference frame
					vp_posyin, //\tposyin	Position table inside within the vertical reference frame.
					vp_posyout //\tposyout	Position table outside within the vertical reference frame.
						} VPos;

public: int m_bBidi; //\taprtl	Table direction is right to left.
public: int m_nAutoFit; //\trautofitN	AutoFit:0	No AutoFit (default).1	AutoFit is on for the row. Overridden by \clwWidthN and \trwWidthN in any table row
public: int m_nGraph; //\trgaphN	Half the space between the cells of a table row in twips.

public: int nTableIndent; //\tblindN 
public: int nTableIndentUnits; //\\tblindtypeN  

public: typedef enum{rj_none,
					rj_trql, //\trql	Left-justifies a table row with respect to its containing column.
					rj_trqr, //\trqr	Right-justifies a table row with respect to its containing column.
					rj_trqc  //\trqc	Centers a table row with respect to its containing column.
						} RowJust;
public: RowJust m_eJust; // 

public: int m_nWrapLeft; //\tdfrmtxtLeftN	Distance in twips, between the left of the table and surrounding text (default is 0).
public: int m_nWrapRight; //\tdfrmtxtRightN	Distance in twips, between the right of the table and surrounding text (default is 0).
public: int m_nWrapTop; //\tdfrmtxtTopN	Distance in twips, between the top of the table and surrounding text (default is 0).
public: int m_nWrapBottom; //\tdfrmtxtBottomN	Distance in twips, between the bottom of the table and surrounding text (default is 0).
public: int m_bOverlap; //\tabsnoovrlp	Do not allow table to overlap with other tables or shapes with similar wrapping not contained within it.

public: HRef m_eHRef;
public: VRef m_eVRef;
public: HPos m_eHPos;
public: int m_nHPos; //\tposxN	Position table N twips from the left edge of the horizontal reference frame.
public: VPos m_eVPos;
public: int m_nVPos; //\tposyN	Position table N twips from the top edge of the vertical reference frame.

public: int m_nLeft;
public: int m_nWidth; //\trwWidthN	Preferred row width. Overrides \trautofitN.
public: MetricUnits m_eMUWidth; //\trftsWidthN	Units for \trwWidthN:

public: int m_nDefCellMarBottom; //\trpaddbN	Default bottom cell margin or padding for the row.
public: int m_nDefCellMarLeft; //\trpaddlN	Default left cell margin or padding for the row.
public: int m_nDefCellMarRight; //\trpaddrN	Default right cell margin or padding for the row.
public: int m_nDefCellMarTop; //\trpaddtN	Default top cell margin or padding for the row.

public: int m_nDefCellMarBottomUnits; //Units for \trpaddbN: 0	Null. Ignore \trpaddbN in favor of \trgaphN (Word 97 style padding). 3	Twips.
public: int m_nDefCellMarLeftUnits;
public: int m_nDefCellMarRightUnits;
public: int m_nDefCellMarTopUnits;

public: int m_nDefCellSpBottom; //\trspdbN	Default bottom cell spacing for the row. The total vertical spacing between adjacent cells is equal to the sum of \trspdtN from the bottom cell and \trspdbN from the top cell, both of which will have the same value when written by Word.
public: int m_nDefCellSpLeft; //\trspdlN
public: int m_nDefCellSpRight; //\trspdrN
public: int m_nDefCellSpTop; //\trspdtN

public: int m_nDefCellSpBottomUnits; //trspdfbN Units for \trspdbN: 0	Null. Ignore \trspdbN. 3	Twips.
public: int m_nDefCellSpLeftUnits;
public: int m_nDefCellSpRightUnits;
public: int m_nDefCellSpTopUnits;

public: RtfBorder m_oBorderLeft;
public: RtfBorder m_oBorderRight;
public: RtfBorder m_oBorderTop;
public: RtfBorder m_oBorderBottom;
public: RtfBorder m_oBorderVert;
public: RtfBorder m_oBorderHor;

public: RtfShadingRow m_oShading;
public: int m_nStyle;

//Autoformatting Flags
public: int m_bAutoFirstRow; //\tbllkhdrrows	Flag sets table autoformat to format the first (header) row.
public: int m_bAutoLastRow; //\tbllklastrow	Flag sets table autoformat to format the last row.
public: int m_bAutoFirstCol; //\tbllkhdrcols	Flag sets table autoformat to format the first (header) column.
public: int m_bAutoLastCol; //\tbllklastcol	Flag sets table autoformat to format the last column.
public: int m_bAutoNoRowBand; //\tbllknorowband	Specifies row banding conditional formatting shall not be applied.
public: int m_bAutoNoColBand; //\tbllknocolband	Specifies column banding conditional formatting shall not be applied.

public: int m_nRowBandSize; //\tscbandshN	Count of rows in a row band
public: int m_nColBandSize; //\tscbandsvN	Count of cells in a cell band


public: RtfTableProperty()
		{
			SetDefault();
		}

public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_bBidi )
			DEFAULT_PROPERTY( m_nAutoFit )
			DEFAULT_PROPERTY( m_nGraph )

			DEFAULT_PROPERTY( nTableIndent )
			DEFAULT_PROPERTY( nTableIndentUnits )

			m_eJust = rj_none;

			DEFAULT_PROPERTY( m_nWrapLeft )
			DEFAULT_PROPERTY( m_nWrapRight )
			DEFAULT_PROPERTY( m_nWrapTop )
			DEFAULT_PROPERTY( m_nWrapBottom )
			DEFAULT_PROPERTY( m_bOverlap )

			DEFAULT_PROPERTY_DEF( m_eHRef, hr_none )
			DEFAULT_PROPERTY_DEF( m_eVRef, vr_none )
			DEFAULT_PROPERTY_DEF( m_eHPos, hp_none )
			DEFAULT_PROPERTY_DEF( m_eVPos, vp_none )
			DEFAULT_PROPERTY( m_nHPos )
			DEFAULT_PROPERTY( m_nVPos )

			DEFAULT_PROPERTY( m_nLeft )
			DEFAULT_PROPERTY( m_nWidth )
			m_eMUWidth = mu_none;

			m_nDefCellMarBottom = 0;
			m_nDefCellMarRight = 108;
			m_nDefCellMarLeft = 108;
			m_nDefCellMarTop = 0;
			//DEFAULT_PROPERTY( m_nDefCellMarBottom )
			//DEFAULT_PROPERTY( m_nDefCellMarRight )
			//DEFAULT_PROPERTY( m_nDefCellMarLeft )
			//DEFAULT_PROPERTY( m_nDefCellMarTop )

			m_nDefCellMarBottomUnits = 3;
			m_nDefCellMarRightUnits = 3;
			m_nDefCellMarLeftUnits = 3;
			m_nDefCellMarTopUnits = 3;
			//DEFAULT_PROPERTY( m_nDefCellMarBottomUnits )
			//DEFAULT_PROPERTY( m_nDefCellMarRightUnits )
			//DEFAULT_PROPERTY( m_nDefCellMarLeftUnits )
			//DEFAULT_PROPERTY( m_nDefCellMarTopUnits )

			DEFAULT_PROPERTY( m_nDefCellSpBottom )
			DEFAULT_PROPERTY( m_nDefCellSpLeft )
			DEFAULT_PROPERTY( m_nDefCellSpRight )
			DEFAULT_PROPERTY( m_nDefCellSpTop )

			DEFAULT_PROPERTY( m_nDefCellSpBottomUnits )
			DEFAULT_PROPERTY( m_nDefCellSpLeftUnits )
			DEFAULT_PROPERTY( m_nDefCellSpRightUnits )
			DEFAULT_PROPERTY( m_nDefCellSpTopUnits )

			m_oBorderLeft.SetEmpty();
			m_oBorderRight.SetEmpty();
			m_oBorderTop.SetEmpty();
			m_oBorderBottom.SetEmpty();
			m_oBorderVert.SetEmpty();
			m_oBorderHor.SetEmpty();

			m_oShading.SetDefault();

			DEFAULT_PROPERTY( m_nStyle )

			DEFAULT_PROPERTY( m_bAutoFirstRow )
			DEFAULT_PROPERTY( m_bAutoLastRow )
			DEFAULT_PROPERTY( m_bAutoFirstCol )
			DEFAULT_PROPERTY( m_bAutoLastCol )
			DEFAULT_PROPERTY( m_bAutoNoRowBand )
			DEFAULT_PROPERTY( m_bAutoNoColBand )

			DEFAULT_PROPERTY( m_nRowBandSize )
			DEFAULT_PROPERTY( m_nColBandSize )
		}
public: bool IsValid()
		{
			return true;
		}
public: void Merge( RtfTableProperty& oTablePr )
		{
			MERGE_PROPERTY( m_bBidi, oTablePr )
			MERGE_PROPERTY( m_nAutoFit, oTablePr )
			MERGE_PROPERTY( m_nGraph, oTablePr )
			MERGE_PROPERTY( nTableIndent, oTablePr )
			MERGE_PROPERTY( nTableIndentUnits, oTablePr )

			MERGE_PROPERTY_DEF( m_eJust, oTablePr, rj_none )

			MERGE_PROPERTY( m_nWrapLeft, oTablePr )
			MERGE_PROPERTY( m_nWrapRight, oTablePr )
			MERGE_PROPERTY( m_nWrapTop, oTablePr )
			MERGE_PROPERTY( m_nWrapBottom, oTablePr )
			MERGE_PROPERTY( m_bOverlap, oTablePr )

			MERGE_PROPERTY_DEF( m_eHRef, oTablePr, hr_none )
			MERGE_PROPERTY_DEF( m_eVRef, oTablePr, vr_none )
			MERGE_PROPERTY_DEF( m_eHPos, oTablePr, hp_none )
			MERGE_PROPERTY_DEF( m_eVPos, oTablePr, vp_none )
			MERGE_PROPERTY( m_nHPos, oTablePr )
			MERGE_PROPERTY( m_nVPos, oTablePr )

			MERGE_PROPERTY( m_nLeft, oTablePr )
			MERGE_PROPERTY( m_nWidth, oTablePr )
			MERGE_PROPERTY_DEF( m_eMUWidth, oTablePr, mu_none )

			MERGE_PROPERTY( m_nDefCellMarBottom, oTablePr )
			MERGE_PROPERTY( m_nDefCellMarRight, oTablePr )
			MERGE_PROPERTY( m_nDefCellMarLeft, oTablePr )
			MERGE_PROPERTY( m_nDefCellMarTop, oTablePr )
			MERGE_PROPERTY( m_nDefCellMarBottomUnits, oTablePr )
			MERGE_PROPERTY( m_nDefCellMarRightUnits, oTablePr )
			MERGE_PROPERTY( m_nDefCellMarLeftUnits, oTablePr )
			MERGE_PROPERTY( m_nDefCellMarTopUnits, oTablePr )

			MERGE_PROPERTY( m_nDefCellSpBottom, oTablePr )
			MERGE_PROPERTY( m_nDefCellSpLeft, oTablePr )
			MERGE_PROPERTY( m_nDefCellSpRight, oTablePr )
			MERGE_PROPERTY( m_nDefCellSpTop, oTablePr )
			MERGE_PROPERTY( m_nDefCellSpBottomUnits, oTablePr )
			MERGE_PROPERTY( m_nDefCellSpLeftUnits, oTablePr )
			MERGE_PROPERTY( m_nDefCellSpRightUnits, oTablePr )
			MERGE_PROPERTY( m_nDefCellSpTopUnits, oTablePr )

			m_oBorderLeft.Merge( oTablePr.m_oBorderLeft );
			m_oBorderRight.Merge( oTablePr.m_oBorderRight );
			m_oBorderTop.Merge( oTablePr.m_oBorderTop );
			m_oBorderBottom.Merge( oTablePr.m_oBorderBottom );
			m_oBorderVert.Merge( oTablePr.m_oBorderVert );
			m_oBorderHor.Merge( oTablePr.m_oBorderHor );
			m_oShading.Merge( oTablePr.m_oShading );

			MERGE_PROPERTY( m_nStyle, oTablePr )

			MERGE_PROPERTY( m_bAutoFirstRow, oTablePr )
			MERGE_PROPERTY( m_bAutoLastRow, oTablePr )
			MERGE_PROPERTY( m_bAutoFirstCol, oTablePr )
			MERGE_PROPERTY( m_bAutoLastCol, oTablePr )
			MERGE_PROPERTY( m_bAutoNoRowBand, oTablePr )
			MERGE_PROPERTY( m_bAutoNoColBand, oTablePr )

			MERGE_PROPERTY( m_nRowBandSize, oTablePr )
			MERGE_PROPERTY( m_nColBandSize, oTablePr )
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};

class RtfFrame: public IRenderableProperty
{
public:typedef enum{hr_none,
				hr_phmrg,
				hr_phpg,
				hr_phcol
				} HRef;
public:typedef enum{vr_none,
				vr_pvmrg,
				vr_pvpg,
				vr_pvpara
					} VRef;
public:typedef enum{hp_none, 
				hp_posxc,
				hp_posxi,
				hp_posxo,
				hp_posxl,
				hp_posxr 
					} HPos;
public:typedef enum{vp_none,
				vp_posyt,
				vp_posyil,
				vp_posyb,
				vp_posyc,
				vp_posyin,
				vp_posyout
				} VPos;
public:typedef enum{tw_none,
				tw_wrapdefault,
				tw_wraparound,
				tw_wraptight,
				tw_wrapthrough
					} TextWrap;


public: int m_nWidth;
public: int m_nHeight;
public: HRef m_eHRef;
public: VRef m_eVRef;
public: HPos m_eHPos;
public: int m_nHPos;
public: VPos m_eVPos;
public: int m_nVPos;
public: int m_bLockAnchor;
public: TextWrap m_eWrap;
public: int m_DropcapType;
public: int m_DropcapLines;
public: int m_nHorSpace;//\dxfrtextN	Distance in twips of a positioned paragraph from text in the main text flow in all directions.
public: int m_nVerSpace;//\dfrmtxtxN	N is the horizontal distance in twips from text on both sides of the frame.
public: int m_nAllSpace;//\dfrmtxtyN	N is the vertical distance in twips from text on both sides of the frame.

public: RtfFrame()
		{
			SetDefault();
		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_nWidth )
			DEFAULT_PROPERTY( m_nHeight )
			DEFAULT_PROPERTY_DEF( m_eHRef, hr_none )
			DEFAULT_PROPERTY_DEF( m_eVRef, vr_none )
			DEFAULT_PROPERTY_DEF( m_eHPos, hp_none )
			DEFAULT_PROPERTY_DEF( m_eVPos, vp_none )
			DEFAULT_PROPERTY( m_nHPos )
			DEFAULT_PROPERTY( m_nVPos )
			DEFAULT_PROPERTY( m_bLockAnchor )
			DEFAULT_PROPERTY_DEF( m_eWrap, tw_none )
			DEFAULT_PROPERTY( m_DropcapType )
			DEFAULT_PROPERTY( m_DropcapLines )
			DEFAULT_PROPERTY( m_nHorSpace )
			DEFAULT_PROPERTY( m_nVerSpace )
			DEFAULT_PROPERTY( m_nAllSpace )
		}
public: void Merge( RtfFrame& oFramePr )
		{
			MERGE_PROPERTY( m_nWidth, oFramePr )
			MERGE_PROPERTY( m_nHeight, oFramePr )
			MERGE_PROPERTY_DEF( m_eHRef, oFramePr, hr_none )
			MERGE_PROPERTY_DEF( m_eVRef, oFramePr, vr_none )
			MERGE_PROPERTY_DEF( m_eHPos, oFramePr, hp_none )
			MERGE_PROPERTY_DEF( m_eVPos, oFramePr, vp_none )
			MERGE_PROPERTY( m_bLockAnchor, oFramePr )
			MERGE_PROPERTY_DEF( m_eWrap, oFramePr, tw_none )
			MERGE_PROPERTY( m_DropcapType, oFramePr )
			MERGE_PROPERTY( m_DropcapLines, oFramePr )
			MERGE_PROPERTY( m_nHorSpace, oFramePr )
			MERGE_PROPERTY( m_nVerSpace, oFramePr )
			MERGE_PROPERTY( m_nAllSpace, oFramePr )
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
public: void ApplyParagraphProp( RtfTableProperty& oProp )
		{
			m_nHPos = oProp.m_nHPos;
			m_nVPos = oProp.m_nVPos;
			switch ( oProp.m_eHRef )
			{
				case RtfTableProperty::hr_phmrg: m_eHRef = hr_phmrg;break;
				case RtfTableProperty::hr_phpg: m_eHRef = hr_phpg;break;
				case RtfTableProperty::hr_phcol: m_eHRef = hr_phcol;break;
			}
			switch ( oProp.m_eVRef )
			{
				case RtfTableProperty::vr_pvmrg: m_eVRef = vr_pvmrg;break;
				case RtfTableProperty::vr_pvpg: m_eVRef = vr_pvpg;break;
				case RtfTableProperty::vr_pvpara: m_eVRef = vr_pvpara;break;
			}
			switch ( oProp.m_eHPos )
			{
				case RtfTableProperty::hp_posxc: m_eHPos = hp_posxc;break;
				case RtfTableProperty::hp_posxi: m_eHPos = hp_posxi;break;
				case RtfTableProperty::hp_posxo: m_eHPos = hp_posxo;break;
				case RtfTableProperty::hp_posxl: m_eHPos = hp_posxl;break;
				case RtfTableProperty::hp_posxr: m_eHPos = hp_posxr;break;
			}
			switch ( oProp.m_eVPos )
			{
				case RtfTableProperty::vp_posyc: m_eVPos = vp_posyc;break;
				case RtfTableProperty::vp_posyin: m_eVPos = vp_posyin;break;
				case RtfTableProperty::vp_posyout: m_eVPos = vp_posyout;break;
				case RtfTableProperty::vp_posyt: m_eVPos = vp_posyt;break;
				case RtfTableProperty::vp_posyb: m_eVPos = vp_posyb;break;
			}
		}
};

class RtfCellProperty: public IRenderableProperty
{		
public: int m_bMergeFirst; //\clmgf	The first cell in a range of table cells to be merged.
public: int m_bMerge; //\clmrg	Contents of the table cell are merged with those of the preceding cell.
public: int m_bMergeFirstVertical; //\clvmgf	The first cell in a range of table cells to be vertically merged.
public: int m_bMergeVertical; //\clvmrg	Contents of the table cell are vertically merged with those of the preceding cell.

public: int m_bFitText; //\clFitText	Fit text in cell, compressing each paragraph to the width of the cell.
public: int m_bNoWrap; //\clNoWrap	Do not wrap text for the cell. Only has an effect if the table cell does not have a preferred \clwWidthN, which overrides \trautofitN.

public: int m_nPaddingLeft; //\clpadlN	Left cell margin or padding. Overrides \trpaddlN.
public: int m_nIsPaddingLeft; //\clpadflN	Units for \clpadlN:
public: int m_nPaddingRight;
public: int m_nIsPaddingRight;
public: int m_nPaddingTop;
public: int m_nIsPaddingTop;
public: int m_nPaddingBottom;
public: int m_nIsPaddingBottom;

public: int m_nSpacingLeft; //\clsplN	Left cell margin or padding. Overrides \trspdlN.
public: int m_nIsSpacingLeft; //\clspflN	Units for \clsplN:
public: int m_nSpacingRight;
public: int m_nIsSpacingRight;
public: int m_nSpacingTop;
public: int m_nIsSpacingTop;
public: int m_nSpacingBottom;
public: int m_nIsSpacingBottom;

public: int m_nWidth; //\clwWidthN	Preferred cell width. Overrides \trautofitN.
public: MetricUnits m_eWidthUnits; //\clftsWidthN	Units for \clwWidthN:

public: int m_bHideMark; //\clhidemark	This control word specifies whether the end of cell glyph shall influence the height of the given table row in the table. If it is specified, then only printing characters in this cell shall be used to determine the row height.

public: RtfBorder m_oBorderDiagonalLR;
public: RtfBorder m_oBorderDiagonalRL;
public: RtfBorder m_oBorderLeft;
public: RtfBorder m_oBorderTop;
public: RtfBorder m_oBorderRight;
public: RtfBorder m_oBorderBottom;
public: RtfBorder m_oBorderInsideH;
public: RtfBorder m_oBorderInsideV;

public: RtfShadingCell m_oShading;

public: typedef enum{ ca_none, 
						ca_Top, //\clvertalt	Text is top-aligned in cell (the default).
						ca_Center, //\clvertalc	Text is centered vertically in cell.
						ca_Bottom  //\clvertalb	Text is bottom-aligned in cell.
							} CellAlign;
public: CellAlign m_eAlign;
public: typedef enum{ cf_none,
						cf_lrtb, //\cltxlrtb	Text in a cell flows from left to right and top to bottom (default).
						cf_tbrl, //\cltxtbrl	Text in a cell flows right to left and top to bottom.
						cf_btlr, //\cltxbtlr	Text in a cell flows left to right and bottom to top.
						cf_lrtbv, //\cltxlrtbv	Text in a cell flows left to right and top to bottom, vertical.
						cf_tbrlv //\cltxtbrlv	Text in a cell flows top to bottom and right to left, vertical.
							} CellFlow;
public: CellFlow m_oCellFlow;

public: int m_nCellx; //\cellxN	Defines the right boundary of a table cell, including its half of the space between cells.
public: int m_nSpan;

//Table Style Specific
public: int m_bStyleFirstRow;//\tscfirstrow	This cell is in the first row.
public: int m_bStyleLastRow;//\tsclastrow	This cell is in the last row.
public: int m_bStyleFirstCol;//\tscfirstcol	This cell is in the first column.
public: int m_bStyleLastCol;//\tsclastcol	This cell is in the last column.
public: int m_bStyleOddRowBand;//\tscbandhorzodd	This cell is in the odd row band.
public: int m_bStyleEvenRowBand;//\tscbandhorzeven	This cell is in the even row band.
public: int m_bStyleOddColBand;//\tscbandvertodd	This cell is in the odd column band.
public: int m_bStyleEvenColBand;//\tscbandverteven	This cell is in the even column band.
public: int m_bStyleNWCell;//\tscnwcell	This is the NW (north west) cell in the table (upper left).
public: int m_bStyleNECell;//\tscnecell	NE cell
public: int m_bStyleSWCell;//\tscswcell	SW cell.
public: int m_bStyleSECell;//\tscsecell	SE cell.

public: RtfCellProperty()
		{
			SetDefault();
		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
			m_nSpan = 1;
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_bMergeFirst )
			DEFAULT_PROPERTY( m_bMerge )
			DEFAULT_PROPERTY( m_bMergeFirstVertical )
			DEFAULT_PROPERTY( m_bMergeVertical )
			DEFAULT_PROPERTY( m_bFitText )
			DEFAULT_PROPERTY( m_bNoWrap )

			DEFAULT_PROPERTY( m_nPaddingLeft )
			DEFAULT_PROPERTY( m_nIsPaddingLeft )
			DEFAULT_PROPERTY( m_nPaddingRight )
			DEFAULT_PROPERTY( m_nIsPaddingRight )
			DEFAULT_PROPERTY( m_nPaddingTop )
			DEFAULT_PROPERTY( m_nIsPaddingTop )
			DEFAULT_PROPERTY( m_nPaddingBottom )
			DEFAULT_PROPERTY( m_nIsPaddingBottom )

			DEFAULT_PROPERTY( m_nSpacingLeft )
			DEFAULT_PROPERTY( m_nIsSpacingLeft )
			DEFAULT_PROPERTY( m_nSpacingRight )
			DEFAULT_PROPERTY( m_nIsSpacingRight )
			DEFAULT_PROPERTY( m_nSpacingTop )
			DEFAULT_PROPERTY( m_nIsSpacingTop )
			DEFAULT_PROPERTY( m_nSpacingBottom )
			DEFAULT_PROPERTY( m_nIsSpacingBottom )

			m_eWidthUnits = mu_none;
			DEFAULT_PROPERTY( m_nWidth )
			DEFAULT_PROPERTY( m_bHideMark )

			m_oBorderDiagonalLR.SetDefault();
			m_oBorderDiagonalRL.SetDefault();
			m_oBorderLeft.SetDefault();
			m_oBorderTop.SetDefault();
			m_oBorderRight.SetDefault();
			m_oBorderBottom.SetDefault();
			m_oBorderInsideH.SetDefault();
			m_oBorderInsideV.SetDefault();
			m_oShading.SetDefault();

			m_eAlign = ca_none;
			m_oCellFlow = cf_none;

			DEFAULT_PROPERTY( m_nCellx )
			DEFAULT_PROPERTY( m_nSpan )

			DEFAULT_PROPERTY( m_bStyleFirstRow )
			DEFAULT_PROPERTY( m_bStyleLastRow )
			DEFAULT_PROPERTY( m_bStyleFirstCol )
			DEFAULT_PROPERTY( m_bStyleLastCol )
			DEFAULT_PROPERTY( m_bStyleOddRowBand )
			DEFAULT_PROPERTY( m_bStyleEvenRowBand )
			DEFAULT_PROPERTY( m_bStyleOddColBand )
			DEFAULT_PROPERTY( m_bStyleEvenColBand )
			DEFAULT_PROPERTY( m_bStyleNWCell )
			DEFAULT_PROPERTY( m_bStyleNECell )
			DEFAULT_PROPERTY( m_bStyleSWCell )
			DEFAULT_PROPERTY( m_bStyleSECell )
		}
public: bool IsValid()
		{
			return PROP_DEF != m_nCellx;
		}

public: void Merge( RtfCellProperty& oCellPr )
		{
			MERGE_PROPERTY( m_bMergeFirst, oCellPr )
			MERGE_PROPERTY( m_bMerge, oCellPr )
			MERGE_PROPERTY( m_bMergeFirstVertical, oCellPr )
			MERGE_PROPERTY( m_bMergeVertical, oCellPr )

			MERGE_PROPERTY( m_bFitText, oCellPr )
			MERGE_PROPERTY( m_bNoWrap, oCellPr )

			MERGE_PROPERTY( m_nPaddingLeft, oCellPr )
			MERGE_PROPERTY( m_nIsPaddingLeft, oCellPr )
			MERGE_PROPERTY( m_nPaddingRight, oCellPr )
			MERGE_PROPERTY( m_nIsPaddingRight, oCellPr )
			MERGE_PROPERTY( m_nPaddingTop, oCellPr )
			MERGE_PROPERTY( m_nIsPaddingTop, oCellPr )
			MERGE_PROPERTY( m_nPaddingBottom, oCellPr )
			MERGE_PROPERTY( m_nIsPaddingBottom, oCellPr )

			MERGE_PROPERTY( m_nSpacingLeft, oCellPr )
			MERGE_PROPERTY( m_nIsSpacingLeft, oCellPr )
			MERGE_PROPERTY( m_nSpacingRight, oCellPr )
			MERGE_PROPERTY( m_nIsSpacingRight, oCellPr )
			MERGE_PROPERTY( m_nSpacingTop, oCellPr )
			MERGE_PROPERTY( m_nIsSpacingTop, oCellPr )
			MERGE_PROPERTY( m_nSpacingBottom, oCellPr )
			MERGE_PROPERTY( m_nIsSpacingBottom, oCellPr )

			MERGE_PROPERTY( m_eWidthUnits, oCellPr )
			MERGE_PROPERTY( m_nWidth, oCellPr )
			MERGE_PROPERTY( m_bHideMark, oCellPr )

			m_oBorderDiagonalLR.Merge( oCellPr.m_oBorderDiagonalLR );
			m_oBorderDiagonalRL.Merge( oCellPr.m_oBorderDiagonalRL );
			m_oBorderLeft.Merge( oCellPr.m_oBorderLeft );
			m_oBorderTop.Merge( oCellPr.m_oBorderTop );
			m_oBorderRight.Merge( oCellPr.m_oBorderRight );
			m_oBorderBottom.Merge( oCellPr.m_oBorderBottom );
			m_oBorderInsideH.Merge( oCellPr.m_oBorderInsideH );
			m_oBorderInsideV.Merge( oCellPr.m_oBorderInsideV );
			m_oShading.Merge( oCellPr.m_oShading );

			MERGE_PROPERTY_DEF( m_eAlign, oCellPr, ca_none )
			MERGE_PROPERTY_DEF( m_oCellFlow, oCellPr, cf_none )

			MERGE_PROPERTY( m_nCellx, oCellPr )
			MERGE_PROPERTY( m_nSpan, oCellPr )

			MERGE_PROPERTY( m_bStyleFirstRow, oCellPr )
			MERGE_PROPERTY( m_bStyleLastRow, oCellPr )
			MERGE_PROPERTY( m_bStyleFirstCol, oCellPr )
			MERGE_PROPERTY( m_bStyleLastCol, oCellPr )
			MERGE_PROPERTY( m_bStyleOddRowBand, oCellPr )
			MERGE_PROPERTY( m_bStyleEvenRowBand, oCellPr )
			MERGE_PROPERTY( m_bStyleOddColBand, oCellPr )
			MERGE_PROPERTY( m_bStyleEvenColBand, oCellPr )
			MERGE_PROPERTY( m_bStyleNWCell, oCellPr )
			MERGE_PROPERTY( m_bStyleNECell, oCellPr )
			MERGE_PROPERTY( m_bStyleSWCell, oCellPr )
			MERGE_PROPERTY( m_bStyleSECell, oCellPr )
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
public: bool GetAlignFromStringRtf(  CString & oAlign, CellAlign& oOutput )
		{
			if( _T("clvertalt") == oAlign ) { oOutput = ca_Top; return true;}
			else if( _T("clvertalc") == oAlign ){ oOutput = ca_Center; return true;}
			else if( _T("clvertalb") == oAlign ){ oOutput = ca_Bottom; return true;}
			return false;
		}
public: bool GetAlignFromStringOOX(  CString & oAlign, CellAlign& oOutput )
		{
			if( _T("top") == oAlign ) { oOutput = ca_Top; return true;}
			else if( _T("center") == oAlign ){ oOutput = ca_Center; return true;}
			else if( _T("bottom") == oAlign ){ oOutput = ca_Bottom; return true;}
			return false;
		}

};
class RtfRowProperty: public RtfTableProperty, public ItemContainer< RtfCellProperty >
{
public: int m_nIndex; //\irowN	N is the row index of this row.
public: int m_nBandIndex; //\irowbandN	N is the row index of the row, adjusted to account for header rows. A header row has a value of –1.

public: int m_bLastRow; //\lastrow	Output if this is the last row in the table.

public: int m_bIsHeader; //\trhdr	Table row header. This row should appear at the top of every page on which the current table appears.
public: int m_bKeep; //\trkeep	Keep table row together. This row cannot be split by a page break. This property is assumed to be off unless the control word is present.

public: int m_nHeight; //\trrhN	Height of a table row in twips. When 0, the height is sufficient for all the text in the line; when positive, the height is guaranteed to be at least the specified height; when negative, the absolute value of the height is used, regardless of the height of the text in the line.

public: int m_nWidthStartInvCell; //\trwWidthBN	Width of invisible cell at the beginning of the row. Used only in cases where rows have different widths.
public: MetricUnits m_eMUStartInvCell; //\trftsWidthBN	Units for \trwWidthBN:

public: int m_nWidthEndInvCell; //\trwWidthAN	Width of invisible cell at the end of the row. Used only when rows have different widths.
public: MetricUnits m_eMUEndInvCell; //\trftsWidthAN	Units for \trwWidthAN:

public: int m_nGridBefore; //для oox
public: int m_nGridAfter; //для oox

public: int m_bStyleFirstRow;//\tscfirstrow	This cell is in the first row.
public: int m_bStyleLastRow;//\tsclastrow	This cell is in the last row.
public: int m_bStyleFirstCol;//\tscfirstcol	This cell is in the first column.
public: int m_bStyleLastCol;//\tsclastcol	This cell is in the last column.
public: int m_bStyleOddRowBand;//\tscbandhorzodd	This cell is in the odd row band.
public: int m_bStyleEvenRowBand;//\tscbandhorzeven	This cell is in the even row band.
public: int m_bStyleOddColBand;//\tscbandvertodd	This cell is in the odd column band.
public: int m_bStyleEvenColBand;//\tscbandverteven	This cell is in the even column band.
public: int m_bStyleNWCell;//\tscnwcell	This is the NW (north west) cell in the table (upper left).
public: int m_bStyleNECell;//\tscnecell	NE cell
public: int m_bStyleSWCell;//\tscswcell	SW cell.
public: int m_bStyleSECell;//\tscsecell	SE cell.

public: RtfRowProperty()
		{
			SetDefault();
		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			RtfTableProperty::SetDefault();

			DEFAULT_PROPERTY( m_nIndex )
			DEFAULT_PROPERTY( m_nBandIndex )
			DEFAULT_PROPERTY( m_bLastRow )
			DEFAULT_PROPERTY( m_nAutoFit )
			DEFAULT_PROPERTY( m_bIsHeader )
			DEFAULT_PROPERTY( m_bKeep )

			DEFAULT_PROPERTY( m_nHeight )

			DEFAULT_PROPERTY( m_nWidthStartInvCell )
			m_eMUStartInvCell = mu_none;
			DEFAULT_PROPERTY( m_nWidthEndInvCell )
			m_eMUEndInvCell = mu_none;
			DEFAULT_PROPERTY( m_nGridBefore )
			DEFAULT_PROPERTY( m_nGridAfter )
			m_aArray.RemoveAll();

			DEFAULT_PROPERTY( m_bStyleFirstRow )
			DEFAULT_PROPERTY( m_bStyleLastRow )
			DEFAULT_PROPERTY( m_bStyleFirstCol )
			DEFAULT_PROPERTY( m_bStyleLastCol )
			DEFAULT_PROPERTY( m_bStyleOddRowBand )
			DEFAULT_PROPERTY( m_bStyleEvenRowBand )
			DEFAULT_PROPERTY( m_bStyleOddColBand )
			DEFAULT_PROPERTY( m_bStyleEvenColBand )
			DEFAULT_PROPERTY( m_bStyleNWCell )
			DEFAULT_PROPERTY( m_bStyleNECell )
			DEFAULT_PROPERTY( m_bStyleSWCell )
			DEFAULT_PROPERTY( m_bStyleSECell )
		}
public: bool IsValid()
		{
			return true;
		}
public: void Merge( RtfRowProperty& oRowPr )
		{
			RtfTableProperty::Merge( oRowPr );

			MERGE_PROPERTY( m_nIndex, oRowPr )
			MERGE_PROPERTY( m_nBandIndex, oRowPr )
			MERGE_PROPERTY( m_bLastRow, oRowPr )

			MERGE_PROPERTY( m_nAutoFit, oRowPr )
			MERGE_PROPERTY( m_bIsHeader, oRowPr )
			MERGE_PROPERTY( m_bKeep, oRowPr )

			MERGE_PROPERTY( m_nHeight, oRowPr )

			MERGE_PROPERTY( m_nWidthStartInvCell, oRowPr )
			MERGE_PROPERTY_DEF( m_eMUStartInvCell, oRowPr, mu_none )
			MERGE_PROPERTY( m_nWidthEndInvCell, oRowPr )
			MERGE_PROPERTY_DEF( m_eMUEndInvCell, oRowPr, mu_none )

			MERGE_PROPERTY_DEF( m_nGridBefore, oRowPr, mu_none )
			MERGE_PROPERTY_DEF( m_nGridAfter, oRowPr, mu_none )

			MERGE_PROPERTY( m_bStyleFirstRow, oRowPr )
			MERGE_PROPERTY( m_bStyleLastRow, oRowPr )
			MERGE_PROPERTY( m_bStyleFirstCol, oRowPr )
			MERGE_PROPERTY( m_bStyleLastCol, oRowPr )
			MERGE_PROPERTY( m_bStyleOddRowBand, oRowPr )
			MERGE_PROPERTY( m_bStyleEvenRowBand, oRowPr )
			MERGE_PROPERTY( m_bStyleOddColBand, oRowPr )
			MERGE_PROPERTY( m_bStyleEvenColBand, oRowPr )
			MERGE_PROPERTY( m_bStyleNWCell, oRowPr )
			MERGE_PROPERTY( m_bStyleNECell, oRowPr )
			MERGE_PROPERTY( m_bStyleSWCell, oRowPr )
			MERGE_PROPERTY( m_bStyleSECell, oRowPr )
		}

public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};


class RtfParagraphProperty: public IRenderableProperty
{
public: int m_bAutoHyphenation; //\hyphpar	Switches automatic hyphenation for the paragraph. Append 1 or nothing to toggle property on; append 0 to turn it off.
public: int m_bInTable; //\intbl	Paragraph is part of a table.
public: int m_nItap; //\itapN	Paragraph nesting level, where 0 is the main document, 1 is a table cell, 2 is a nested table cell, 3 is a doubly nested table cell, and so forth (default is 1).
public: int m_bKeep; //\keep	Keep paragraph intact (completely on one page if possible).
public: int m_bKeepNext; //\keepn	Keep paragraph with the next paragraph.
public: int m_bPageBB; //\pagebb	Break page before the paragraph.
public: int m_nOutlinelevel;//\outlinelevelN	Outline level of paragraph. The N argument is a value from 0 to 8 representing the outline level of the paragraph. In the default case, no outline level is specified (same as body text).
public: int m_nStyle; //\sN	Designates paragraph style. If a paragraph style is specified, style properties must be specified with the paragraph. N references an entry in the style sheet.

public: typedef enum {pa_none,
						pa_qc, //\qc	Centered.
						pa_qj, //\qj	Justified.
						pa_ql, //\ql	Left-aligned (the default).
						pa_qr, //\qr	Right-aligned.
						pa_qd, //\qd	Distributed.
						pa_qk0, //\qkN	Percentage of line occupied by Kashida justification (0 – low, 10 – medium, 20 – high).
						pa_qk10, //
						pa_qk20, //
							} ParagraphAlign;
public: ParagraphAlign m_eAlign;
public: typedef enum {fa_none,
						fa_faauto, //\faauto	Font alignment. The default setting for this is "Auto."
						fa_fahang, //\fahang	Font alignment: Hanging.
						fa_facenter, //\facenter	Font alignment: Center.
						fa_faroman, //\faroman	Font alignment: Roman (default).
						fa_favar, //\favar	Font alignment: Upholding variable.
						fa_fafixed, //\fafixed	Font alignment: Upholding fixed.
							} FontAlign;
public: FontAlign m_eFontAlign;

public: int m_nIndFirstLine; //\fiN	First-line indent in twips (default is 0).
public: int m_nIndLeft; //\liN	Left indent in twips (default is 0).
public: int m_nIndRight; //\riN	Right indent in twips (default is 0).
public: int m_nIndStart; //\linN	Left indent for left-to-right paragraphs; right indent for right-to-left paragraphs (default is 0). \linN defines space before the paragraph.
public: int m_nIndEnd; //\rinN	Right indent for left-to-right paragraphs; left indent for right-to-left paragraphs (default is 0). \rinN defines space after the paragraph.
public: int m_bIndRightAuto; //\adjustright	Automatically adjust right indent when document grid is defined.
public: int m_bIndMirror; //\indmirror...

public: int m_nSpaceBefore; //\sbN	Space before in twips (default is 0).
public: int m_nSpaceAfter; //\saN	Space after in twips (default is 0).
public: int m_nSpaceBeforeAuto; //\sbautoN	Auto spacing before:
public: int m_nSpaceAfterAuto; //\saautoN	Auto spacing after:
public: int m_nSpaceBeforeLine; //\lisbN	Space before in hundredths of a character unit. Overrides \sbN, although they should both be emitted with equivalent values.
public: int m_nSpaceAfterLine; //\lisaN	Space after in hundredths of a character unit. Overrides \saN, although they should both be emitted with equivalent values.
public: int m_nSpaceBetween; //\slN	Space between lines. If this control word is missing or if \sl0 is used, the line spacing is automatically determined by the tallest character in the line. If N is a positive value, this size is used only if it is taller than the tallest character (otherwise, the tallest character is used); if N is a negative value, the absolute value of N is used, even if it is shorter than the tallest character.
public: int m_nSpaceMultiLine; //\slmultN
public: int m_bContextualSpacing; //\contextualspace

public: int m_bRtl; //\rtlpar	Text in this paragraph will display with right-to-left precedence.
public: int m_bNoWordWrap; //\nowwrap
public: int m_bSnapToGrid; //\nosnaplinegrid	Disable snap line to grid.

public: typedef enum {tbw_none,
						tbw_txbxtwno, //\txbxtwno
						tbw_txbxtwalways, //\txbxtwalways
						tbw_txbxtwfirstlast, //\txbxtwfirstlast
						tbw_txbxtwfirst, //\txbxtwfirst
						tbw_txbxtwlast, //\txbxtwlast

							} TextBoxWrap;
public: TextBoxWrap m_eTextBoxWrap; //1
public: int m_nListId; //\lsN	Should exactly match the \lsN for one of the list overrides in the List Override table.
public: int m_nListLevel; //\ilvlN	The 0-based level of the list to which the paragraph belongs. For all simple lists, N should always be 0. For multilevel lists, it can be 0 through 8. The value 9 is never used. The values 10 through 12 have the special meanings for documents generated by Word 6: 10 = ilvlBullet (a bulleted paragraph in Word 6), 11 = ilvlList (a numbered paragraph in Word 6), 12 = ilvlContinue (a paragraph that was not itself numbered, but took its indenting scheme from its numbering properties and did not “break” numbering (that in Word 6 required otherwise contiguous paragraphs).

public: RtfShadingPar m_oShading; //

public: RtfBorder m_oBorderTop; //
public: RtfBorder m_oBorderLeft; //
public: RtfBorder m_oBorderBottom; //
public: RtfBorder m_oBorderRight; //
public: RtfBorder m_oBorderBox; //
public: RtfBorder m_oBorderBar; //

public: RtfFrame m_oFrame; //
public: int m_bOverlap;//1\absnoovrlpN	Allow overlap with other frames or objects with similar wrapping:
public: typedef enum{tf_none,
				tf_frmtxlrtb, //\frmtxlrtb	Frame box flows from left to right and top to bottom (default).
				tf_frmtxtbrl, //\frmtxtbrl	Frame box flows right to left and top to bottom.
				tf_frmtxbtlr, //\frmtxbtlr	Frame box flows left to right and bottom to top.
				tf_frmtxlrtbv, //\frmtxlrtbv	Frame box flows left to right and top to bottom, vertical.
				tf_frmtxtbrlv  //\frmtxtbrlv	Frame box flows top to bottom and right to left, vertical.
					} TextFollow;
public: TextFollow m_eTextFollow;
public: RtfTabs m_oTabs;

//Table Style Specific
public: int m_nTableStyle;//\ytsN	Designates the table style handle that was applied to the row/cell.
public: int m_bStyleFirstRow;//\tscfirstrow	This cell is in the first row.
public: int m_bStyleLastRow;//\tsclastrow	This cell is in the last row.
public: int m_bStyleFirstCollumn;//\tscfirstcol	This cell is in the first column.
public: int m_bStyleLastCollumn;//\tsclastcol	This cell is in the last column.
public: int m_bStyleOddRowBand;//\tscbandhorzodd	This cell is in the odd row band.
public: int m_bStyleEvenRowBand;//\tscbandhorzeven	This cell is in the even row band.
public: int m_bStyleOddColBand;//\tscbandvertodd	This cell is in the odd column band.
public: int m_bStyleEvenColBand;//\tscbandverteven	This cell is in the even column band.
public: int m_bStyleNWCell;//\tscnwcell	This is the NW (north west) cell in the table (upper left).
public: int m_bStyleNECell;//\tscnecell	NE cell.
public: int m_bStyleSWCell;//\tscswcell	SW cell.
public: int m_bStyleSECell;//\tscsecell	SE cell.

public: RtfCharProperty m_oCharProperty;

public: RtfParagraphProperty()
		{
			SetDefault();
		}
public: bool IsValid()
		{
			return true;
		}
public: void SetDefaultRtf()
		{
			SetDefault();
			m_nSpaceAfter = 0;
			m_nSpaceBetween = 240;
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_bAutoHyphenation )
			DEFAULT_PROPERTY( m_bInTable )
			DEFAULT_PROPERTY( m_nItap )
			DEFAULT_PROPERTY( m_bKeep )
			DEFAULT_PROPERTY( m_bKeepNext )
			DEFAULT_PROPERTY( m_bPageBB )
			DEFAULT_PROPERTY( m_nOutlinelevel )
			DEFAULT_PROPERTY( m_nStyle )

			m_eAlign = pa_none;
			m_eFontAlign = fa_none;

			DEFAULT_PROPERTY( m_nIndFirstLine )
			DEFAULT_PROPERTY( m_nIndLeft)
			DEFAULT_PROPERTY( m_nIndRight)
			DEFAULT_PROPERTY( m_nIndStart )
			DEFAULT_PROPERTY( m_nIndEnd )
			DEFAULT_PROPERTY( m_bIndRightAuto )
			DEFAULT_PROPERTY( m_bIndMirror )


			DEFAULT_PROPERTY( m_nSpaceBefore )
			
			DEFAULT_PROPERTY( m_nSpaceAfter )
			DEFAULT_PROPERTY( m_nSpaceBeforeAuto )
			DEFAULT_PROPERTY( m_nSpaceAfterAuto )
			DEFAULT_PROPERTY( m_nSpaceAfterLine )
			DEFAULT_PROPERTY( m_nSpaceBeforeLine )
			DEFAULT_PROPERTY( m_nSpaceBetween )
			DEFAULT_PROPERTY( m_nSpaceMultiLine )
			DEFAULT_PROPERTY( m_bContextualSpacing )

			DEFAULT_PROPERTY( m_bRtl )
			DEFAULT_PROPERTY( m_bNoWordWrap )
			DEFAULT_PROPERTY( m_bSnapToGrid )

			m_eTextBoxWrap = tbw_none;

			DEFAULT_PROPERTY( m_nListId )
			DEFAULT_PROPERTY( m_nListLevel )

			m_oShading.SetDefault();

			m_oBorderTop.SetDefault();
			m_oBorderLeft.SetDefault();
			m_oBorderBottom.SetDefault();
			m_oBorderRight.SetDefault();
			m_oBorderBox.SetDefault();
			m_oBorderBar.SetDefault();

			m_oFrame.SetDefault();
			DEFAULT_PROPERTY( m_bOverlap )
			m_eTextFollow = tf_none;
			m_oTabs.SetDefault();

			DEFAULT_PROPERTY( m_nTableStyle )
			DEFAULT_PROPERTY( m_bStyleFirstRow )
			DEFAULT_PROPERTY( m_bStyleLastRow )
			DEFAULT_PROPERTY( m_bStyleFirstCollumn )
			DEFAULT_PROPERTY( m_bStyleLastCollumn )
			DEFAULT_PROPERTY( m_bStyleOddRowBand )
			DEFAULT_PROPERTY( m_bStyleOddColBand )
			DEFAULT_PROPERTY( m_bStyleEvenRowBand )
			DEFAULT_PROPERTY( m_bStyleEvenColBand )
			DEFAULT_PROPERTY( m_bStyleNWCell )
			DEFAULT_PROPERTY( m_bStyleNECell )
			DEFAULT_PROPERTY( m_bStyleSWCell )
			DEFAULT_PROPERTY( m_bStyleSECell )

			m_oCharProperty.SetDefault();
		}
public: void Merge( RtfParagraphProperty& oParPr )
		{
			MERGE_PROPERTY( m_bAutoHyphenation, oParPr )
			MERGE_PROPERTY( m_bInTable, oParPr )
			MERGE_PROPERTY( m_nItap, oParPr )
			MERGE_PROPERTY( m_bKeep, oParPr )
			MERGE_PROPERTY( m_bKeepNext, oParPr )
			MERGE_PROPERTY( m_bPageBB, oParPr )
			MERGE_PROPERTY( m_nOutlinelevel, oParPr )
			MERGE_PROPERTY( m_nStyle, oParPr )
			MERGE_PROPERTY_DEF( m_eAlign, oParPr, pa_none )
			MERGE_PROPERTY_DEF( m_eFontAlign, oParPr, fa_none )
			MERGE_PROPERTY( m_nIndFirstLine, oParPr )
			MERGE_PROPERTY( m_nIndLeft, oParPr )
			MERGE_PROPERTY( m_nIndRight, oParPr )
			MERGE_PROPERTY( m_nIndStart, oParPr )
			MERGE_PROPERTY( m_nIndEnd, oParPr )
			MERGE_PROPERTY( m_bIndRightAuto, oParPr )
			MERGE_PROPERTY( m_bIndMirror, oParPr )

			MERGE_PROPERTY( m_nSpaceBefore, oParPr )
			MERGE_PROPERTY( m_nSpaceAfter, oParPr )
			MERGE_PROPERTY( m_nSpaceBeforeAuto, oParPr )
			MERGE_PROPERTY( m_nSpaceAfterAuto, oParPr )
			MERGE_PROPERTY( m_nSpaceBeforeLine, oParPr )
			MERGE_PROPERTY( m_nSpaceAfterLine, oParPr )
			MERGE_PROPERTY( m_nSpaceBetween, oParPr )
			MERGE_PROPERTY( m_nSpaceMultiLine, oParPr )
			MERGE_PROPERTY( m_bSnapToGrid, oParPr )
			MERGE_PROPERTY( m_bContextualSpacing, oParPr )

			MERGE_PROPERTY( m_bRtl, oParPr )
			MERGE_PROPERTY( m_bNoWordWrap, oParPr )
			MERGE_PROPERTY_DEF( m_eTextBoxWrap, oParPr, tbw_none )

			MERGE_PROPERTY( m_nListId, oParPr )
			MERGE_PROPERTY( m_nListLevel, oParPr )

			m_oShading.Merge( oParPr.m_oShading );
			m_oBorderTop.Merge( oParPr.m_oBorderTop );
			m_oBorderLeft.Merge( oParPr.m_oBorderLeft );
			m_oBorderBottom.Merge( oParPr.m_oBorderBottom );
			m_oBorderRight.Merge( oParPr.m_oBorderRight );
			m_oBorderBox.Merge( oParPr.m_oBorderBox );
			m_oBorderBar.Merge( oParPr.m_oBorderBar );

			m_oFrame.Merge( oParPr.m_oFrame );

			MERGE_PROPERTY( m_bOverlap, oParPr )
			MERGE_PROPERTY_DEF( m_eTextFollow, oParPr, tf_none )

			m_oTabs.Merge( oParPr.m_oTabs );

			MERGE_PROPERTY( m_nTableStyle, oParPr )
			MERGE_PROPERTY( m_bStyleFirstRow, oParPr )
			MERGE_PROPERTY( m_bStyleLastRow, oParPr )
			MERGE_PROPERTY( m_bStyleFirstCollumn, oParPr )
			MERGE_PROPERTY( m_bStyleLastCollumn, oParPr )
			MERGE_PROPERTY( m_bStyleOddRowBand, oParPr )
			MERGE_PROPERTY( m_bStyleEvenRowBand, oParPr )
			MERGE_PROPERTY( m_bStyleOddColBand, oParPr )
			MERGE_PROPERTY( m_bStyleEvenColBand, oParPr )
			MERGE_PROPERTY( m_bStyleNWCell, oParPr )
			MERGE_PROPERTY( m_bStyleNECell, oParPr )
			MERGE_PROPERTY( m_bStyleSWCell, oParPr )
			MERGE_PROPERTY( m_bStyleSECell, oParPr )

			//m_oCharProperty.Merge( oParPr.m_oCharProperty );
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
//class RtfParagraphPropertyWithTable: public RtfParagraphProperty
//{
//public: RtfRowProperty m_oRowProperty;
//public: RtfCellProperty m_oCellProperty;
//
//public: RtfParagraphPropertyWithTable()
//		{
//			SetDefault();
//		}
//public: void SetDefaultRtfPar()
//		{
//			RtfParagraphProperty::SetDefaultRtf();
//		}
//public: void SetDefaultRtfTable()
//		{
//			m_oRowProperty.SetDefaultRtf();
//		}
//public: void SetDefault()
//		{
//			RtfParagraphProperty::SetDefault();
//			m_oRowProperty.SetDefault();
//		}
//public: CString RenderToRtf(RenderParameter oRenderParameter)
//		{
//			CString sResult;
//			sResult.Append( m_oRowProperty.RenderToRtf(  oRenderParameter  ) );
//			sResult.Append(_T(" {")+RtfParagraphProperty::RenderToRtf(  oRenderParameter  )+_T(" }") );
//			return sResult;
//		}
//};
class RtfTime: public IRenderableProperty
		{
public: int m_nYear;
public: int m_nMonth;
public: int m_nDay;
public: int m_nHour;
public: int m_nMin;
public: int m_nSecond;
public: RtfTime()
		{
			SetDefault();
		}
public: bool IsValid()
		{
			return true;
		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( m_nYear )
			DEFAULT_PROPERTY( m_nMonth )
			DEFAULT_PROPERTY( m_nDay )
			DEFAULT_PROPERTY( m_nHour )
			DEFAULT_PROPERTY( m_nMin )
			DEFAULT_PROPERTY( m_nSecond )
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
		};
class RtfInformation: public IRenderableProperty
{

public:  CString m_sTitle;
public:  CString m_sSubject;
public:  CString m_sAuthor;
public:  CString m_sManager;
public:  CString m_sCompany;
public:  CString m_sOperator;
public:  CString m_sCategory;
public:  CString m_sKeywords;
public:  CString m_sComment;
public:  CString m_sDocCom;
public:  CString m_sLinkBase;
public:  RtfTime m_oCreateTime;
public:  RtfTime m_oRevTime;
public:  RtfTime m_oPrintTime;
public:  RtfTime m_oBackupTime;


public: int m_nVersion;
public: int m_nInternalVersion;
public: int m_nEndingTime;

public: int m_nNumberOfPages;
public: int m_nNumberOfWords;
public: int m_nNumberOfCharactersWithSpace;
public: int m_nNumberOfCharactersWithoutSpace;
public: int m_nInternalId;
public: RtfInformation()
		{
			SetDefault();
		}
public: bool IsValid()
		{
			return true;
		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			m_sTitle = _T("");
			m_sSubject = _T("");
			m_sAuthor = _T("");
			m_sManager = _T("");
			m_sCompany = _T("");
			m_sOperator = _T("");
			m_sCategory = _T("");
			m_sKeywords = _T("");
			m_sComment = _T("");
			m_sDocCom = _T("");
			m_sLinkBase = _T("");
			m_oCreateTime.SetDefault();
			m_oRevTime.SetDefault();
			m_oPrintTime.SetDefault();
			m_oBackupTime.SetDefault();

			DEFAULT_PROPERTY( m_nVersion )
			DEFAULT_PROPERTY( m_nInternalVersion )
			DEFAULT_PROPERTY( m_nEndingTime )

			DEFAULT_PROPERTY( m_nNumberOfPages )
			DEFAULT_PROPERTY( m_nNumberOfWords )
			DEFAULT_PROPERTY( m_nNumberOfCharactersWithSpace )
			DEFAULT_PROPERTY( m_nNumberOfCharactersWithoutSpace )
			DEFAULT_PROPERTY( m_nInternalId )
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};

class RtfCharStyle: public RtfStyle
{
public: RtfCharProperty m_oCharProp;

public:RtfCharStyle()
	   {
		   SetDefault();
		   m_eType = stCharacter;
	   }
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_STYLE_CHAR;
		}
public: void Merge( RtfStylePtr oStyle );
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfParagraphStyle: public RtfCharStyle
{
public: RtfParagraphProperty m_oParProp;

public:RtfParagraphStyle()
	   {
		   SetDefault();
		   m_eType = stParagraph;
	   }
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_STYLE_PARAGRAPH;
		}
public: void Merge( RtfStylePtr oStyle );
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
//class RtfTableStyleProperty : public IRenderableProperty
//{
//public: typedef enum{ av_none,
//			av_tsvertalt, //\tsvertalt	Top vertical alignment of cell
//			av_tsvertalc, //\tsvertalc	Center vertical alignment of cell
//			av_tsvertalb //\tsvertalb	Bottom vertical alignment of cell
//		}AlignVertical;
//public: int m_nPaddingLeft; //\tscellpaddlN	Left padding value.
//public: int m_nIsPaddingLeft; //\tscellpaddflN	Units for \tscellpaddlN
//public: int m_nPaddingRight; //\tscellpaddrN	Right padding value
//public: int m_nIsPaddingRight; //\tscellpaddfrN	Units for \tscellpaddrN
//public: int m_nPaddingTop; //\tscellpaddtN	Top padding value.
//public: int m_nIsPaddingTop; //\tscellpaddftN	Units for \tscellpaddtN 
//public: int m_nPaddingBottom; //\tscellpaddbN	Bottom padding value
//public: int m_nIsPaddingBottom; //\tscellpaddfbN	Units for \tscellpaddbN
//
//public: AlignVertical m_eAlign;
//public: int m_bNoCellWrap;//\tsnowrap	No cell wrapping
//
//public: RtfShadingTableStyle m_oShading;
//
//
//public: RtfBorder m_oCellTopBorder; //\tsbrdrt	Top border for cell
//public: RtfBorder m_oCellBottomBorder; //\tsbrdrb	Bottom border for cell
//public: RtfBorder m_oCellLeftBorder; //\tsbrdrl	Left border for cell
//public: RtfBorder m_oCellRightBorder; //\tsbrdrr	Right border for cell
//public: RtfBorder m_oCellHorBorder; //\tsbrdrh	Horizontal (inside) border for cell
//public: RtfBorder m_oCellVerBorder; //\tsbrdrv	Vertical (inside) border for cell
//public: int m_nRowBandNumber; //\tscbandshN	Count of rows in a row band
//public: int m_nCellBandNumber; //\tscbandsvN	Count of cells in a cell band
//
//public: RtfTableStyleProperty()
//		{
//			SetDefault();
//		}
//public: void SetDefault()
//		{
//			DEFAULT_PROPERTY( m_nPaddingLeft )
//			DEFAULT_PROPERTY( m_nIsPaddingLeft )
//			DEFAULT_PROPERTY( m_nPaddingRight )
//			DEFAULT_PROPERTY( m_nIsPaddingRight )
//			DEFAULT_PROPERTY( m_nPaddingTop )
//			DEFAULT_PROPERTY( m_nIsPaddingTop )
//			DEFAULT_PROPERTY( m_nPaddingBottom )
//			DEFAULT_PROPERTY( m_nIsPaddingBottom )
//			m_eAlign = av_none;
//			DEFAULT_PROPERTY( m_bNoCellWrap )
//			DEFAULT_PROPERTY( m_nRowBandNumber )
//			DEFAULT_PROPERTY( m_nCellBandNumber )
//
//			m_oShading.SetDefault();
//			m_oCellTopBorder.SetDefault();
//			m_oCellBottomBorder.SetDefault();
//			m_oCellLeftBorder.SetDefault();
//			m_oCellRightBorder.SetDefault();
//			m_oCellHorBorder.SetDefault();
//			m_oCellVerBorder.SetDefault();
//		}
//public: CString RenderToRtf(RenderParameter oRenderParameter);
//public: CString RenderToOOX(RenderParameter oRenderParameter);
//};
class RtfTableStyle;
typedef boost::shared_ptr<RtfTableStyle> RtfTableStylePtr;
class RtfTableStyle: public RtfParagraphStyle
{
public: RtfTableProperty m_oTableProp;
public: RtfRowProperty m_oRowProp;
public: RtfCellProperty m_oCellProp;

//public: RtfTableStyleProperty m_oTableStyleProperty;

public: RtfTableStylePtr m_oFirstRow;
public: RtfTableStylePtr m_oLastRow;
public: RtfTableStylePtr m_oFirstCol;
public: RtfTableStylePtr m_oLastCol;
public: RtfTableStylePtr m_oBandHorEven;
public: RtfTableStylePtr m_oBandVerEven;
public: RtfTableStylePtr m_oBandHorOdd;
public: RtfTableStylePtr m_oBandVerOdd;
public: RtfTableStylePtr m_oNWCell;
public: RtfTableStylePtr m_oNECell;
public: RtfTableStylePtr m_oSWCell;
public: RtfTableStylePtr m_oSECell;
public:RtfTableStyle()
	   {
		   SetDefault();
			m_eType = stTable;
	   }
public:void SetDefault()
	   {
		   RtfStyle::SetDefault();
			m_oFirstRow = RtfTableStylePtr();
			m_oLastRow = RtfTableStylePtr();
			m_oFirstCol = RtfTableStylePtr();
			m_oLastCol = RtfTableStylePtr();
			m_oBandHorEven = RtfTableStylePtr();
			m_oBandVerEven = RtfTableStylePtr();
			m_oBandHorOdd = RtfTableStylePtr();
			m_oBandVerOdd = RtfTableStylePtr();
			m_oNWCell = RtfTableStylePtr();
			m_oNECell = RtfTableStylePtr();
			m_oSWCell = RtfTableStylePtr();
			m_oSECell = RtfTableStylePtr();
	   }
public: int GetType()
		{
			return TYPE_RTF_PROPERTY_STYLE_TABLE;
		}
public: void Merge( RtfStylePtr oStyle );
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};




class RtfMathProperty: public IRenderableProperty
{
public: int mbrkBin;
public: int mbrkBinSub;
public: int mdefJc;
public: int mdispDef;
public: int minterSp;
public: int mintraSp;
public: int mlMargin;
public: int mmathFont;
public: int mnaryLim;
public: int mpostSp;
public: int mpreSp;
public: int mrMargin;
public: int msmallFrac;
public: int mwrapIndent;
public: int mwrapRight;
public: RtfMathProperty()
		{
			SetDefault();
		}

//public: bool IsValid()
//		{
//			return PROP_DEF != mbrkBin || PROP_DEF != mbrkBinSub || PROP_DEF != mdispDef || PROP_DEF != minterSp ||
//					 PROP_DEF != mintraSp || PROP_DEF != mlMargin || PROP_DEF != mmathFont || PROP_DEF != mnaryLim ||
//					  PROP_DEF != mpostSp || PROP_DEF != mpreSp || PROP_DEF != mrMargin || PROP_DEF != msmallFrac ||
//					   PROP_DEF != mwrapIndent || PROP_DEF != mwrapRight ;
//		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( mbrkBin )
			DEFAULT_PROPERTY( mbrkBinSub )
			mdefJc = 1; //centered as a group 
			DEFAULT_PROPERTY( mdispDef )
			DEFAULT_PROPERTY( minterSp )
			DEFAULT_PROPERTY( mintraSp )
			DEFAULT_PROPERTY( mlMargin )
			DEFAULT_PROPERTY( mmathFont )
			DEFAULT_PROPERTY( mnaryLim )
			DEFAULT_PROPERTY( mpostSp )
			DEFAULT_PROPERTY( mpreSp )
			DEFAULT_PROPERTY( mrMargin )
			DEFAULT_PROPERTY( msmallFrac )
			DEFAULT_PROPERTY( mwrapIndent )
			DEFAULT_PROPERTY( mwrapRight )
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};
class RtfMathSpecProp: public IRenderableProperty
{
//moMathParaPr  
public: int moMathParaPr;
//moMath 
public: int Font;
//mboxPr 
public: int Break;
//meqArrPr 
public: int RowSpacing;
public: int RowSpacingRule;
//mmPr 
public: int CellGap;
public: int CellGapRule;
public: int CellSpacing;
//msSubSupPr 
public: int malnScr;
//borderBoxPrp
public: int HideLeft;
public: int HideTop;
public: int HideRight;
public: int HideBottom;
public: int StrikeHor;
public: int StrikeVer;
public: int StrikeLR;
public: int StrikeRL;
//boxPrp
public: int Alignment;
public: int Differential;
public: int NoBreak;
public: int Emulator;
//mrPr
public: int NormalText;
public: int mscr;
public: int msty;
public: int mlit;
//phantPrp
public: int mshow;
public: int mtransp;
public: int mzeroAsc;
public: int mzeroDesc;
public: int mzeroWid;
//mchr
public: int mchr;
//charProp
public: RtfCharProperty m_oCharProp;

public: RtfMathSpecProp()
		{
			SetDefault();
		}
public: bool IsValid()
		{
			return true;
		}
public: void SetDefaultRtf()
		{
			SetDefault();
		}
public: void SetDefaultOOX()
		{
			SetDefault();
		}
public: void SetDefault()
		{
			DEFAULT_PROPERTY( moMathParaPr )
			DEFAULT_PROPERTY( Font )
			DEFAULT_PROPERTY( Break )
			DEFAULT_PROPERTY( RowSpacing )
			DEFAULT_PROPERTY( RowSpacingRule )
			DEFAULT_PROPERTY( CellGap )
			DEFAULT_PROPERTY( CellGapRule )
			DEFAULT_PROPERTY( CellSpacing )
			DEFAULT_PROPERTY( malnScr )


			DEFAULT_PROPERTY( HideLeft )
			DEFAULT_PROPERTY( HideTop )
			DEFAULT_PROPERTY( HideRight )
			DEFAULT_PROPERTY( HideBottom )
			DEFAULT_PROPERTY( StrikeHor )
			DEFAULT_PROPERTY( StrikeVer )

			DEFAULT_PROPERTY( StrikeLR )
			DEFAULT_PROPERTY( StrikeRL )
			DEFAULT_PROPERTY( Alignment )
			DEFAULT_PROPERTY( Differential )

			DEFAULT_PROPERTY( NoBreak )
			DEFAULT_PROPERTY( Emulator )
			DEFAULT_PROPERTY( NormalText )

			DEFAULT_PROPERTY( mscr )
			DEFAULT_PROPERTY( msty )
			DEFAULT_PROPERTY( mlit )
			DEFAULT_PROPERTY( mshow )
			DEFAULT_PROPERTY( mtransp )
			DEFAULT_PROPERTY( mzeroAsc )
			DEFAULT_PROPERTY( mzeroDesc )
			DEFAULT_PROPERTY( mzeroWid )

			DEFAULT_PROPERTY( mchr )

			m_oCharProp.SetDefault();
		}
public: CString RenderToRtf(RenderParameter oRenderParameter);
public: CString RenderToOOX(RenderParameter oRenderParameter);
};

typedef boost::shared_ptr<RtfMathSpecProp> RtfMathSpecPropPtr;
typedef boost::shared_ptr<RtfMathProperty> RtfMathPropertyPtr;

//typedef boost::shared_ptr<RtfTableStyleProperty> RtfTableStylePropertyPtr;
typedef boost::shared_ptr<RtfCharStyle> RtfCharStylePtr;
typedef boost::shared_ptr<RtfParagraphStyle> RtfParagraphStylePtr;
typedef boost::shared_ptr<RtfInformation> RtfInformationPtr;
typedef boost::shared_ptr<RtfTime> RtfTimePtr;
typedef boost::shared_ptr<RtfParagraphProperty> RtfParagraphPropertyPtr;
typedef boost::shared_ptr<RtfRowProperty> RtfRowPropertyPtr;
typedef boost::shared_ptr<RtfCellProperty> RtfCellPropertyPtr;
typedef boost::shared_ptr<RtfFrame> RtfFramePtr;
typedef boost::shared_ptr<RtfTableProperty> RtfTablePropertyPtr;
typedef boost::shared_ptr<RtfTab> RtfTabPtr;
//typedef boost::shared_ptr<RtfStyleException> RtfStyleExceptionPtr;

typedef boost::shared_ptr<RtfListOverrideProperty> RtfListOverridePropertyPtr;
typedef boost::shared_ptr<RtfListProperty> RtfListPropertyPtr;
typedef boost::shared_ptr<RtfListLevelProperty> RtfListLevelPropertyPtr;
typedef boost::shared_ptr<RtfCharProperty> RtfCharPropertyPtr;
typedef boost::shared_ptr<RtfBorder> RtfBorderPtr;
typedef boost::shared_ptr<RtfShadingTableStyle> RtfShadingTableStylePtr;
typedef boost::shared_ptr<RtfShadingRow> RtfShadingRowPtr;
typedef boost::shared_ptr<RtfShadingCell> RtfShadingCellPtr;
typedef boost::shared_ptr<RtfShadingChar> RtfShadingCharPtr;
typedef boost::shared_ptr<RtfShadingPar> RtfShadingParPtr;
typedef boost::shared_ptr<RtfShading> RtfShadingPtr;
typedef boost::shared_ptr<RtfColor> RtfColorPtr;
typedef boost::shared_ptr<RtfFont> RtfFontPtr;
//typedef boost::shared_ptr<RtfColorSchemeMapping> RtfColorSchemeMappingPtr;