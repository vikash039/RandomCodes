/*
 *       Filename:  MinesSweeper.c
 *    Description:  Minesweeper
 */

#include <stdio.h>

#define MAX 301

int N;
char board[MAX][MAX];
int mines, moves, visited_c;

int count_mines(int x, int y){
	int count = 0;
	//North-West
	if(x-1 >= 0 && y-1 >= 0 && board[x-1][y-1] == '*')
		count++;
	//North
	if(x-1 >= 0 && board[x-1][y] == '*')
		count++;
	//North-East
	if(x-1 >= 0 && y+1 < N && board[x-1][y+1] == '*')
		count++;
	//East
	if(y+1 < N && board[x][y+1] == '*')
		count++;
	//South-East
	if(x+1 < N && y+1 < N && board[x+1][y+1] == '*')
		count++;
	//South
	if(x+1 < N && board[x+1][y] == '*')
		count++;
	//South-West
	if(x+1 < N && y-1 >= 0 && board[x+1][y-1] == '*')
		count++;
	//West
	if(y-1 >= 0 && board[x][y-1] == '*')
		count++;
	return count;
}

void blast_cells(int x, int y, int visited[][MAX]){
	//North-West
	if(x-1 >= 0 && y-1 >= 0 && !visited[x-1][y-1]){
		visited[x-1][y-1] = 1;
		visited_c++;
		if(count_mines(x-1, y-1) == 0)
			blast_cells(x-1, y-1, visited);
	}
	//North
	if(x-1 >= 0 && !visited[x-1][y]){
		visited[x-1][y] = 1;
		visited_c++;
		if(count_mines(x-1, y) == 0)
			blast_cells(x-1, y, visited);
	}
	//North-East
	if(x-1 >= 0 && y+1 < N && !visited[x-1][y+1]){
		visited[x-1][y+1] = 1;
		visited_c++;
		if(count_mines(x-1, y+1) == 0)
			blast_cells(x-1, y+1, visited);
	}
	//East
	if(y+1 < N && !visited[x][y+1]){
		visited[x][y+1] = 1;
		visited_c++;
		if(count_mines(x, y+1) == 0)
			blast_cells(x, y+1, visited);
	}
	//South-East
	if(x+1 < N && y+1 < N && !visited[x+1][y+1]){
		visited[x+1][y+1] = 1;
		visited_c++;
		if(count_mines(x+1, y+1) == 0)
			blast_cells(x+1, y+1, visited);
	}
	//South
	if(x+1 < N && !visited[x+1][y]){
		visited[x+1][y] = 1;
		visited_c++;
		if(count_mines(x+1, y) == 0)
			blast_cells(x+1, y, visited);
	}
	//South-West
	if(x+1 < N && y-1 >= 0 && !visited[x+1][y-1]){
		visited[x+1][y-1] = 1;
		visited_c++;
		if(count_mines(x+1, y-1) == 0)
			blast_cells(x+1, y-1, visited);
	}
	//West
	if(y-1 >= 0 && !visited[x][y-1]){
		visited[x][y-1] = 1;
		visited_c++;
		if(count_mines(x, y-1) == 0)
			blast_cells(x, y-1, visited);
	}
}

void solve_game(void){
	int i, j;
	int visited[MAX][MAX] = {0};
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(board[i][j] != '*' && !visited[i][j] && count_mines(i, j) == 0){
				visited_c++;
				moves++;
				visited[i][j] = 1;
				blast_cells(i, j, visited);
			}
		}
	}
}

int main()
{
	int tc, T, i, j;
	scanf("%d", &T);
	for(tc=1;tc<=T;tc++){
		mines = moves = visited_c = 0;
		scanf("%d", &N);
		for(i=0;i<N;i++){
			scanf("%s", board[i]);
			for(j=0;j<N;j++)
				if(board[i][j] == '*')
					mines++;
		}
		solve_game();
		moves += (N*N - visited_c - mines);
		printf("Case #%d: %d\n", tc, moves);
	}
	return 0;
}
