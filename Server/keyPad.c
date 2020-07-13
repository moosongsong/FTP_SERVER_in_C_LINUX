#include "keyPad.h"
int freeColor(WINDOW* win[]){
	if(win==NULL){
		perror("win");
		return -1;
	}
	for(int i=0;i<4;i++){
		wbkgd(win[i],COLOR_PAIR(1));
		if(i==0)
			wborder(win[i], 0, 0, 0, ' ', 0, 0, ' ', ' ');
		else
			wborder(win[i], 0, 0, 0, 0, 0, 0, 0, 0);
		refresh();
		wrefresh(win[i]);
	}
	return 0;
}
int keyPad(Windows *windows){
	if(windows==NULL){
		perror("windows");
		return -1;
	}
    mvwprintw(windows->consolewin, 2, 1, ">>                                            ");
	wmove(windows->consolewin, 2, 4);
	refresh();
	wrefresh(windows->consolewin);

	int ch;
    noecho();
	WINDOW* win[4];
	win[0]=windows->logwin;
	win[1]=windows->leftwin;
	win[2]=windows->rightwin;
	win[3]=windows->consolewin;
	int now=3;
	int cursor=4;
	int cursor2=4;
	int line=1;
	WINDOW *currentwin=win[now];
	WINDOW *prevwin=win[2];
	wborder(windows->upwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wbkgd(windows->upwin, COLOR_PAIR(3));
	refresh();
	wrefresh(windows->upwin);

	wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wbkgd(currentwin, COLOR_PAIR(2));
	refresh();
	wrefresh(currentwin);
	keypad(stdscr, TRUE);
	//char command[80]="echo 'hoho' > ./ho.txt";
	char command[152]="";
	int spaceCnt=0;
	while((ch=getch())!=27) //콘솔창에 x라는 문자 쓰는일 많아서 esc누르면 나가게했음
	{
		switch(ch)
		{
			case 96:
				mvwprintw(windows->logwin,3,1,"[server] client request type : quit");
				mvwprintw(windows->logwin,2,1,"[server] client disconnected : 192.168.30.10    ");
				refresh();
				wrefresh(windows->logwin);
				break;
			case 10: //엔터입력시 현재 win창에 따라 다르게 동작
				spaceCnt=0;
				freeColor(win);
			  if(now==1) //leftwin에서 엔터쳤을 경우 업로드, 결과는 logwin에 출력 + 로그파일에도 출력
				{
					;
				}
				else if(now==2)//rightwin에서 엔터쳤을 경우 다운로드 혹은 아무일도 일어나지 않게, 결과는 logwin에 출력 + 로그파일에도 출력
				{
					;
				}
				else if(now==3)//consolewin에서 엔터쳤을 경우 커널에 명령어 전달, 결과는 logwin에 출력 + 로그파일에도 출력??
				{
					//wmove(win[3], 2, 4);
					//wclear(win[3]);
					wdeleteln(win[3]);
					winsertln(win[3]);
					line=1;
					cursor=4;
					cursor2=4;
					//mvwprintw(win[3],1, 1,"console");
					mvwprintw(win[3], 2, 1, ">> ");
					wborder(win[3],' ', ' ',' ',' ',' ',' ',' ',' ');
					wbkgd(win[3], COLOR_PAIR(2));
					refresh();
					wrefresh(win[3]);
					system(command);
					wmove(win[3],2,3);
					refresh();
					wrefresh(currentwin);
				}
				refresh();
				wrefresh(currentwin);
				break;
			case 43:  //+입력시 꿀단지 차오르게함
				if(spaceCnt!=4)
					spaceCnt++;
				else
					spaceCnt=1;

				freeColor(win);
				if(spaceCnt==1)
					;
				if(spaceCnt==2)
				{
					wborder(win[3], 0, 0, ' ', 0, 0, 0, 0, 0);
					wbkgd(win[3],COLOR_PAIR(2));
				}
				else if(spaceCnt==3)
				{
					wborder(win[3], 0, 0, ' ', 0, 0, 0, 0, 0);
					wbkgd(win[3],COLOR_PAIR(2));

					wborder(win[2], ' ', 0, 0, 0, 0, 0, 0, 0);
					wbkgd(win[2],COLOR_PAIR(2));

					wborder(win[1], 0, ' ', 0,0, 0, 0, 0,0);
					wbkgd(win[1],COLOR_PAIR(2));
				}
				else if(spaceCnt==4)
				{
					wborder(win[3], 0, 0, ' ', 0, 0, 0, 0, 0);
					wbkgd(win[3],COLOR_PAIR(2));
					
					 wborder(win[2], ' ', 0, 0, 0, 0, 0, 0, 0);
					 wbkgd(win[2],COLOR_PAIR(2));

 					 wborder(win[1], 0, ' ', 0,0, 0, 0, 0,0);
 					 wbkgd(win[1],COLOR_PAIR(2));

					wborder(win[0], 0, 0, 0, ' ', 0,0, 0, 0);
					wbkgd(win[0],COLOR_PAIR(2));
				}
				refresh();
				wrefresh(win[0]);
				wrefresh(win[1]);
				wrefresh(win[2]);
				wrefresh(win[3]);
				break;
			case KEY_LEFT:
				spaceCnt=0;
				freeColor(win);
				prevwin=currentwin;
				if(now==0)
					now=3;
				else
					now--;
				currentwin=win[now];
				if(prevwin==windows->logwin)
					wborder(prevwin, 0, 0, 0, ' ', 0, 0, ' ', ' ');
				else
					wborder(prevwin, 0, 0, 0, 0, 0, 0, 0, 0);
				wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wbkgd(prevwin, COLOR_PAIR(1));
				wbkgd(currentwin, COLOR_PAIR(2));
				refresh();
				wrefresh(prevwin);
				wrefresh(currentwin);
				break;
			case KEY_RIGHT:
				spaceCnt=0;
				freeColor(win);
				prevwin=currentwin;
				if(now==3)
					now=0;
				else
					now++;
				currentwin=win[now];
			    if(prevwin==windows->logwin)
					wborder(prevwin, 0, 0, 0, ' ', 0, 0, ' ', ' ');
				else
					wborder(prevwin, 0, 0, 0, 0, 0, 0, 0, 0);
				wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wbkgd(prevwin, COLOR_PAIR(1));
				wbkgd(currentwin, COLOR_PAIR(2));
				refresh();
				wrefresh(prevwin);
				wrefresh(currentwin);
				break;
			case KEY_UP:
				spaceCnt=0;	
				if(now==1||now==2)
			    {
					wscrl(currentwin,-1);
					//scroll(currentwin);
					refresh();
					wrefresh(currentwin);
				}
				if(now==3)
					mvwprintw(windows->consolewin, 2, 4, "^");
				break;
			case KEY_DOWN:
				spaceCnt=0;
				if(now==1||now==2)
				{
					wscrl(currentwin,1);
					//scroll(currentwin);
					refresh();
					wrefresh(currentwin);
				}
				if(now==3)
					mvwprintw(windows->consolewin, 2, 4, "v");
				break;
			case KEY_BACKSPACE: //delete문자 했을 경우 (backspace)
				 spaceCnt=0;
				 freeColor(win);
				 prevwin=currentwin;
				 now=3;
				currentwin=win[now];
				if(prevwin==windows->logwin)
   				 wborder(prevwin, 0, 0, 0, ' ', 0, 0, ' ', ' ');
				else
    				wborder(prevwin, 0, 0, 0, 0, 0, 0, 0, 0);
				wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				wbkgd(prevwin, COLOR_PAIR(1));
				wbkgd(currentwin, COLOR_PAIR(2));
				refresh();
				wrefresh(prevwin);
				wrefresh(currentwin);
				command[cursor+cursor2-8]=' ';
				if(line==1){
					if(cursor!=4)
							cursor--;

					mvwprintw(windows->consolewin, 2, cursor, " "); 
					wmove(windows->consolewin, 2, cursor);
				}
				else if(line==2){
					if(cursor2!=4)
						{
							if(cursor2==76)
								mvwprintw(windows->consolewin, 3, 76," ");
							cursor2--;
					  		mvwprintw(windows->consolewin, 3, cursor2, " ");
							wmove(windows->consolewin, 3, cursor2);
						}
					else
						{
							mvwprintw(windows->consolewin, 3, 2, " ");
							mvwprintw(windows->consolewin, 3, 1, " ");
							mvwprintw(windows->consolewin, 2, 76," ");
							line=1;
							wmove(windows->consolewin, 2, cursor);
						}				
				}
				break;
			default:  //add문자 했을 경우
				 spaceCnt=0;
				 freeColor(win);
				 prevwin=currentwin;
     			 now=3;
 				 currentwin=win[now];
 				if(prevwin==windows->logwin)
     				wborder(prevwin, 0, 0, 0, ' ', 0, 0, ' ', ' ');
 				else
     				wborder(prevwin, 0, 0, 0, 0, 0, 0, 0, 0);
				wborder(currentwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
 				wbkgd(prevwin, COLOR_PAIR(1));
 				wbkgd(currentwin, COLOR_PAIR(2));
 				refresh();
 				wrefresh(prevwin);
				wrefresh(currentwin);
				command[cursor+cursor2-8]=(char)ch;
				 if(line==1){
					mvwprintw(windows->consolewin, 2, cursor, "%d", (int)ch);
	
						if(cursor!=76)
							{
								cursor++;
							    wmove(windows->consolewin, 2, cursor);
							}
						else{
								line=2;
								mvwprintw(windows->consolewin, 3, 1, ">>");
								wmove(windows->consolewin, 3, cursor2);
							}
	            }				
				else if(line==2){
					mvwprintw(windows->consolewin, 3, cursor2, "%c", (char)ch);
						if(cursor2!=76)
							{
								cursor2++;
								wmove(windows->consolewin, 3, cursor2);
							}
				}
				break;
		}
		//noecho();
		refresh();
		wrefresh(windows->consolewin);
	}
	delwin(windows->upwin);
	delwin(windows->logwin);
	delwin(windows->leftwin);
	delwin(windows->rightwin);
	delwin(windows->consolewin);
	endwin();
	exit(0);
	return 0;
}
/*int main(Windows *windows){
	keyPad(windows);
return 0;
}*/
