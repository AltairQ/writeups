#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint64_t QWORD;     // QWORD = unsigned 64 bit value
typedef uint32_t DWORD;   // DWORD = unsigned 32 bit value
typedef uint16_t WORD;    // WORD = unsigned 16 bit value
typedef uint8_t BYTE;     // BYTE = unsigned 8 bit value


//code stolen+modified from stackoverflow!
int inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='z'){
        c[0]='A';
        return inc(c+sizeof(char));
    }
    if(c[0]=='Z')
    	c[0] = 'a';
    else
    	c[0]++;

    return 1;
}


uint64_t calc(uint16_t x, uint16_t y, uint8_t z)
{
    return 1693LL * (y + x + z) - 811
            * ((uint64_t)(0xA19E253F72959F69LL
                                * (__uint128_t)(uint64_t)(1693LL* (y + x + z)) >> 64) >> 9);
}

int64_t chksum(char *str, unsigned int *a2)
{
  int64_t result; // rax
  unsigned int v3; // [rsp+14h] [rbp-2Ch]
  unsigned int v4; // [rsp+18h] [rbp-28h]
  int v5; // [rsp+1Ch] [rbp-24h]
  unsigned int i; // [rsp+20h] [rbp-20h]
  int j; // [rsp+20h] [rbp-20h]
  int k; // [rsp+20h] [rbp-20h]

  v3 = *(DWORD *)str;
  v4 = *((DWORD *)str + 1);
  v5 = 0;
  for ( i = 0; i <= 47; ++i )
  {
    v5 -= 559038737;
    v3 += (v4 + v5) ^ (16 * v4 + a2[1]) ^ ((v4 >> 5) + a2[2]);
    v4 += (v3 + v5) ^ (16 * v3 + a2[3]) ^ ((v3 >> 5) + *a2);
  }
  for ( j = v4 & 0x7F; j; --j )
    v3 += v4 + j;
  for ( k = v3 & 0x7F; k; --k )
    v4 += v3 - k;
  *(DWORD *)str = v3;
  result = v4;
  *((DWORD *)str + 1) = v4;
  return result;
}


uint64_t posHash;

bool mockup(const char* playerNick)
{
    unsigned int someConsts[4];

    someConsts[0] = 0xCAFEBABE;
    someConsts[1] = 0xDEDEDEDE;
    someConsts[2] = 0xCAFEBABE;
    someConsts[3] = 0xCAFEBABE;

    uint64_t posHash = calc(95, 117, 7);

    char sthPlayerNick[8];

    for (int i = 0; i <= 7; ++i )
      sthPlayerNick[i] = (BYTE)playerNick[i];

    chksum(sthPlayerNick, someConsts);

    return ( posHash == *(QWORD *)sthPlayerNick
                  - 811
                  * ((uint64_t)(0xA19E253F72959F69LL * (__uint128_t)*(uint64_t *)sthPlayerNick >> 64) >> 9) );
}



int main()
{
    // SPAWN COORDS
    // x = 95
    // y = 117
    // z = 7
    posHash = calc(95, 117, 7);

	std::cout << "GOAL = " << posHash << std::endl;

    int n = 8;
    int i,j;
    char *c = new char[n+1];
    for(i=8;i<=n;i++){
        for(j=0;j<i;j++) c[j]='A';
        c[i]=0;
        do {
           	if(mockup(c))
           		printf("gottit: %s\n", c);
        } while(inc(c));
    }

   	delete [] c;
	return 0;
}