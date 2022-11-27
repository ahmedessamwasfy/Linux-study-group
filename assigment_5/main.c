#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
   typedef struct {
    uint16_t others_x:1;
    uint16_t others_w:1;
    uint16_t others_r:1;
    uint16_t group_x:1;
    uint16_t group_w:1;
    uint16_t group_r:1;
    uint16_t owner_x:1;
    uint16_t owner_w:1;
    uint16_t owner_r:1;
    uint16_t sticky:1;
    uint16_t sgid:1;
    uint16_t suid:1;
    uint16_t file_type:4;
} mode_s;
 typedef union {
    mode_s mode;
    uint16_t value;
} mode_u;
typedef struct dirs dirs;
 struct dirs {
    char  dirname[50];
    dirs * next;
    char mypwd[500];
};
dirs * headDir = NULL;
 int main(int argc, char **argv)
{
    if (argc < 2)
	return -1;
    DIR * dir;
    int recurseive = 0;
     struct stat mystat;
    int i = 1;
    mode_u myMode;
    char date[200] = { "" };
    char pwd[1000];
    struct dirent *entry;
    getcwd(pwd, 1000);
    struct passwd *mypasswd;
    struct group *mygroup;
    int token = strcmp(argv[1], "-R\0");
    if (token == 0) {
	recurseive = 1;
	i++;
    }
     char dirctory_path[1000];
    strcpy(dirctory_path, argv[i]);
     while (i < argc && (dir = opendir(dirctory_path))) {
	if (dir == NULL)return -1;
	 chdir(argv[i]);
	printf("%s \n",dirctory_path);while (entry = readdir(dir)) {
	    stat(entry->d_name, &mystat);
	    myMode.value = mystat.st_mode;
	    mygroup = getgrgid(mystat.st_gid);
	    mypasswd = getpwuid(mystat.st_uid);
	    strncpy(date, ctime(&mystat.st_atime) + 4, 12);
	    printf
		("%c%c%c%c%c%c%c%c%c%c %+5lu %-5s %-5s %-5lu %-5s %-5s\n",
		 (myMode.value & S_IFMT) ==
		 S_IFDIR ? 'd' : (myMode.value & S_IFMT) ==
		 S_IFLNK ? 'l' : '-' ,
		 myMode.mode.owner_r == 1 ? 'r' : '-' ,
		 myMode.mode.owner_w == 1 ? 'w' : '-' ,
		 myMode.mode.owner_x == 1 ? 'x' : '-' ,
		 myMode.mode.group_r == 1 ? 'r' : '-' ,
		 myMode.mode.group_w == 1 ? 'w' : '-' ,
		 myMode.mode.group_x == 1 ? 'x' : '-' ,
		 myMode.mode.others_r == 1 ? 'r' : '-' ,
		 myMode.mode.others_w == 1 ? 'w' : '-' ,
		 myMode.mode.others_x == 1 ? myMode.mode.sticky ==
		 1 ? 't' : 'x' : '-' , mystat.st_nlink ,
		 mypasswd->pw_name , mygroup->gr_name ,
		 mystat.st_blocks * 512 , date , entry->d_name);
	    
	    if (recurseive && ((myMode.value & S_IFMT) == S_IFDIR) && entry->d_name[0]!='.') {dirs * ptr = (dirs *) malloc(sizeof(dirs));dirs *current=headDir;
getcwd(ptr->mypwd, 500);ptr->next=NULL;
strcpy(ptr->dirname,entry->d_name);
if(headDir==NULL)headDir=ptr;
else { while(current->next != NULL)current=current->next;	current->next = ptr;
	}

	} }sud


closedir(dir);printf("\n");
	 		i++;if (i < argc  || headDir != NULL) {

	if(recurseive){
		if (headDir == NULL){
	    strcpy(dirctory_path, argv[i]);
		chdir(pwd);
		}
		else{
		i--;
		dirs * ptr = headDir;
		strcpy(dirctory_path, ptr->dirname);
		chdir(ptr->mypwd);
		headDir=headDir->next;
		free(ptr);
		}
		}
	else{
	    strcpy(dirctory_path, argv[i]);
		chdir(pwd);
	}
	}
	else {
	    dirctory_path[0] = '\0';
	}
}
    return 0;
}
