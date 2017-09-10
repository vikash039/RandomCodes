/*
 *       Filename:  prof2.cpp
 *    Description:  user file
 */

#define BOARD_MAX_WIDTH		10
#define BOARD_MAX_HEIGHT	600

typedef struct{
	bool filled;
	bool is_hinder;
	union{
		int color;
		int life;
	}u;
}bcell;

typedef struct {
	int col;
	int color;
}blk_t;

bcell board[BOARD_MAX_HEIGHT][BOARD_MAX_WIDTH];
blk_t iblk[2];
bool blk_top;
int hinder_cnt;
int hinder_life;
int maxwidth;
int maxheight;
int maxheight_col;

void init(int width){
	for(int i=0;i<maxwidth;i++){
		for(int j=0;j<=maxheight;j++){
			board[j][i].filled = false;
			board[j][i].is_hinder = false;
			board[j][i].u.color = 0;
			board[j][i].u.life = 0;
		}
	}
	maxwidth = width;
	maxheight = -1;
	maxheight_col = -1;
}

void newblock(int *block){
	iblk[0].color = block[0];
	iblk[0].col = 1;
	iblk[1].color = block[1];
	iblk[1].col = 2;
	blk_top = 0;
}

void hinders(int count, int life){
	hinder_cnt = count;
	hinder_life = life;
}

void rotate(int angle){
	switch(angle){//1 - 90, 2 - 180, 3 - 270, 4 - 360
		case 1:{
			if(iblk[0].col == iblk[1].col){//vertically placed
				iblk[1].col += (blk_top == 0 ? -1 : 1);
				if(iblk[1].col < 0){//out of bound of left hand
					iblk[1].col = 0;
					iblk[0].col = 1;
				}
				else if(iblk[1].col >= maxwidth){//out of bound on right hand
					iblk[1].col = maxwidth-1;
					iblk[0].col = maxwidth-2;
				}
			}
			/*else if(iblk[0].col > iblk[1].col){//previous rotation of 180
				iblk[1].col = iblk[0].col;
				blk_top = 1;
			}*/
			else{
				blk_top = (iblk[0].col > iblk[1].col ? 1 : 0);
				iblk[1].col = iblk[0].col;
			}
			break;
		}
		case 2:{
			if(iblk[0].col == iblk[1].col){//vertically placed
				blk_top = !(blk_top);
			}/*
			else if(iblk[0].col > iblk[1].col){//previous rotation of 180
				
			}*/
			else{
				iblk[1].col += (iblk[0].col < iblk[1].col ? -2 : 2);
				if(iblk[1].col < 0){//out of bound on left hand
					iblk[1].col = 0;
					iblk[0].col = 1;
				}
				else if(iblk[1].col >= maxwidth){//out of bound on right hand
					iblk[1].col = maxwidth-1;
					iblk[0].col = maxwidth-2;
				}
			}
			break;
		}
		case 3:{
			if(iblk[0].col == iblk[1].col){//vertically placed
				iblk[1].col += (blk_top == 0 ? 1 : -1);
				if(iblk[1].col < 0){//out of bound of left hand
					iblk[1].col = 0;
					iblk[0].col = 1;
				}
				else if(iblk[1].col >= maxwidth){//out of bound on right hand
					iblk[1].col = maxwidth-1;
					iblk[0].col = maxwidth-2;
				}
			}
			/*else if(iblk[0].col > iblk[1].col){//previous rotation of 180
				iblk[1].col = iblk[0].col;
				blk_top = 0;
			}*/
			else{
				blk_top = (iblk[0].col < iblk[1].col ? 1 : 0);
				iblk[1].col = iblk[0].col;
			}
			break;
		}
		case 4:
			/* DO NOTHING */
		default:
			break;
	}
}

void move(int distance){
	iblk[0].col += distance;
	iblk[1].col += distance;
	if(iblk[0].col < 0 || iblk[1].col < 0){//out of bound on left hand
		if(iblk[0].col == iblk[1].col){
			iblk[0].col = iblk[1].col = 0;
		}
		else if(iblk[0].col > iblk[1].col){
			iblk[1].col = 0;
			iblk[0].col = 1;
		}
		else{
			iblk[1].col = 1;
			iblk[0].col = 0;
		}
	}
	else if(iblk[0].col >= maxwidth || iblk[1].col >= maxwidth){//out of bound on right hand
		if(iblk[0].col == iblk[1].col){
			iblk[0].col = iblk[1].col = maxwidth-1;
		}
		else if(iblk[0].col > iblk[1].col){
			iblk[1].col = maxwidth-2;
			iblk[0].col = maxwidth-1;
		}
		else{
			iblk[1].col = maxwidth-1;
			iblk[0].col = maxwidth-2;
		}
	}
}

#define MAXQ	50
typedef struct{
	int r;
	int c;
}q_t;

bool run_bfs(int r, int c, int color){
	q_t q[MAXQ] = {0,0};
	int fnt = -1, rnr = 0;
	bool visited[BOARD_MAX_HEIGHT][BOARD_MAX_WIDTH] = {false};
	fnt++;
	q[fnt].r = r;
	q[fnt].c = c;
	visited[r][c] = true;
	while(fnt >= rnr){
		q_t tmp = q[rnr++];
		if(tmp.r-1 >= 0 && !visited[tmp.r-1][tmp.c] && board[tmp.r-1][tmp.c].filled && !board[tmp.r-1][tmp.c].is_hinder && board[tmp.r-1][tmp.c].u.color == color){
			fnt++;
			q[fnt].r = tmp.r-1;
			q[fnt].c = tmp.c;
			visited[tmp.r-1][tmp.c] = true;
		}
		if(tmp.c-1 >= 0 && !visited[tmp.r][tmp.c-1] && board[tmp.r][tmp.c-1].filled && !board[tmp.r][tmp.c-1].is_hinder && board[tmp.r][tmp.c-1].u.color == color){
			fnt++;
			q[fnt].r = tmp.r;
			q[fnt].c = tmp.c-1;
			visited[tmp.r][tmp.c-1] = true;
		}
		if(tmp.r+1 < BOARD_MAX_HEIGHT && !visited[tmp.r+1][tmp.c] && board[tmp.r+1][tmp.c].filled && !board[tmp.r+1][tmp.c].is_hinder && board[tmp.r+1][tmp.c].u.color == color){
			fnt++;
			q[fnt].r = tmp.r+1;
			q[fnt].c = tmp.c;
			visited[tmp.r+1][tmp.c] = true;
		}
		if(tmp.c+1 < maxwidth && !visited[tmp.r][tmp.c+1] && board[tmp.r][tmp.c+1].filled && !board[tmp.r][tmp.c+1].is_hinder && board[tmp.r][tmp.c+1].u.color == color){
			fnt++;
			q[fnt].r = tmp.r;
			q[fnt].c = tmp.c+1;
			visited[tmp.r][tmp.c+1] = true;
		}
	}
	if(fnt >= 3){//4 or more adjacent block with same color
		bool visited2[BOARD_MAX_HEIGHT][BOARD_MAX_WIDTH] = {false};
		for(int i=0;i<=fnt;i++){
			q_t tmp = q[i];
			board[tmp.r][tmp.c].filled = false;
			if(tmp.r-1 >= 0 && !visited2[tmp.r-1][tmp.c] && board[tmp.r-1][tmp.c].is_hinder){
				visited2[tmp.r-1][tmp.c] = true;
				board[tmp.r-1][tmp.c].u.life -= 1;
				if(board[tmp.r-1][tmp.c].u.life == 0){
					board[tmp.r-1][tmp.c].filled = false;
					board[tmp.r-1][tmp.c].is_hinder = false;
				}
			}
			if(tmp.c-1 >= 0 && !visited2[tmp.r][tmp.c-1] && board[tmp.r][tmp.c-1].is_hinder){
				visited2[tmp.r][tmp.c-1] = true;
				board[tmp.r][tmp.c-1].u.life -= 1;
				if(board[tmp.r][tmp.c-1].u.life == 0){
					board[tmp.r][tmp.c-1].filled = false;
					board[tmp.r][tmp.c-1].is_hinder = false;
				}
			}
			if(tmp.r+1 < BOARD_MAX_HEIGHT  && !visited2[tmp.r+1][tmp.c] && board[tmp.r+1][tmp.c].is_hinder){
				visited2[tmp.r+1][tmp.c] = true;
				board[tmp.r+1][tmp.c].u.life -= 1;
				if(board[tmp.r+1][tmp.c].u.life == 0){
					board[tmp.r+1][tmp.c].filled = false;
					board[tmp.r+1][tmp.c].is_hinder = false;
				}
			}
			if(tmp.c+1 < maxwidth && !visited2[tmp.r][tmp.c+1] && board[tmp.r][tmp.c+1].is_hinder){
				visited2[tmp.r][tmp.c+1] = true;
				board[tmp.r][tmp.c+1].u.life -= 1;
				if(board[tmp.r][tmp.c+1].u.life == 0){
					board[tmp.r][tmp.c+1].filled = false;
					board[tmp.r][tmp.c+1].is_hinder = false;
				}
			}
		}
		return true;
	}
	return false;
}

int fill_empty_cells(int mrow){
	int row, frow;
	int tmp_mrow = -1;
	for(int col=0;col<maxwidth;col++){
		frow = 0;
		row = 0;
		while(row<=mrow){
			if(board[row][col].filled){
				if(frow != row){
					board[frow][col] = board[row][col];
					board[row][col].filled = false;
				}
				frow++;
				row++;
			}
			else{
				row++;
			}
		}
		if(tmp_mrow < frow - 1){
			tmp_mrow = frow - 1;
		}
	}
	return tmp_mrow;
}

void check_and_blow_block(int mrow){
	for(int col=0;col<maxwidth;col++){
		for(int row = mrow; row >= 0; row--){
			if(board[row][col].filled == true && board[row][col].is_hinder == false){//cell filled with block
				if(run_bfs(row, col, board[row][col].u.color)){
					mrow = fill_empty_cells(mrow);
					if(mrow != -1){
						check_and_blow_block(mrow);
					}
					return;
				}
			}
		}
	}
}

void cal_max_height(void){
	int tmp_maxht = -1;
	int tmp_max_col = -1;
	for(int col=0;col < maxwidth; col++){
		int row = 0;
		while(row < BOARD_MAX_HEIGHT && board[row][col].filled){
			row++;
		}
		if(tmp_maxht < row){
			tmp_maxht = row;
			tmp_max_col = col;
		}
	}
	maxheight = tmp_maxht;
	maxheight_col = tmp_max_col;
}

int land(void){
	if(hinder_cnt > 0){//land hinders
		for(int col=0;col<hinder_cnt && col<maxwidth; col++){
			for(int row = 0;row < BOARD_MAX_HEIGHT; row++){
				if(board[row][col].filled == false){//empty cell
					board[row][col].filled = true;
					board[row][col].is_hinder = true;
					board[row][col].u.life = hinder_life;
					break;
				}
			}
			if(col == maxheight_col){
				maxheight++;
			}
		}
		hinder_cnt = 0;
	}
	else{//land block
		int mrow = -1;
		if(iblk[0].col == iblk[1].col){//vertically placed
			int col = iblk[0].col;
			for(int row = 0;row < BOARD_MAX_HEIGHT; row++){
				if(board[row][col].filled == false){//empty cell
					board[row][col].filled = true;
					board[row][col].is_hinder = false;
					board[row][col].u.color = (blk_top == 0 ? iblk[1].color : iblk[0].color);
					++row;//fill next cell also
					board[row][col].filled = true;
					board[row][col].is_hinder = false;
					board[row][col].u.color = (blk_top == 0 ? iblk[0].color : iblk[1].color);
					mrow = row;
					break;
				}
			}
		}
		else{//horizontally placed
			int col0 = iblk[0].col;
			int col1 = iblk[1].col;
			int row = 0;
			for(;row < BOARD_MAX_HEIGHT; row++){
				if(col0 >= 0 && board[row][col0].filled == false){//empty cell
					board[row][col0].filled = true;
					board[row][col0].is_hinder = false;
					board[row][col0].u.color = iblk[0].color;
					col0 = -1;
				}
				if(col1 >= 0 & board[row][col1].filled == false){//empty cell
					board[row][col1].filled = true;
					board[row][col1].is_hinder = false;
					board[row][col1].u.color = iblk[1].color;
					col1 = -1;
				}
				if(col0 < 0 && col1 < 0){
					break;
				}
			}
			mrow = row;
		}
		check_and_blow_block((mrow >= maxheight) ? mrow : maxheight);
		cal_max_height();
	}
	return maxheight;
}
