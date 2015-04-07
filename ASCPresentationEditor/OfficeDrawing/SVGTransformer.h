#pragma once

//#include "../../../Interfaces/AVSRenderer.h"
//#include "../../../../../AVSOfficeStudio/Common/OfficeFileErrorDescription.h"
//#include "../../../../../../../Common/GdiPlusEx.h"
//#include "../../DesktopEditor/graphics/IRenderer.h"
#include "SVGFramework.h"

// ISVGTransformer
//[
//	object,
//	uuid("89CCD2D4-3A3B-438C-A45F-7401AFB901A2"),
//	dual,	helpstring("ISVGTransformer Interface"),
//	pointer_default(unique)
//]
//__interface ISVGTransformer : IDispatch
//{
//	[id(10101)] HRESULT LoadFile([in] BSTR File);
//	[id(10102)] HRESULT Load([in] BSTR Str);
//
//	[id(10103)] HRESULT Draw([in] IUnknown* pUnk, [in] double dX, [in] double dY, [in] double dWidth, [in] double dHeight);
//	[id(10104), propget] HRESULT Width([out, retval] LONG* Width);
//	[id(10105), propget] HRESULT Height([out, retval] LONG* Height);
//	[id(10106), propget] HRESULT Metrics([out, retval] LONG* Metrics);
//
//	[id(10201)]	HRESULT SetAdditionalParam([in] BSTR ParamName, [in] VARIANT	ParamValue);
//	[id(10202)]	HRESULT GetAdditionalParam([in] BSTR ParamName, [out] VARIANT *	ParamValue);
//};
//
//// _ISVGDrawerEvents
//[
//	dispinterface,
//	uuid("541E44F9-BDE1-4425-BE00-9D952CE2A565"),
//	helpstring("_ISVGTransformerEvents Interface")
//]
//__interface _ISVGTransformerEvents
//{
//
//};
//
//// CSVGDrawer
//
//[
//	coclass,
//	default(ISVGTransformer, _ISVGTransformerEvents),
//	threading(apartment),
//	event_source(com),
//	vi_progid("AVSOfficeSVGFile.SVGTransformer"),
//	progid("AVSOfficeSVGFile.SVGTransformer.1"),
//	version(1.0),
//	uuid("AB7920A5-428A-44FD-9C36-2398FA802F74"),
//	helpstring("SVGDrawer Class")
//]
class /*ATL_NO_VTABLE */SVGTransformer /*: public ISVGTransformer*/
{
public:

	SVGTransformer()
	{
		//m_oGdiPlusInit.Init();
	}

	//__event __interface _ISVGTransformerEvents;


	//DECLARE_PROTECT_FINAL_CONSTRUCT()

	//HRESULT FinalConstruct()
	//{
	//	return S_OK;
	//}

	//void FinalRelease()
	//{
	//}

public:

	//HRESULT ( LoadFile )( BSTR File );
	HRESULT ( Load )( CString Str );
	
	HRESULT ( Draw )( void* pRender, double dX, double dY, double dWidth, double dHeight );
	HRESULT ( get_Width ) ( LONG* pWidth );
	HRESULT ( get_Height ) ( LONG* pHeight );
	HRESULT ( get_Metrics ) ( LONG* pMetrics );

	//HRESULT ( SetAdditionalParam )( BSTR ParamName, VARIANT	ParamValue );
	//HRESULT ( GetAdditionalParam )( BSTR ParamName, VARIANT*	ParamValue );

private:

	//CGdiPlusInit	m_oGdiPlusInit;
	
	SVG::Parser		m_oXmlParser;
	SVG::Storage	m_oStorage;
	SVG::Painter	m_oRender;
};
