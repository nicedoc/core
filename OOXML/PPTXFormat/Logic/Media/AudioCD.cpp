/*
 * (c) Copyright Ascensio System SIA 2010-2023
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-6 Ernesta Birznieka-Upish
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include "AudioCD.h"

namespace PPTX
{
	namespace Logic
	{
		AudioCD::AudioCD()
		{
		}
		AudioCD& AudioCD::operator=(const AudioCD& oSrc)
		{
			parentFile		= oSrc.parentFile;
			parentElement	= oSrc.parentElement;

			stTrack		= oSrc.stTrack;
			endTrack	= oSrc.endTrack;

			stTime		= oSrc.stTime;
			endTime		= oSrc.endTime;

			return *this;
		}
		void AudioCD::fromXML(XmlUtils::CXmlLiteReader& oReader)
		{
			//todooo
		}
		void AudioCD::fromXML(XmlUtils::CXmlNode& node)
		{
			XmlUtils::CXmlNode oMem;

			oMem		= node.ReadNode(_T("a:st"));
			stTrack		= oMem.ReadAttributeInt(L"track");
			XmlMacroReadAttributeBase(oMem, L"time", stTime);

			oMem		= node.ReadNode(_T("a:end"));
			endTrack	= oMem.ReadAttributeInt(L"track");
			XmlMacroReadAttributeBase(oMem, L"time", endTime);

			Normalize();
		}
		std::wstring AudioCD::toXML() const
		{
			XmlUtils::CAttribute oAttr1;
			oAttr1.Write(_T("track"), stTrack);
			oAttr1.Write(_T("time"), stTime);

			XmlUtils::CAttribute oAttr2;
			oAttr2.Write(_T("track"), endTrack);
			oAttr2.Write(_T("time"), endTime);

			return _T("<a:audioCd>") + XmlUtils::CreateNode(_T("a:st"), oAttr1) + XmlUtils::CreateNode(_T("a:end"), oAttr2) + _T("</a:audioCd>");
		}
		void AudioCD::FillParentPointersForChilds(){}
		void AudioCD::Normalize()
		{
			stTrack = (std::max)(0, (std::min)(255, stTrack));
			stTrack = (std::max)(0, (std::min)(255, endTrack));

			stTime.normalize_positive();
			endTime.normalize_positive();
		}
	} // namespace Logic
} // namespace PPTX
