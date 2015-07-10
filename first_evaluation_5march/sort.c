#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
 
 
  /* A Quicksort for structures of type address. */
void quick_struct(struct dirent **namelist, int count) {
    qs_struct(namelist,0,count);
}
 
int qs_struct(struct dirent **namelist, int left, int right) {
 
    register int i, j;
 
    struct dirent *temp;
    struct stat ibuf;
    struct stat jbuf;
    struct stat xbuf;
             
    i = left; j = right;
 
    stat(namelist[i]->d_name, &ibuf);
    stat(namelist[j]->d_name, &jbuf);  
    stat(namelist[(left+right)/2]->d_name, &xbuf);
 
 
    do {
        while((ibuf.st_mtime < xbuf.st_mtime) && (i < right)) {
            i++;
            stat(namelist[i]->d_name, &ibuf);
        }
        while((jbuf.st_mtime > xbuf.st_mtime) && (j > left))  {
            j--;
            stat(namelist[j]->d_name, &jbuf);
        }
        if(i <= j) {
            temp = namelist[i];
            namelist[i] = namelist[j];
            namelist[j] = temp;
      
              
            i++; j--;
        }
     
    } while(i <= j);
 
    if(left < j) qs_struct(namelist, left, j);
    if(i < right) qs_struct(namelist, i, right);
 
 
}
 
int main(void) {
   
    struct dirent **namelist;
    int n;
    const char *targetdirectory = ".";
     
    n = scandir(targetdirectory, &namelist, 0, alphasort);
     
    struct stat buf;
     
    if (n < 0)
        perror("scandir");
    else {
            quick_struct(namelist, n);
 
        while (n--) {
         
            stat(namelist[n]->d_name, &buf);
            printf("%-23s  %10ld \t %s \n", namelist[n]->d_name, buf.st_mtime, ctime(&buf.st_mtime));
             
             
            free(namelist[n]);
        }
         
        free(namelist);
         
    }
   
   
 
 
 
}