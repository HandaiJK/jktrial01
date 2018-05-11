#include <stdio.h>
/*
int lifegame(int, int, int [],int);
int answer(int, int, char [][]);
int checkfield(int, int, char[][]);
*/
int main(){
	const int w = 10;
	const int h = 10;
	int input[] = {11,22,3,13,23};
	int input_length = 5;
	lifegame(w, h, input, input_length);
	
	return 0;
}

int lifegame(int w, int h, int input[], int input_length){
	char field[w][h], cfield[w][h], pfield[w+2][h+2];
	int count=0, judge=0;
	//	initialize
	for (int j=0; j<h; j++){
		for(int i=0; i<w; i++){
			field[i][j] = '-';
			}
	}
	for (int i=0; i<input_length; i++){
		field[input[i]/10][input[i]%10] = '*';
	}
	answer(w, h, field);

	printf("How many times do you chenge the situation accoding to the Life Game role?\n");
	scanf("%d",&count);

	for (int k=0; k<count; k++){
		//	padding field
		for (int j=0; j<h+2; j++){
			for(int i=0; i<w+2; i++){
				pfield[i][j] = '-';
				}
		}
		for (int j=0; j<h; j++){
			for(int i=0; i<w; i++){
				pfield[i+1][j+1] = field[i][j];
			}
		}

		for (int j=0; j<h; j++){
			for (int i=0; i<w; i++){
			 judge = checkfield(i+1, j+1, h,  pfield);
				if (judge < 2 || judge > 3 ){
					cfield[i][j] = '-';
				}
				else if (judge == 2 ){
					cfield[i][j] = field[i][j];
				}
				else	cfield[i][j] = '*';
			}
		}

		for (int j=0; j<h; j++){	//copy field <- cfield
			for(int i=0; i<w; i++){
				field[i][j] = cfield[i][j];
			}
		}

		answer(w, h, field);
	}
return 0;
}

int checkfield(int x, int y, int h, char pfield[][h+2]){
	int ans=0;
	for (int j=-1; j<=1; j++){
		for(int i=-1; i<=1; i++){
			if(pfield[x+i][y+j] == '*'){
				ans++;
			}
		}
	}
	if(pfield[x][y] == '*') ans--; 
	return ans;
}

int answer(int w, int h, char field[w][h]){
	for (int j=0; j<h; j++){
		for(int i=0; i<w; i++){
			printf("%c",field[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

