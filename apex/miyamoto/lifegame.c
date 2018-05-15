#include <stdio.h>
#include <stdbool.h>

/*********************** Option **************************/

enum { COUNT_OF_ADV_GEN = 12 };

/*********************************************************/

typedef enum
{
	DEAD  = 0,
	ALIVE = 1
} CellState;

// 盤面は1次元配列で保持
typedef       CellState*const Field;
typedef const CellState*const cField;


static int width;  // immutable after initialization
static int height; // immutable after initialization


/*********************************************************/
/******************** Board Primitive ********************/
/*********************************************************/

static bool isInField(const int x, const int y)
{
	return x >= 0 && x < width && y >= 0 && y < height;
}


static void setCellState(Field field, const int x, const int y, const CellState state)
{
	if (isInField(x, y))
	{
		field[y * width + x] = state;
	}
}


static CellState getCellState(cField field, const int x, const int y)
{
	return isInField(x, y)? field[y * width + x]: DEAD;
}


static void toggleCellState(Field field, const int x, const int y)
{
	if (isInField(x, y))
	{
		setCellState(field, x, y, !getCellState(field, x, y));
	}
}


static void initializeField(Field field, const int ini_alive[], const int len)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			setCellState(field, x, y, DEAD);
		}
	}

	for (int i = 0; i < len; ++i)
	{
		const int p = ini_alive[i];
		setCellState(field, p / 10, p % 10, ALIVE);
	}
}

/*********************************************************/
/****************** Advance of Generation ****************/
/*********************************************************/

// 座標(x,y)の周りの8個のセルで生きているものを数える
static int countLiveCells(cField field, const int x, const int y)
{
	static const int pos[8][2] = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{ 0, -1},          { 0, 1},
		{ 1, -1}, { 1, 0}, { 1, 1}
	};
	int cnt = 0;
	for (int i = 0; i < 8; ++i)
	{
		if(getCellState(field, x + pos[i][0], y + pos[i][1]))
		{
			++cnt;
		}
	}
	return cnt;
}

// 座標(x,y)のセルの生死が，次の世代で反転するか否か
static bool isCellToToggle(cField field, const int x, const int y)
{
	const int live_count = countLiveCells(field, x, y);

	if (getCellState(field, x, y))
	{
		return live_count != 2 && live_count != 3;
	}
	else
	{
		return live_count == 3;
	}
}


static void copyField(Field to, cField from)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			setCellState(to, x, y, getCellState(from, x, y));
		}
	}
}


static void advanceGeneration(Field field)
{
	CellState old_field[height * width];
	copyField(old_field, field);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (isCellToToggle(old_field, x, y))
			{
				toggleCellState(field, x, y);
			}
		}
	}
}

/*********************************************************/
/************************ Output *************************/
/*********************************************************/

// 盤面出力
static void printField(cField field)
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			printf(getCellState(field, x, y) ? "* " : "- ");
		}
		puts("");
	}
	puts("");
}


/*********************************************************/

void lifegame(int w, int h, int input[], int input_length)
{
	CellState field[h * w];
	width = w;
	height = h;
	initializeField(field, input, input_length);

	for (int i = 0; i < COUNT_OF_ADV_GEN; ++i)
	{
		advanceGeneration(field);
	}
	printField(field);
}


int main(void)
{
    /// 入力として与えるもの
    /// 盤面の横幅 (col)
    /// 盤面の縦幅 (row)
    /// 盤面の初期状態
    ///   -> ライフが存在するセルの番地を表す数値の配列
    ///   -> 番地の表し方 (2, 3) => 23, (0, 2) => 2
    const int w = 10;
    const int h = 10;
    int input[] = {11, 22, 3, 13, 23};
    int input_length = 5;

    /// lifegame関数を作成し、この位置で呼び出すこと。
    lifegame(w, h, input, input_length);

    return 0;
}



