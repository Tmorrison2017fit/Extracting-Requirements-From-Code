#include <stdlib.h>
#include <stdio.h>  
#include <string.h>

int main(void){
  char *line_buffer = NULL;
  size_t size_line_buffer = 0;
  int line_counter = 0;
  ssize_t line_size;
  // Open file in read mode
 char filename[] = "hello_world.c";
  FILE *file = fopen(filename, "r");
  
  // If error opening file
  if (!file){
    fprintf(stderr, "Error opening file '%s'\n", filename);
    exit(-1);
  }

  // Get the first line of the file.
  line_size = getline(&line_buffer, &size_line_buffer, file);

  //Loop through each line until end of file is reached
  while (line_size >= 0){
    line_counter++;

    // Display details of line
    //printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_counter, line_size, size_line_buffer, line_buffer);

    // Get next line
    line_size = getline(&line_buffer, &size_line_buffer, file);
	
	if(strstr(line_buffer, "printf") != NULL) {
		printf("Prints to the screen: \n", line_buffer);
	}
	else if(strstr(line_buffer, "scanf") != NULL) {
		printf("Reads from the user\n");
	}
  }

  free(line_buffer);
  line_buffer = NULL;


  fclose(file);

  return 0;
}