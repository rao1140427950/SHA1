#include "sha1.h"
#include <sstream>
#include <iomanip>

void buffer_to_block(string buffer, uint32 block[INTS_NUM])
{
	for (size_t i = 0; i < INTS_NUM; i++)
	{
		block[i] = (buffer[4 * i + 3] & 0xff)
			| (buffer[4 * i + 2] & 0xff) << 8
			| (buffer[4 * i + 1] & 0xff) << 16
			| (buffer[4 * i + 0] & 0xff) << 24;
	}
}

uint32 cyclic_shift_left(uint32 x, uint32 n)
{
	return (x << n) | (x >> (32 - n));
}

uint32 blk(uint32 block[INTS_NUM], uint32 i)
{
	return cyclic_shift_left(block[(i + 13) & 15] ^ block[(i + 8) & 15] ^ block[(i + 2) & 15] ^ block[i], 1);
}

void round0(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i)
{
	z += ((w & (x ^ y)) ^ y) + block[i] + 0x5a827999 + cyclic_shift_left(v, 5);
	w = cyclic_shift_left(w, 30);
}

void round1(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i)
{
	block[i] = blk(block, i);
	z += ((w & (x ^ y)) ^ y) + block[i] + 0x5a827999 + cyclic_shift_left(v, 5);
	w = cyclic_shift_left(w, 30);
}


void round2(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i)
{
	block[i] = blk(block, i);
	z += (w ^ x ^ y) + block[i] + 0x6ed9eba1 + cyclic_shift_left(v, 5);
	w = cyclic_shift_left(w, 30);
}


void round3(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i)
{
	block[i] = blk(block, i);
	z += (((w | x) & y) | (w & x)) + block[i] + 0x8f1bbcdc + cyclic_shift_left(v, 5);
	w = cyclic_shift_left(w, 30);
}


void round4(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32  i)
{
	block[i] = blk(block, i);
	z += (w ^ x ^ y) + block[i] + 0xca62c1d6 + cyclic_shift_left(v, 5);
	w = cyclic_shift_left(w, 30);
}

void transform(uint32 state[5], uint32 block[INTS_NUM], uint64& transforms)
{
	/* Copy digest[] to working vars */
	uint32 a = state[0];
	uint32 b = state[1];
	uint32 c = state[2];
	uint32 d = state[3];
	uint32 e = state[4];

	/* 4 rounds of 20 operations each. Loop unrolled. */
	round0(block, a, b, c, d, e, 0);
	round0(block, e, a, b, c, d, 1);
	round0(block, d, e, a, b, c, 2);
	round0(block, c, d, e, a, b, 3);
	round0(block, b, c, d, e, a, 4);
	round0(block, a, b, c, d, e, 5);
	round0(block, e, a, b, c, d, 6);
	round0(block, d, e, a, b, c, 7);
	round0(block, c, d, e, a, b, 8);
	round0(block, b, c, d, e, a, 9);
	round0(block, a, b, c, d, e, 10);
	round0(block, e, a, b, c, d, 11);
	round0(block, d, e, a, b, c, 12);
	round0(block, c, d, e, a, b, 13);
	round0(block, b, c, d, e, a, 14);
	round0(block, a, b, c, d, e, 15);
	round1(block, e, a, b, c, d, 0);
	round1(block, d, e, a, b, c, 1);
	round1(block, c, d, e, a, b, 2);
	round1(block, b, c, d, e, a, 3);
	round2(block, a, b, c, d, e, 4);
	round2(block, e, a, b, c, d, 5);
	round2(block, d, e, a, b, c, 6);
	round2(block, c, d, e, a, b, 7);
	round2(block, b, c, d, e, a, 8);
	round2(block, a, b, c, d, e, 9);
	round2(block, e, a, b, c, d, 10);
	round2(block, d, e, a, b, c, 11);
	round2(block, c, d, e, a, b, 12);
	round2(block, b, c, d, e, a, 13);
	round2(block, a, b, c, d, e, 14);
	round2(block, e, a, b, c, d, 15);
	round2(block, d, e, a, b, c, 0);
	round2(block, c, d, e, a, b, 1);
	round2(block, b, c, d, e, a, 2);
	round2(block, a, b, c, d, e, 3);
	round2(block, e, a, b, c, d, 4);
	round2(block, d, e, a, b, c, 5);
	round2(block, c, d, e, a, b, 6);
	round2(block, b, c, d, e, a, 7);
	round3(block, a, b, c, d, e, 8);
	round3(block, e, a, b, c, d, 9);
	round3(block, d, e, a, b, c, 10);
	round3(block, c, d, e, a, b, 11);
	round3(block, b, c, d, e, a, 12);
	round3(block, a, b, c, d, e, 13);
	round3(block, e, a, b, c, d, 14);
	round3(block, d, e, a, b, c, 15);
	round3(block, c, d, e, a, b, 0);
	round3(block, b, c, d, e, a, 1);
	round3(block, a, b, c, d, e, 2);
	round3(block, e, a, b, c, d, 3);
	round3(block, d, e, a, b, c, 4);
	round3(block, c, d, e, a, b, 5);
	round3(block, b, c, d, e, a, 6);
	round3(block, a, b, c, d, e, 7);
	round3(block, e, a, b, c, d, 8);
	round3(block, d, e, a, b, c, 9);
	round3(block, c, d, e, a, b, 10);
	round3(block, b, c, d, e, a, 11);
	round4(block, a, b, c, d, e, 12);
	round4(block, e, a, b, c, d, 13);
	round4(block, d, e, a, b, c, 14);
	round4(block, c, d, e, a, b, 15);
	round4(block, b, c, d, e, a, 0);
	round4(block, a, b, c, d, e, 1);
	round4(block, e, a, b, c, d, 2);
	round4(block, d, e, a, b, c, 3);
	round4(block, c, d, e, a, b, 4);
	round4(block, b, c, d, e, a, 5);
	round4(block, a, b, c, d, e, 6);
	round4(block, e, a, b, c, d, 7);
	round4(block, d, e, a, b, c, 8);
	round4(block, c, d, e, a, b, 9);
	round4(block, b, c, d, e, a, 10);
	round4(block, a, b, c, d, e, 11);
	round4(block, e, a, b, c, d, 12);
	round4(block, d, e, a, b, c, 13);
	round4(block, c, d, e, a, b, 14);
	round4(block, b, c, d, e, a, 15);

	/* Add the working vars back into digest[] */
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;

	/* Count the number of transformations */
	transforms++;
}


string getSHA1(string message)
{
	string buffer = "";
	uint64 transforms = 0;
	uint32 state[5];

	istringstream is(message);

	state[0] = A;
	state[1] = B;
	state[2] = C;
	state[3] = D;
	state[4] = E;

	while (true)
	{
		char sbuf[BYTES_NUM];
		is.read(sbuf, BYTES_NUM - buffer.size());
		buffer.append(sbuf, (uint32)is.gcount());
		if (buffer.size() != BYTES_NUM)
		{
			break;
		}
		uint32 block[INTS_NUM];
		buffer_to_block(buffer, block);
		transform(state, block, transforms);
		buffer.clear();
	}

	uint64 total_bits = (transforms * BYTES_NUM + buffer.size()) * 8;
	buffer += (char)0x80;
	uint32 buffer_size = buffer.size();

	while (buffer.size() < BYTES_NUM)
	{
		buffer += (char)0x00;
	}

	uint32 block[INTS_NUM];
	buffer_to_block(buffer, block);

	if (buffer_size > BYTES_NUM - 8)
	{
		transform(state, block, transforms);
		for (uint32 i = 0; i < INTS_NUM - 2; i++)
		{
			block[i] = 0;
		}
	}

	block[INTS_NUM - 1] = (uint32)total_bits;
	block[INTS_NUM - 2] = (uint32)(total_bits >> 32);
	transform(state, block, transforms);

	string str = "";
	for (uint32 i = 0; i < 5; i++)
	{
		for (uint32 j = 0; j < 8; j++)
		{
			uint8 index = uint8((state[i] >> ((7 - j) * 4)) & 0x0000000f);
			str.append(1, HEX[index]);
		}
	}

	return str;
}