#include "parsing.h"

struct typedef DStruct{
	char *directories[DIRECTORY_SIZE];
	int dNext=0;
}DStruct;

struct typedef FStruct{
	char *files[FILE_SIZE];
	int fNext=0;
}FStruct;

int main(){
//	char *directories[DIRECTORY_SIZE];
// 	int dNext=0;
//	char *files[FILE_SIZE];
//	int fNext=0;
	struct Dtruct dStruct;
	struct FStruct fStruct;
	parsing("list.txt",struct dStruct.directories, fStruct.files, &dStruct.dNext, &fStruct.fNext);
 	parsing("myList.txt", struct dStruct.directories, fStruct.files, &dStruct.dNext, &fStruct.fNext);
  	/*	for(int i=0;i<dNext;i++){
     printf("%s\n", directories[i]);
 	}
	 for(int i=0;i<fNext;i++){
     printf("%s\n", files[i]);
 	}	*/
	return 0;
}

int parsing(char *path,char **directories, char **files, int *dNext, int *fNext){
//	char * directories[10];
//	int dNext=0;
//	char * files[10];
//	int fNext=0;
/*
	int fd=open(path, O_RDONLY| O_CREAT, 444);
	if(fd<0){
		perror("open");
		return -1;
	}
	char buf[BUFSIZ];
	while(1){
		int nRead=read(fd, buf, sizeof(buf));
		if(nRead<0){
			perror("read");
			return -1;
		}
		else if (nRead==0){
			break;
		}
	
	char *savePtr, *saveStr;
	char *ptr=strtok_r(buf, "\n", &savePtr);
		  ptr=strtok_r(NULL, "\n", &savePtr);
		  ptr=strtok_r(NULL, "\n", &savePtr);
	while(ptr!=NULL)	{
			char *str=strtok_r(ptr, " ", &saveStr);
			char type=str[0];
			for(int i=0;i<8;i++)
			{
				str=strtok_r(NULL, " ", &saveStr);
			}
			if(type=='d')
			{
				//printf("directory");
				directories[*dNext]=str;
				(*dNext)++;
			}
			else if(type=='-')
			{
				//printf("file");
				files[*fNext]=str;
				(*fNext)++;
			}
			else
				break;
			//printf("%s", str);			
			ptr=strtok_r(NULL, "\n", &savePtr);
			//printf("\n");
		}
	}*/
return 0;
}
