#ifndef __common_h_
#define __common_h_

#include <fcntl.h>

#ifndef TRUE
#define TRUE		1
#endif

#ifndef FALSE
#define FALSE 	0
#endif

#ifndef STD_IN
#define STD_IN	0
#endif

#ifndef STD_OUT
#define STD_OUT	1
#endif

#ifndef STD_ERR
#define STD_ERR	2
#endif

static inline void setlock(int fd,int flag)
{
	if(flag){
		fcntl(fd,F_SETFL,fcntl(fd,F_GETFL) & ~O_NONBLOCK);
	}
	else{
		fcntl(fd,F_SETFL,fcntl(fd,F_GETFL) | O_NONBLOCK);
	}		
}

#endif

