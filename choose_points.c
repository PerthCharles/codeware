#include<stdio.h>

#define CLUSTER 48
//TOP means we want to choose #TOP points 
#define TOP 100

struct info
{
  int linenum;
  float distance;
//  int tag;
};//<--

void main(int argc,char* argv[])
{
  void select(int k,int i,char arg[],char arg2[],int m);
  if(argc!=3)
  {  
    printf("usage:./choose [inputfilename] [outputfilename]\n");
    exit(0);
  }
  int each_nums[CLUSTER]={0};
  int each_choose[CLUSTER]={0};
  int tmpLabel;
  int total_nums=0;
  int i;
  double tmpdis;
  FILE *fin1;
  fin1=fopen(argv[1],"r");
  //caculate these is how much vectors in each clusters
  while(fscanf(fin1,"%d %f",&tmpLabel,&tmpdis)!=-1)
  {
    each_nums[tmpLabel]++;
    total_nums++;
  }
printf("%d %d %d\n",total_nums,each_nums[0],each_nums[1]);
  for(i=0;i<CLUSTER;i++)
  {
    each_choose[i]=(each_nums[i]/(total_nums+0.01))*TOP+1;
    select(each_choose[i],i,argv[1],argv[2],each_nums[i]);
  }
  fclose(fin1);
}

//choose #k item in cluster i of file arg[],
//the total # in cluster i is m
void select(int k,int i,char arg[],char arg2[],int m)
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
if(tmp!=m){ printf("tmp:%d m:%d\n",tmp,m); exit(0);}
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
    fprintf(fouttmp,"linenum:%d\t distance:%f\t cluster:%d\n",tmpinfo[i1].linenum,tmpinfo[i1].distance,i);
  }
  fclose(fintmp);
  fclose(fouttmp);
}
