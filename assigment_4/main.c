#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <inttypes.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#define SIZE_TO_READ 512

#define	CONCAT(X,Y) argv[1]##i+1
typedef struct {
	uint8_t status;
	uint8_t CHS_1[3];
	uint8_t partition_type;
	uint8_t CHS_2[3];
	uint32_t lba;
	uint32_t sector_count;
	
}msdos_partion_table;


// return the fd
int readFile(uint8_t* buffer, char * toRead ){
		int fd = open(toRead, O_RDONLY);	
		int Echeck=read(fd, buffer, SIZE_TO_READ);
		assert(Echeck != -1);
		return fd;
}


char* partion_types[10]={"HPFS/NTFS/exFAT","Extended", "Linux swap / Solaris", "Linux"};
uint8_t partion_id[10] ={0x07, 0x05, 0x82 , 0x83};
int main(int argc, char **argv){

	uint8_t buff[SIZE_TO_READ];
	int fd = open(argv[1], O_RDONLY);	
	int Echeck=0;
	Echeck=read(fd, buff, SIZE_TO_READ);
	assert(Echeck != -1);
	msdos_partion_table* msdos_partion_entery = (msdos_partion_table*) &buff[446];
	printf("\n");
	printf("%-13s%-11s%-10s%-10s%-10s%-10s%-8s%-2s \n","Device", "Boot","Start",       "End",   "Sectors",   "Size", "Id" , "Type" );

		int i=0;
		uint8_t v=0;
		bool current_extended=false;
		uint32_t extended_offset=0;
		while((  *(uint16_t*)&msdos_partion_entery[i-v])!=0xaa55 && (  *(uint32_t*)&msdos_partion_entery[i-v])!=0){
		printf("%+5s%-5d%-12c%-10u%-10u%-10u%-10.3f%-8x",argv[1], i-v+1,
		msdos_partion_entery[i-v].status == 0x80 ? '*':' ',
		msdos_partion_entery[i-v].lba+extended_offset,
		msdos_partion_entery[i-v].lba + msdos_partion_entery[i-v].sector_count-1+extended_offset,
		msdos_partion_entery[i-v].sector_count,
		(float)((double)msdos_partion_entery[i-v].sector_count*512/(1024*1024*1024)),
		msdos_partion_entery[i-v].partition_type);
		bool found=false;
		for(int j =0; j<4;j++){
			if(msdos_partion_entery[i-v].partition_type == partion_id[j]){
				printf("%-2s",partion_types[j]);
				if(partion_id[j]==0x05 && !current_extended){
					v=i+1+48;
					strcat(argv[1], (char *)&v);
					extended_offset=msdos_partion_entery[i].lba;
					readFile(buff, argv[1]);
					v=i+1;
					msdos_partion_entery = (msdos_partion_table*) &buff[446];
					current_extended = true;
					partion_types[1]="Linux";
				}
			break;
			}
		}
		printf("\n");
		i++;
		
	}
	
	return 0;
}