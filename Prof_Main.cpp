/*
 *       Filename:  prof1.cpp
 *    Description:  main file
 */

#include <stdio.h>

#define BOARD_MAX_WIDTH 10
#define HINDERS		9
#define ROTATE		100
#define MOVE		200

/* externs */
extern void init(int width);
extern void newblock(int *blocks);
extern void hinders(int count, int life);
extern void rotate(int angle);
extern void move(int distance);
extern int land(void);

int width, blk_cnt, answer;
int block[2];
int score, totalscore;

int main()
{
	int tc;
	int cmds, cmd_type, option, result;

	scanf("%d", &tc);
	totalscore = 0;

	for(int t=1;t<=tc;t++){
		score = 100;
		scanf("%d %d", &width, &blk_cnt);
		init(width);

		for(int i=0;i<blk_cnt;i++){
			scanf("%d %d", &block[0], &block[1]);
			if(block[0] == HINDERS){
				int life;
				scanf("%d", &life);
				hinders(block[1], life);
			}
			else{
				newblock(block);

				scanf("%d", &cmds);
				for(int j=0;j<cmds;j++){
					scanf("%d %d", &cmd_type, &option);
					switch(cmd_type){
						case ROTATE:
							rotate(option);
							break;
						case MOVE:
							move(option);
							break;
						default:
							printf("invalid cmd_type\n");
							break;
					}
				}
			}
			scanf("%d", &answer);
			result = land();
			printf("result [%d] answer [%d]\n", result, answer);
			if(result != answer){
				score = 0;
			}
		}
		printf("#%d %d\n", t, score);
		totalscore += score;
	}
	printf("totalscore: %d\n", totalscore/tc);
	return 0;
}
