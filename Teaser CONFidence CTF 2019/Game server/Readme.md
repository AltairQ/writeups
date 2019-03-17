# Game server (misc [RE really])
## 357 pts

This challenge is almost exactly the same as the "Hard Tibia" from ECSC, so make sure to [read my writeup of it](../../hack.cert/re/hard%20tibia). It's so similar that my old modified otclient still worked!

Only difference is that the server-side "authentication" has changed. It still depends on only two inputs - the character's nickname and its position. Let's see how it's done, courtesy of IDA decompiler:

```c++

__int64 __fastcall chksum(char *nick?, unsigned int *a2)
{
  __int64 result; // rax
  unsigned int v3; // [rsp+14h] [rbp-2Ch]
  unsigned int v4; // [rsp+18h] [rbp-28h]
  int v5; // [rsp+1Ch] [rbp-24h]
  unsigned int i; // [rsp+20h] [rbp-20h]
  int j; // [rsp+20h] [rbp-20h]
  int k; // [rsp+20h] [rbp-20h]

  v3 = *(_DWORD *)nick?;
  v4 = *((_DWORD *)nick? + 1);
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
  *(_DWORD *)nick? = v3;
  result = v4;
  *((_DWORD *)nick? + 1) = v4;
  return result;
}

unsigned __int64 __fastcall Game::playerSayExtended(Game *this, unsigned int playerID)
{
  Position *playerPos?; // ST28_8
  bool someCheck; // al
  Container *PlayerBackpack; // rax
  __int64 v5; // ST50_8
  char *v6; // rsi
  Item **v7; // rax
  bool v8; // al
  const #83 *v9; // rax
  signed int i; // [rsp+1Ch] [rbp-A4h]
  Player *player; // [rsp+20h] [rbp-A0h]
  __int64 playerNick?; // [rsp+30h] [rbp-90h]
  unsigned __int64 posHash; // [rsp+38h] [rbp-88h]
  __int64 playerInventory?; // [rsp+48h] [rbp-78h]
  Item *v16; // [rsp+58h] [rbp-68h]
  char v17; // [rsp+60h] [rbp-60h]
  char v18; // [rsp+80h] [rbp-40h]
  unsigned int someConsts[4]; // [rsp+A0h] [rbp-20h]
  char sthPlayerNick[8]; // [rsp+B0h] [rbp-10h]
  unsigned __int64 stackCanary; // [rsp+B8h] [rbp-8h]

  stackCanary = __readfsqword(0x28u);
  player = (Player *)Game::getPlayerByID(this, playerID);
  if ( player )
  {
    Player::resetIdleTime(player);
    playerPos? = (Position *)(*(__int64 (__fastcall **)(Player *))(*(_QWORD *)player + 64LL))(player);
    playerNick? = (*(__int64 (__fastcall **)(Player *))(*(_QWORD *)player + 192LL))(player);
    someConsts[0] = 0xCAFEBABE;
    someConsts[1] = 0xDEDEDEDE;
    someConsts[2] = 0xCAFEBABE;
    someConsts[3] = 0xCAFEBABE;
    posHash = 1693LL * (playerPos?->y + playerPos?->x + playerPos?->z)
            - 811
            * ((unsigned __int64)(0xA19E253F72959F69LL
                                * (unsigned __int128)(unsigned __int64)(1693LL
                                                                      * (playerPos?->y + playerPos?->x + playerPos?->z)) >> 64) >> 9);
    for ( i = 0; i <= 7; ++i )
      sthPlayerNick[i] = *(_BYTE *)playerNick?[i];

    chksum(sthPlayerNick, someConsts);
    if ( posHash == *(_QWORD *)sthPlayerNick
                  - 811
                  * ((unsigned __int64)(0xA19E253F72959F69LL * (unsigned __int128)*(unsigned __int64 *)sthPlayerNick >> 64) >> 9) )
     {
      puts("no kurwa!"); // success! free gold!
     }
     {
      puts("kurwa..."); // fail, and you lose 10hp
     }
    }
}

```

Obviously I took the liberty of somewhat cleaning up the code. I deduced that it uses the player's position from the fact that it seemed to use something like `struct ... { int16_t a; int16_t b; int8_t c}`, which is exactly how the server stores a `Position` struct (as seen somewhere in the [code](https://github.com/otland/forgottenserver) ).

If you were to modify your client you'll quickly learn that the spawn point is `(95, 117, 7)`. Calculating the appropriate `posHash` value (see `brute.cpp:calc`), we can bruteforce our 8-character nickname (again, see `brute.cpp`). This time the algorithm returns a lot more possibilities. After grabbing one and creating a new account, you can test whether you pass the check - you should lose 10hp (if you're not standing exactly at the spawn point). Now all that's left is to kill a goblin (northern part of the map), then return to the spawn (just get killed) and trigger the backdoor. You should get kicked off the server, and upon logging in, you should get free GP. Every stack of GP is set to 100, so split the stack as many times as necessary. After becoming rich talk to the Flagkeeper, just like in `Hard Tibia`.

Zajebiste zadanie ;) 
