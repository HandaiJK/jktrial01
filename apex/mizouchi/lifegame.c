#include<stdio.h>
#include<stdbool.h>

//board_aの情報をboard_bにコピー
void copy_board(int w, int h, bool board_a[w][h], bool board_b[w][h]){
	int i, j;
	
	for(i = 0; i < h; i++){
		for(j = 0; j < w; j++){
			board_b[j][i] = board_a[j][i];
		}
	}
}

//盤面を標準出力に表示
void print_board(int w, int h, bool current_board[w][h]){
	int i, j;
	
	for(i = 0; i < h; i++){
		for(j = 0; j < w; j++){
			if(current_board[j][i]){
				printf("* ");
			}else{
				printf("- ");
			}
			if(j == (w - 1)) printf("\n");
		}
	}
}

//セルの周囲8マスを探索し，生きているセルの数を返す
int search(int w, int h, bool current_board[w][h],int  x,int  y){
	int num_of_alive = 0;
	int i, j;
	
	for(i = (y - 1); i <= (y + 1); i++){
		for(j = (x - 1); j <= (x + 1); j++){
			if(i == y && j == x) continue;	//中心のセルは無視
			if(j >= 0 && i >= 0 && j < w && i < h)	//磐面の外も無視
				if(current_board[j][i]) ++num_of_alive;
		}
	}
	
	return num_of_alive;
}

//盤面を1世代進める
void next(int w, int h, bool current_board[w][h], bool shadow_board[w][h]){
	int i, j;
	
	copy_board(w, h, current_board, shadow_board);
	
	
	for(i = 0; i < h; i++){
		for(j = 0; j < w; j++){
			if(current_board[j][i]){	//生きているセルの周囲に，2つまたは3つの生きているセルがあればそのセルは生存
				if(search(w, h, current_board, j, i) <= 1 || search(w, h, current_board, j, i) >= 4) shadow_board[j][i] = false;
			}else{	//死んでいるセルの周囲に，3つの生きているセルがあれば生きているセルが誕生
				if(search(w, h, current_board, j, i) == 3) shadow_board[j][i] = true;
			}
		}
	}
	
	copy_board(w, h, shadow_board, current_board);

}

void lifegame(int w,int h, int *input, int input_length){
	bool current_board[w][h];
	bool shadow_board[w][h];
	int i,j;
	
	//盤面のセルをすべて死んでいる状態で初期化
	for(i = 0; i < h; i++){
		for(j = 0; j < w; j++){
			current_board[j][i] = false;
		}
	}
	
	//inputの情報をもとに第1世代で生きているセルを設定
	for(i = 0; i < input_length; i++){
		current_board[input[i] / 10][input[i] % 10] = true;
	}
	
	//盤面を12世代進める
	for(i = 0; i < 12; i++){
		next(w, h, current_board, shadow_board);
	}
	
	//盤面を表示
	print_board(w, h, current_board);
}


int main()
{
	const int w = 10;	//盤面の横幅
	const int h = 10;	//盤面の縦幅
	int input[] = {11, 22, 3, 13, 23};	//第1世代で生存しているセルの座標(x,y)を10x+yの形で表したもの
	int input_length = 5;	//input[]の要素数
	
	lifegame(w, h, input, input_length);
	
	return 0;

}