#include "stdio.h"
#include "defs.h"

void resetBoard(S_BOARD *pos)
{
    for (size_t i = 0; i < BRD_SQ_NUM; ++i)
    {
        pos->pieces[i] = OFFBOARD;
    }

    for (size_t i = 0; i < 64; ++i)
    {
        pos->pieces[SQ120(i)] = EMPTY;
    }

    for (size_t i = 0; i < 3; ++i)
    {
        pos->bigPiece[i] = 0;
        pos->majorPiece[i] = 0;
        pos->minorPiece[i] = 0;
        pos->pawns[i] = 0ULL;
    }

    for (size_t i = 0; i < 13; ++i)
    {
        pos->piecesNum[i] = 0;
    }

    pos->kingSq[WHITE] = pos->kingSq[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->enPas = NO_SQ;
    pos->fiftyMove = 0;

    pos->ply = 0;
    pos->historyPly = 0;

    pos->castlePerm = 0;

    pos->posKey = 0ULL;
}

int parseFEN(char *fen, S_BOARD *pos)
{
    ASSERT(fen != NULL);
    ASSERT(pos != NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int piece = 0;
    int countEmptySq = 0;
    int sq64 = 0;
    int sq120 = 0;

    resetBoard(pos);

    while ((rank >= RANK_1) && *fen)
    {
        countEmptySq = 1;

        switch (*fen)
        {
        case 'p':
            piece = bPawn;
            break;
        case 'r':
            piece = bRook;
            break;
        case 'n':
            piece = bNight;
            break;
        case 'b':
            piece = bBishop;
            break;
        case 'k':
            piece = bKing;
            break;
        case 'q':
            piece = bQueen;
            break;
        case 'P':
            piece = bPawn;
            break;
        case 'R':
            piece = wRook;
            break;
        case 'N':
            piece = wNight;
            break;
        case 'B':
            piece = wBishop;
            break;
        case 'K':
            piece = wKing;
            break;
        case 'Q':
            piece = wQueen;
            break;
        
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            piece = EMPTY;
            countEmptySq = *fen - '0';
            break;
        
        case '/':
        case ' ':
            rank--;
            file = FILE_A;
            fen++;
            continue;

        default:
            printf("FEN error \n");
            return -1;
        }

        // Counting empty squarce and setting a figure where needed via FEN
        for (size_t i = 0; i < countEmptySq; ++i)
        {
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);
            if (piece != EMPTY)
            {
                pos->pieces[sq120] = piece;
            }
            file++;
        }
        fen++;
    }
    
}