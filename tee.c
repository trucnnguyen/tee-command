/******************************************************************************
 * Truc Nguyen
 * ID: 016465020
 * CS2600, Fall 2022
 * Program Assignment 06
 * This assignment is to write a version of "tee" command in Linux/Unix.
 
*******************************************************************************/
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define POSIX_SOURCE
#define SIZE 1000

char *fileArr[SIZE];
/*****************************************************
void signal_handler(int signum);
Purpose: This function will handle the Ctrl-C signal. 
So instead of wipe out all contents and data entered,
it would juts exit. 
*******************************************************/
void signal_handler(int signum) {
  printf("\nIt exits\n");
  exit(1);
}
void tee(int file, int count, int option);
int main(int argc, char *argv[])
{
  FILE *file;
  char *filename, *s, *c, line[SIZE];
  int option = 0, size, j = 0, fileExist = 0, copy, fd;
  /*-----------------------------------
      Breakdown user input
  -------------------------------------*/
  for(int i = 0; i < argc; i++)
  {
    //Check if there is "-a" command
    if(strcmp(argv[i], "-a") == 0)
    {
        option = 1;
    }
    //Get file name(s)
    c = strstr(argv[i], ".txt");
    if(c != NULL)
    {
      fileExist = 1;
      if(j == argc)
      {
        break;
      }
      else
      {
        filename = argv[i];
        fileArr[j] = filename;
        j++;
      }
    }
  }
  //Function Call for tee command
  tee(fileExist, argc, option);
  return 0;
}

/***************************************************************************
  void tee(int file, int count, int option);
  This function will take user's entry and display back to stdin and file(s)
if there's any. 
  Function will also check if there's "-a". If there is not, system will overwrite 
the file(s)'s content.
****************************************************************************/
void tee(int file, int count, int option)
{
  char line[SIZE];
  FILE *pfile;
  int fd, copy;

  if(option == 0)
  {
    printf("It enters...\n");
    for(int l = 0; l < count; l++)
      if(fileArr[l] != NULL)
        pfile = fopen(fileArr[l], "w");
  }      
  while(1){
    fgets(line, SIZE, stdin);
    printf("%s", line);
    if(file){
    copy = dup(1);
    for(int k = 0; k < count; k++)
    {
      if(fileArr[k] != NULL)
      {
        close(1);
        fd = open(fileArr[k], O_RDWR);
        lseek(fd, 0, SEEK_END);
        printf("%s", line);
        close(fd);
        dup2(copy,1);
        signal(SIGINT, signal_handler);
      }
    }
  }
}
}