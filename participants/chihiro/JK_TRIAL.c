#include <stdio.h>


void display(int cells[12][12])
{
	for(int i=1; i<11; i++){
		for(int j=1; j<11; j++){
			cells[i][j]==1 ? printf("* ") : printf("- ");
			/* 生きてるセルは"*"、死んでるセルは"-" */
		}
		printf("\n");
	}
	printf("\n");
}	

void lifegame(int w, int h, int living_cells[], int living_cells_count)
{
	int i, j;
	int cells[12][12]={0};
	
	for(int k=0; k<living_cells_count; k++){
		int a=living_cells[k];
		i=(a%10); j=(a/10);
		/* i行j列は、(living_cellsの1の位)行(living_cellsの10の位)列 */
		cells[i+1][j+1]=1;
		/* 余白を作ってる分、+1 */
	}	
	
	display(cells);
	
	for(int n=0; n<12; n++){
		int sum_around, next_cells[12][12];
		for(i=1; i<11; i++){
			for(j=1; j<11; j++){
				sum_around=0;
				sum_around=cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]
				           +cells[i][j-1]+cells[i][j+1]
				           +cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
				  
				if(cells[i][j]==1){
				/*　cells[i][j]を直接書き換えると、cells[i][j+1]などの計算に
				　　　変更後の値が使われるから、next_cellsを使う*/
					if(sum_around==2 || sum_around==3){
						next_cells[i][j]=1;
					}else{
						next_cells[i][j]=0;
					}
				}else{
					if(sum_around==3){
						next_cells[i][j]=1;
					}else{
						next_cells[i][j]=0;
					}
				}
			}
		}
		for(i=1; i<11; i++){
			for(j=1; j<11; j++){
				cells[i][j]=next_cells[i][j];
			}
		}
		display(cells);
	}

}

int main()
{
    int w = 10;
    int h = 10;
    int living_cells[] = {11, 22, 3, 13, 23};
    int living_cells_count = 5;

    lifegame(w, h, living_cells, living_cells_count);

    return 0;
}