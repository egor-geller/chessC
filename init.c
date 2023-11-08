#include "stdlib.h"
#include "defs.h"


/*
    How does the RAND_64 works

    Line 1: 0000 000000000000000 000000000000000 000000000000000 111111111111111
    Line 2: 0000 000000000000000 000000000000000 111111111111111 000000000000000
    Line 3: 0000 000000000000000 111111111111111 000000000000000 000000000000000
    Line 4: 0000 111111111111111 000000000000000 000000000000000 000000000000000
    Line 5: 1111 000000000000000 000000000000000 000000000000000 000000000000000
    Final: Sum up all numbers to create one unique/random 64 bit number
*/

#define RAND_64 ( \
    (U64)rand() + \
    (U64)rand() << 15 + \
    (U64)rand() << 30 + \
    (U64)rand() << 45 + \
    ((U64)rand() & 0xf) << 60 \
)

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 setMask[64];
U64 clearMask[64];

U64 pieceKeys[13][120];
U64 sideKey;
U64 castleKeys[16];

void initHashKeys()
{
    for(size_t i = 0; i < 13; ++i)
    {
        for(size_t j = 0; j < 120; ++j)
        {
            pieceKeys[i][j] = RAND_64;
        }
    }

    sideKey = RAND_64;
    
    for (size_t i = 0; i < 16; ++i)
    {
        castleKeys[i] = RAND_64;
    }
    
}

void initBitMasks()
{
    for(size_t i = 0; i < 64; i++)
    {
        setMask[i] = 0ULL;
        clearMask[i] = 0ULL;
    }

    for (size_t i = 0; i < 64; i++)
    {
        setMask[i] |= (1ULL << i);
        clearMask[i] = ~setMask[i];
    }
    
}

void initSq120To64()
{
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0; // representing the 64 numbers in the array (board)

    for (index = 0; index < BRD_SQ_NUM; ++index)
    {
        Sq120ToSq64[index] = 65; // safety check, value should never be return
    }

    for (index = 0; index < 64; ++index)
    {
        Sq64ToSq120[index] = 120; // safety check, value should never be return
    }

    for (rank = RANK_1; rank <= RANK_8; ++rank)
    {
        for (file = FILE_A; file <= FILE_H; ++file)
        {
            sq = FR2SQ(file, rank);
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
}

void allInit()
{
    initSq120To64();
    initBitMasks();
    initHashKeys();
}