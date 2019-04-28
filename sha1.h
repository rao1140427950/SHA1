#ifndef _SHA1_H_
#define _SHA1_H_

#include <string>

using namespace std;

#define INTS_NUM  16
#define BYTES_NUM  (INTS_NUM * 4)

const char HEX[16] = {
  '0', '1', '2', '3',
  '4', '5', '6', '7',
  '8', '9', 'a', 'b',
  'c', 'd', 'e', 'f'
};

typedef unsigned long uint32;
typedef unsigned char uint8;
typedef unsigned long long uint64;

#define A (uint32(0x67452301))
#define B (uint32(0xefcdab89))
#define C (uint32(0x98badcfe))
#define D (uint32(0x10325476))
#define E (uint32(0xc3d2e1f0))

void buffer_to_block(string buffer, uint32 block[INTS_NUM]);
uint32 cyclic_shift_left(uint32 x, uint32 n);
void round0(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i);
void round1(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i);
void round2(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i);
void round3(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i);
void round4(uint32 block[INTS_NUM], uint32 v, uint32& w, uint32 x, uint32 y, uint32& z, uint32 i);
void transform(uint32 state[5], uint32 block[INTS_NUM], uint64& transforms);


string getSHA1(string message);

#endif // _SHA1_H_