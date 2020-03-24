#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include<sys/time.h>

/*�ַ�ͳ��*/
int CharNum(char *file){
	 int count = 0;
	 FILE *fp;
     char a;
	 fp=fopen(file,"r");
	 //��ʼ
	 while(!feof(fp)){
	 	a=fgetc(fp);
	 	if(a!=' '&&a!='\n'&&a!='\t')	
		//���ո� ���� tab�� ������һ���ַ� 
	 	count++;
	 }
	 fclose(fp); 
	 count--;
	 return count;
}

/*����ͳ��*/
int WordNum(char *file){
	 int w = 0;
	 FILE *fp;
	 int a,t = 10;
	 int mark = 0;
	 fp = fopen(file,"r");
	 //��ʼ
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

/*����ͳ��*/
int LineNum(char *file){
	 int count = 0;
	 FILE *fp;
     fp=fopen(file,"r");
	 char a;
	 //��ʼ
	 while(!feof(fp)){
		a=fgetc(fp);
		if(a=='\n')	count++;
	 }
	 fclose(fp);
	 return count;
}

/*Ѱ��Ŀ¼��txt��cpp�ļ�*/
int searchfile(void){
    //�ļ��洢��Ϣ�ṹ�� 
    struct _finddata_t fileinfo;	//�����ļ���� 
    long fHandle;	//�ļ�����¼��
    //��ʼ
    //check .txt 
    int t=0;
    if( (fHandle=_findfirst( "*txt", &fileinfo )) == -1L ){
        printf( "��ǰĿ¼��û��txt�ļ�\n");
	}
    else
    do{
		t++;
		printf("�ҵ��ļ�:%s\n", fileinfo.name);
	}while(_findnext(fHandle,&fileinfo)==0);
	printf("txt�ļ�������%d\n",t);
	//check .cpp
	t=0;
    if( (fHandle=_findfirst( "*cpp", &fileinfo )) == -1L ){
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

/*����ͳ��*/
void MoreData(char *file)
{
    FILE *fp;
    if ((fp=fopen(file,"r")) == NULL){
        printf("�Ҳ����ļ���");
        exit(0);
    }
	int empty = 0,code = 0,note = 0,state1= 0,state2=0;
	char ch;
	//��ʼ 
	while(!feof(fp)){
		ch = fgetc(fp);
		if(ch=='\n'||ch==EOF){
			if(state2==0)	//���� 
				empty++;
			else if(state2==1){	//������ 
				code++;
				state2 = 0;
			}
			else{	//ע���� 
				note++;
				state2 = 0;
			}
		}
		else if(ch!=' '&&ch!='\t'&&ch!='{'&&ch!='}'){
			if(ch=='/'){
				if(state2==0&&state1==0)
					state1 = 1;
				else if(state2==0&&state1==1){
					state2 = 2;
					state1 = 0;
				}
			} 
			else if(state2!=2)
				state2 = 1;	 
		}
	}
	printf("������Ϊ��%d  ��������Ϊ��%d  ע������Ϊ��%d\n",empty,code,note);
	fclose(fp);
}

/*������*/
int main (int argc, char *argv[]){
	/* ���������ṹ�� */
	/* ����ʼ֮ǰ��ʱstart */
	struct timeval start;
	struct timeval end;
	unsigned long timer;
	gettimeofday(&start, NULL);
	int i;
	for(i=1;i<argc;i++){
		
		/*�ַ�ͳ��*/ 
		if(!strcmp(argv[i],"-c")){
			printf("charnumber:%d\n",CharNum(argv[argc-1]));
		}
		/*����ͳ��*/
		else if(!strcmp(argv[i],"-w")){
			printf("wordnumber:%d\n",WordNum(argv[argc-1]));
		}
		/*����ͳ��*/
		else if (!strcmp(argv[i],"-l")){
			printf("linenumber:%d\n",LineNum(argv[argc-1]));
		}
		/*Ѱ��Ŀ¼��txt��cpp�ļ�*/
		else if(!strcmp(argv[i],"-s")){
			searchfile();
		}
		/*����ͳ��*/
		else if(!strcmp(argv[i],"-a")){
			MoreData(argv[argc-1]);
		}
	}

	gettimeofday(&end, NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("��ʱ = %ld us\n", timer);

	return 0;
}
