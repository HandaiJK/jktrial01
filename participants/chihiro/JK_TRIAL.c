#include <stdio.h>


void display(int cells[12][12])
{
	for(int i=1; i<11; i++){
		for(int j=1; j<11; j++){
			if(cells[i][j]==1){
				printf("* ");
			}else{
				printf("- ");
			}
		}
		printf("\n");
	}
	printf("\n");
}	

void lifegame(int w, int h,int living_cells[],int living_cells_count)
{
	int i,j;
	int cells[12][12]={
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
	};
	
	for(int k=0; k<living_cells_count; k++){
		int a=living_cells[k];
		i=(a%10); j=(a/10);
		cells[i+1][j+1]=1;
	}	
	
	display(cells);
	
	for(int n=0;n<12;n++){
		int l,next_cells[12][12];
		for(i=1; i<11; i++){
			for(j=1; j<11; j++){
				l=0;
				l=cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]
				  +cells[i][j-1]+cells[i][j+1]
				  +cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
				if(cells[i][j]==1){
					if(l==2||l==3){
						next_cells[i][j]=1;
					}else{
						next_cells[i][j]=0;
					}
				}else{
					if(l==3){
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