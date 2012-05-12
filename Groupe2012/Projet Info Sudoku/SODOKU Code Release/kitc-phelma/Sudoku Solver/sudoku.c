/* Program to solve Su Doko puzzles. */
#include "stdrusty.h"
#include <assert.h>
#include <stdio.h>


static int initial_puzzle[9][9] =
{ { 0, 1, 9, 2, 0, 0, 5, 0, 0, },
  { 7, 0, 0, 0, 8, 0, 3, 0, 0, },
  { 0, 4, 0, 5, 0, 0, 0, 0, 0, },
  { 3, 0, 0, 0, 0, 0, 0, 0, 0, },
  { 0, 2, 0, 1, 0, 7, 0, 8, 0, },
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, },
  { 0, 0, 0, 0, 0, 4, 0, 5, 0, },
  { 0, 0, 5, 0, 1, 0, 0, 0, 6, },
  { 0, 0, 2, 0, 0, 6, 7, 9, 0, },
};

#define FINISHED (1 << 15)

static inline unsigned int hweight16(unsigned int w)
{
        unsigned int res = (w & 0x5555) + ((w >> 1) & 0x5555);
        res = (res & 0x3333) + ((res >> 2) & 0x3333);
        res = (res & 0x0F0F) + ((res >> 4) & 0x0F0F);
        return (res & 0x00FF) + ((res >> 8) & 0x00FF);
}

static unsigned row(u16 puzzle[9][9], unsigned int x, unsigned int y,
		    u16 *value,
		    bool (*fn)(u16 p[9][9], unsigned int, unsigned int, u16 *))
{
	unsigned int i, total = 0;

	for (i = 0; i < 9; i++)
		if (i != x && !(puzzle[y][i] & FINISHED))
			total += fn(puzzle, i, y, value);
	return total;
}

static unsigned column(u16 puzzle[9][9], unsigned int x, unsigned int y,
		       u16 *value,
		       bool (*fn)(u16 p[9][9], unsigned, unsigned, u16 *))
{
	unsigned int i, total = 0;

	for (i = 0; i < 9; i++)
		if (i != y && !(puzzle[i][x] & FINISHED))
			total += fn(puzzle, x, i, value);
	return total;
}

static unsigned box(u16 puzzle[9][9], unsigned int x, unsigned int y,
		    u16 *value,
		    bool (*fn)(u16 p[9][9], unsigned int, unsigned int, u16 *))
{
	unsigned int ix, iy, total = 0;

	/* Integer division gives us the 3x3 box we're in. */
	for (ix = x / 3 * 3; ix < x / 3 * 3 + 3; ix++) {
		for (iy = y / 3 * 3; iy < y / 3 * 3 + 3; iy++) {
			if (puzzle[iy][ix] & FINISHED)
				continue;
			if (ix == x && iy == y)
				continue;
			total += fn(puzzle, ix, iy, value);
		}
	}
	return total;
}

static void eliminate(u16 puzzle[9][9], unsigned int x, unsigned int y);

static bool reduce(u16 puzzle[9][9], unsigned int x, unsigned int y, u16 *val)
{
	puzzle[y][x] &= ~*val;
	assert(puzzle[y][x] != 0);

	if (hweight16(puzzle[y][x]) == 1) {
		printf("Solved %ix%i = %i\n", x+1, y+1, ffs(puzzle[y][x]));
		eliminate(puzzle, x, y);
		return true;
	}
	return false;
}

static void eliminate(u16 puzzle[9][9], unsigned int x, unsigned int y)
{
	assert(puzzle[y][x] != 0);
	puzzle[y][x] |= FINISHED;

	row(puzzle, x, y, &puzzle[y][x], reduce);
	column(puzzle, x, y, &puzzle[y][x], reduce);
	box(puzzle, x, y, &puzzle[y][x], reduce);
}

/* Take away the possibilities of this square. */
static bool cutdown(u16 puzzle[9][9], unsigned int x, unsigned int y, u16 *val)
{
	if (*val & puzzle[y][x]) {
		*val &= ~puzzle[y][x];
		return true;
	}
	return false;
}

void dump_val(u16 val)
{
	unsigned int i;

	for (i = 0; i < 9; i++)
		if (val & (1 << i))
			printf("%i", i+1);
		else
		{

		}
			//printf(" ");
}

int dump_val2(u16 val)
{
	unsigned int i;

	for (i = 0; i < 9; i++)
		if (val & (1 << i))
		{
            printf("%i", i+1);
			return i+1;
		}

		else
		{

		}
			//printf(" ");
}

static void dump(u16 puzzle[9][9])
{
    int grille [81];

    int i=0;
    int j=0;
    int compteur=0;
    for (i=0;i<81;i++)
    {
        grille[i]=0;
    }
    printf ("\n\n\n1\n\n");
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
            dump_val(puzzle[i][j]);
        }
    }
    printf ("\n\n\n2\n\n");

    // BIDOUILLAGE
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
            grille[j+9*i]= dump_val2(puzzle[i][j]);
        }
    }

    // FIN BIDOUILLAGe
    printf ("\n\n\nES CE QUE CA MARCHE?\n\n");


    for (i=0;i<81;i++)
    {
        printf("%d",grille[i]);
    }

    printf ("\n\n\nOUI OU NON\n\n");
    for(i=0;i<81;i++)
    {
        compteur++;
        printf("%d",grille[i]);
        if(compteur==9)
        {
            printf("\n");
            compteur=0;
        }
    }
    printf ("\n\n\n5\n\n");
	unsigned int x, y;

	for (y = 0; y < 9; y++) {
		if (y % 3 == 0)
			printf(" -----------------------------------------------------------------------------------------\n");
		for (x = 0; x < 9; x++) {
			if (x % 3 == 0)
				printf("|");
			else
				printf(".");
			dump_val(puzzle[y][x]);
		}
		printf("|\n");
	}
	printf(" -----------------------------------------------------------------------------------------\n");

}

/* If we have a possibility which no other square has, that's our value */
static bool try_cutdown(u16 puzzle[9][9], unsigned int x, unsigned int y)
{
	u16 val;

	val = puzzle[y][x];
	row(puzzle, x, y, &val, cutdown);
	if (val) {
		printf("Row eliminated %ix%i = %i\n",
		       x+1, y+1, ffs(val));
		goto elim;
	}

	val = puzzle[y][x];
	column(puzzle, x, y, &val, cutdown);
	if (val) {
		printf("Col eliminated %ix%i = %i\n",
		       x+1, y+1, ffs(val));
		goto elim;
	}

	val = puzzle[y][x];
	box(puzzle, x, y, &val, cutdown);
	if (val) {
		printf("Box eliminated %ix%i = %i\n",
		       x+1, y+1, ffs(val));
		goto elim;
	}
	return false;

elim:
	/* Can't have more than one answer. */
	assert(hweight16(val) == 1);
	puzzle[y][x] = val;
	eliminate(puzzle, x, y);
	return true;
}

static bool match(u16 puzzle[9][9], unsigned int x, unsigned int y, u16 *val)
{
	return (puzzle[y][x] == *val);
}

/* If not equal, remove these bits. */
static bool reduce_unequal(u16 puzzle[9][9], unsigned x, unsigned y, u16 *val)
{
	if (puzzle[y][x] == *val)
		return false;

	if (!(puzzle[y][x] & *val))
		return false;

	puzzle[y][x] &= ~*val;
	assert(puzzle[y][x] != 0);

	if (hweight16(puzzle[y][x]) == 1) {
		printf("Matches eliminated %ix%i = %i\n",
		       x+1, y+1, ffs(puzzle[y][x]));
		eliminate(puzzle, x, y);
	}
	return true;
}

/* If there are 2 identical pairs, nothing else can be that value.
 * Similarly 3 identical triplets. */
static bool try_matches(u16 puzzle[9][9], unsigned int x, unsigned int y)
{
	unsigned int matches;
	bool progress = false;

	matches = row(puzzle, x, y, &puzzle[y][x], match);
	if (matches+1 == hweight16(puzzle[y][x]))
		progress = row(puzzle, x, y, &puzzle[y][x], reduce_unequal);

	matches = column(puzzle, x, y, &puzzle[y][x], match);
	if (matches+1 == hweight16(puzzle[y][x]))
		progress = column(puzzle, x, y, &puzzle[y][x], reduce_unequal);

	matches = box(puzzle, x, y, &puzzle[y][x], match);
	if (matches+1 == hweight16(puzzle[y][x]))
		progress = box(puzzle, x, y, &puzzle[y][x], reduce_unequal);

	return progress;
}

int main()
{
	unsigned int x, y;
	bool progress;
	u16 puzzle[9][9];

	/* Blank puzzle. */
	for (x = 0; x < 9; x++)
		for (y = 0; y < 9; y++)
			puzzle[y][x] = (1 << 9) - 1;

	printf("Adding known numbers...\n");
	for (x = 0; x < 9; x++) {
		for (y = 0; y < 9; y++) {
			if (!initial_puzzle[y][x])
				continue;
			puzzle[y][x] = 1 << (initial_puzzle[y][x] - 1);
			printf("We know %ix%i = %i\n",
			       x+1, y+1, ffs(puzzle[y][x]));
			eliminate(puzzle, x, y);
		}
	}

	printf("Deriving new numbers...\n");
	do {
		progress = false;
		for (x = 0; x < 9; x++) {
			for (y = 0; y < 9; y++) {
				if (puzzle[y][x] & FINISHED)
					continue;
				progress |= try_cutdown(puzzle, x, y);
				progress |= try_matches(puzzle, x, y);
			}
		}
	} while(progress);
	dump(puzzle);

	return 0;
}
