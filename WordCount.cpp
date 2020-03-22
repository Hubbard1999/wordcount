#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include<sys/time.h>


int charcalculate(char *file) /*�ַ�ͳ��*/
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

int wordcalculate(char *file)   /*����ͳ��*/
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
	//printf("w������%d mark:%d t:%d word:%d��%c\n",w,mark,t,a,a);
	 }
	 if(t==0) w++;
	 }
	 fclose(fp);
	 return w;
}

int linecalculate(char *file)  /*����ͳ��*/
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

int searchfile(void)    /*Ѱ��Ŀ¼��txt�ļ�*/
{
    //�ļ��洢��Ϣ�ṹ�� 
    struct _finddata_t fileinfo;
    //�����ļ���� 
    long fHandle;
    //�ļ�����¼��
    int t=0;
       if( (fHandle=_findfirst( "*txt", &fileinfo )) == -1L ) 
		{
        printf( "��ǰĿ¼��û��txt�ļ�\n");
		
		}
    else
    do{
		 t++;
		printf("�ҵ��ļ�:%s\n", fileinfo.name);
	}while (_findnext(fHandle,&fileinfo)==0);
	printf("txt�ļ�������%d\n",t);
	
	t=0;
       if( (fHandle=_findfirst( "*cpp", &fileinfo )) == -1L ) 
		{
        printf( "��ǰĿ¼��û��cpp�ļ�\n");
		
		}
    else
    do{
		 t++;
		printf("�ҵ��ļ�:%s\n", fileinfo.name);
	}while (_findnext(fHandle,&fileinfo)==0);
	printf("cpp�ļ�������%d\n",t);	
	
	
    _findclose(fHandle);

    
    return 0;
}

void MoreData(char *file)  /*����ͳ��*/
{
	 FILE *f;
     f=fopen(file,"r");
    int letter = 0, code = 0, empty = 0, note = 0, mark = 0, notemark = 0;
    /*
    �����ַ���������������������ע�����������ͱ�ǣ�ע���б��
    mark�Ĳ�����0���У�1���ڸ�ʽ���ַ��Ŀ��У�2�����У�3ע����
    notemark������0δ�ж���1����ע�ͣ�2����ע��
    */
    while (!feof(f))
    {
        letter = fgetc(f);
        if (mark == 0 || mark == 1) //�ж�����
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

        if (mark == 2) //�ж�������
        {
            while (!feof(f) && letter != '\n')
                letter = fgetc(f);
            mark = 0;
            code++;
            continue;
        }

        if (mark == 3) //�ж�ע����
        {
            while (!feof(f))
            {
                letter = fgetc(f);

                if (letter == '/' && notemark == 0) //����ע����ʼ�ж�
                    notemark = 1;
                else if (letter == '*' && notemark == 0) //����ע����ʼ�ж�
                    notemark = 2;
                else if (letter == '*' && notemark == 2) //����ע�ͽ����ж�
                    notemark = 3;

                if (notemark == 1) //����ע�ͽ����ж�
                {
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                    mark = 0;
                    notemark = 0;
                    break;
                }

                if (notemark == 2)  //����ע���м���������
                {
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                }

                if (notemark == 3 && letter == '/') //����ע�ͽ����ж�
                {
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                    mark = 0;
                    notemark = 0;
                    break;
                }
                else if (notemark == 3 && letter != '*') //�ж��Ƿ�Ϊע���е�*
                    notemark = 2;
            }
        }
    }
    printf("���п����� %d  �������� %d  ע������ %d\n", empty, code - 1, note); //��ȥeof��
}

int main (int argc, char *argv[])   /*������*/
{
	/* ���������ṹ�� */
	struct timeval start;
	struct timeval end;
	unsigned long timer;
	/* ����ʼ֮ǰ��ʱstart */
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

	/* �����������ʱend */
	gettimeofday(&end, NULL);
	/* ͳ�Ƴ��������ʱ��(unit is usec)*/
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("��ʱ = %ld us\n", timer);

	return 0;
}
