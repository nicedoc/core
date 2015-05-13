#ifndef _PDF_READER_LEXER_H
#define _PDF_READER_LEXER_H

#include "Object.h"
#include "Stream.h"

namespace PdfReader
{
	class XRef;

#define TokenBufferSize 128

	//------------------------------------------------------------------------
	// Lexer
	//------------------------------------------------------------------------

	class Lexer
	{
	public:

		// ����������� ��� ������ ������. ������� ���� ����� � �����������.
		Lexer(XRef *pXref, Stream *pStream);

		// ���������� ��� ������ ������ ��� ������� �������.
		Lexer(XRef *pXref, Object *pObject);

		~Lexer();

		// �������� ��������� ������ �� ������.
		Object *GetObject(Object *obj);

		// ��������� � ������ ����� ������.
		void SkipToNextLine();

		// ��������� � ���������� �������.
		void SkipChar()
		{
			GetChar();
		}


		Stream *GetStream()
		{
			return m_oCurStream.IsNone() ? (Stream *)NULL : m_oCurStream.GetStream();
		}

		// ������� �������. ������������ ������ ��� ��������� �� ������, �������
		// ������������ �������� ���� int, � �� unsigned int.
		int GetPos()
		{
			return m_oCurStream.IsNone() ? -1 : (int)m_oCurStream.StreamGetPos();
		}


		void SetPos(unsigned int unPos, int nDir = 0)
		{
			if (!m_oCurStream.IsNone())
				m_oCurStream.StreamSetPos(unPos, nDir);
		}

		// ��������� �������� �� nChar ��������.
		static bool IsSpace(int nChar);

	private:

		int GetChar();
		int LookChar();

	private:

		Array *m_pStreams;        // ������ �������
		int    m_nCurStreamIndex; // ����� �������� ������
		Object m_oCurStream;      // ������� �����
		bool   m_bFreeArray;      // ������ �� �� � ������ ������ ����������� ������ �������?
		char   m_sTempBuffer[TokenBufferSize];	// Buffer
	};
}

#endif // _PDF_READER_LEXER_H