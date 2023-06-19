#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define linemax 1024
#define G 9.7936174  // 重力加速度
struct datehead
{
    double time;
    double ac[3];
    double Gy[3];
   struct datehead *next;
};
int main()
{
    int samplenum=0;
    double time,ac_x,ac_y,ac_z,gy_x,gy_y,gy_z;
    FILE* fp;
    struct datehead *head,*p,*q,*f;
    head=NULL;
    fp=fopen("Calibration_Data.txt","r");
if(fp==NULL){
    printf("open failed");
    return 0;
}
else {
    printf("file opend ,please press any key\n");
    system("pause");
    }
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
    samplenum++;
}
    fclose(fp);
    // 定义参数和变量
    double sam_rate = 200;  // 采样频率
    double zero_bias[3] = {0.0};   // 零偏误差
    double scale_err[3] = {0.0};    // 比例因子误差
    double cross_err[3] = {0.0};    // 交轴耦合误差
    int start=0; 
    int end=samplenum/2;//中值滤波
    f=head;
    //零位偏差
for(int i=start;i<end;i++){
        zero_bias[0]+=f->ac[0];
        zero_bias[1]+=f->ac[1];
        zero_bias[2]+=f->ac[2];
    f=f->next;
    if(f==NULL){
        break;
    }
   }
    zero_bias[0]=zero_bias[0]/(end-start);
    zero_bias[1]=zero_bias[1]/(end-start);
    zero_bias[2]=zero_bias[2]/(end-start);//求均值求得零位误差。
//比例因子
f=head;
 for(int j=start;j<end;j++){
    scale_err[0]+=f->ac[0]/(G-zero_bias[2]);
    scale_err[1]+=f->ac[1]/(G-zero_bias[2]);
    scale_err[2]+=f->ac[2]/(G-zero_bias[2]);
    f=f->next;
    if(f==NULL){
        break;
    }
    }
    scale_err[0]=scale_err[0]/(end - start);
    scale_err[1]=scale_err[1]/(end - start);
    scale_err[2]=scale_err[2]/(end - start);
//交叉耦合项
f=head;
for (int i = start; i < end; i++) {
        double ac_corr_x = f->ac[0] - zero_bias[0];
        double ac_corr_y = f->ac[1] - zero_bias[1];
        double ac_corr_z = f->ac[2] - zero_bias[2];
        cross_err[0] += (ac_corr_x - scale_err[0] * ac_corr_x) * f->Gy[0] * sam_rate;
        cross_err[1] += (ac_corr_y - scale_err[1] * ac_corr_y) * f->Gy[2] * sam_rate;
        cross_err[2] += (ac_corr_z - scale_err[2] * ac_corr_z) * f->Gy[1] * sam_rate;
        f=f->next;
    if(f==NULL){
        break;
           }
    }
    cross_err[0] /= (end - start);
    cross_err[1] /= (end - start);
    cross_err[2] /= (end - start);
        printf("零点偏差：\n");
    printf("x轴:%lf\n", zero_bias[0]);
    printf("y轴:%lf\n", zero_bias[1]);
    printf("Z轴:%lf\n\n", zero_bias[2]);

    printf("比例因子误差：\n");
    printf("X轴:%lf\n", scale_err[0]);
    printf("Y轴:%lf\n", scale_err[1]);
    printf("Z轴:%lf\n\n", scale_err[2]);

    printf("交轴耦合误差：\n");
    printf("XY轴:%lf\n", cross_err[0]);
    printf("YZ轴:%lf\n", cross_err[1]);
    printf("ZX轴:%lf\n", cross_err[2]);
    system("pause");
   return 0;
}