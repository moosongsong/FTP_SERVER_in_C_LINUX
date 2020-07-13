#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include<pthread.h>
#include "commandFunc.h"
#include "sendRequest.h"
#include "listOpen.h"
#include "myListOpen.h"

void *doListThread(void *arg){
	int *sockPtr=(int *)arg;
	listDownload("ls",NULL,NULL,*sockPtr);
	return NULL;
}

void * doDownloadThread(void *arg){
	int *sockPtr=(int*)arg;
	fileDownload("download",NULL,NULL,*sockPtr);
	return NULL;
}


void myflush(){
	while(getchar()!='\n'){;}
}

void doCommand(int sock, const char *ip){
	char cmd;
	char *srcPath[100];
	char *destPath=NULL;
	char *msg=".";
	pthread_t tid;

	while(1){
		
	cmd=getchar();
	
	switch(cmd){
		case ' ' : putSrcPath(srcPath, &msg);
				   break;

		case '\n': //listopen();
					break;

		case 'c' : getDestPath(destPath, &msg, "복사할 경로를 입력하세요:"); 
				   doCopy(srcPath,len,destPath,&msg);
				   freeDestPath(destPath,&msg);
				   break;

		case 'm' : getDestPath(destPath, &msg, "이동할 경로를 입력하세요:");
				   doMove(srcPath,len,destpath,&msg);
				   freeDestPath(destpath,&msg);
				   break;

		case 'r' : doRemove(srcPath,len,&msg);
				   break;

		case 'n' : getDestPath(destPath,&msg, "바꿀 이름을 입력하세요:");
				   doRename(srcPath,len,destPath,&msg);
				   freeDestPath(destPath,&msg);
				   break;

		case 'f' : if(pthread_create(&tid,NULL,doDownloadThread,*resInfo)!=0){
					   perror("pthread_create");
					   return -1;
				   }
				   //download();
				   break;

		case 'p' : ;
		case 'h' : ;
		case 'k' : getDestPath(destPath, &msg, "생성할 디렉토리명을 입력하세요:");
				   doMkdir(destPath,&msg);
				   freeDestPath(destPath,&msg);
				   break;

		case 'x' : ;
	}

	}

}

int main(){
	myListOpen();
	listOpen();
	//ls요청 한번 보내고 출력해야됨
	doCommand();


	return 0;
}
