#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	unsigned int pid;
	time_t t;
	struct tm *tm;	
	int fd;
	char *argv[3];
	char buf[512];
	int fd0, fd1, fd2;

	fd = open("./crontab", O_RDWR);
	pid = fork();
	
	if(pid == -1) return -1;
	if(pid != 0)
		exit(0);
	if(setsid() < 0)
		exit(0);
	if(chdir("/") < 0)
		exit(0);

	umask(0);

	close(0);
	close(1);
	close(2);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = open("/dev/null", O_RDWR);
	fd2 = open("/dev/null", O_RDWR);

	t = time(NULL);
	tm = localtime(&t);

	while (1)
	{
		buf[0] = '\0';	

		// insert your code
		
		lseek(fd,0,SEEK_SET);
		read(fd,buf,sizeof(buf));
			
		//printf("%s\n",buf);
		
		char *token=NULL;
		char *pos=buf;
		int i=0;
		
		//printf("%s\n",buf);

		while((token=strtok_r(pos," \n",&pos))){
			argv[i]=token;
			i++;
		}
		
		int min=0;
		int hour=0;

		t=time(NULL);
		tm=localtime(&t);
		
		//printf("%dh %dmin %dsec \n",tm->tm_hour, tm->tm_min, tm->tm_sec);
		//printf("%s, %s\n",argv[0],argv[1]);
		if (strcmp(argv[0],"*")==0){
			min=tm->tm_min;
		}
		else{
			min=atoi(argv[0]);
		}
		
		if (strcmp(argv[1],"*")==0){
			hour=tm->tm_hour;
		}
		else{
			hour=atoi(argv[1]);
		}
		
		//printf("every %dh %dm\n",hour,min);
		//pid=fork();

		if(tm->tm_min==min && tm->tm_hour==hour){
			pid=fork();
			if (pid<0)
			{
				return -1;
			}
			else if (pid==0)
			{
				execl("/bin/sh", "/bin/sh", "-c", argv[2], (char*) NULL);			
		
			}
			else{
			
				wait(NULL);
			}
		}


		
		// ##  hints  ##

		// strtok_r();
		// pid = fork();
		// execl("/bin/sh", "/bin/sh", "-c", argv[2], (char*) NULL);

		t = time(NULL);
		tm = localtime(&t);
		

		sleep(60 - tm->tm_sec % 60);
		//printf("AFT Sleep : %dh %dmin %dsec \n",tm->tm_hour, tm->tm_min, tm->tm_sec);

	}

	return 0;
}
