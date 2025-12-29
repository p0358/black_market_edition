#pragma once

class Vector;
class QAngle;

typedef enum
{
	BITBUFERROR_VALUE_OUT_OF_RANGE = 0, // Tried to write a value with too few bits.
	BITBUFERROR_BUFFER_OVERRUN,         // Was about to overrun a buffer.

	BITBUFERROR_NUM_ERRORS
} BitBufErrorType;

#define LittleDWord(val) (val)
#define LittleFloat(pOut, pIn)	(*pOut = *pIn)

#define LOG2_BITS_PER_INT	5
#define BITS_PER_INT		32

inline int GetBitForBitnum(int bitNum)
{
	static int bitsForBitnum[] =
	{
		(1 << 0),
		(1 << 1),
		(1 << 2),
		(1 << 3),
		(1 << 4),
		(1 << 5),
		(1 << 6),
		(1 << 7),
		(1 << 8),
		(1 << 9),
		(1 << 10),
		(1 << 11),
		(1 << 12),
		(1 << 13),
		(1 << 14),
		(1 << 15),
		(1 << 16),
		(1 << 17),
		(1 << 18),
		(1 << 19),
		(1 << 20),
		(1 << 21),
		(1 << 22),
		(1 << 23),
		(1 << 24),
		(1 << 25),
		(1 << 26),
		(1 << 27),
		(1 << 28),
		(1 << 29),
		(1 << 30),
		(1 << 31),
	};

	return bitsForBitnum[(bitNum) & (BITS_PER_INT - 1)];
}

inline int BitByte(int bits)
{
	// return PAD_NUMBER( bits, 8 ) >> 3;
	return (bits + 7) >> 3;
}

//-----------------------------------------------------------------------------
// Used for serialization
//-----------------------------------------------------------------------------
class CBitBuffer
{
public:
	CBitBuffer();
	void SetDebugName(const char* pName) { m_pDebugName = pName; }
	const char* GetDebugName() const { return m_pDebugName; }
	FORCEINLINE void SetOverflowFlag() { m_bOverflow = true; }
	FORCEINLINE bool IsOverflowed() const { return m_bOverflow; }

	////////////////////////////////////
protected: friend struct CBitBuffer_verify;
		 const char* m_pDebugName;
		 uint8_t m_bOverflow;
		 size_t m_nDataBits;
		 size_t m_nDataBytes;
};

struct CBitBuffer_verify
{
	static_assert(sizeof(CBitBuffer) == 32);
	static_assert(offsetof(CBitBuffer, m_pDebugName) == 0);
	static_assert(offsetof(CBitBuffer, m_bOverflow) == 8);
	static_assert(offsetof(CBitBuffer, m_nDataBits) == 16);
	static_assert(offsetof(CBitBuffer, m_nDataBytes) == 24);
};

class CBitRead : public CBitBuffer
{
public:
	CBitRead() : CBitBuffer()
	{
		m_nInBufWord = 0;
		m_nBitsAvail = 0;
		m_pDataIn = nullptr;
		m_pBufferEnd = nullptr;
		m_pData = nullptr;
	}

	CBitRead(const void* pData, int nBytes, int nBits = -1)
	{
		StartReading(pData, nBytes, 0, nBits);
	}

	CBitRead(const char* pDebugName, const void* pData, int nBytes, int nBits = -1)
	{
		SetDebugName(pDebugName);
		StartReading(pData, nBytes, 0, nBits);
	}

	void StartReading(const void* pData, size_t nBytes, size_t iStartBit = 0, size_t nBits = -1);

	FORCEINLINE size_t Tell() const { return GetNumBitsRead(); }
	FORCEINLINE size_t TotalBytesAvailable() const { return m_nDataBytes; }
	FORCEINLINE size_t GetNumBitsLeft() const { return m_nDataBits - Tell(); }
	FORCEINLINE size_t GetNumBytesLeft() const { return GetNumBitsLeft() >> 3; }

	bool Seek(size_t nPosition);
	FORCEINLINE bool SeekRelative(size_t nOffset) { return Seek(GetNumBitsRead() + nOffset); }
	FORCEINLINE unsigned char const* GetBasePointer() { return reinterpret_cast<unsigned char const*>(m_pData); }

	size_t GetNumBitsRead() const;
	FORCEINLINE size_t GetNumBytesRead() const { return ((GetNumBitsRead() + 7) >> 3); }

	void GrabNextDWord(bool bOverFlowImmediately = false);
	void FetchNext();

	uint32_t ReadUBitLong(unsigned int numbits);
	int32_t ReadSBitLong(unsigned int numbits);

	bool ReadOneBit();
	FORCEINLINE char ReadChar() { return static_cast<char>(ReadSBitLong(sizeof(char) << 3)); }
	FORCEINLINE unsigned char ReadByte() { return static_cast<unsigned char>(ReadUBitLong(sizeof(unsigned char) << 3)); }
	FORCEINLINE short ReadShort() { return static_cast<short>(ReadSBitLong(sizeof(short) << 3)); }
	FORCEINLINE unsigned short ReadWord() { return static_cast<unsigned short>(ReadUBitLong(sizeof(unsigned short) << 3)); }
	FORCEINLINE int ReadLong() { return static_cast<int>(ReadSBitLong(sizeof(int) << 3)); }
	FORCEINLINE float ReadFloat() { auto raw = ReadUBitLong(sizeof(int) << 3); return reinterpret_cast<float&>(raw); }
	int64_t ReadLongLong();
	FORCEINLINE uint64_t ReadULongLong() { auto raw = ReadLongLong(); return reinterpret_cast<uint64_t&>(raw); }

	FORCEINLINE int8_t ReadInt8() { return static_cast<int8_t>(ReadSBitLong(sizeof(int8_t) << 3)); }
	FORCEINLINE uint8_t ReadUInt8() { return static_cast<uint8_t>(ReadUBitLong(sizeof(uint8_t) << 3)); }
	FORCEINLINE int16_t ReadInt16() { return static_cast<int16_t>(ReadSBitLong(sizeof(int16_t) << 3)); }
	FORCEINLINE uint16_t ReadUInt16() { return static_cast<uint16_t>(ReadUBitLong(sizeof(uint16_t) << 3)); }
	FORCEINLINE int32_t ReadInt32() { return static_cast<int32_t>(ReadSBitLong(sizeof(int32_t) << 3)); }
	FORCEINLINE uint32_t ReadUInt32() { return static_cast<uint32_t>(ReadUBitLong(sizeof(uint32_t) << 3)); }
	FORCEINLINE int64_t ReadInt64() { return ReadLongLong(); }
	FORCEINLINE uint64_t ReadUInt64() { auto raw = ReadLongLong(); return reinterpret_cast<uint64_t&>(raw); }

	void ReadBits(void* pOut, int nBits);
	FORCEINLINE bool ReadBytes(void* pOut, int nBytes) { ReadBits(pOut, nBytes << 3); return !IsOverflowed(); }
	template<std::size_t nBytes> FORCEINLINE bool ReadBytes(char(&pOut)[nBytes]) { ReadBits(pOut, nBytes << 3); return !IsOverflowed(); }
	bool ReadString(char* pStr, int bufLen, bool bLine = false, int* pOutNumChars = nullptr);
	template<std::size_t bufLen> FORCEINLINE bool ReadString(char(&pStr)[bufLen], bool bLine = false, int* pOutNumChars = nullptr) { return ReadString(pStr, bufLen, bLine, pOutNumChars); }
	bool ReadStdString(std::string& out, bool bLine = false);

	////////////////////////////////////
protected: friend struct CBitRead_verify;
		 uint32_t m_nInBufWord;
		 uint32_t m_nBitsAvail;
		 const uint32_t* m_pDataIn;
		 const uint32_t* m_pBufferEnd;
		 const uint32_t* m_pData;
};

struct CBitRead_verify
{
	static_assert(sizeof(CBitRead) == 32 + 32);
	static_assert(offsetof(CBitRead, m_nInBufWord) == 32);
	static_assert(offsetof(CBitRead, m_nBitsAvail) == 36);
	static_assert(offsetof(CBitRead, m_pDataIn) == 40);
	static_assert(offsetof(CBitRead, m_pBufferEnd) == 48);
	static_assert(offsetof(CBitRead, m_pData) == 56);
};

class bf_read : public CBitRead
{
public:
	//bf_read() : CBitRead() {}
	//bf_read(const void* pData, int nBytes, int nBits = -1) : CBitRead(pData, nBytes, nBits) {}
	//bf_read(const char* pDebugName, const void* pData, int nBytes, int nBits = -1) : CBitRead(pDebugName, pData, nBytes, nBits) {}
	using CBitRead::CBitRead; // inherit constructors
};

class bf_write
{
public:
	bf_write();

	// nMaxBits can be used as the number of bits in the buffer. 
	// It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
	bf_write(void* pData, int nBytes, int nMaxBits = -1);
	bf_write(const char* pDebugName, void* pData, int nBytes, int nMaxBits = -1);

	// Start writing to the specified buffer.
	// nMaxBits can be used as the number of bits in the buffer. 
	// It must be <= nBytes*8. If you leave it at -1, then it's set to nBytes * 8.
	void StartWriting(void* pData, int nBytes, int iStartBit = 0, int nMaxBits = -1);

	// Restart buffer writing.
	FORCEINLINE void Reset() { m_iCurBit = 0; m_bOverflow = false; }

	// How many bytes are filled in?
	FORCEINLINE int GetNumBytesWritten() const { return BitByte(this->m_iCurBit); }
	FORCEINLINE int GetNumBitsWritten() const { return this->m_iCurBit; }
	FORCEINLINE int GetMaxNumBits() const { return this->m_nDataBits; }
	FORCEINLINE int GetNumBitsLeft() const { return this->m_nDataBits - m_iCurBit; }
	FORCEINLINE int GetNumBytesLeft() const { return this->GetNumBitsLeft() >> 3; }
	FORCEINLINE unsigned char* GetData() const { return reinterpret_cast<unsigned char*>(this->m_pData); }
	const char* GetDebugName() const { return this->m_pDebugName; }

	// Has the buffer overflowed?
	bool CheckForOverflow(int nBits);
	FORCEINLINE bool IsOverflowed() const { return this->m_bOverflow; }
	void SetOverflowFlag();

	// Bit functions.

	void WriteOneBit(int nValue);
	void WriteOneBitNoCheck(int nValue);
	void WriteOneBitAt(int iBit, int nValue);

	// Write signed or unsigned. Range is only checked in debug.
	void WriteUBitLong(unsigned int data, int numbits, bool bCheckRange = true);
	void WriteSBitLong(int data, int numbits);

	bool WriteBits(const void* pIn, int nBits);
	// Copy the bits straight out of pIn. This seeks pIn forward by nBits.
	// Returns an error if this buffer or the read buffer overflows.
	bool WriteBitsFromBuffer(class bf_read* pIn, int nBits);

	void WriteUBitVar(unsigned int data); // writes an unsigned integer with variable bit length

	// writes a varint encoded integer
	void WriteVarInt32(uint32_t data);
	void WriteVarInt64(uint64_t data);
	void WriteSignedVarInt32(int32_t data);
	void WriteSignedVarInt64(int64_t data);
	/*int ByteSizeVarInt32(uint32_t data);
	int ByteSizeVarInt64(uint64_t data);
	int ByteSizeSignedVarInt32(int32_t data);
	int ByteSizeSignedVarInt64(int64_t data);*/

	void WriteBitAngle(float fAngle, int numbits);
	void WriteBitCoord(const float f);
	void WriteBitCoordMP(const float f, bool bIntegral, bool bLowPrecision);
	void WriteBitFloat(float val);
	//void WriteBitVec3Coord(const Vector& fa);
	void WriteBitNormal(float f);
	//void WriteBitVec3Normal(const Vector& fa);
	//void WriteBitAngles(const QAngle& fa);

	FORCEINLINE void WriteChar(char val) { WriteSBitLong(val, sizeof(char) << 3); }
	FORCEINLINE void WriteByte(unsigned char val) { WriteUBitLong(val, sizeof(unsigned char) << 3); }
	FORCEINLINE void WriteShort(short val) { WriteSBitLong(val, sizeof(short) << 3); }
	FORCEINLINE void WriteWord(unsigned short val) { WriteUBitLong(val, sizeof(unsigned short) << 3); }
	FORCEINLINE void WriteLong(long val) { WriteSBitLong(val, sizeof(long) << 3); }

	FORCEINLINE void WriteInt8(int8_t val) { WriteSBitLong(val, sizeof(int8_t) << 3); }
	FORCEINLINE void WriteUInt8(uint8_t val) { WriteUBitLong(val, sizeof(uint8_t) << 3); }
	FORCEINLINE void WriteInt16(int16_t val) { WriteSBitLong(val, sizeof(int16_t) << 3); }
	FORCEINLINE void WriteUInt16(uint16_t val) { WriteUBitLong(val, sizeof(uint16_t) << 3); }
	FORCEINLINE void WriteInt32(int32_t val) { WriteSBitLong(val, sizeof(int32_t) << 3); }
	FORCEINLINE void WriteUInt32(uint32_t val) { WriteUBitLong(val, sizeof(uint32_t) << 3); }
	FORCEINLINE void WriteInt64(int64_t val) { WriteLongLong(val); }
	FORCEINLINE void WriteUInt64(uint64_t val) { WriteLongLong(reinterpret_cast<int64_t&>(val)); }

	void WriteLongLong(int64_t val);
	void WriteFloat(float val);
	FORCEINLINE bool WriteBytes(const void* pBuf, int nBytes) { return WriteBits(pBuf, nBytes << 3); }
	template<std::size_t nBytes> FORCEINLINE bool WriteBytes(char(&pBuf)[nBytes]) { return WriteBits(pBuf, nBytes << 3); }

	// Returns false if it overflows the buffer.
	bool WriteString(const char* pStr);


protected: friend struct bf_write_verify;
		 uint32_t* m_pData;
		 int m_nDataBytes;
		 int m_nDataBits;
		 int m_iCurBit;
		 bool m_bOverflow;
		 bool m_bAssertOnOverflow;
		 const char* m_pDebugName;
};

struct bf_write_verify
{
	static_assert(sizeof(bf_write) == 32);
	static_assert(offsetof(bf_write, m_pData) == 0);
	static_assert(offsetof(bf_write, m_nDataBytes) == 8);
	static_assert(offsetof(bf_write, m_nDataBits) == 12);
	static_assert(offsetof(bf_write, m_iCurBit) == 16);
	static_assert(offsetof(bf_write, m_bOverflow) == 20);
	static_assert(offsetof(bf_write, m_bAssertOnOverflow) == 21);
	static_assert(offsetof(bf_write, m_pDebugName) == 24);
};
