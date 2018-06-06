/*
  ECE 373
  Instructors PJ Waskiewicz Jr. and Shannon Nelson
  Higgins, Jeremy
  Assignment #4 - Test
  
  The purpose of this program is to open the module created by
  "pci_blink.c" and blink LED0 at a 50% duty cycle at the rate
  specified as a module_param so long as the device within is
  in a open state.
*/


/* Include Required Libraries. */
#include <sys/types.h>   /* Required for open() System Call. */
#include <sys/stat.h>    /* Required for open() System Call. */
#include <fcntl.h>       /* Required for open() System Call. */
#include <unistd.h>      /* Required for close(), read(), and write() System Calls. */
#include <stdio.h>       /* Required for printf() Function. */
#include <stdint.h>      /* Required for unsigned long datatype. */
#include <stdlib.h>      /* Required for atoi() function. */


/* Main function. */
int main(int argc, char *argv[]){
  int file_descriptor = 0;
  unsigned long blink_rate;
  int temp;
  
  /* Open "/dev/char/pci_device" module. */
  file_descriptor = open("/dev/pci_blink", O_RDWR);
  
  /* Open failed. */
  if(file_descriptor < 0){
    printf("Could not open pci_blink.\n");
    perror("Error");
    return(-1);
  }
  
  /* Read the current blink_rate. */
  if(read(file_descriptor, &blink_rate, sizeof(unsigned long)) < 0){
    printf("Could not read pci_device.\n");
    perror("Error");
    return(-1);
  }
  
  /* Echo message to user. */
  printf("Current blink_rate is: %d.\n", (int)blink_rate);
  
  /* Update blink_rate if user provided an integer argument. */  
  if(argc == 2){
    if(!atoi(argv[1])){
      printf("Invalid argument. Please enter an integer value.\n");
      return(-1);
    }
    
  temp = atoi(argv[1]);

    if(write(file_descriptor, &temp, sizeof(int)) < 0){
      printf("Could not write to pci_device.\n");
      perror("Error");
      return(-1);
    }
    
    printf("Updated blink_rate is: %d.\n", (int)blink_rate);
  }
  
  /* Close the file. */
  close(file_descriptor);
  
  /* Exit Program. */
  return(0);
}
