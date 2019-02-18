#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

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
	return 1693 * (y + x + (unsigned int)z) % 811;
}

uint64_t hash(const std::string &pn)
{
	uint64_t coeff2 = 0;

	for(int i = 1; i < pn.length(); i+=2)
	{
		uint8_t c1 = pn[i - 1];
		coeff2 += c1 ^ (uint8_t)(~pn[i]);
	}

	coeff2 = 4273 * coeff2 - 821 * ((uint64_t)(0x9FA6328395FBA275LL * (unsigned __int128)(4273 * coeff2) >> 64) >> 9);
}

int main()
{
    // SPAWN COORDS
    // x = 95
    // y = 117
    // z = 7

	uint64_t goal = calc(95, 117, 7);

	std::cout<< "GOAL = " << goal << std::endl;

    int n = 7;
    int i,j;
    char *c = new char[n+1];
    for(i=1;i<=n;i++){
        for(j=0;j<i;j++) c[j]='A';
        c[i]=0;
        do {
           	if(hash(std::string(c)) == goal)
           		printf("gottit: %s\n", c);
        } while(inc(c));
    }

   	delete [] c;
	return 0;
}
