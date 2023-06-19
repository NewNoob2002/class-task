#include <stdio.h>
#include <stdlib.h>
#define linemax 1024
struct datehead
{
    double time;
    double ac[3];
    double Gy[3];
   struct datehead *next;
};
int main()
{
double time,ac_x,ac_y,ac_z,gy_x,gy_y,gy_z;
FILE* fp;
struct datehead *head,*p,*q,*f;
head=NULL;
fp=fopen("1.txt","r");
if(fp==NULL){
    printf("open failed");
    return 0;
}
else {
    printf("file opend\n");
    system("pause");
while(!feof(fp)){ 
    p=(struct datehead*)malloc(sizeof(struct datehead));
// 从文件中读取数据并存储到相应的变量中
fscanf(fp, "%lf", &time);
fscanf(fp, "%lf", &ac_x);
fscanf(fp, "%lf", &ac_y);
fscanf(fp, "%lf", &ac_z);
fscanf(fp, "%lf", &gy_x);
fscanf(fp, "%lf", &gy_y);
fscanf(fp, "%lf", &gy_z);
	p->time=time;
    p->ac[0]=ac_x;
    p->ac[1]=ac_y;
    p->ac[2]=ac_z;
    p->Gy[0]=gy_x;
    p->Gy[1]=gy_y;
    p->Gy[2]=gy_z;
    p->next=NULL;
    if(head==NULL){
        head=p;
    }
    else{
        q->next=p;
    }
    q=p;
}
}
fclose(fp);
f=head;
while(f!=NULL){
    printf("%lf\n",f->time);
    for(int i=0;i<3;i++)
    {printf("%lf\n",f->ac[i]);
    printf("%lf\n",f->Gy[i]);
    }
    f=f->next;
}
system("pause");
   return 0;
}