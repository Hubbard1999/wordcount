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
void MoreData(char *file){
	FILE *f;
    f=fopen(file,"r");
    int letter = 0, code = 0, empty = 0, note = 0, mark = 0, notemark = 0;
    //��ʼ 
    while (!feof(f)){
        letter = fgetc(f);
        //�ж�����
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
		//�ж�������
        if (mark == 2){
            while (!feof(f) && letter != '\n')
                letter = fgetc(f);
            mark = 0;
            code++;
            continue;
        }
		//�ж�ע����
        if (mark == 3){
            while (!feof(f)){
                letter = fgetc(f);
                if (letter == '/' && notemark == 0) //����ע����ʼ�ж�
                    notemark = 1;
                else if (letter == '*' && notemark == 0) //����ע����ʼ�ж�
                    notemark = 2;
                else if (letter == '*' && notemark == 2) //����ע�ͽ����ж�
                    notemark = 3;

                if (notemark == 1){ //����ע�ͽ����ж�
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                    mark = 0;
                    notemark = 0;
                    break;
                }

                if (notemark == 2){  //����ע���м���������
                    while (!feof(f) && letter != '\n')
                        letter = fgetc(f);
                    note++;
                }

                if (notemark == 3 && letter == '/'){ //����ע�ͽ����ж�
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
    printf("���п����� %d  �������� %d  ע������ %d\n", empty, code - 1, note);
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
