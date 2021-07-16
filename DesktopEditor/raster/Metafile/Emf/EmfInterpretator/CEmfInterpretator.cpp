#include "CEmfInterpretator.h"

#include <fstream>

#include <iostream>

namespace MetaFile
{
        CEmfInterpretator::CEmfInterpretator(const wchar_t* wsFilepath) :
                m_pOutStream(new std::ofstream(wsFilepath, std::ios::binary | std::ios::out)),
                unFileSize(0){}

        CEmfInterpretator::~CEmfInterpretator()
        {
                m_pOutStream->close();
                delete m_pOutStream;
        }

        InterpretatorType CEmfInterpretator::GetType()
        {
                return InterpretatorType::Emf;
        }

        void CEmfInterpretator::HANDLE_EMR_HEADER(const TEmfHeader &oTEmfHeader, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {
                int unExplicitRecordSize    = 88;
                int unType                  = EMR_HEADER;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oTEmfHeader.oBounds);
                WriteRectangle(oTEmfHeader.oFrame);

                m_pOutStream->write((char*)&oTEmfHeader.ulSignature,        sizeof (unsigned int));
                m_pOutStream->write((char*)&oTEmfHeader.ulVersion,          sizeof (unsigned int));
                m_pOutStream->write((char*)&oTEmfHeader.ulSize,             sizeof (unsigned int));
                m_pOutStream->write((char*)&oTEmfHeader.ulRecords,          sizeof (unsigned int));
                m_pOutStream->write((char*)&oTEmfHeader.ushObjects,         sizeof (unsigned short));
                m_pOutStream->write((char*)&oTEmfHeader.ushReserved,        sizeof (unsigned short));
                m_pOutStream->write((char*)&oTEmfHeader.ulSizeDescription,  sizeof (unsigned int));
                m_pOutStream->write((char*)&oTEmfHeader.ulOffsetDescription,sizeof (unsigned int));
                m_pOutStream->write((char*)&oTEmfHeader.ulPalEntries,       sizeof (unsigned int));

                WriteSize(oTEmfHeader.oDevice);
                WriteSize(oTEmfHeader.oMillimeters);
        }

        void CEmfInterpretator::HANDLE_EMR_ALPHABLEND(const TEmfAlphaBlend &oTEmfAlphaBlend, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {
                int unExplicitRecordSize    = 108 + oTEmfAlphaBlend.cbBitsSrc + oTEmfAlphaBlend.cbBmiSrc;
                int unType                  = EMR_ALPHABLEND;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oTEmfAlphaBlend.Bounds);

                m_pOutStream->write((char *)&oTEmfAlphaBlend.xDest,     sizeof (int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.yDest,     sizeof (int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.cxDest,    sizeof (int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.cyDest,    sizeof (int));

                m_pOutStream->write((char *)&oTEmfAlphaBlend.BlendOperation,    sizeof (unsigned char));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.BlendFlags,        sizeof (unsigned char));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.SrcConstantAlpha,  sizeof (unsigned char));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.AlphaFormat,       sizeof (unsigned char));

                m_pOutStream->write((char *)&oTEmfAlphaBlend.xSrc,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.ySrc,      sizeof (int));

                WriteForm(oTEmfAlphaBlend.XformSrc);
                WriteColor(oTEmfAlphaBlend.BkColor);

                m_pOutStream->write((char *)&oTEmfAlphaBlend.UsageSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.offBmiSrc, sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.cbBmiSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.offBitsSrc,sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.cbBitsSrc, sizeof (unsigned int));

                m_pOutStream->write((char *)&oTEmfAlphaBlend.cxSrc,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfAlphaBlend.cySrc,      sizeof (int));

                if (oTEmfAlphaBlend.cbBmiSrc > 0)
                {
                        unsigned int unZero = 0;
                        for (unsigned int i = 0; i < oTEmfAlphaBlend.cbBmiSrc; ++i)
                            m_pOutStream->write((char *)&unZero, sizeof (BYTE));
                }

                if (oTEmfAlphaBlend.cbBitsSrc > 0)
                        m_pOutStream->write((char *)oDataStream.GetCurPtr(), sizeof (BYTE) * oTEmfAlphaBlend.cbBitsSrc);
        }

        void CEmfInterpretator::HANDLE_EMR_STRETCHDIBITS(const TEmfStretchDIBITS &oTEmfStretchDIBITS, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {
                int unExplicitRecordSize    = 80 + oTEmfStretchDIBITS.cbBitsSrc + oTEmfStretchDIBITS.cbBmiSrc;
                int unType                  = EMR_STRETCHDIBITS;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oTEmfStretchDIBITS.Bounds);

                m_pOutStream->write((char *)&oTEmfStretchDIBITS.xDest,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.yDest,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.xSrc,       sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.ySrc,       sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.cxSrc,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.cySrc,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.offBmiSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.cbBmiSrc,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.offBitsSrc, sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.cbBitsSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.UsageSrc,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.\
                                                    BitBltRasterOperation,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.cxDest,     sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchDIBITS.cyDest,     sizeof (int));

                if (oTEmfStretchDIBITS.cbBmiSrc > 0)
                {
                        unsigned int unZero = 0;
                        for (unsigned int i = 0; i < oTEmfStretchDIBITS.cbBmiSrc; ++i)
                            m_pOutStream->write((char *)&unZero, sizeof (BYTE));
                }

                if (oTEmfStretchDIBITS.cbBitsSrc > 0)
                        m_pOutStream->write((char *)oDataStream.GetCurPtr(), sizeof (BYTE) * oTEmfStretchDIBITS.cbBitsSrc);
        }

        void CEmfInterpretator::HANDLE_EMR_BITBLT(const TEmfBitBlt &oTEmfBitBlt, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {
                int unExplicitRecordSize    = 100 + oTEmfBitBlt.cbBitsSrc + oTEmfBitBlt.cbBmiSrc;
                int unType                  = EMR_BITBLT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oTEmfBitBlt.Bounds);

                m_pOutStream->write((char *)&oTEmfBitBlt.xDest,     sizeof (int));
                m_pOutStream->write((char *)&oTEmfBitBlt.yDest,     sizeof (int));
                m_pOutStream->write((char *)&oTEmfBitBlt.cxDest,    sizeof (int));
                m_pOutStream->write((char *)&oTEmfBitBlt.cyDest,    sizeof (int));
                m_pOutStream->write((char *)&oTEmfBitBlt.\
                                            BitBltRasterOperation,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfBitBlt.xSrc,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfBitBlt.ySrc,      sizeof (int));

                WriteForm(oTEmfBitBlt.XfromSrc);
                WriteColor(oTEmfBitBlt.BkColorSrc);

                m_pOutStream->write((char *)&oTEmfBitBlt.UsageSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfBitBlt.offBmiSrc, sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfBitBlt.cbBmiSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfBitBlt.offBitsSrc,sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfBitBlt.cbBitsSrc, sizeof (unsigned int));

                if (oTEmfBitBlt.cbBmiSrc > 0)
                {
                        unsigned int unZero = 0;
                        for (unsigned int i = 0; i < oTEmfBitBlt.cbBmiSrc ; ++i)
                            m_pOutStream->write((char *)&unZero, sizeof (BYTE));
                }

                if (oTEmfBitBlt.cbBitsSrc > 0)
                        m_pOutStream->write((char *)oDataStream.GetCurPtr(), sizeof (BYTE) * oTEmfBitBlt.cbBitsSrc);
        }

        void CEmfInterpretator::HANDLE_EMR_SETDIBITSTODEVICE(const TEmfSetDiBitsToDevice &oTEmfSetDiBitsToDevice, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {
                int unExplicitRecordSize    = 76 + oTEmfSetDiBitsToDevice.cbBitsSrc + oTEmfSetDiBitsToDevice.cbBmiSrc;
                int unType                  = EMR_BITBLT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oTEmfSetDiBitsToDevice.Bounds);

                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.xDest,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.yDest,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.xSrc,       sizeof (int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.ySrc,       sizeof (int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.cxSrc,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.cySrc,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.offBmiSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.cbBmiSrc,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.offBitsSrc, sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.cbBitsSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.UsageSrc,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.iStartScan, sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfSetDiBitsToDevice.cScans,     sizeof (unsigned int));

                if (oTEmfSetDiBitsToDevice.cbBmiSrc > 0)
                {
                        unsigned int unZero = 0;
                        for (unsigned int i = 0; i < oTEmfSetDiBitsToDevice.cbBmiSrc; ++i)
                            m_pOutStream->write((char *)&unZero, sizeof (BYTE));
                }

                if (oTEmfSetDiBitsToDevice.cbBitsSrc > 0)
                        m_pOutStream->write((char *)oDataStream.GetCurPtr(), sizeof (BYTE) * oTEmfSetDiBitsToDevice.cbBitsSrc);
        }

        void CEmfInterpretator::HANDLE_EMR_STRETCHBLT(const TEmfStretchBLT &oTEmfStretchBLT, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {
                int unExplicitRecordSize    = 84 + oTEmfStretchBLT.cbBitsSrc + oTEmfStretchBLT.cbBmiSrc;
                int unType                  = EMR_BITBLT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oTEmfStretchBLT.Bounds);

                m_pOutStream->write((char *)&oTEmfStretchBLT.xDest,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.yDest,      sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.cxDest,     sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.cyDest,     sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.\
                                                BitBltRasterOperation,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.xSrc,       sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.ySrc,       sizeof (int));

                WriteForm(oTEmfStretchBLT.XformSrc);
                WriteColor(oTEmfStretchBLT.BkColorSrc);

                m_pOutStream->write((char *)&oTEmfStretchBLT.UsageSrc,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.offBmiSrc,  sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.cbBmiSrc,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.offBitsSrc, sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.cbBitsSrc,  sizeof (unsigned int));

                m_pOutStream->write((char *)&oTEmfStretchBLT.cxSrc,       sizeof (int));
                m_pOutStream->write((char *)&oTEmfStretchBLT.cySrc,       sizeof (int));

                if (oTEmfStretchBLT.cbBmiSrc > 0)
                {
                        unsigned int unZero = 0;
                        for (unsigned int i = 0; i < oTEmfStretchBLT.cbBmiSrc; ++i)
                            m_pOutStream->write((char *)&unZero, sizeof (BYTE));
                }

                if (oTEmfStretchBLT.cbBitsSrc > 0)
                        m_pOutStream->write((char *)oDataStream.GetCurPtr(), sizeof (BYTE) * oTEmfStretchBLT.cbBitsSrc);
        }

        void CEmfInterpretator::HANDLE_EMR_EOF(const unsigned int &unCount, const unsigned int &unOffset, const unsigned int &unSizeLast)
        {
                int unExplicitRecordSize    = 20;
                int unType                  = EMR_EOF;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unCount,               sizeof (unsigned int));
                m_pOutStream->write((char *)&unOffset,              sizeof (unsigned int));
                m_pOutStream->write((char *)&unSizeLast,            sizeof (unsigned int));

                m_pOutStream->seekp(48);
                m_pOutStream->write((char *)&unFileSize,            sizeof (unsigned int));
                m_pOutStream->close();
        }

        void CEmfInterpretator::HANDLE_EMR_SAVEDC()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_SAVEDC;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_RESTOREDC(const int &nIndexDC)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_RESTOREDC;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&nIndexDC,              sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_MODIFYWORLDTRANSFORM(const TXForm &oXForm, const unsigned int &unMode)
        {
                int unExplicitRecordSize    = 36;
                int unType                  = EMR_MODIFYWORLDTRANSFORM;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteForm(oXForm);

                m_pOutStream->write((char *)&unMode,                sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETWORLDTRANSFORM(const TXForm &oXForm)
        {
                int unExplicitRecordSize    = 32;
                int unType                  = EMR_SETWORLDTRANSFORM;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteForm(oXForm);
        }

        void CEmfInterpretator::HANDLE_EMR_CREATEBRUSHINDIRECT(const unsigned int &unBrushIndex, const CEmfLogBrushEx *pBrush)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_CREATEBRUSHINDIRECT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unBrushIndex,          sizeof (unsigned int));
                m_pOutStream->write((char *)&(pBrush->BrushStyle),  sizeof (unsigned int));

                WriteColor(pBrush->Color);

                m_pOutStream->write((char *)&(pBrush->BrushHatch),  sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETTEXTCOLOR(const TEmfColor &oColor)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETTEXTCOLOR;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteColor(oColor);
        }

        void CEmfInterpretator::HANDLE_EMR_SELECTOBJECT(const unsigned int &unObjectIndex)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SELECTOBJECT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unObjectIndex,  sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_EXTCREATEFONTINDIRECTW(const unsigned int &unIndex, CEmfLogFont *oLogFont, const unsigned int unRecordSize)
        {
                int unExplicitRecordSize    = unRecordSize + 8;
                int unType                  = EMR_EXTCREATEFONTINDIRECTW;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unIndex,               sizeof (unsigned int));

                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Height,        sizeof (int));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Width,         sizeof (int));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Escapement,    sizeof (int));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Orientation,   sizeof (int));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Weight,        sizeof (int));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Italic,        sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Underline,     sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.StrikeOut,     sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.CharSet,       sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.OutPrecision,  sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.ClipPrecision, sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.Quality,       sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.PitchAndFamily,sizeof (unsigned char));
                m_pOutStream->write((char *)&oLogFont->LogFontEx.LogFont.FaceName,      sizeof (unsigned short) * 16);
                m_pOutStream->write((char *)&oLogFont->LogFontEx.FullName,              sizeof (unsigned short) * 32);
                m_pOutStream->write((char *)&oLogFont->LogFontEx.Style,                 sizeof (unsigned short) * 32);
                m_pOutStream->write((char *)&oLogFont->LogFontEx.Script,                sizeof (unsigned short) * 32);

                if (!oLogFont->IsFixedLength())
                {
                        m_pOutStream->write((char *)&oLogFont->DesignVector.Signature,     sizeof (unsigned int));
                        m_pOutStream->write((char *)&oLogFont->DesignVector.NumAxes,       sizeof (unsigned int));

                        for (unsigned int i = 0; i < oLogFont->DesignVector.NumAxes; ++i)
                                m_pOutStream->write((char *)&oLogFont->DesignVector.Values[i], sizeof (int));
                }
        }

        void CEmfInterpretator::HANDLE_EMR_SETTEXTALIGN(const unsigned int &unAlign)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETTEXTALIGN;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unAlign,               sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETBKMODE(const unsigned int &unBgMode)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETBKMODE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unBgMode,              sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_DELETEOBJECT(const unsigned int &unObjectIndex)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_DELETEOBJECT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unObjectIndex,  sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETMITERLIMIT(const unsigned int &unMeterLimit)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETMITERLIMIT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unMeterLimit,          sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_EXTCREATEPEN(const unsigned int &unPenIndex, CEmfLogPen *pPen, const unsigned int &unRecordSize)
        {

        }

        void CEmfInterpretator::HANDLE_EMR_CREATEPEN(const unsigned int &unPenIndex, const unsigned int &unWidthX, const CEmfLogPen *pPen)
        {

        }

        void CEmfInterpretator::HANDLE_EMR_SETPOLYFILLMODE(const unsigned int &unFillMode)
        {

        }

        void CEmfInterpretator::HANDLE_EMR_BEGINPATH()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_BEGINPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_ENDPATH()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_ENDPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_CLOSEFIGURE()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_CLOSEFIGURE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_FLATTENPATH()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_FLATTENPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_WIDENPATH()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_WIDENPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_ABORTPATH()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_ABORTPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_MOVETOEX(const TEmfPointL &oPoint)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_MOVETOEX;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_SETARCDIRECTION(const unsigned int &unDirection)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETARCDIRECTION;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unDirection,           sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_FILLPATH(const TEmfRectL &oBounds)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_FILLPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);
        }

        void CEmfInterpretator::HANDLE_EMR_SETMAPMODE(const unsigned int &unMapMode)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETMAPMODE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unMapMode,             sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETWINDOWORGEX(const TEmfPointL &oOrigin)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_SETWINDOWORGEX;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WritePoint(oOrigin);
        }

        void CEmfInterpretator::HANDLE_EMR_SETWINDOWEXTEX(const TEmfSizeL &oExtent)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_SETWINDOWEXTEX;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteSize(oExtent);
        }

        void CEmfInterpretator::HANDLE_EMR_SETVIEWPORTORGEX(const TEmfPointL &oOrigin)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_SETVIEWPORTORGEX;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WritePoint(oOrigin);
        }

        void CEmfInterpretator::HANDLE_EMR_SETVIEWPORTEXTEX(const TEmfSizeL &oExtent)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_SETVIEWPORTORGEX;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteSize(oExtent);
        }

        void CEmfInterpretator::HANDLE_EMR_SETSTRETCHBLTMODE(const unsigned int &unStretchMode)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETSTRETCHBLTMODE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unStretchMode,         sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETICMMODE(const unsigned int &unICMMode)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETICMMODE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unICMMode,             sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_CREATEDIBPATTERNBRUSHPT(const unsigned int &unBrushIndex, const TEmfDibPatternBrush &oDibBrush, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {

        }

        void CEmfInterpretator::HANDLE_EMR_SELECTCLIPPATH(const unsigned int &unRegionMode)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SELECTCLIPPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unRegionMode,          sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETBKCOLOR(const TEmfColor &oColor)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_SETBKCOLOR;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteColor(oColor);
        }

        void CEmfInterpretator::HANDLE_EMR_EXCLUDECLIPRECT(const TEmfRectL &oClip)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_EXCLUDECLIPRECT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oClip);
        }

        void CEmfInterpretator::HANDLE_EMR_EXTSELECTCLIPRGN(const unsigned int &unRgnDataSize, const unsigned int &unRegionMode, CDataStream &oDataStream, const unsigned int &unRecordSize)
        {
                int unExplicitRecordSize    = 16 + unRgnDataSize;
                int unType                  = EMR_EXTSELECTCLIPRGN;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unRgnDataSize,         sizeof (unsigned int));
                m_pOutStream->write((char *)&unRegionMode,          sizeof (unsigned int));

                if (unRgnDataSize > 0)
                        m_pOutStream->write((char *)0, sizeof (BYTE) * unRgnDataSize);
        }

        void CEmfInterpretator::HANDLE_EMR_SETMETARGN()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_SETMETARGN;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETROP2(const unsigned int &unRop2Mode)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETROP2;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unRop2Mode,            sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_CREATEPALETTE(const unsigned int &unPaletteIndex, const CEmfLogPalette *oEmfLogPalette, const unsigned int &unRecordSize)
        {

        }

        void CEmfInterpretator::HANDLE_EMR_SELECTPALETTE(const unsigned int &unPaletteIndex)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SELECTPALETTE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unPaletteIndex,        sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_REALIZEPALETTE()
        {
                int unExplicitRecordSize    = 8;
                int unType                  = EMR_REALIZEPALETTE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));
        }

        void CEmfInterpretator::HANDLE_EMR_INTERSECTCLIPRECT(const TEmfRectL &oClip)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_INTERSECTCLIPRECT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oClip);
        }

        void CEmfInterpretator::HANDLE_EMR_SETLAYOUT(const unsigned int &unLayoutMode)
        {
                int unExplicitRecordSize    = 12;
                int unType                  = EMR_SETLAYOUT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                m_pOutStream->write((char *)&unLayoutMode,          sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_SETBRUSHORGEX(const TEmfPointL &oOrigin)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_SETBRUSHORGEX;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WritePoint(oOrigin);
        }

        void CEmfInterpretator::HANDLE_EMR_ANGLEARC(const TEmfPointL &oCenter, const unsigned int &unRadius, const double &dStartAngle, const double &dSweepAngle)
        {
                int unExplicitRecordSize    = 28;
                int unType                  = EMR_ANGLEARC;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WritePoint(oCenter);

                m_pOutStream->write((char *)&unRadius,          sizeof (unsigned int));
                m_pOutStream->write((char *)&dStartAngle,       sizeof (float));
                m_pOutStream->write((char *)&dSweepAngle,       sizeof (float));
        }

        void CEmfInterpretator::HANDLE_EMR_ARC(const TEmfRectL &oBox, const TEmfPointL &oStart, const TEmfPointL &oEnd)
        {
                int unExplicitRecordSize    = 40;
                int unType                  = EMR_ARC;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBox);
                WritePoint(oStart);
                WritePoint(oEnd);
        }

        void CEmfInterpretator::HANDLE_EMR_ARCTO(const TEmfRectL &oBox, const TEmfPointL &oStart, const TEmfPointL &oEnd)
        {
                int unExplicitRecordSize    = 40;
                int unType                  = EMR_ARCTO;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBox);
                WritePoint(oStart);
                WritePoint(oEnd);
        }

        void CEmfInterpretator::HANDLE_EMR_CHORD(const TEmfRectL &oBox, const TEmfPointL &oStart, const TEmfPointL &oEnd)
        {
                int unExplicitRecordSize    = 40;
                int unType                  = EMR_CHORD;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBox);
                WritePoint(oStart);
                WritePoint(oEnd);
        }

        void CEmfInterpretator::HANDLE_EMR_ELLIPSE(const TEmfRectL &oBox)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_ELLIPSE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBox);
        }

        void CEmfInterpretator::HANDLE_EMR_EXTTEXTOUTA(const TEmfExtTextoutA &oTEmfExtTextoutA, const unsigned int &unRecordSize)
        {
        }

        void CEmfInterpretator::HANDLE_EMR_EXTTEXTOUTW(const TEmfExtTextoutW &oTEmfExtTextoutW, const unsigned int &unRecordSize)
        {
                const unsigned int unDxCount = oTEmfExtTextoutW.wEmrText.Options & ETO_PDY ? 2 * oTEmfExtTextoutW.wEmrText.Chars : oTEmfExtTextoutW.wEmrText.Chars;

                int unExplicitRecordSize    = 76 + oTEmfExtTextoutW.wEmrText.Chars * 2 + unDxCount * 4;
                int unType                  = EMR_EXTTEXTOUTW;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oTEmfExtTextoutW.Bounds);

                m_pOutStream->write((char *)&oTEmfExtTextoutW.iGraphicsMode,    sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfExtTextoutW.exScale,          sizeof (float));
                m_pOutStream->write((char *)&oTEmfExtTextoutW.eyScale,          sizeof (float));

                WritePoint(oTEmfExtTextoutW.wEmrText.Reference);

                m_pOutStream->write((char *)&oTEmfExtTextoutW.wEmrText.Chars,       sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfExtTextoutW.wEmrText.offString,   sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfExtTextoutW.wEmrText.Options,     sizeof (unsigned int));

                WriteRectangle(oTEmfExtTextoutW.wEmrText.Rectangle);

                m_pOutStream->write((char *)&oTEmfExtTextoutW.wEmrText.offDx,       sizeof (unsigned int));
                m_pOutStream->write((char *)&oTEmfExtTextoutW.wEmrText.OutputString,sizeof (unsigned short) * oTEmfExtTextoutW.wEmrText.Chars);

                if (unDxCount > 0)
                        m_pOutStream->write((char *)&oTEmfExtTextoutW.wEmrText.OutputDx,sizeof (unsigned int) * unDxCount);
        }

        void CEmfInterpretator::HANDLE_EMR_LINETO(const TEmfPointL &oPoint)
        {
                int unExplicitRecordSize    = 16;
                int unType                  = EMR_LINETO;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_PIE(const TEmfRectL &oBox, const TEmfPointL &oStart, const TEmfPointL &oEnd)
        {
                int unExplicitRecordSize    = 40;
                int unType                  = EMR_PIE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBox);
                WritePoint(oStart);
                WritePoint(oEnd);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYBEZIER(const TEmfRectL &oBounds, const std::vector<TEmfPointL> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 8 * arPoints.size();
                int unType                  = EMR_POLYBEZIER;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointL& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYBEZIER(const TEmfRectL &oBounds, const std::vector<TEmfPointS> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 4 * arPoints.size();
                int unType                  = EMR_POLYBEZIER;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointS& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYBEZIERTO(const TEmfRectL &oBounds, const std::vector<TEmfPointL> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 8 * arPoints.size();
                int unType                  = EMR_POLYBEZIERTO;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointL& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYBEZIERTO(const TEmfRectL &oBounds, const std::vector<TEmfPointS> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 4 * arPoints.size();
                int unType                  = EMR_POLYBEZIERTO;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointS& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYDRAW(const TEmfRectL &oBounds, TEmfPointL *arPoints, const unsigned int &unCount, const unsigned char *pAbTypes)
        {
                if (NULL == arPoints || NULL == pAbTypes)
                        return;

                int unExplicitRecordSize    = 28 + 8 * unCount;
                int unType                  = EMR_POLYDRAW;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)&unCount,  sizeof (unsigned int));

                for (unsigned int i = 0; i < unCount; ++i)
                        WritePoint(arPoints[i]);

                for (unsigned int i = 0; i < unCount; ++i)
                        m_pOutStream->write((char *)&pAbTypes[i],  sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_POLYDRAW(const TEmfRectL &oBounds, TEmfPointS *arPoints, const unsigned int &unCount, const unsigned char *pAbTypes)
        {
                if (NULL == arPoints || NULL == pAbTypes)
                        return;

                int unExplicitRecordSize    = 28 + 4 * unCount;
                int unType                  = EMR_POLYDRAW;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)&unCount,  sizeof (unsigned int));

                for (unsigned int i = 0; i < unCount; ++i)
                        WritePoint(arPoints[i]);

                for (unsigned int i = 0; i < unCount; ++i)
                        m_pOutStream->write((char *)&pAbTypes[i],  sizeof (unsigned int));
        }

        void CEmfInterpretator::HANDLE_EMR_POLYGON(const TEmfRectL &oBounds, const std::vector<TEmfPointL> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 8 * arPoints.size();
                int unType                  = EMR_POLYGON;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointL& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYGON(const TEmfRectL &oBounds, const std::vector<TEmfPointS> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 4 * arPoints.size();
                int unType                  = EMR_POLYGON;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointS& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYLINE(const TEmfRectL &oBounds, const std::vector<TEmfPointL> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 8 * arPoints.size();
                int unType                  = EMR_POLYLINE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointL& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYLINE(const TEmfRectL &oBounds, const std::vector<TEmfPointS> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 4 * arPoints.size();
                int unType                  = EMR_POLYLINE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointS& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYLINETO(const TEmfRectL &oBounds, const std::vector<TEmfPointL> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 8 * arPoints.size();
                int unType                  = EMR_POLYLINETO;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointL& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_POLYLINETO(const TEmfRectL &oBounds, const std::vector<TEmfPointS> &arPoints)
        {
                int unExplicitRecordSize    = 28 + 4 * arPoints.size();
                int unType                  = EMR_POLYLINETO;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);

                m_pOutStream->write((char *)arPoints.size(),  sizeof (unsigned int));

                for (const TEmfPointS& oPoint : arPoints)
                        WritePoint(oPoint);
        }

        void CEmfInterpretator::HANDLE_EMR_RECTANGLE(const TEmfRectL &oBox)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_RECTANGLE;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBox);
        }

        void CEmfInterpretator::HANDLE_EMR_ROUNDRECT(const TEmfRectL &oBox, const TEmfSizeL &oCorner)
        {
                int unExplicitRecordSize    = 32;
                int unType                  = EMR_ROUNDRECT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBox);
                WriteSize(oCorner);
        }

        void CEmfInterpretator::HANDLE_EMR_SETPIXELV(const TEmfPointL &oPoint, const TEmfColor &oColor)
        {
                int unExplicitRecordSize    = 20;
                int unType                  = EMR_ROUNDRECT;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WritePoint(oPoint);
                WriteColor(oColor);
        }

        void CEmfInterpretator::HANDLE_EMR_SMALLTEXTOUT(const TEmfSmallTextout &oText, const unsigned int &unRecordSize)
        {

        }

        void CEmfInterpretator::HANDLE_EMR_STROKEANDFILLPATH(const TEmfRectL &oBounds)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_STROKEANDFILLPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);
        }

        void CEmfInterpretator::HANDLE_EMR_STROKEPATH(const TEmfRectL &oBounds)
        {
                int unExplicitRecordSize    = 24;
                int unType                  = EMR_STROKEPATH;

                unFileSize += unExplicitRecordSize;

                m_pOutStream->write((char *)&unType,                sizeof (int));
                m_pOutStream->write((char *)&unExplicitRecordSize,  sizeof (int));

                WriteRectangle(oBounds);
        }

        void CEmfInterpretator::WriteRectangle(const TEmfRectL &oBounds)
        {
                m_pOutStream->write((char *)&oBounds.lLeft,   sizeof(int));
                m_pOutStream->write((char *)&oBounds.lTop,    sizeof(int));
                m_pOutStream->write((char *)&oBounds.lRight,  sizeof(int));
                m_pOutStream->write((char *)&oBounds.lBottom, sizeof(int));
        }

        void CEmfInterpretator::WriteSize(const TEmfSizeL &oSize)
        {
                m_pOutStream->write((char *)&oSize.cx,   sizeof(unsigned int));
                m_pOutStream->write((char *)&oSize.cy,   sizeof(unsigned int));
        }

        void CEmfInterpretator::WriteColor(const TEmfColor &oColor)
        {
                m_pOutStream->write((char *)&oColor.r, sizeof (unsigned char));
                m_pOutStream->write((char *)&oColor.g, sizeof (unsigned char));
                m_pOutStream->write((char *)&oColor.b, sizeof (unsigned char));
                m_pOutStream->write((char *)&oColor.a, sizeof (unsigned char));
        }

        void CEmfInterpretator::WriteForm(const TXForm &oForm)
        {
                m_pOutStream->write((char *)&oForm.M11,  sizeof (float));
                m_pOutStream->write((char *)&oForm.M12,  sizeof (float));
                m_pOutStream->write((char *)&oForm.M21,  sizeof (float));
                m_pOutStream->write((char *)&oForm.M22,  sizeof (float));
                m_pOutStream->write((char *)&oForm.Dx,   sizeof (float));
                m_pOutStream->write((char *)&oForm.Dy,   sizeof (float));
        }

        void CEmfInterpretator::WritePoint(const TEmfPointL &oPoint)
        {
                m_pOutStream->write((char *)&oPoint.x, sizeof (int));
                m_pOutStream->write((char *)&oPoint.y, sizeof (int));
        }

        void CEmfInterpretator::WritePoint(const TEmfPointS &oPoint)
        {
                m_pOutStream->write((char *)&oPoint.x, sizeof (short));
                m_pOutStream->write((char *)&oPoint.y, sizeof (short));
        }
}


