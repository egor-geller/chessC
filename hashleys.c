#include "defs.h"

U64 generatePosKey(const S_BOARD *pos)
{
    U64 finaleKey = 0;
    int piece = 0;

    // Pieces
    for (size_t i = 0; i < BRD_SQ_NUM; ++i)
    {
        piece = pos->pieces[i];
        if (piece != NO_SQ && piece != EMPTY)
        {
            ASSERT(piece >= wPawn && piece <= bKing);
            finaleKey ^= pieceKeys[piece][i];
        }
    }

    if(pos->side == WHITE)
    {
        finaleKey ^= sideKey;
    }

    if (pos->enPas != NO_SQ)
    {
        ASSERT(pos->enPas >= 0 && pos->enPas < BRD_SQ_NUM);
        finaleKey ^= pieceKeys[EMPTY][pos->enPas];
    }
    
    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    finaleKey ^= castleKeys[pos->castlePerm];

    return finaleKey;
}