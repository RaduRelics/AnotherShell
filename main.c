/***************************************************************************//**
@file         main.c
@author       Michael Alexander Radu
@date         Thursday,  31 December 2022
@brief        ASH (Another SHell)
*******************************************************************************/


#define ASH_RL_BUFSIZE 1024
// ash_read_line that avoids a getline implementation
/*char *ash_read_line(void)
{
  int bufsize = ASH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if(!buffer) {
    fprintf(stderr, "ash: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while(1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += ASH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "ash: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}*/

char *ash_read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS); // We received an EOF
    } else {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}

void ash_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = ash_read_line();
    args = ash_split_line(line);
    status = ash_execute(args);

    free(line);
    free(args);
  } while(status);
}

int main(int argc, char **argv)
{
  // Load config files.

  // Run command loop.
  ash_loop();

  // Perform shutdown/cleanup.

  return EXIT_SUCCESS;
}
