#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#define BUFFERSIZE 1024
#define COPYMORE 0644
 
void errExit(char *, char *);
int copyFile(char *src, char *dest);
int dostat(char *filename);
int mode_isReg(struct stat info);
 
 
int main(int ac, char *av[])
{
  /* checks args */
  if(ac != 3)
  {
    fprintf(stderr, "usage: %s source destination\n", *av);
    exit(1);
  }
 
 
   char *src = av[1];
   char *dest = av[2];
 
 
   if( src[0] != '/' && dest[0] != '/' )//cp2 file1.txt file2.txt
   {
       copyFile(src, dest);
   }
   else if( src[0] != '/' && dest[0] == '/' )//cp2 file1.txt /dir 
   {
      int i;
      for(i=1; i<=strlen(dest); i++)
      {
          dest[(i-1)] = dest[i];
      }
      strcat(dest, "/");
      strcat(dest, src);
      copyFile(src, dest);
    
   }


   //LOOP THROUGH AV[1] TO AV[AC-1] 


       //SOME STUFF HERE


       //PASS STUFF TO COPYFILE( )




  else
  {
      fprintf(stderr, "usage: cp1 source destination\n");
      exit(1);
  }
}
 
 
 
int dostat(char *filename)
{
    struct stat fileInfo;
     
    //printf("Next File %s\n", filename);
    if(stat(filename, &fileInfo) >=0)
    if(S_ISREG(fileInfo.st_mode))
      return 1;
    else return 0;
     
    return 0;
}

 
 
 
 
int copyFile(char *source, char *destination)
{
  int in_fd, out_fd, n_chars;
  char buf[BUFFERSIZE];
 
 
  /* open files */
  if( (in_fd=open(source, O_RDONLY)) == -1 )
  {
    errExit("Cannot open ", source);
  }
 
 
  if( (out_fd=creat(destination, COPYMORE)) == -1 )
  {
    errExit("Cannot create ", destination);
  }
 
 
  /* copy files */
  while( (n_chars = read(in_fd, buf, BUFFERSIZE)) > 0 )
  {
    if( write(out_fd, buf, n_chars) != n_chars )
    {
      errExit("Write error to ", destination);
    }
 
 
    if( n_chars == -1 )
    {
      errExit("Read error from ", source);
    }
  }
 
 
    /* close files */
    if( close(in_fd) == -1 || close(out_fd) == -1 )
    {
      errExit("Error closing files", "");
    }
 
 
    return 1;
}
 
 
  void errExit(char *s1, char *s2)
  {
    fprintf(stderr, "Error: %s ", s1);
    perror(s2);
    exit(1);
  }
