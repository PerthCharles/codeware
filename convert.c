#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdint.h>

#define DEBUG 0
//Memory BandWidth
#define MBW(a,b) (((a)+(b))/(0.002*16*1024))
///ratio between Read and Wrtite
#define RVSW(a,b) ((a)/((b)+0.001))
//ROW Buffer Miss
#define ROWBM(a,b,c) ((a)/((b)+(c)+0.001))
//L3 Miss 
#define L3M(a,b,c) (((a)+(b))/((a)+(b)+(c)+0.001))



void main(int argc, char* argv[])
{
  if(argc!=3)
  {  
    printf("usage:./convert filein0 filein1\n");
    exit(0);
  }
  int read(FILE *fin0,FILE *fin1,uint64_t *a0,uint64_t *a1);
//  int readb(FILE *fin0,FILE *fin1);
  char filein0[64],filein1[64],fileout[64];
  int start,end;
  int tmp;
  memset(filein0,0,64);
  memset(filein1,0,64);
  strcpy(filein0,argv[1]);
  strcpy(filein1,argv[2]);
  strcpy(fileout,argv[1]);
  strcat(fileout,".txt");

  uint64_t *a0,*a1,*b0,*b1;//a0 is read from filein0, a1 is read from filein1, b is the next line below a.
  a0=(uint64_t *)malloc(sizeof(uint64_t)*12);
  a1=(uint64_t *)malloc(sizeof(uint64_t)*12);
  b0=(uint64_t *)malloc(sizeof(uint64_t)*12);
  b1=(uint64_t *)malloc(sizeof(uint64_t)*12);
  memset(a0,0,sizeof(a0));
  memset(a1,0,sizeof(a1));
  memset(b0,0,sizeof(b0));
  memset(b1,0,sizeof(b1));
  
  
  FILE *fin0,*fin1,*fout;
  fin0=fopen(filein0,"r");
  fin1=fopen(filein1,"r");
  fout=fopen(fileout,"a");
  fprintf(fout,"MBW\t RVSW\t ROWBM\t L3M\t ReadC\t WriteC\t\n");

if(DEBUG) printf("%s\t %s\t %s\t\n",filein0,filein1,fileout);
  start=time((time_t*) NULL);

  if(!read(fin0,fin1,a0,a1)) {printf("Should not reach here for filein0!\n");exit(0);}
if(DEBUG) printf("%s\t %s\t %s\t\n",filein0,filein1,fileout);
  while(read(fin0,fin1,b0,b1)) 
  {
    fprintf(fout,"%f %f %f %f %llu %llu\n",MBW(b0[6]-a0[6],b0[7]-a0[7])\
                                          ,RVSW(b0[6]-a0[6],b0[7]-a0[7])\
                                          ,ROWBM(b0[8]-a0[8],b0[6]-a0[6],b0[7]-a0[7])\
                                          ,L3M(b0[9]+b1[9]-a0[9]-a1[9],b0[10]+b1[10]-a0[10]-a1[10],b0[6]-a0[6])\
                                          ,b0[4]-a0[4],b0[5]-a0[5]);
//    memcpy(a0,b0,sizeof(b0));
//    memcpy(a1,b1,sizeof(b1));
    for(tmp=0;tmp<12;tmp++)
    {
      a0[tmp]=b0[tmp];
      a1[tmp]=b1[tmp];
    }
if(DEBUG) {printf("%llu %llu\n",a0[4],a0[5]);}
  }
  
  end=time((time_t*)NULL);  
  printf("Happy ending with %d seconds\n",end-start);
  exit(0);
}

int read(FILE *fin0,FILE *fin1,uint64_t *a0, uint64_t *a1)
{
  int tmp;
  for(tmp=0;tmp<12;tmp++)
  {
    if(fscanf(fin0,"%llu",&a0[tmp])!=-1 && fscanf(fin1,"%llu",&a1[tmp])!=-1) continue;
    else return 0;
  }
  return 1;
}
