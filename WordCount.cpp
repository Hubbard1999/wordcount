#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include<sys/time.h>


int charcalculate(char *file) /*字符统计*/
{
	 int c=0;
	 FILE *fp;
     char a;
	 fp=fopen(file,"r");
	 while(!feof(fp))
	 {
		 a=fgetc(fp);
		    if(a!=' '&&a!='\n'&&a!='\t')
               c++;
			
	 }
	 fclose(fp); 
	 c--;
	 return c;
}

int wordcalculate(char *file)   /*词数统计*/
{
	 int w=0;
	 FILE *fp;
	 int a,t=10;
	 int mark=0;
	 fp=fopen(file,"r");
	 if (charcalculate(file)==0)
         w=0;  
	 else
	 {
		 while(!feof(fp))
	 {
		 a=fgetc(fp);
		    if(a==32||a==10||a==9) //        ' '||'\n'||'\t'
               mark++;
            else{
            	if(a==-1) t=mark;
            	mark=0;
            }
            if(mark==1) w++;
	//printf("w数量：%d mark:%d t:%d word:%d和%c\n",w,mark,t,a,a);
	 }
	 if(t==0) w++;
	 }
	 fclose(fp);
	 return w;
}

int linecalculate(char *file)  /*行数统计*/
{
	 int l=0;
	 FILE *fp;
     fp=fopen(file,"r");
	 char a;
	 while(!feof(fp))
	 {
		 a=fgetc(fp);
		    if(a=='\n')
               l++;
	 }
	 fclose(fp); 
	 return l;
}

int searchfile(void)    /*寻找目录下txt文件*/
{
    //文件存储信息结构体 
    struct _finddata_t fileinfo;
    //保存文件句柄 
    long fHandle;
    //文件数记录器
    int t=0;
       if( (fHandle=_findfirst( "*txt", &fileinfo )) == -1L ) 
		{
        printf( "当前目录下没有txt文件\n");
		
		}
    else
    do{
		 t++;
		printf("找到文件:%s\n", fileinfo.name);
	}while (_findnext(fHandle,&fileinfo)==0);
	printf("txt文件数量：%d\n",t);
	
	t=0;
       if( (fHandle=_findfirst( "*cpp", &fileinfo )) == -1L ) 
		{
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

void MoreData(char *file)  /*更多统计*/
{
	 FILE *f;
     f=fopen(file,"r");
    int letter = 0, code = 0, empty = 0, note = 0, mark = 0, notemark = 0;
    /*
    接受字符，代码行数，空行数，注释行数，类型标记，注释行标记
    mark的参数：0空行，1存在格式化字符的空行，2代码行，3注释行
    notemark参数：0未判定，1单行注释，2多行注释
    */
    while (!feof(f))
    {
        letter = fgetc(f);
        if (mark == 0 || mark == 1) //判定空行
        {
            if (letter == ' ')
                continue;
            else if (letter == '\n')
            {
                empty++;
                mark = 0;
                continue;
            }
            else if ((letter == '{' || letter == '}') && mark == 0)
            {
                mark = 1;
                continue;
            }


            else
            {
                if (letter == '/')
                    mark = 3;
                else
                    mark = 2;
            }
        }

        if (mark == 2) //判定代码行
        {
            while (!feof(f) && letter != '\n')
                letter = fgetc(f);
            mark = 0;
            code++;
            continue;
        }

        if (mark == 3) //判定注释行
        {
            while (!feof(f))
            {
                letter = fgetc(f);

                if (letter == '/' && notemark == 0) //单行注释起始判定
                    notemark = 1;
                else if (letter == '*' && notemark == 0) //多行注释起始判定
                    notemark = 2;
                else if (letter == '*' && notemark == 2) //多行注释结束判定
                    notemark = 3;

                if (notemark == 1) //单行注释结束判定
                {
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                    mark = 0;
                    notemark = 0;
                    break;
                }

                if (notemark == 2)  //多行注释中间行数计算
                {
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                }

                if (notemark == 3 && letter == '/') //多行注释结束判定
                {
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
    printf("共有空行数 %d  代码行数 %d  注释行数 %d\n", empty, code - 1, note); //除去eof行
}

int main (int argc, char *argv[])   /*主函数*/
{
	/* 定义两个结构体 */
	struct timeval start;
	struct timeval end;
	unsigned long timer;
	/* 程序开始之前计时start */
	gettimeofday(&start, NULL);

	   if(!strcmp(argv[1],"-c"))
	{
		printf("charnumber:%d\n",charcalculate(argv[2]));
	}

	   else if(!strcmp(argv[1],"-w"))
	{
		printf("wordnumber:%d\n",wordcalculate(argv[2]));
	}

	   else if (!strcmp(argv[1],"-l"))
	{
		printf("linenumber:%d\n",linecalculate(argv[2]));
	}
	else if(!strcmp(argv[1],"-s"))
	{
		searchfile();
	}
	else if(!strcmp(argv[1],"-a"))
	{
		MoreData(argv[2]);
	}

	/* 程序块结束后计时end */
	gettimeofday(&end, NULL);
	/* 统计程序段运行时间(unit is usec)*/
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("耗时 = %ld us\n", timer);

	return 0;
}
