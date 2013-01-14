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
int tmp=0;
  FILE *fin,*fout,*fmax;
  fin=fopen(argv[1],"r");
  fout=fopen(argv[2],"a");
  fmax=fopen("my-config","r");
printf("%s %s\n",argv[1],argv[2]);
  fscanf(fmax,"%f %f %f %f %llu %llu %d",&colmax1[0],&colmax1[1],&colmax1[2],&colmax1[3],&colmax2[0],&colmax2[1],&colnum);

  fprintf(fout,"%d:w\n",colnum);
  
printf("%f %d\n",colmax1[0],colnum);
  while(fscanf(fin,"%f %f %f %f %llu %llu",&tmp1[0],&tmp1[1],&tmp1[2],&tmp1[3],&tmp2[0],&tmp2[1])!=-1)
  {
//    printf("%f\n",tmp1[0]);
//    if(tmp==0)
      fprintf(fout,"%0.16f %d: %0.16f %0.16f %0.16f %0.16f %0.16f %0.16f\n",1.0/colnum,INDEX_NUM,tmp1[0]/colmax1[0],tmp1[1]/colmax1[1],tmp1[2]/colmax1[2],tmp1[3]/colmax1[3],tmp2[0]/(colmax2[0]+0.01),tmp2[1]/(colmax2[1]+0.01));
//    else 
//      fprintf(fout,":%f:%f:%f:%f:%f:%f",tmp1[0]/colmax1[0],tmp1[1]/colmax1[1],tmp1[2]/colmax1[2],tmp1[3]/colmax1[3],tmp2[0]/(colmax2[0]+0.01),tmp2[1]/(colmax2[1]+0.01));
//  tmp++;
//printf("%d\n",tmp);
  }
  fclose(fin);
  fclose(fmax);
  fclose(fout);
}
