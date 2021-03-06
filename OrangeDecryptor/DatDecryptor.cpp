#include "stdafx.h"
#include "DatDecryptor.h"

#include <algorithm>

const unsigned char szDecryptVector[] = {
	0x61, 0x38, 0x59, 0x62, 0x35, 0x24, 0x49, 0x70,
	0x56, 0x6F, 0x62, 0x52, 0x2C, 0x31, 0x58, 0x70,

	0x68, 0x21, 0x6B, 0x28, 0x23, 0x21, 0x42, 0x39,
	0x68, 0x24, 0x56, 0x5B, 0x6F, 0x5B, 0x72, 0x2D,

	0x49, 0x27, 0x78, 0x2E, 0x33, 0x37, 0x51, 0x25,
	0x45, 0x3B, 0x6C, 0x74, 0x32, 0x77, 0x47, 0x67,

	0x6B, 0x29, 0x68, 0x4E, 0x46, 0x5F, 0x70, 0x5F,
	0x21, 0x6D, 0x46, 0x3F, 0x44, 0x73, 0x35, 0x34,

	0x2E, 0x2A, 0x38, 0x45, 0x72, 0x62, 0x43, 0x4B,
	0x2C, 0x33, 0x30
};


DatDecryptor::DatDecryptor()
	:m_index(0)
{
	// Nothing to do.
}

void DatDecryptor::Reset()
{
	m_index = 0;
}

void DatDecryptor::DecryptBuffer(LPBYTE lpBuffer, int64_t bufferSize)
{
	std::transform(lpBuffer, lpBuffer + bufferSize, lpBuffer, [this](const BYTE c)->BYTE {
		return c ^ GetNextKey();
	});
}

BYTE DatDecryptor::GetNextKey()
{
	BYTE result = szDecryptVector[m_index];
	m_index++;
	if (m_index >= _countof(szDecryptVector))
	{
		m_index = 0;
	}
	return result;
}
