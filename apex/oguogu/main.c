#include<stdio.h>

int w = 10;
int h = 10;
int living_cells[10][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0},
	{0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0}
};
int living_cells_count = 5;

void next_generation ()
{
	int i, j, k;
	int next_cell[10][10];
	int living_count = 0;
	int around_i, around_j;
	// 全てのセルを走査
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			// セルの周囲から生きてるセルを探す
			for (k = 0; k < 9; k++)
			{
				// 走査に必要な添字の生成
				around_i = i + k % 3 - 1;
				around_j = j + k / 3 - 1;
				// 存在しないのは除外
				if (around_i < 0 || around_i >= h) continue;
				if (around_j < 0 || around_j >= w) continue;
				// 自分自身も除外
				if (around_i == i && around_j == j) continue;
				// 生きている周囲の数を数える
				if (living_cells[around_i][around_j] != 0) living_count++;
			}
			// 生死の判定
			if (living_count <= 1 || 3 < living_count)
			{
				next_cell[i][j] = 0;//過密と過疎で死
			}
			else if (living_count == 3)
			{
				next_cell[i][j] = 1;//いい感じの環境で生
			}
			else
			{
				next_cell[i][j] = living_cells[i][j];//そのまま
			}
			living_count = 0;
		}
	}
	// 出力
	printf("Generation!----------\n");
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			living_cells[i][j] = next_cell[i][j];
			printf ("%d,",living_cells[i][j]);
		}
		printf("\n");
	}
	return;
}

int main()
{
	int generation_count = 0;
	// 世代を進める
	while (generation_count < 10)
	{
    	next_generation ();
    	generation_count++;
    }
    return 0;
} 