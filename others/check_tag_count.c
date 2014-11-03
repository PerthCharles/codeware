#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <stdint.h>
//////////////////////////////////////////////////////////
//							//
//	Get the address regions sampled by FPGA		//
//							//
//////////////////////////////////////////////////////////
#define	SAMPLE			//only use the SAMPLE information in the ../cfg_content
//#define	DUAL_CHANNEL	//the memory configuration is dual_channel or not, 
				//this will influence the address collected by FPGA
#include "GetCfgContent.h"
//------------------------------------------------------//



//////////////////////////////////////////////////////////
//							//
//	Define the trace formats			//	
//							//
//////////////////////////////////////////////////////////

#define TRACE_FORMAT_64BITS

#ifdef TRACE_FORMAT_64BITS	
#define	TRACE_LENGTH	8
#define	SEQ_FIELD	1	//Have the seq_no field.
#define	MAX_SEQ		0x4000U	//The maximun seq_no is 0x4000U
#define MAX_DUR		0x100000U
#define MAX_DUR_C	24448
#define COMPRESS_START	16384	//start of the compression
#define COMPRESS_STEP	128	//step of the compression
#endif

//--------------------------------------------------------//

//command parameters
unsigned long long start;	//specify the first trace to analyze
unsigned long long end;		//specify the last trace to analyze
char analyze_option[3];		//specify the trace type to analyze:
				//	"r", only the read access
				//	"w", only the write access
				//	"rw", both the read and write access
char print_option[2];		//specify whether to print the trace:
				//	"p", print trace on the screen
				//	others, don't print trace on the screen
char operation[20];		//specify what operation the analysis does
				//	"test", check the continuity of physical addresses
				//	others, don't perform the check


//read buffer
char 		   *buf;	//tmp buffer for fetching traces from trace_file into memory
unsigned int       rd_cnt;	//the size of data fetched from file
unsigned char      *ptr;	//the pointer of traces in the buffer

//trace fields
unsigned int       seq_no,last_seq_no;	//the sequence number field of the trace, should be continueous
unsigned long long timer;		//the timestampe field of the trace. for HUAWEI, it is a globle
					//timer; for others it is the duration time of current memory access
unsigned int       r_w;			//the read/write field of the trace, 1 is read, 0 is write
unsigned int       addr,last_addr;	//the physical address field of the trace

unsigned int       addr_m;		//the physical address in MB

//statistics
unsigned long long trace_no;		//the number of current analyzing trace from the beginning of the file.
unsigned long long total_abandon = 0;	//the total number of lost traces, obtained by analyzing seq_no
unsigned long long total_gap = 0;	//the total number of discontinuity, obtained by analyzing addr
unsigned long long total_cycle = 0;
unsigned long long total_read = 0;
unsigned long long total_write = 0;


//define by zhongbin
unsigned long long timecount=0;
int count=0;
#define MAX_C 21000
//split the trace by choosed tag
    int linenum=0;
    int choose_cluster[MAX_C]={0};
    int choose_line[MAX_C]={0};
    int ptr_choose=0;
int flag_zh_open_flag=0;//the number of file have open to be write
FILE *fout;
int num_choose=0;
char output_trace[256];
int outputnum=0;//the # of output files by split
/****************************************************************************************
*											*
*	Decode the sequence number, timestamp, read/write and physical address		*
*	from the binary traces according to the corresponding format			*
*											*
****************************************************************************************/
void trace_decode()
{
	unsigned int       tmp;
   #ifdef TRACE_FORMAT_64BITS
        seq_no = (unsigned int)( (*(unsigned long long*)ptr) >> 50 );
        seq_no = (unsigned int)( seq_no & 0x03fffU );
        timer  = (unsigned long long)( (*(unsigned long long*)ptr) >> 30);
        timer  = (unsigned long long)( timer & 0x00fffffULL );
        tmp    = (unsigned int)( *(unsigned int*)ptr );
        r_w    = (unsigned int)( (tmp>>29) & 0x01U );
        addr   = (unsigned int)( tmp & 0x1fffffffU );
        addr   = (unsigned int)( addr << 3 );
//check for added tag number
//	printf("addr:%x\n",addr);
	if((addr^0xc8100000)==0) 
	{
	//	printf("Good news c4400000!!! %d\n",count);
		count++;
	}
        
	addr_m = addr/1024/1024;//in MB
   #endif
	ptr += TRACE_LENGTH;
	

	total_cycle += timer;
	total_read += r_w;
	
	return;
}


/********************************************************************************
*										*
*	Check the sequence number to see if any traces are lost during		*
*	the PCIe transmission or before the FPGA buffer				*
*										*
********************************************************************************/
void seq_check()
{
	if(trace_no==start)
	{	
		last_seq_no = seq_no-1;
	}

	if(seq_no != (last_seq_no + 1))
	{
        	if(seq_no == 0 && last_seq_no == MAX_SEQ-1 );
        	else if(seq_no < last_seq_no){
            		total_abandon += seq_no + MAX_SEQ - last_seq_no -1;
        	}
        	else{
		    	total_abandon += seq_no - last_seq_no -1;
	    	}
    	}

	last_seq_no = seq_no;
	return;
}



/********************************************************************************
*										*
*	Check the physical addresses to see if they are continueous.		*
*										*
********************************************************************************/
void continuity_check()
{
	if(trace_no==start|trace_no==start+1)
	{	
		last_addr = addr - 0x40;
	}

        if(addr >= chg_sample_start1 && last_addr <= chg_sample_end1-0x40 )
	{

	if(addr != (last_addr + 0x40))
	{
        	if(addr == chg_sample_start1 && last_addr == chg_sample_end1-0x40 );
        	else 
		{
			total_gap ++;
           		printf("@ discontinuity:  trace %6d | last addr 0x%x | addr 0x%x\n",trace_no,last_addr,addr);
	    	}
    	}

	last_addr = addr;
	}
	
}




/********************************************************
*							*
*	Print the analyzed trace on the screen.		*
*							*
********************************************************/
char char_r_w()
{
	if(r_w)	return 'r';
	else	return 'w';
}

void trace_display()
{
       	if(strcmp(analyze_option,"rw")==0)
       	{
        //     	printf("# trace%6d:    %3x   %14x   %c   %8x;   %4d m\n",trace_no,seq_no,timer,char_r_w(),addr,addr_m);
	//	printf("addr:%8x %d %d\n",addr,addr,addr^addr);
	//	if((addr^0xc40fffe0)==0) {printf("Good news c40fffe0!!! %d\n",count);count++;}//find the tag!
//		timecount+=timer;
       	}
	else
	{
		printf("Should not reach here! Please check the command option you used\n");
	}

}


/********************************************************
*							*
*	Statistic the duration of traces.		*
*							*
********************************************************/

unsigned long long dur[MAX_DUR] = {0};		// dur[i] is the number of trace with duration of i
unsigned long long dur_c[MAX_DUR_C] = {0};	// compressed:
						//	for i in [0,COMPRESS_START), dur_c[i] is the number of trace with duration of i
						//	for i in [COMPRESS_START,MAX_DUR_C), dur_c[i] is the nuber of trace with duration in [COMPRESS_START+COMPRESS_STEP*(i-COMPRESS_START),COMPRESS_START+COMPRESS_STEP*(i+1-COMPRESS_START))

void statistic_duration()
{
	dur[timer]++;
	if( timer>=0 && timer<COMPRESS_START )	dur_c[timer]++ ;
	else	dur_c[COMPRESS_START+(timer-COMPRESS_START)/COMPRESS_STEP]++ ;
}


/********************************************************
*							*
*	Statistic the duration of traces.		*
*							*
********************************************************/

int flag = 0;
unsigned long long rd_above_1G=0;
unsigned long long wr_above_1G=0;
FILE *fp_r,*fp_w;
void glb_timer()
{
//	if(addr>=0x40000000)
	{
		if(r_w == 1)	
		{	
			rd_above_1G++;
			fprintf(fp_r,"%llu	%u\n",total_cycle,addr);
		}
		else
		{
			wr_above_1G++;
			fprintf(fp_w,"%llu	%u\n",total_cycle,addr);
		}
	}
}

/********************************************************
*							*
*			Trace split			*
*							*
********************************************************/
char tmp_output_trace[256];
uint64_t *record_buffer=NULL;
uint64_t *record_ptr=NULL;
uint64_t record_count=0;
void trace_split()
{

	if( (addr^0xc8100000) == 0 )
	{
		if( linenum == choose_line[ptr_choose] )
		{
		//	printf("record_count(normal):%d\n",record_count);	
			fwrite(record_buffer,8,record_count,fout);
			record_count=0;
			free(record_buffer);
	    		fclose(fout);
			flag_zh_open_flag=0;
			ptr_choose++;
		}	
		linenum++;
	}
	else if( linenum==choose_line[ptr_choose] )
	{
	  if(flag_zh_open_flag==0) 
	  {
	    record_buffer=(uint64_t *)malloc(8*1024*1024);
	    memset( record_buffer, 0, 8*1024*1024 );
	    record_ptr=record_buffer;

	    memset( tmp_output_trace, 0, 256 );
	    flag_zh_open_flag=1;//the number of file have open to be write
	    sprintf(tmp_output_trace,"%s-split-%d-%d",output_trace,choose_cluster[ptr_choose],choose_line[ptr_choose]);
	    fout=fopen(tmp_output_trace,"ab+");
	  }
	  *record_ptr=(uint64_t)(  (*(uint64_t *)ptr) << 3 );
	  *record_ptr=(uint64_t)( (*(uint64_t *)record_ptr) & 0x001fffffffffffffULL);
//printf("record_ptr_address:%x %x %x\n",record_ptr,record_ptr+1,record_ptr+8);
	  record_ptr+=1;
	  record_count++;
	  if( record_count >= 1024*1024 )
	  {
	    printf("record_count(should not reach here):%llu\n",record_count);
	    fwrite(record_buffer,8,record_count,fout);
	   // free(record_buffer);
	    record_count=0;
	    memset(record_buffer,0,8*1024*1024);
	    record_ptr=record_buffer;
	  }	
//  fwrite(&tmp_record,8,1,fout);
	}
}


/********************************************************
*							*
*		Read choose points			*
*							*
********************************************************/
void read_choose(char* choose_input)
{
	FILE *f_choose;
	strcat(choose_input,".txt");
	f_choose=fopen(choose_input,"r");
	while( (fscanf(f_choose,"%d %d",&choose_line[num_choose],&choose_cluster[num_choose])) !=-1)
	{
		num_choose++;
	}
}

/********************************************************
*							*
*			MAIN				*
*							*
********************************************************/


int main(int argc, char **argv)
{

    char filename[256];
    char filename2[256];
    char start_i[256];
    char length_i[256];
    char stat_result[256];
    FILE *fp,*fp1;
    memset(filename, 0, 256);
    memset(filename2, 0, 256);
    memset(analyze_option, 0, 3);
    memset(start_i, 0 ,256);
    memset(length_i, 0 ,256);
    memset(print_option, 0 , 2);
    memset(operation, 0 , 20);
    memset(stat_result, 0, 256);
    memset(output_trace,0,256);
//    strcat(output_trace,"/trace_zhongbin");
    if(argc < 6)
    {
        printf("./analyze filename rw start length print_option [operation] [stat_result]\n");
        return 0;
    }
    strcpy(filename, argv[1]);
    strcpy(filename2, argv[1]);
    strcpy(output_trace, argv[1]);
    strcpy(analyze_option, argv[2]);
    strcpy(start_i, argv[3]);
    strcpy(length_i, argv[4]);
    strcpy(print_option, argv[5]);
    if(argc>6) strcpy(operation, argv[6]);
    if(argc==8) {
	strcpy(stat_result, argv[7]);
	strcat(stat_result,".stat");
    }


    if((fp = fopen(filename, "r")) == NULL)
    {
        printf("Open file %s error\n",filename);
        return 0;
    }

//read_choose(filename2);
    printf("\n---------------------------------------------------------------\n");
    
    //get the file size    
    unsigned long long file_size = 0;
    fseek(fp,0,SEEK_END);
    file_size = ftell(fp);
    printf("size of %s (MB):		%.2f\n",filename,(double)file_size/1024/1024);
    printf("total trace number:			%lld\n",file_size/TRACE_LENGTH);

    //check the start and end of analysis
    start =(unsigned long long) atoi(start_i);
    if(strcmp(length_i,"all")!=0)
        end =(unsigned long long)( start + (unsigned long long)atoi(length_i));
    else
        end = (unsigned long long)file_size/TRACE_LENGTH;
    printf("	start:				%lld\n	end:				%lld\n",start,end);
    if(start > end)
    {
        printf("start should less than end!\n");
        return 0;
    }
    if(end*TRACE_LENGTH > file_size)
    {
        printf("    end:    %llu\n  end*TRACE_LENGTH:  %llu\n  file_size:  %llu\n",end,end*TRACE_LENGTH,file_size);
        printf("the input length is too large\n");
        return 0;
    }

    //set fp to the trace need to analyze
    fseek(fp,start*TRACE_LENGTH,SEEK_SET);


    //Get Config information
    GetCfgContent();
    

    //malloc the tmp buf for trace
    buf = (char*)malloc(TRACE_LENGTH*1024*1024*8);
    if(!buf) 
    {
        printf("malloc failed\n");
        return 0;
    }

    printf("---------------------------------------------------------------\n");

	unsigned long long last_total_abandon=0;	

	struct timeval  tvafter;
	struct timeval  tvpre;
	struct timezone tz;

	gettimeofday(&tvpre,&tz);

    //trace analyze
    for(trace_no=start; trace_no<end; trace_no++)
    {
        
        if((trace_no-start)%(1024*1024*8)==0) 
        {
            rd_cnt = fread(buf,1, TRACE_LENGTH*1024*1024*8,fp);
            ptr = buf;

		printf("$ number of %10.2f million analyzed, %12d abandoned in last million!\r",(double)(trace_no-start)/(1024*1024),total_abandon-last_total_abandon);
		fflush(stdout);
		if(last_total_abandon != total_abandon)	printf("\n");
		last_total_abandon = total_abandon;
        }
    
	    trace_decode();
//split the trace
//	    trace_split();
	   // if( strcmp(print_option,"p")==0 ) trace_display();
	    
/*	    if( SEQ_FIELD == 1 )	seq_check();

	    if( strcmp(operation,"test")==0 ) continuity_check();

	    if( strcmp(operation,"stat_dur")==0 || strcmp(operation,"stat_dur_c")==0 ) statistic_duration();
	
	    if( strcmp(operation,"glb_timer")==0 ){; 
		if( flag == 0)
		{
		char *p;
		p=strstr(filename,".trace");
	    	*p='\0';
    		char filename_r[256],filename_w[256];
    		strcpy(filename_r,filename);
    		strcpy(filename_w,filename);
    		strcat(filename_r,".rtrace");
    		strcat(filename_w,".wtrace");
    		if((fp_r = fopen(filename_r, "w+")) == NULL)
    		{
    		    	printf("Open file %s error\n",filename_r);
    	    		return 0;
    		}
    		if((fp_w = fopen(filename_w, "w+")) == NULL)
    		{
        		printf("Open file %s error\n",filename_w);
        		return 0;
    		}
		flag ++;
		}
		glb_timer();
	   }
*/
    }

	gettimeofday(&tvafter,&tz);
	    
		
	printf("$ number of %10.2f million analyzed, %12d abandoned!                         \r",(double)(trace_no-start)/(1024*1024),total_abandon);
	fflush(stdout);
/*	
	if( strcmp(operation,"glb_timer")==0 ) 
	{
		fclose(fp_r);
		fclose(fp_w);
		printf("\nrd_above_1G:	%llu\nwr_above_1G:	%llu\n\n",rd_above_1G,wr_above_1G);
	} 
*/
    printf("\n---------------------------------------------------------------\n");
   
	printf("Time of analyzed trace (seconds):	%.3f\n",(double)total_cycle*0.0000000025); 
	printf("Time to analyze trace (seconds):	%.3f\n",(double)(tvafter.tv_sec-tvpre.tv_sec)+(double)(tvafter.tv_usec-tvpre.tv_usec)/1000000);

    printf("trace number analyzed:			%ld\n",end-start);
    printf("total number abandoned:			%ld\n",total_abandon);
    printf("total number read:				%ld\n",total_read);
    printf("total number write:				%ld\n",end-start-total_read);
    if(strcmp(operation,"test")==0)
    	printf("total discontinuity:			%ld\n",total_gap);
    if(strcmp(operation,"stat_dur")==0)
    {
    	if((fp1 = fopen(stat_result, "w+")) == NULL)
    	{
        	printf("Open file %s error\n",stat_result);
        	return 0;
    	}
	else printf("Write statistic result into %s\n",stat_result);
	int i;
	fprintf(fp1,"DUR		number\n");
	fprintf(fp1,"----------------------------------------\n");
	for(i=0;i<MAX_DUR;i++) 
		fprintf(fp1,"%d		%lld\n",i,dur[i]);
    	fclose(fp1);
    }
    else if(strcmp(operation,"stat_dur_c")==0)
    {
    	if((fp1 = fopen(stat_result, "w+")) == NULL)
    	{
        	printf("Open file %s error\n",stat_result);
        	return 0;
    	}
	else printf("Write statistic result into %s\n",stat_result);
	int i;
	fprintf(fp1,"This is the compressed statistic result.\n");
	fprintf(fp1,"COMPRESS_START:	%d\nCOMPRESS_STEP:	%d\n",COMPRESS_START,COMPRESS_STEP);
	fprintf(fp1,"----------------------------------------\n");
	fprintf(fp1,"DUR		number\n");
	fprintf(fp1,"----------------------------------------\n");
	for(i=0;i<COMPRESS_START;i++)
		fprintf(fp1,"%d		%lld\n",i,dur_c[i]);
	for(i=COMPRESS_START;i<MAX_DUR_C;i++)
		fprintf(fp1,"%d		%lld\n",COMPRESS_START+COMPRESS_STEP/2+(i-COMPRESS_START)*COMPRESS_STEP,dur_c[i]);
    	fclose(fp1);
    }
	

    free(buf);
    fclose(fp);

    printf("---------------------------------------------------------------\n\n");
   // printf("timecount:%llu\n",timecount);
    printf("Good news c8100000!!! %d\n",count);
    printf("num_choose:%d\n",num_choose);
    printf("---------------------------------------------------------------\n\n");
    return 1;

}
