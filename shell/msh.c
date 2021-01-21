/*
    Name: Golay Nie
    ID: 1001678015
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports 10 arguments


//this section handles all the shell builtin commands not from directory

//exit/quit commands. Argument/return irrelevant
int exitt(char **token)
{
  exit(0);
  return 0;
}

//changes directory to token[1]. input directory name. returns 1 to continue
int cd(char **token)
{
  chdir(token[1]);
  return 1;
}

//didn't finish history
int history(char **token)
{
  return 1;
}

//launches program based on token input. Forks and uses execvp in child.
//waits for termination. returns 1 to continue
int execute(char **token)
{
  pid_t pid=fork();

  if( pid == -1 )
  {
    // When fork() returns -1, an error happened.
    perror("fork failed: ");
    exit( EXIT_FAILURE );
  }
  else if ( pid == 0 )
  {
    // When fork() returns 0, we are in the child process.
    execvp(token[0],token);
    fflush(NULL);
    exit( EXIT_SUCCESS );
  }
  else
  {
    // When fork() returns a positive number, we are in the parent
    // process and the return value is the PID of the newly created
    // child process.
    int status;

    // Force the parent process to wait until the child process
    // exits
    waitpid(pid, &status, 0 );
    fflush( NULL );
  }
  return EXIT_SUCCESS;
}

//runs tokens, deciding if it's a built in function or a command from directory
int run(char **token)
{
  if(token[0]==NULL) {
    return 1;
  }
    if(strcmp(token[0],"exit")==0||strcmp(token[0],"quit")==0){
      return(exitt(token));
    }
    if(strcmp(token[0],"cd")==0){
      return(cd(token));
    }
    if(strcmp(token[0],"listpids")==0){
    token[0]="ps";
      return(execute(token));
    }
    else if(strcmp(token[0],"history")==0){
      return(history(token));
    }
  return execute(token);
}

int main()
{

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;

    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;

    char *working_str  = strdup( cmd_str );

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) &&
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    // Now print the tokenized input as a debug check
    // \TODO Remove this code and replace with your shell functionality
    /*
    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ )
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );
    }
    */

    run(token);

    //functionality above this free
    free( working_root );

  }
  return 0;
}
