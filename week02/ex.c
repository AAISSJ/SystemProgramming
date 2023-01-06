#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

ssize_t readline (char *buf, size_t sz, char *fn, off_t *offset);

int main (int argc, char **argv) {

    if (argc < 2) return 1;

    char line[128] = {0};
    off_t offset = 0;
    ssize_t len = 0;
    int i = 1;
    int fd2=open("Aladdin_num.txt",O_CREAT|O_WRONLY,0764);
    char new[5]={0};
    while ((len = readline (line, 128, argv[1], &offset)) != -1){
        //printf (" %d |  %s \n", i++, line);
	//printf("%ld\n",len);
	snprintf(new,sizeof(new),"%d",i);
	write(fd2,new,sizeof(new));
	write(fd2," | ",3);
	write(fd2,line, len-1);
	write(fd2, "\n",1);
	i++;
    }

    close(fd2);
    return 0;
}

ssize_t readline (char *buf, size_t sz, char *fn, off_t *offset)
{
    int fd = open (fn, O_RDONLY);
    if (fd == -1) {
        return -1;
    }

    ssize_t nchr = 0;
    ssize_t idx = 0;
    char *p = NULL;

 
    if ((nchr = lseek (fd, *offset, SEEK_SET)) != -1)
        nchr = read (fd, buf, sz);
    close (fd);

    if (nchr == -1) {
        return nchr;
    }

    if (nchr == 0) return -1;

    p = buf;    
    while (idx < nchr && *p != '\n') p++, idx++;
    *p = 0;

    if (idx == nchr) { 
        *offset += nchr;

      
        return nchr < (ssize_t)sz ? nchr : 0;
    }

    *offset += idx + 1;

    return idx;
}

