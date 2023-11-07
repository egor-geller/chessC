#include "stdio.h"
#include "defs.h"

const int bitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8};

int popBit(U64 *bitBoard)
{
    U64 b = *bitBoard ^ (*bitBoard - 1);
    unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
    *bitBoard &= (*bitBoard - 1);
    return bitTable[(fold * 0x783a9b23) >> 26];
}

int countBits(U64 bits)
{
    int i;
    for (i = 0; bits; i++, bits &= bits - 1);
    return i;
}

void printBitBoard(U64 bitBoard)
{
    U64 shiftMe = 1ULL;

    int rank = 0;
    int file = 0;
    int sq = 0;
    int sq64 = 0;

    printf("\n");

    for (rank = RANK_8; rank >= RANK_1; --rank)
    {
        for (file = FILE_A; file <= FILE_H; ++file)
        {
            sq = FR2SQ(file, rank); // 120 based index
            sq64 = SQ64(sq);        // 64 based index

            if ((shiftMe << sq64) & bitBoard)
            {
                printf("X");
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}