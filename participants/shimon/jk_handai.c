#include<stdio.h>
// lifegame関数
void lifegame(int w , int h , int living_cells[] , int living_cells_count)
{
	printf("life game\n");
	
	 int cells[12][12] = {} ;
		
	
	//初期の状態　出力
	
	int i , j ;
	
	for(int n = 0 ; n < living_cells_count ; n++ ){
		int a = living_cells[n];
		j = a /10;
		i = a %10;
		cells[ i ][ j ] = 1;
		}
	for( i = 0 ; i < 10 ; i++){
		for( j = 0 ; j <10 ; j++){
			printf("%c",(cells[ i ][ j ] == 1)?'*':'-');
		}
		printf("\n");
	}
	printf("\n");
	
	//世代を進める
	int around_living_cells_count = 0;
	int next_cells[12][12];
	for( i = 1 ; i < 11 ; i++){
		for( j = 1 ; j < 11 ; j++){
			around_living_cells_count = cells[i-1][j-1]+cells[i-1][j]+cells[i-1][j+1]+cells[i][j-1]+cells[i][j+1]+cells[i+1][j-1]+cells[i+1][j]+cells[i+1][j+1];
			
			if(around_living_cells_count ==3){
				next_cells[i][j] = 1;
				}else if(around_living_cells_count == 2){
					next_cells[i][j] = cells[i][j];
					}else{
					next_cells[i][j] = 0;
					}
		}
	}
	//次世代　出力
	for( i = 0 ; i < 10 ; i++){
		for( j = 0 ; j <10 ; j++){
			printf("%c",(next_cells[ i ][ j ] == 1)?'*':'-');
		}
		printf("\n");
	}
	printf("\n");	
	
	
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
