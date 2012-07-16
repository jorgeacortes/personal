/* Serial app.
 * Opens a serial port and if reads a one executes
 * the script you have typed
 * (C) 7/2012 Jorge A. Cortés http://electronics.jorgeacortes.com
 */
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#define N 8		/* Buffer length */
#define L 256	/* Command and path length */
int open_port(void);

int main()
{
  char buf[N],com[L];
  size_t nbytes;
  ssize_t bytes_read;
  int fd;
  nbytes = sizeof(buf);
  printf("\nSerial app.\nType script (ex:sh /dir/to/script/):");
  fgets(com,L,stdin);
  fd=open_port();
  while(fd!=-1)
  {
    bytes_read = read(fd, buf, nbytes);
    fprintf(stdout,"\nOutput:%s",buf);
    if(buf[0]=='1') //If we recieve one executes the command
      system(com);
  }
  printf
  (	  "*******************"
	"\n**Exiting program**"
	"\n*******************"
  );
  return 0;
}

int open_port(void)
{
  /*
   * 'open_port()' - Open serial port typed.
   * Returns the file descriptor on success or -1 on error.
   */
  char dir[L]; // Port path
  int fd; /* File descriptor for the port */
  printf("Type the port path:");
  fgets(dir,L,stdin);
  dir[strlen(dir)-1]='\0'; // delete return
  fd = open(dir, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  { //Could not open the port.
    perror("open_port: Unable to open");
    printf("Path introduced:%s\n",dir);
  }
  else
    fcntl(fd, F_SETFL, 0);
  return (fd);
}
