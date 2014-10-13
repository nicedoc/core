#pragma once

#include "OfficeArtRecord.h"
#include "../BitMarkedStructs.h"

namespace XLS
{
	class CFRecord;
}


namespace ODRAW
{;

class OfficeArtClientAnchorSheet : public OfficeArtRecord
{
	BASE_OBJECT_DEFINE_CLASS_NAME(OfficeArtClientAnchorSheet)
public:
	OfficeArtClientAnchorSheet();
	XLS::BiffStructurePtr clone();

	//virtual void setXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag);
	//virtual void getXMLAttributes(MSXML2::IXMLDOMElementPtr xml_tag);
	virtual void loadFields(XLS::CFRecord& record);
	virtual void storeFields(XLS::CFRecord& record);

private:
	bool fMove;
	bool fSize;

	XLS::Col256U colL;
	short dxL;
	XLS::RwU rwT;
	short dyT;
	XLS::Col256U colR;
	short dxR;
	XLS::RwU rwB;
	short dyB;

	unsigned int _dxL;
	unsigned int _dyT;
	unsigned int _dxR;
	unsigned int _dyB;
};

typedef boost::shared_ptr<OfficeArtClientAnchorSheet> OfficeArtClientAnchorSheetPtr;


} // namespace XLS