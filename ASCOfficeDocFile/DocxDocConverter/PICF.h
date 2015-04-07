#pragma once

#include "MFPF.h"
#include "PICF_Shape.h"
#include "PICMID.h"

namespace ASCDocFileFormat
{
  class PICF: public IOperand
  {
    private:
      MFPF mfpf;

      static const unsigned char SIZE_IN_BYTES = 68;
	  unsigned char bytes[SIZE_IN_BYTES];

    public:
	  PICF():
	  mfpf(Constants::MM_SHAPE)
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

		unsigned int offset = ( sizeof(int) + sizeof(unsigned short) );

		memcpy( ( this->bytes + offset ), (unsigned char*)(this->mfpf), this->mfpf.Size() );
		offset += this->mfpf.Size();
	  }

	  explicit PICF( int dataSize /*( lcb - cbHeader )*/, const PICMID& _picmid, const MFPF& _mfpf = MFPF(), const PICF_Shape& _innerHeader = PICF_Shape() ):
	  mfpf(_mfpf)
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

	    unsigned int offset = 0;

	    FormatUtils::SetBytes( ( this->bytes + offset ), (int)( SIZE_IN_BYTES + dataSize ) );
	    offset += sizeof(dataSize);

	    FormatUtils::SetBytes( ( this->bytes + offset ), (unsigned short)(SIZE_IN_BYTES) );
	    offset += sizeof(unsigned short);

		memcpy( ( this->bytes + offset ), (unsigned char*)(this->mfpf), this->mfpf.Size() );
		offset += this->mfpf.Size();

   	    memcpy( ( this->bytes + offset ), (unsigned char*)_innerHeader, _innerHeader.Size() );
	    offset += _innerHeader.Size();

        memcpy( ( this->bytes + offset ), (unsigned char*)_picmid, _picmid.Size() );
	    offset += _picmid.Size();
	  }

	  PICF( const PICF& _pICF )
	  {
	    memset( this->bytes, 0, SIZE_IN_BYTES );

	    memcpy( this->bytes, _pICF.bytes, SIZE_IN_BYTES );
	  }

	  virtual ~PICF()
	  {
	  }

	  virtual operator unsigned char*() const
	  {
	    return (unsigned char*)(this->bytes);
	  }

	  virtual operator const unsigned char*() const
	  {
	    return (const unsigned char*)this->bytes;
	  }

	  virtual unsigned int Size() const
	  {
	    return sizeof(this->bytes);
      }

	  Constants::PictureDataFormat GetPictureDataFormat() const
	  {
	    return (Constants::PictureDataFormat)(this->mfpf);  
	  }
  };
}