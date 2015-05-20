/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: salgdilayout.cxx,v $
 * $Revision: 1.31.30.1 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifdef AVS
// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_vcl.hxx"

#include <tools/ref.hxx>
#ifndef _SV_SVSYS_HXX
#include <svsys.h>
#endif
#include <vcl/salgdi.hxx>
#include <vcl/salframe.hxx>
#include <vcl/salvd.hxx>
#include <vcl/salprn.hxx>
#include <tools/debug.hxx>
#include <vcl/svdata.hxx>
#include <vcl/svapp.hxx>
#include <tools/poly.hxx>
#include <vcl/region.hxx>
#include <vcl/region.h>
#include <vcl/virdev.hxx>
#include <vcl/window.h>
#include <vcl/window.hxx>
#include <vcl/metaact.hxx>
#include <vcl/gdimtf.hxx>
#include <vcl/outdata.hxx>
#include <vcl/print.hxx>
#include <implncvt.hxx>
#include <vcl/outdev.h>
#include <vcl/outdev.hxx>
#include <vcl/unowrap.hxx>
#include <vcl/sallayout.hxx>
#include "basegfx/polygon/b2dpolygon.hxx"
#endif

#include "../vcl/salgdi.hxx"
#include "../vcl/salgtype.hxx"

using namespace SVMCore;


#ifdef AVS
// ----------------------------------------------------------------------------
// The only common SalFrame method
// ----------------------------------------------------------------------------

SalFrameGeometry SalFrame::GetGeometry()
{
    // mirror frame coordinates at parent
    SalFrame *pParent = GetParent();
    if( pParent && Application::GetSettings().GetLayoutRTL() )
    {
        SalFrameGeometry aGeom = maGeometry;
        int parent_x = aGeom.nX - pParent->maGeometry.nX;
        aGeom.nX = pParent->maGeometry.nX + pParent->maGeometry.nWidth - maGeometry.nWidth - parent_x;
        return aGeom;
    }
    else
        return maGeometry;
}
#endif
// ----------------------------------------------------------------------------

SalGraphics::SalGraphics() 
:   m_nLayout( 0 )
#ifdef AVS
,
    m_bAntiAliasB2DDraw(false)
#endif
{
#ifdef AVS
    // read global RTL settings
    if( Application::GetSettings().GetLayoutRTL() )
	    m_nLayout = SAL_LAYOUT_BIDI_RTL;
#endif
}

SalGraphics::~SalGraphics()
{
}

// ----------------------------------------------------------------------------

bool SalGraphics::drawAlphaBitmap( const SalTwoRect&,
    const SalBitmap&, const SalBitmap& )
{
    return false;
}

// ----------------------------------------------------------------------------


void SalGraphics::mirror( long& x, const OutputDevice *pOutDev, bool bBack ) const
{
	long w;
    if( pOutDev && pOutDev->GetOutDevType() == OUTDEV_VIRDEV )
        w = pOutDev->GetOutputWidthPixel();
#ifdef AVS
    else
        w = GetGraphicsWidth();
#endif
	if( w )
    {
        if( pOutDev && pOutDev->ImplIsAntiparallel() )
        {
            OutputDevice *pOutDevRef = (OutputDevice*) pOutDev;
            // mirror this window back
            if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) )
            {
                long devX = w-pOutDevRef->GetOutputWidthPixel()-pOutDevRef->GetOutOffXPixel();   // re-mirrored mnOutOffX
                if( bBack )
                    x = x - devX + pOutDevRef->GetOutOffXPixel();
                else
                    x = devX + (x - pOutDevRef->GetOutOffXPixel());
            }
            else
            {
                long devX = pOutDevRef->GetOutOffXPixel();   // re-mirrored mnOutOffX
                if( bBack )
                    x = x - pOutDevRef->GetOutputWidthPixel() + devX - pOutDevRef->GetOutOffXPixel() + 1;
                else
                    x = pOutDevRef->GetOutputWidthPixel() - (x - devX) + pOutDevRef->GetOutOffXPixel() - 1;
            }
        }
        else if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) )
		    x = w-1-x;
    }
}

void SalGraphics::mirror( long& x, long& nWidth, const OutputDevice *pOutDev, bool bBack ) const
{
	long w;
    if( pOutDev && pOutDev->GetOutDevType() == OUTDEV_VIRDEV )
        w = pOutDev->GetOutputWidthPixel();
#ifdef AVS
    else
        w = GetGraphicsWidth();
#endif
	if( w )
    {
        if( pOutDev && pOutDev->ImplIsAntiparallel() )
        {
            OutputDevice *pOutDevRef = (OutputDevice*) pOutDev;
            // mirror this window back
            if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) )
            {
                long devX = w-pOutDevRef->GetOutputWidthPixel()-pOutDevRef->GetOutOffXPixel();   // re-mirrored mnOutOffX
                if( bBack )
                    x = x - devX + pOutDevRef->GetOutOffXPixel();
                else
                    x = devX + (x - pOutDevRef->GetOutOffXPixel());
            }
            else
            {
                long devX = pOutDevRef->GetOutOffXPixel();   // re-mirrored mnOutOffX
                if( bBack )
                    x = x - pOutDevRef->GetOutputWidthPixel() + devX - pOutDevRef->GetOutOffXPixel() + nWidth;
                else
                    x = pOutDevRef->GetOutputWidthPixel() - (x - devX) + pOutDevRef->GetOutOffXPixel() - nWidth;
            }
        }
        else if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) )
		    x = w-nWidth-x;

    }
}

BOOL SalGraphics::mirror( sal_uInt32 nPoints, const SalPoint *pPtAry, SalPoint *pPtAry2, const OutputDevice *pOutDev, bool bBack ) const
{
	long w;
    if( pOutDev && pOutDev->GetOutDevType() == OUTDEV_VIRDEV )
        w = pOutDev->GetOutputWidthPixel();
#ifdef AVS
    else
        w = GetGraphicsWidth();
#endif
	if( w )
	{
		sal_uInt32 i, j;

        if( pOutDev && pOutDev->ImplIsAntiparallel() )
        {
            OutputDevice *pOutDevRef = (OutputDevice*) pOutDev;
            // mirror this window back
            if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) )
            {
                long devX = w-pOutDevRef->GetOutputWidthPixel()-pOutDevRef->GetOutOffXPixel();   // re-mirrored mnOutOffX
                if( bBack )
                {
                    for( i=0, j=nPoints-1; i<nPoints; i++,j-- )
                    {
                        //long x = w-1-pPtAry[i].mnX;
                        //pPtAry2[j].mnX = devX + ( pOutDevRef->mnOutWidth - 1 - (x - devX) );
                        pPtAry2[j].mnX = pOutDevRef->GetOutOffXPixel() + (pPtAry[i].mnX - devX);
                        pPtAry2[j].mnY = pPtAry[i].mnY;
                    }
                }
                else
                {
                    for( i=0, j=nPoints-1; i<nPoints; i++,j-- )
                    {
                        //long x = w-1-pPtAry[i].mnX;
                        //pPtAry2[j].mnX = devX + ( pOutDevRef->mnOutWidth - 1 - (x - devX) );
                        pPtAry2[j].mnX = devX + (pPtAry[i].mnX - pOutDevRef->GetOutOffXPixel());
                        pPtAry2[j].mnY = pPtAry[i].mnY;
                    }
                }
            }
            else
            {
                long devX = pOutDevRef->GetOutOffXPixel();   // re-mirrored mnOutOffX
                if( bBack )
                {
                    for( i=0, j=nPoints-1; i<nPoints; i++,j-- )
                    {
                        //long x = w-1-pPtAry[i].mnX;
                        //pPtAry2[j].mnX = devX + ( pOutDevRef->mnOutWidth - 1 - (x - devX) );
                        pPtAry2[j].mnX = pPtAry[i].mnX - pOutDevRef->GetOutputWidthPixel() + devX - pOutDevRef->GetOutOffXPixel() + 1;
                        pPtAry2[j].mnY = pPtAry[i].mnY;
                    }
                }
                else
                {
                    for( i=0, j=nPoints-1; i<nPoints; i++,j-- )
                    {
                        //long x = w-1-pPtAry[i].mnX;
                        //pPtAry2[j].mnX = devX + ( pOutDevRef->mnOutWidth - 1 - (x - devX) );
                        pPtAry2[j].mnX = pOutDevRef->GetOutputWidthPixel() - (pPtAry[i].mnX - devX) + pOutDevRef->GetOutOffXPixel() - 1;
                        pPtAry2[j].mnY = pPtAry[i].mnY;
                    }
                }
            }
        }
        else if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) )
        {
		    for( i=0, j=nPoints-1; i<nPoints; i++,j-- )
		    {
			    pPtAry2[j].mnX = w-1-pPtAry[i].mnX;
			    pPtAry2[j].mnY = pPtAry[i].mnY;
		    }
        }
		return TRUE;
	}
	else
		return FALSE;
}

void SalGraphics::mirror( Region& rRgn, const OutputDevice *pOutDev, bool bBack ) const
{
    // mirror the bounding rect and move Region by resulting offset
    Rectangle aRect( rRgn.GetBoundRect() );
    long nWidth = aRect.GetWidth();
    long x      = aRect.Left();
    long x_org = x;

    mirror( x, nWidth, pOutDev, bBack );
    rRgn.Move( x - x_org, 0 );
}

void SalGraphics::mirror( Rectangle& rRect, const OutputDevice *pOutDev, bool bBack ) const
{
    long nWidth = rRect.GetWidth();
    long x      = rRect.Left();
    long x_org = x;

    mirror( x, nWidth, pOutDev, bBack );
    rRect.Move( x - x_org, 0 );
}
#ifdef AVS
basegfx::B2DPoint SalGraphics::mirror( const basegfx::B2DPoint& i_rPoint, const OutputDevice *i_pOutDev, bool i_bBack ) const
{
	long w;
    if( i_pOutDev && i_pOutDev->GetOutDevType() == OUTDEV_VIRDEV )
        w = i_pOutDev->GetOutputWidthPixel();
    else
        w = GetGraphicsWidth();
    
    DBG_ASSERT( w, "missing graphics width" );

    basegfx::B2DPoint aRet( i_rPoint );
	if( w )
    {
        if( i_pOutDev && !i_pOutDev->IsRTLEnabled() )
        {
            OutputDevice *pOutDevRef = (OutputDevice*)i_pOutDev;
            // mirror this window back
            double devX = w-pOutDevRef->GetOutputWidthPixel()-pOutDevRef->GetOutOffXPixel();   // re-mirrored mnOutOffX
            if( i_bBack )
                aRet.setX( i_rPoint.getX() - devX + pOutDevRef->GetOutOffXPixel() );
            else
                aRet.setX( devX + (i_rPoint.getX() - pOutDevRef->GetOutOffXPixel()) );
        }
        else
		    aRet.setX( w-1-i_rPoint.getX() );
    }
    return aRet;
}

basegfx::B2DPolygon SalGraphics::mirror( const basegfx::B2DPolygon& i_rPoly, const OutputDevice *i_pOutDev, bool i_bBack ) const
{
	long w;
    if( i_pOutDev && i_pOutDev->GetOutDevType() == OUTDEV_VIRDEV )
        w = i_pOutDev->GetOutputWidthPixel();
    else
        w = GetGraphicsWidth();
    
    DBG_ASSERT( w, "missing graphics width" );
    
    basegfx::B2DPolygon aRet;
	if( w )
    {
        sal_Int32 nPoints = i_rPoly.count();
        for( sal_Int32 i = 0; i < nPoints; i++ )
        {
            aRet.append( mirror( i_rPoly.getB2DPoint( i ), i_pOutDev, i_bBack ) );
            if( i_rPoly.isPrevControlPointUsed( i ) )
                aRet.setPrevControlPoint( i, mirror( i_rPoly.getPrevControlPoint( i ), i_pOutDev, i_bBack ) ); 
            if( i_rPoly.isNextControlPointUsed( i ) )
                aRet.setNextControlPoint( i, mirror( i_rPoly.getNextControlPoint( i ), i_pOutDev, i_bBack ) ); 
        }
        aRet.setClosed( i_rPoly.isClosed() );
        aRet.flip();
    }
    else
        aRet = i_rPoly;
    return aRet;
}

basegfx::B2DPolyPolygon SalGraphics::mirror( const basegfx::B2DPolyPolygon& i_rPoly, const OutputDevice *i_pOutDev, bool i_bBack ) const
{
	long w;
    if( i_pOutDev && i_pOutDev->GetOutDevType() == OUTDEV_VIRDEV )
        w = i_pOutDev->GetOutputWidthPixel();
    else
        w = GetGraphicsWidth();
    
    DBG_ASSERT( w, "missing graphics width" );
    
    basegfx::B2DPolyPolygon aRet;
	if( w )
    {
        sal_Int32 nPoly = i_rPoly.count();
        for( sal_Int32 i = 0; i < nPoly; i++ )
            aRet.append( mirror( i_rPoly.getB2DPolygon( i ), i_pOutDev, i_bBack ) );
        aRet.setClosed( i_rPoly.isClosed() );
        aRet.flip();
    }
    else
        aRet = i_rPoly;
    return aRet;
}

#endif
// ----------------------------------------------------------------------------

BOOL	SalGraphics::UnionClipRegion( long nX, long nY, long nWidth, long nHeight, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) ) 
		mirror( nX, nWidth, pOutDev );
	return unionClipRegion( nX, nY, nWidth, nHeight );
}

#ifdef AVS
bool SalGraphics::unionClipRegion( const ::basegfx::B2DPolyPolygon& )
{
	return false;
}

BOOL SalGraphics::UnionClipRegion( const ::basegfx::B2DPolyPolygon& rPoly, const OutputDevice* pOutDev )
{
	(void)pOutDev;// TODO: SAL_LAYOUT_BIDI_RTL
	return unionClipRegion( rPoly );
}

#endif
void	SalGraphics::DrawPixel( long nX, long nY, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, pOutDev );
	drawPixel( nX, nY );
}
void	SalGraphics::DrawPixel( long nX, long nY, Color nSalColor, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, pOutDev );
	drawPixel( nX, nY, ImplColorToSal( nSalColor ));
}
void	SalGraphics::DrawLine( long nX1, long nY1, long nX2, long nY2, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		mirror( nX1, pOutDev );
		mirror( nX2, pOutDev );
	}
	drawLine( nX1, nY1, nX2, nY2 );
}
void	SalGraphics::DrawRect( long nX, long nY, long nWidth, long nHeight, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, nWidth, pOutDev );
	drawRect( nX, nY, nWidth, nHeight );
}
#ifdef AVS
bool SalGraphics::drawPolyLine( 
    const basegfx::B2DPolygon& /*rPolyPolygon*/, 
    const basegfx::B2DVector& /*rLineWidths*/, 
    basegfx::B2DLineJoin /*eLineJoin*/)
{
    return false;
}
#endif
void SalGraphics::DrawPolyLine( ULONG nPoints, const SalPoint* pPtAry, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalPoint* pPtAry2 = new SalPoint[nPoints];
		BOOL bCopied = mirror( (long)nPoints, pPtAry, pPtAry2, pOutDev ); 
		drawPolyLine( nPoints, bCopied ? pPtAry2 : pPtAry );
		delete [] pPtAry2;
	}
	else
		drawPolyLine( nPoints, pPtAry );
}

void SalGraphics::DrawPolygon( ULONG nPoints, const SalPoint* pPtAry, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalPoint* pPtAry2 = new SalPoint[nPoints];
		BOOL bCopied = mirror( nPoints, pPtAry, pPtAry2, pOutDev ); 
		drawPolygon( nPoints, bCopied ? pPtAry2 : pPtAry );
		delete [] pPtAry2;
	}
	else
		drawPolygon( nPoints, pPtAry );
}

void SalGraphics::DrawPolyPolygon( sal_uInt32 nPoly, const sal_uInt32* pPoints, PCONSTSALPOINT* pPtAry, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
        // TODO: optimize, reduce new/delete calls
        SalPoint **pPtAry2 = new SalPoint*[nPoly];
        ULONG i;
        for(i=0; i<nPoly; i++)
        {
            ULONG nPoints = pPoints[i];
            pPtAry2[i] = new SalPoint[ nPoints ];
		    mirror( nPoints, pPtAry[i], pPtAry2[i], pOutDev ); 
        }

        drawPolyPolygon( nPoly, pPoints, (PCONSTSALPOINT*)pPtAry2 );

        for(i=0; i<nPoly; i++)
            delete [] pPtAry2[i];
        delete [] pPtAry2;
    }
    else
	    drawPolyPolygon( nPoly, pPoints, pPtAry );
}

#ifdef AVS
bool SalGraphics::DrawPolyPolygon( const ::basegfx::B2DPolyPolygon& i_rPolyPolygon, double i_fTransparency, const OutputDevice* i_pOutDev )
{
    bool bRet = false;
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) ) 
	{
        basegfx::B2DPolyPolygon aMirror( mirror( i_rPolyPolygon, i_pOutDev ) );
        bRet = drawPolyPolygon( aMirror, i_fTransparency );
    }
    else
        bRet = drawPolyPolygon( i_rPolyPolygon, i_fTransparency );
    return bRet;
}

bool SalGraphics::drawPolyPolygon( const ::basegfx::B2DPolyPolygon&, double /*fTransparency*/)
{
	return false;
}

#endif
sal_Bool SalGraphics::DrawPolyLineBezier( ULONG nPoints, const SalPoint* pPtAry, const BYTE* pFlgAry, const OutputDevice* pOutDev )
{
    sal_Bool bResult = sal_False;
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) ) 
	{
		SalPoint* pPtAry2 = new SalPoint[nPoints];
		BOOL bCopied = mirror( (long)nPoints, pPtAry, pPtAry2, pOutDev ); 
		bResult = drawPolyLineBezier( nPoints, bCopied ? pPtAry2 : pPtAry, pFlgAry );
		delete [] pPtAry2;
	}
	else
        bResult = drawPolyLineBezier( nPoints, pPtAry, pFlgAry );
    return bResult;
}

sal_Bool SalGraphics::DrawPolygonBezier( ULONG nPoints, const SalPoint* pPtAry, const BYTE* pFlgAry, const OutputDevice* pOutDev )
{
    sal_Bool bResult = sal_False;
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) ) 
	{
		SalPoint* pPtAry2 = new SalPoint[nPoints];
		BOOL bCopied = mirror( (long)nPoints, pPtAry, pPtAry2, pOutDev ); 
		bResult = drawPolygonBezier( nPoints, bCopied ? pPtAry2 : pPtAry, pFlgAry );
		delete [] pPtAry2;
	}
	else
        bResult = drawPolygonBezier( nPoints, pPtAry, pFlgAry );
    return bResult;
}

sal_Bool SalGraphics::DrawPolyPolygonBezier( sal_uInt32 i_nPoly, const sal_uInt32* i_pPoints,
                                                   const SalPoint* const* i_pPtAry, const BYTE* const* i_pFlgAry, const OutputDevice* i_pOutDev )
{
    sal_Bool bRet = sal_False;
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) ) 
	{
        // TODO: optimize, reduce new/delete calls
        SalPoint **pPtAry2 = new SalPoint*[i_nPoly];
        ULONG i;
        for(i=0; i<i_nPoly; i++)
        {
            ULONG nPoints = i_pPoints[i];
            pPtAry2[i] = new SalPoint[ nPoints ];
		    mirror( nPoints, i_pPtAry[i], pPtAry2[i], i_pOutDev ); 
        }

        bRet = drawPolyPolygonBezier( i_nPoly, i_pPoints, (PCONSTSALPOINT*)pPtAry2, i_pFlgAry );

        for(i=0; i<i_nPoly; i++)
            delete [] pPtAry2[i];
        delete [] pPtAry2;
    }
    else
	    bRet = drawPolyPolygonBezier( i_nPoly, i_pPoints, i_pPtAry, i_pFlgAry );
    return bRet;
}

#ifdef AVS
bool SalGraphics::DrawPolyLine( const ::basegfx::B2DPolygon& i_rPolygon,
    const ::basegfx::B2DVector& i_rLineWidth, basegfx::B2DLineJoin i_eLineJoin,
    const OutputDevice* i_pOutDev )
{
    bool bRet = false;
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) ) 
	{
        basegfx::B2DPolygon aMirror( mirror( i_rPolygon, i_pOutDev ) );
        bRet = drawPolyLine( aMirror, i_rLineWidth, i_eLineJoin );
    }
    else
        bRet = drawPolyLine( i_rPolygon, i_rLineWidth, i_eLineJoin );
    return bRet;
}


void	SalGraphics::CopyArea( long nDestX, long nDestY,
                               long nSrcX, long nSrcY,
                               long nSrcWidth, long nSrcHeight,
                               USHORT nFlags, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) ) 
	{
		mirror( nDestX, nSrcWidth, pOutDev );
		mirror( nSrcX, nSrcWidth, pOutDev );
	}
	copyArea( nDestX, nDestY, nSrcX, nSrcY, nSrcWidth, nSrcHeight, nFlags );
}
#endif
void	SalGraphics::CopyBits( const SalTwoRect* pPosAry,
                               SalGraphics* pSrcGraphics, const OutputDevice *pOutDev, const OutputDevice *pSrcOutDev )
{
	if( ( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) ) || 
        (pSrcGraphics && ( (pSrcGraphics->GetLayout() & SAL_LAYOUT_BIDI_RTL)  || (pSrcOutDev && pSrcOutDev->IsRTLEnabled()) ) ) )
	{
		SalTwoRect pPosAry2 = *pPosAry;
		if( pSrcGraphics && (pSrcGraphics->GetLayout() & SAL_LAYOUT_BIDI_RTL) || (pSrcOutDev && pSrcOutDev->IsRTLEnabled()) )
			mirror( pPosAry2.mnSrcX, pPosAry2.mnSrcWidth, pSrcOutDev ); 
		if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) ) 
			mirror( pPosAry2.mnDestX, pPosAry2.mnDestWidth, pOutDev ); 
		copyBits( &pPosAry2, pSrcGraphics );
	}
	else
		copyBits( pPosAry, pSrcGraphics );
}
void	SalGraphics::DrawBitmap( const SalTwoRect* pPosAry,
									const SalBitmap& rSalBitmap, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalTwoRect pPosAry2 = *pPosAry;
		mirror( pPosAry2.mnDestX, pPosAry2.mnDestWidth, pOutDev ); 
		drawBitmap( &pPosAry2, rSalBitmap );
	}
	else
		drawBitmap( pPosAry, rSalBitmap );
}
void	SalGraphics::DrawBitmap( const SalTwoRect* pPosAry,
									const SalBitmap& rSalBitmap,
									Color nTransparentColor, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalTwoRect pPosAry2 = *pPosAry;
		mirror( pPosAry2.mnDestX, pPosAry2.mnDestWidth, pOutDev ); 
		drawBitmap( &pPosAry2, rSalBitmap, ImplColorToSal( nTransparentColor ) );
	}
	else
		drawBitmap( pPosAry, rSalBitmap, ImplColorToSal( nTransparentColor ) );
}
void SalGraphics::DrawBitmap( const SalTwoRect* pPosAry,
                              const SalBitmap& rSalBitmap,
                              const SalBitmap& rTransparentBitmap, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalTwoRect pPosAry2 = *pPosAry;
		mirror( pPosAry2.mnDestX, pPosAry2.mnDestWidth, pOutDev ); 
		drawBitmap( &pPosAry2, rSalBitmap, rTransparentBitmap );
	}
	else
		drawBitmap( pPosAry, rSalBitmap, rTransparentBitmap );
}
void	SalGraphics::DrawMask( const SalTwoRect* pPosAry,
								  const SalBitmap& rSalBitmap,
								  Color nMaskColor, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalTwoRect pPosAry2 = *pPosAry;
		mirror( pPosAry2.mnDestX, pPosAry2.mnDestWidth, pOutDev ); 
		drawMask( &pPosAry2, rSalBitmap, ImplColorToSal( nMaskColor ) );
	}
	else
		drawMask( pPosAry, rSalBitmap, ImplColorToSal( nMaskColor ) );
}

SalBitmap*	SalGraphics::GetBitmap( long nX, long nY, long nWidth, long nHeight, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, nWidth, pOutDev );
	return getBitmap( nX, nY, nWidth, nHeight );
}

SalColor	SalGraphics::GetPixel( long nX, long nY, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, pOutDev );
	return getPixel( nX, nY );
}
#ifdef AVS
void	SalGraphics::Invert( long nX, long nY, long nWidth, long nHeight, SalInvert nFlags, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, nWidth, pOutDev );
	invert( nX, nY, nWidth, nHeight, nFlags );
}
void	SalGraphics::Invert( ULONG nPoints, const SalPoint* pPtAry, SalInvert nFlags, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalPoint* pPtAry2 = new SalPoint[nPoints];
		BOOL bCopied = mirror( nPoints, pPtAry, pPtAry2, pOutDev ); 
		invert( nPoints, bCopied ? pPtAry2 : pPtAry, nFlags );
		delete [] pPtAry2;
	}
	else
		invert( nPoints, pPtAry, nFlags );
}

BOOL	SalGraphics::DrawEPS( long nX, long nY, long nWidth, long nHeight, void* pPtr, ULONG nSize, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, nWidth, pOutDev );
	return drawEPS( nX, nY, nWidth, nHeight,  pPtr, nSize );
}

BOOL SalGraphics::HitTestNativeControl( ControlType nType, ControlPart nPart, const Region& rControlRegion,
                                                const SalPoint& aPos, SalControlHandle& rControlHandle, BOOL& rIsInside, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
    {
        SalPoint pt( aPos );
        Region rgn( rControlRegion );
        mirror( pt.X(), pOutDev );
        mirror( rgn, pOutDev );
        return hitTestNativeControl( nType, nPart, rgn, pt, rControlHandle, rIsInside );
    }
    else
        return hitTestNativeControl( nType, nPart, rControlRegion, aPos, rControlHandle, rIsInside );
}

void SalGraphics::mirror( ControlType nType, const ImplControlValue& rVal, const OutputDevice* pOutDev, bool bBack ) const
{
    if( rVal.getOptionalVal() )
    {
        switch( nType )
        {
            case CTRL_SCROLLBAR:
            {
                ScrollbarValue* pScVal = reinterpret_cast<ScrollbarValue*>(rVal.getOptionalVal());
                mirror(pScVal->maThumbRect,pOutDev,bBack);
                mirror(pScVal->maButton1Rect,pOutDev,bBack);
                mirror(pScVal->maButton2Rect,pOutDev,bBack);
            }
            break;
            case CTRL_SPINBOX:
            case CTRL_SPINBUTTONS:
            {
                SpinbuttonValue* pSpVal = reinterpret_cast<SpinbuttonValue*>(rVal.getOptionalVal());
                mirror(pSpVal->maUpperRect,pOutDev,bBack);
                mirror(pSpVal->maLowerRect,pOutDev,bBack);
            }
            break;
            case CTRL_TOOLBAR:
            {
                ToolbarValue* pTVal = reinterpret_cast<ToolbarValue*>(rVal.getOptionalVal());
                mirror(pTVal->maGripRect,pOutDev,bBack);
            }
            break;
        }
    }
}

BOOL SalGraphics::DrawNativeControl( ControlType nType, ControlPart nPart, const Region& rControlRegion,
                                                ControlState nState, const ImplControlValue& aValue, SalControlHandle& rControlHandle,
                                                const OUString& aCaption, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
    {
        Region rgn( rControlRegion );
        mirror( rgn, pOutDev );
        mirror( nType, aValue, pOutDev );
        BOOL bRet = drawNativeControl( nType, nPart, rgn, nState, aValue, rControlHandle, aCaption );
        mirror( nType, aValue, pOutDev, true );
        return bRet;
    }
    else
        return drawNativeControl( nType, nPart, rControlRegion, nState, aValue, rControlHandle, aCaption );
}

BOOL SalGraphics::DrawNativeControlText( ControlType nType, ControlPart nPart, const Region& rControlRegion,
                                                ControlState nState, const ImplControlValue& aValue,
                                                SalControlHandle& rControlHandle, const OUString& aCaption, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
    {
        Region rgn( rControlRegion );
        mirror( rgn, pOutDev );
        mirror( nType, aValue, pOutDev );
        BOOL bRet = drawNativeControlText( nType, nPart, rgn, nState, aValue, rControlHandle, aCaption );
        mirror( nType, aValue, pOutDev, true );
        return bRet;
    }
    else
        return drawNativeControlText( nType, nPart, rControlRegion, nState, aValue, rControlHandle, aCaption );
}

BOOL SalGraphics::GetNativeControlRegion( ControlType nType, ControlPart nPart, const Region& rControlRegion, ControlState nState,
                                                const ImplControlValue& aValue, SalControlHandle& rControlHandle, const OUString& aCaption,
                                                Region &rNativeBoundingRegion, Region &rNativeContentRegion, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
    {
        Region rgn( rControlRegion );
        mirror( rgn, pOutDev );
        mirror( nType, aValue, pOutDev );
        if( getNativeControlRegion( nType, nPart, rgn, nState, aValue, rControlHandle, aCaption, 
                                                rNativeBoundingRegion, rNativeContentRegion ) )
        {
            mirror( rNativeBoundingRegion, pOutDev, true );
            mirror( rNativeContentRegion, pOutDev, true );
            mirror( nType, aValue, pOutDev, true );
            return TRUE;
        }
        else
        {
            mirror( nType, aValue, pOutDev, true );
            return FALSE;
        }
    }
    else
        return getNativeControlRegion( nType, nPart, rControlRegion, nState, aValue, rControlHandle, aCaption, 
                                                rNativeBoundingRegion, rNativeContentRegion );
}

#endif
bool SalGraphics::DrawAlphaBitmap( const SalTwoRect& rPosAry,
                                   const SalBitmap& rSourceBitmap,
                                   const SalBitmap& rAlphaBitmap, 
                                   const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
	{
		SalTwoRect pPosAry2 = rPosAry;
		mirror( pPosAry2.mnDestX, pPosAry2.mnDestWidth, pOutDev ); 
		return drawAlphaBitmap( pPosAry2, rSourceBitmap, rAlphaBitmap );
	}
	else
		return drawAlphaBitmap( rPosAry, rSourceBitmap, rAlphaBitmap );
}

bool SalGraphics::DrawAlphaRect( long nX, long nY, long nWidth, long nHeight, 
                                 sal_uInt8 nTransparency, const OutputDevice *pOutDev )
{
	if( (m_nLayout & SAL_LAYOUT_BIDI_RTL) || (pOutDev && pOutDev->IsRTLEnabled()) )
		mirror( nX, nWidth, pOutDev );

	return drawAlphaRect( nX, nY, nWidth, nHeight, nTransparency );
}

bool SalGraphics::filterText( const String&, String&, xub_StrLen, xub_StrLen&, xub_StrLen&, xub_StrLen& )
{
    return false;
}
#ifdef AVS
void SalGraphics::AddDevFontSubstitute( OutputDevice* pOutDev,
                                        const String& rFontName,
                                        const String& rReplaceFontName,
                                        USHORT nFlags )
{
    pOutDev->ImplAddDevFontSubstitute( rFontName, rReplaceFontName, nFlags );
}

#endif