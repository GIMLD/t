#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define DATA_TAG -9999
#define DATA_FILE "data.dat"

enum { ASC=1, DESC=2};  

struct TInfo{
    int num;
    char name[12];
    char gender[6];
    char tel[16];
    int age;
};

struct TDataCheck{
    int tag;
    int count;
};

TInfo *data_arr[100];
int data_cnt;
bool is_update;

int getNum(char *pa, int start, int end);
void initjob(void);
void appendJob();
void modifyJob();
void removeJob();
void insertJob();
void sortJob();
void totalView();
void screenClear();
void exitJob();
void storejob();
int numComp( TInfo *pa, TInfo *pb);
int nameComp(TInfo *pa, TInfo *pb);
int genderComp(TInfo *pa, TInfo *pb);
int telComp(TInfo *pa, TInfo *pb);
int ageComp(TInfo *pa, TInfo *pb);
void sort(int n, int(*func)(TInfo *, TInfo *));

main(){
    int menu_id;

    initjob();

    while(1){
        printf("<���θ޴�>\n");
        menu_id = getNum("1:�߰�, 2:����, 3:����, 4:����, 5:����, 6:���, 7:ȭ�������, 8:����=>", 1, 8);
        switch(menu_id){
            case 1: appendJob(); break;
            case 2: modifyJob(); break;
            case 3: removeJob(); break;
            case 4: insertJob(); break;
            case 5: sortJob(); break;
            case 6: totalView(); break;
            case 7: system("cls"); break;
            case 8: storejob(); exit(1);
        }
    }    
}


int getNum(char *pa, int start, int end)
{
    int temp;

    while(1){
        printf(pa); scanf("%d", &temp);
        fflush(stdin);

        if( temp>=start && temp<=end)
            return temp;
            printf("�߸� �Է��߽��ϴ� �ٽ� �Է��Ͻÿ�\n");
    }

    return temp;
}

void initjob(void)
{
    FILE *fh;
    int i;
    fh = fopen(DATA_FILE, "rb");

    if(fh==0){
        printf("file not found!");
        return;
    }

    TDataCheck TCheck;

    fread(&TCheck, sizeof(TDataCheck), 1, fh);
    
    if(TCheck.tag != DATA_TAG){
    
        printf("���� ������ Ʋ���ϴ�.!");
        fclose(fh);
        return;
    }

    for(i = 0; i < TCheck.count; i++){
        data_arr[i] = new TInfo;
        fread( data_arr[i], sizeof(TInfo), 1, fh);
    }

    data_cnt = i;

    fclose(fh);
}

void appendJob()
{
    int i, sw;
    TInfo temp;

    while(1)
    {
        printf("<�߰��۾�>\n");
        totalView();
        printf("��ȣ (end=-999) :"); scanf("%d", &temp.num);
        fflush(stdin);

        sw = 0;
        if(temp.num == -999) return;
        for(i = 0; i < data_cnt; i++)
        {
            if(data_arr[i]->num == temp.num) 
            {
                printf("�ش� ��ȣ�� �̹� �����մϴ�\n");
                sw = 1;
                break;
            }
        }
        if(sw == 0)
        {
            printf("�̸�: "); scanf("%s", temp.name); 
            fflush(stdin);
            printf("����: "); scanf("%s", temp.gender); 
            fflush(stdin);
            printf("����ó:"); scanf("%s", temp.tel); 
            fflush(stdin);
            printf("����:"); scanf("%d", &temp.age);
            fflush(stdin);

            TInfo *tinfo = new TInfo;
            *tinfo = temp;

            data_arr[data_cnt++] = tinfo;
            is_update = true;
            printf("�߰��߽��ϴ�.!!\n");
        }
    }

}

void totalView()
{
    int i;
    printf("----------------------------------------------------\n");
    printf("%2s %7s %5s %3s %7s %3s \n", "No", "����ȣ", "�̸�", "����", "����ó", "����");
    printf("----------------------------------------------------\n");
    for(i = 0; i < data_cnt; i++)
        printf("%2d %7d %5s %3s %7s %3d \n", i+1, data_arr[i]->num, data_arr[i]->name, data_arr[i]->gender, data_arr[i]->tel, data_arr[i]->age);
    printf("----------------------------------------------------\n");
}

void storejob()
{
    if(is_update == 0) return;
    else{
        FILE *fh;
        int i;

        fh = fopen(DATA_FILE, "wb");

        TDataCheck tCheck;
        tCheck.tag = DATA_TAG;
        tCheck.count = data_cnt;

        fwrite(&tCheck, sizeof(TDataCheck), 1, fh);

        for(i = 0; i < data_cnt; i++){
            fwrite(data_arr[i], sizeof(TInfo), 1, fh);
        }

        fclose(fh);
    }
}

void modifyJob()
{
    if(data_cnt == 0)
    {
        printf("������ ���ڵ尡 �����ϴ�\n");
        return;
    }

    int n, sw, i;
    TInfo tinfo;


    while(1){
        sw = 0;
        printf("<�����۾�>\n");
        totalView();
        printf("�����ϰ����ϴ� ���ڵ� ��ȣ (end=-999) :"); scanf("%d", &n);
        fflush(stdin);

        if(n == -999) return;

        if(!(n==1) && data_cnt == 1){
            printf("-999 �Ǵ� 1�� �Է��ϼ���\n"); 
            continue;
        }
        else if(n < 1 || n > data_cnt && data_cnt > 1){
            printf("-999 �Ǵ� 1~%d ������ ���� �Է��ϼ���.\n", data_cnt); 
            continue;
        } 

        printf("�� ��ȣ: "); scanf("%d", &tinfo.num);
        fflush(stdin);

        for(i = 0; i < data_cnt; i++)
        {
            if(tinfo.num == data_arr[i]->num && tinfo.num != data_arr[n-1]->num)
            {
                printf("�ش� ��ȣ�� �̹� �����մϴ�\n");
                sw = 1;
            } 
        }
        if(sw==1) continue;
        else
        {
            printf("����: "); scanf("%s", tinfo.gender); fflush(stdin);
            printf("����ó: "); scanf("%s", tinfo.tel); fflush(stdin);
            printf("����: "); scanf("%d", &tinfo.age); fflush(stdin);
            printf("�̸�: "); scanf("%s", tinfo.name); fflush(stdin);

            *data_arr[n-1] = tinfo;
            is_update = true;
            printf("�����߽��ϴ�.\n");
        }
    }

}

void removeJob()
{
    if(data_cnt == 0)
    {
        printf("������ ���ڵ尡 �����ϴ�\n");
        return;
    }

    int n, sw;
    char del[10];

    while(1)
    {
        totalView();
        printf("�����ϰ����ϴ� ���ڵ� ��ȣ (end = -999)"); scanf("%d", &n);
        fflush(stdin);

        if(n == -999) return;

        if(!(n==1) && data_cnt == 1){
            printf("-999 �Ǵ� 1�� �Է��ϼ���\n"); 
            continue;
        }
        else if(n < 1 || n > data_cnt && data_cnt > 1){
            printf("-999 �Ǵ� 1~%d ������ ���� �Է��ϼ���.\n", data_cnt); 
            continue;
        } 

        printf("��ȣ: %d, �̸�:%s, ����:%s, ����ó:%s, ����:%d \n", data_arr[n-1]->num, data_arr[n-1]->name, data_arr[n-1]->gender, 
                                                                    data_arr[n-1]->tel, data_arr[n-1]->age);

        while(1){
            printf("�����ұ�� (y/n) ?"); scanf("%s", del);
            fflush(stdin);
            if(strcmp(del, "y") == 0) break;
            else if(strcmp(del, "n") == 0) break;
            else{
                printf("��Ȯ�ϰ� �Է����ּ���\n"); continue;
            } 
        }

        if(strcmp(del, "y") == 0) 
        {
            memmove(data_arr + n - 1, data_arr + n, sizeof(TInfo) * (data_cnt - n));
            data_cnt--;
            totalView();
            is_update = true;
            printf("�����߽��ϴ�.\n");
        }
        else if(strcmp(del, "n") == 0) printf("���� ���\n");
    }
}

void insertJob()
{
    TInfo temp;
    int n, sw, i;

    while(1)
    {
        totalView();
        printf("������ ���ڵ带 �������� (�Է��� ���ڵ忡 ���Ե� end = -999)"); scanf("%d", &n);
        fflush(stdin);

        if (n == -999) return;
        if(data_cnt == 1 && n != 1){
            printf("-999 �Ǵ� 1�� �Է��ϼ���\n");
        }
        else if(data_cnt > 1 && n < 1 || n > data_cnt){
            printf("-999 �Ǵ� 1~%d ������ ���� �Է��ϼ���.\n", data_cnt);
        }

        printf("��ȣ (end=-999) :"); scanf("%d", &temp.num);
        fflush(stdin);

        sw = 0;
        if(temp.num == -999) return;
        for(i = 0; i < data_cnt; i++)
        {
            if(data_arr[i]->num == temp.num) 
            {
                printf("�ش� ��ȣ�� �̹� �����մϴ�\n");
                sw = 1;
                break;
            }

        }
        if(sw == 1) continue;
        else{
            printf("�̸�: "); scanf("%s", temp.name); 
            fflush(stdin);
            printf("����: "); scanf("%s", temp.gender); 
            fflush(stdin);
            printf("����ó:"); scanf("%s", temp.tel); 
            fflush(stdin);
            printf("����:"); scanf("%d", &temp.age);
            fflush(stdin);

            TInfo *tinfo = new TInfo;
            *tinfo = temp;
            memmove(data_arr + n , data_arr+n - 1 , sizeof(TInfo) * (data_cnt++));
            data_arr[n-1] = tinfo;
            is_update = true;
            printf("���ԵǾ����ϴ�\n");
        }
    }

    return;
}

void sortJob()
{
    int n;
    int w;
    int (*fp)(TInfo *, TInfo *);

    printf("<���� �۾�>\n"); 
    printf("1. ����ȣ, 2.�̸�, 3.����, 4.����ó, 5.����, 6.������=>"); scanf("%d", &n);
    fflush(stdin);

    switch(n){
        case 1: fp = numComp; break;
        case 2: fp = nameComp; break;
        case 3: fp = genderComp; break;
        case 4: fp = telComp; break;
        case 5: fp = ageComp; break;
        case 6: return;
    }

    printf("1. ��������, 2. ��������=>"); scanf("%d", &w);
    fflush(stdin);

    sort(w,fp);
    is_update = true;
    totalView();
}

int numComp(TInfo *pa, TInfo *pb)
{
    return pa->num - pb->num;
}
int nameComp(TInfo *pa, TInfo *pb)
{
    return strcmp( pa->name, pb->name);
}
int genderComp(TInfo *pa, TInfo *pb)
{
    return strcmp( pa->gender, pb ->gender);
}
int telComp(TInfo *pa, TInfo *pb)
{
    return strcmp(pa->tel, pb->tel);
}
int ageComp(TInfo *pa, TInfo *pb)
{
    return pa->age - pb->age;
} 

void sort(int n, int(*func)(TInfo *, TInfo *))
{
    int i, j;
    TInfo *key;

    for( i = 1; i < data_cnt; i++){
        key = data_arr[i];
        for(j = i -1; j >= 0; j--){
            if(func(data_arr[j], key) <0 && n == 1)
                break;
            if(func(data_arr[i], key) > 0 && n == 2)
                break;
            
            data_arr[j+1] = data_arr[j];
        }
        data_arr[j+1] = key;
    }
}