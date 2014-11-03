#include<stdio.h>
#include<stdlib.h>

//#define CLUSTER 115
//TOP means we want to choose #TOP points 
#define TOP 10000
//int choose_flag[900000]={0};

struct info
{
  int linenum;
  float distance;
//  int tag;
};//<--

void main(int argc,char* argv[])
{
//  void select_zhongbin(int k,int i,char arg[],char arg2[],int m);
  void select_zhongbin(int k,int i,char arg[],int m,int* choose_flag2);
  if(argc!=5)
  {  
    printf("usage:./choose [inputfilename] [outputfilename] [linetotal] [clusternum]\n");
    exit(0);
  }
  int* choose_flag;
  int linetotal=0;
  int cluster=0;
  cluster=atoi(argv[4]);
//get the total number of line in 
  linetotal=atoi(argv[3]);
  choose_flag=(int *)malloc(sizeof(int)*linetotal);
  memset(choose_flag,0,sizeof(int)*linetotal);

//  int each_nums[cluster]={0};
//  int each_choose[cluster]={0};
  int *each_nums,*each_choose;
  each_nums=(int*)malloc(sizeof(int)*cluster);
  each_choose=(int*)malloc(sizeof(int)*cluster);
  memset(each_nums,0,sizeof(int)*cluster);
  memset(each_choose,0,sizeof(int)*cluster);
  
  int tmpLabel;
  int total_nums=0;
  int total_choosed=0;
  int i;
  double tmpdis;
  FILE *fin1,*fin2,*fouttmp;
  fin1=fopen(argv[1],"r");
  fin2=fopen(argv[1],"r");
  fouttmp=fopen(argv[2],"a");

  //caculate these is how much vectors in each clusters
  while(fscanf(fin1,"%d %f",&tmpLabel,&tmpdis)!=-1)
  {
    each_nums[tmpLabel]++;
    total_nums++;
  }
  for(i=0;i<cluster;i++)
  {
    each_choose[i]=(each_nums[i]/(total_nums+0.01))*TOP+1;
    if(each_choose[i]>each_nums[i]) each_choose[i]=each_nums[i];
    total_choosed+=each_choose[i];
    select_zhongbin(each_choose[i],i,argv[1],each_nums[i],choose_flag);
  }
//---------------------debug messages------------//
if(total_nums!=linetotal)
	printf("linetotal:%d\n",linetotal);
printf("total_nums:%d total_choosed:%d each_nums[0]:%d each_nums[1]:%d\n",total_nums,total_choosed,each_nums[0],each_nums[1]);
//---------------------------------------//
  for(i=0;i<linetotal;i++)
  {  
     fscanf(fin2,"%d %f",&tmpLabel,&tmpdis);
     if(choose_flag[i]==1)
       fprintf(fouttmp,"%8d %8d\n",i,tmpLabel);
  }
  printf("Having choose %d points from %d points\n",total_choosed,i);
  fclose(fin1);
}

//choose #k item in cluster i of file arg[],
//the total # in cluster i is m
/*
void select_zhongbin(int k,int i,char arg[],char arg2[],int m)
{
//  printf("%s\n",arg);
  struct info tmpinfo[m];

  FILE *fintmp,*fouttmp;
  fintmp=fopen(arg,"r");
  fouttmp=fopen(arg2,"a");
  int tmp=0,tmpline=0;
  int tag;
  float distance;
  struct info povit;
  while(fscanf(fintmp,"%d %f",&tag,&distance)!=-1)
  {
    if(tag==i)
    {
      tmpinfo[tmp].linenum=tmpline;
      tmpinfo[tmp].distance=distance;
      tmp++;
    }
    tmpline++;
  }

if(tmp!=m){ printf("the number found is different from the total number belong in cluser!\nfound:%d total:%d\n",tmp,m); exit(0);}
  int i1,j;
  for(i1=1;i1<m;i1++)
  {
    povit.linenum=tmpinfo[i1].linenum;
    povit.distance=tmpinfo[i1].distance;
    j=i1-1;
    while(povit.distance<tmpinfo[j].distance&&j>=0) 
    {
      tmpinfo[j+1].linenum=tmpinfo[j].linenum;
      tmpinfo[j+1].distance=tmpinfo[j].distance;
      j--;
    }
    tmpinfo[j+1].linenum=povit.linenum;
    tmpinfo[j+1].distance=povit.distance;
  }
  for(i1=0;i1<k;i1++)
  {
   // fprintf(fouttmp,"linenum:%d\t distance:%f\t cluster:%d\n",tmpinfo[i1].linenum,tmpinfo[i1].distance,i);
    fprintf(fouttmp,"%8d %8d\n",tmpinfo[i1].linenum,i);
  }
  fclose(fintmp);
  fclose(fouttmp);
}
*/

void select_zhongbin(int k,int i,char arg[],int m,int* choose_flag2)
{
//  printf("%s\n",arg);
  struct info tmpinfo[m];

  FILE *fintmp;
  fintmp=fopen(arg,"r");
//  fouttmp=fopen(arg2,"a");
  int tmp=0,tmpline=0;
  int tag;
  float distance;
  struct info povit;
  while(fscanf(fintmp,"%d %f",&tag,&distance)!=-1)
  {
    if(tag==i)
    {
      tmpinfo[tmp].linenum=tmpline;
      tmpinfo[tmp].distance=distance;
      tmp++;
    }
    tmpline++;
  }

if(tmp!=m){ printf("the number found is different from the total number belong in cluser!\nfound:%d total:%d\n",tmp,m); exit(0);}
  int i1,j;
  for(i1=1;i1<m;i1++)
  {
    povit.linenum=tmpinfo[i1].linenum;
    povit.distance=tmpinfo[i1].distance;
    j=i1-1;
    while(povit.distance<tmpinfo[j].distance&&j>=0) 
    {
      tmpinfo[j+1].linenum=tmpinfo[j].linenum;
      tmpinfo[j+1].distance=tmpinfo[j].distance;
      j--;
    }
    tmpinfo[j+1].linenum=povit.linenum;
    tmpinfo[j+1].distance=povit.distance;
  }
  for(i1=0;i1<k;i1++)
  {
   // fprintf(fouttmp,"linenum:%d\t distance:%f\t cluster:%d\n",tmpinfo[i1].linenum,tmpinfo[i1].distance,i);
 //   fprintf(fouttmp,"%8d %8d\n",tmpinfo[i1].linenum,i);
      choose_flag2[ tmpinfo[i1].linenum ] = 1;
  }
  fclose(fintmp);
//  fclose(fouttmp);
}
