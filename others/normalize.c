#include<stdio.h>
#include<stdint.h>

#define INDEX_NUM 6



void main(int argc,char* argv[])
{
  if(argc!=3)
    {
      printf("usage:./normalize [inputfilename] [outputfilename]\nexample:./normalize BFS_log_0.kt.txt BFS.bb\n");
      exit(0);
    }
  float colmax1[4];
  uint64_t colmax2[2];
  float tmp1[4];
  uint64_t tmp2[2];
  int colnum;
  int normalize_count=0;
  int tail_cut;//how much is left when it's been cut
  FILE *fin,*fout,*fmax;
  fin=fopen(argv[1],"r");
  fout=fopen(argv[2],"a");
  fmax=fopen("data/my-config","r");
printf("%s %s\n",argv[1],argv[2]);
  fscanf(fmax,"%f %f %f %f %llu %llu %d",&colmax1[0],&colmax1[1],&colmax1[2],&colmax1[3],&colmax2[0],&colmax2[1],&colnum);
  if( colnum > 25000 )  tail_cut=colnum-5000;
  else tail_cut=colnum;
  fprintf(fout,"%d:w\n",tail_cut);
  
printf("col_max:%f col_num:%d\n",colmax1[0],colnum);
  while(fscanf(fin,"%f %f %f %f %llu %llu",&tmp1[0],&tmp1[1],&tmp1[2],&tmp1[3],&tmp2[0],&tmp2[1])!=-1)
  {
    if(normalize_count<tail_cut)
    {  
      normalize_count++;
      fprintf(fout,"%0.16f %d: %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n",1.0/tail_cut,INDEX_NUM,tmp1[0]/colmax1[0],tmp1[1]/colmax1[1],tmp1[2]/colmax1[2],tmp1[3]/colmax1[3],tmp2[0]/(colmax2[0]+0.01),tmp2[1]/(colmax2[1]+0.01));
    }
    else break;
  }
printf("colnum:%d tail_cut:%d normalize_count:%d\n",colnum,tail_cut,normalize_count);
  fclose(fin);
  fclose(fmax);
  fclose(fout);
}
