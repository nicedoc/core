#include "NamedShowSlidesAtom.h"

using namespace PPT;

void CRecordNamedShowSlidesAtom::ReadFromStream(SRecordHeader &oHeader, POLE::Stream *pStream)
{
    return CUnknownRecord::ReadFromStream(oHeader, pStream);
}
