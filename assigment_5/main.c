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

    
    
    
    
    
    
    
    
    
    
    
    
    


    
    



    
    
    



{
    
	return -1;
    
    
    
    
    
    
    
    
    
    
    
    
    
	recurseive = 1;
	
    }
    
    
    
	
	
	
	    
	    
	    
	    
	    
	    
		("%c%c%c%c%c%c%c%c%c%c %+5lu %-5s %-5s %-5lu %-5s %-5s\n",
		 
		 S_IFDIR ? 'd' : (myMode.value & S_IFMT) ==
		 S_IFLNK ? 'l' : '-' 
		 myMode.mode.owner_r == 1 ? 'r' : '-' 
		 myMode.mode.owner_w == 1 ? 'w' : '-' 
		 myMode.mode.owner_x == 1 ? 'x' : '-' 
		 myMode.mode.group_r == 1 ? 'r' : '-' 
		 myMode.mode.group_w == 1 ? 'w' : '-' 
		 myMode.mode.group_x == 1 ? 'x' : '-' 
		 myMode.mode.others_r == 1 ? 'r' : '-' 
		 myMode.mode.others_w == 1 ? 'w' : '-' 
		 myMode.mode.others_x == 1 ? myMode.mode.sticky ==
		 1 ? 't' : 'x' : '-' 
		 mypasswd->pw_name 
		 mystat.st_blocks * 512 
	    
	    
getcwd(ptr->mypwd, 500);
strcpy(ptr->dirname,entry->d_name);
if(headDir==NULL)headDir=ptr;
else { while(current->next != NULL)current=current->next;
	}

	}


closedir(dir);
	

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

    
