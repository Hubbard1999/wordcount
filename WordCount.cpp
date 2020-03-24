#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include<sys/time.h>

/*字符统计*/
int CharNum(char *file){
	 int count = 0;
	 FILE *fp;
     char a;
	 fp=fopen(file,"r");
	 //开始
	 while(!feof(fp)){
	 	a=fgetc(fp);
	 	if(a!=' '&&a!='\n'&&a!='\t')	
		//除空格 换行 tab外 都当作一个字符 
	 	count++;
	 }
	 fclose(fp); 
	 count--;
	 return count;
}

/*词数统计*/
int WordNum(char *file){
	 int w = 0;
	 FILE *fp;
	 int a,t = 10;
	 int mark = 0;
	 fp = fopen(file,"r");
	 //开始
	 if (CharNum(file)==0)	w = 0;
	 else{
		while(!feof(fp)){
		 	a = fgetc(fp);
		    if(a==32||a==10||a==9)	mark++;
			//   ' '||'\n'||'\t'
            else{
            	if(a==-1) t = mark;
            	mark = 0;
            }
            if(mark==1)	w++;
	 	}
	 	if(t==0) w++;
	 }
	 fclose(fp);
	 return w;
}

/*行数统计*/
int LineNum(char *file){
	 int count = 0;
	 FILE *fp;
     fp=fopen(file,"r");
	 char a;
	 //开始
	 while(!feof(fp)){
		a=fgetc(fp);
		if(a=='\n')	count++;
	 }
	 fclose(fp);
	 return count;
}

/*寻找目录下txt、cpp文件*/
int searchfile(void){
    //文件存储信息结构体 
    struct _finddata_t fileinfo;	//保存文件句柄 
    long fHandle;	//文件数记录器
    //开始
    //check .txt 
    int t=0;
    if( (fHandle=_findfirst( "*txt", &fileinfo )) == -1L ){
        printf( "当前目录下没有txt文件\n");
	}
    else
    do{
		t++;
		printf("找到文件:%s\n", fileinfo.name);
	}while(_findnext(fHandle,&fileinfo)==0);
	printf("txt文件数量：%d\n",t);
	//check .cpp
	t=0;
    if( (fHandle=_findfirst( "*cpp", &fileinfo )) == -1L ){
        printf( "当前目录下没有cpp文件\n");
	}
    else
    do{
		 t++;
		printf("找到文件:%s\n", fileinfo.name);
	}while (_findnext(fHandle,&fileinfo)==0);
	printf("cpp文件数量：%d\n",t);	
    _findclose(fHandle);
    
    return 0;
}

/*更多统计*/
void MoreData(char *file){
	FILE *f;
    f=fopen(file,"r");
    int letter = 0, code = 0, empty = 0, note = 0, mark = 0, notemark = 0;
    //开始 
    while (!feof(f)){
        letter = fgetc(f);
        //判定空行
        if (mark == 0 || mark == 1){
            if (letter == ' ')	continue;
            else if (letter == '\n'){
                empty++;
                mark = 0;
                continue;
            }
            else if ((letter == '{' || letter == '}') && mark == 0){
                mark = 1;
                continue;
            }
	        else{
	            if (letter == '/')	mark = 3;
	            else	mark = 2;
	            }
        }
		//判定代码行
        if (mark == 2){
            while (!feof(f) && letter != '\n')
                letter = fgetc(f);
            mark = 0;
            code++;
            continue;
        }
		//判定注释行
        if (mark == 3){
            while (!feof(f)){
                letter = fgetc(f);
                if (letter == '/' && notemark == 0) //单行注释起始判定
                    notemark = 1;
                else if (letter == '*' && notemark == 0) //多行注释起始判定
                    notemark = 2;
                else if (letter == '*' && notemark == 2) //多行注释结束判定
                    notemark = 3;

                if (notemark == 1){ //单行注释结束判定
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                    mark = 0;
                    notemark = 0;
                    break;
                }

                if (notemark == 2){  //多行注释中间行数计算
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                }

                if (notemark == 3 && letter == '/'){ //多行注释结束判定
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                    mark = 0;
                    notemark = 0;
                    break;
                }
                else if (notemark == 3 && letter != '*') //判定是否为注释中的*
                    notemark = 2;
            }
        }
    }
    printf("共有空行数 %d  代码行数 %d  注释行数 %d\n", empty, code - 1, note);
}

/*主函数*/
int main (int argc, char *argv[]){
	/* 定义两个结构体 */
	/* 程序开始之前计时start */
	struct timeval start;
	struct timeval end;
	unsigned long timer;
	gettimeofday(&start, NULL);
	int i;
	for(i=1;i<argc;i++){
		
		/*字符统计*/ 
		if(!strcmp(argv[i],"-c")){
			printf("charnumber:%d\n",CharNum(argv[argc-1]));
		}
		/*词数统计*/
		else if(!strcmp(argv[i],"-w")){
			printf("wordnumber:%d\n",WordNum(argv[argc-1]));
		}
		/*行数统计*/
		else if (!strcmp(argv[i],"-l")){
			printf("linenumber:%d\n",LineNum(argv[argc-1]));
		}
		/*寻找目录下txt、cpp文件*/
		else if(!strcmp(argv[i],"-s")){
			searchfile();
		}
		/*更多统计*/
		else if(!strcmp(argv[i],"-a")){
			MoreData(argv[argc-1]);
		}
	}

	gettimeofday(&end, NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("耗时 = %ld us\n", timer);

	return 0;
}
