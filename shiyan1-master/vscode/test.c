#include <stdio.h>
#include <stdlib.h>
#define linemax 1024
struct datehead
{
    double time;
    double ac[2];
    double Gy[2];
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
    fscanf(fp,"%Lf",&time);
    fscanf(fp,"%Lf",&ac_x);
    fscanf(fp,"%Lf",&ac_y);
    fscanf(fp,"%Lf",&ac_z);
    fscanf(fp,"%Lf",&gy_x);
    fscanf(fp,"%Lf",&gy_y);
    fscanf(fp,"%Lf",&gy_z);
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
    // printf("%lf\b",f->time);
    printf("%lf\n",p->Gy[2]);
    f=f->next;
}
system("pause");
   return 0;
}