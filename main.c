#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/*
	Function Declarations for builtin shell commands:
 */
static char ** commands;
static int commandCount=0;
int sh_cd(char **args);
int sh_help(char **args);
int sh_history(char** args);
int sh_exit(char **args);

/*
	List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
	"cd",
	"help",
	"history",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&sh_cd,
	&sh_help,
	&sh_history,
	&sh_exit
};

int sh_num_builtins() {
	return sizeof(builtin_str) / sizeof(char *);
}

/*
	Builtin function implementations.
*/
int sh_cd(char **args)
{
	if (args[1] == NULL) {
		fprintf(stderr, "sh: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("sh");
		}
	}
	return 1;
}

int sh_history(char**args)
{
	 if (args[1] == NULL) {
		fprintf(stderr, "sh: expected argument to \"history\"\n");
	} else {
		int j;
		for(j=0;j<atoi(args[1]) && j < commandCount;j++)
			printf("%d\t%s\n", j+1, commands[j]);
	}
	return 1;
}

int sh_help(char **args)
{
	int i;
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < sh_num_builtins(); i++) {
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

int sh_exit(char **args)
{
	return 0;
}
int sh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0) {
		// Child process
		if (execvp(args[0], args) == -1) {
			perror("sh");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		// Error forking
		perror("sh");
	} else {
		// Parent process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int sh_execute(char **args)
{
	int i;

	if (args[0] == NULL) {
		// An empty command was entered.
		return 1;
	}

	for (i = 0; i < sh_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {

			pid_t pid, wpid;
			int status;

			pid = fork();

			if (pid == 0) {						// Child process
				// printf("%s : %d\n", "Child Process", getpid());
				status = (*builtin_func[i])(args);
				exit(status);
			} else if (pid < 0) {				// Error forking
				perror("sh");
			} else {							// Parent process
				waitpid(-1, &status, 0);
				return WEXITSTATUS(status);
			}
		}
	}

	// if not a builtin function, then run as a linux shell command
	// return sh_launch(args);
}

#define sh_TOK_BUFSIZE 64
#define sh_TOK_DELIM " \t\r\n\a"
char **sh_split_line(char *line)
{
	int bufsize = sh_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, sh_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += sh_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "sh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, sh_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

#define sh_RL_BUFSIZE 1024
char *sh_read_line(void)
{
	int bufsize = sh_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	if (!buffer) {
		fprintf(stderr, "sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
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
			bufsize += sh_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer) {
				fprintf(stderr, "sh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

#define sh_HIST_BUFFER 10
void sh_loop(void)
{
	char *line;
	char **args;
	int status;
	int histSize = sh_HIST_BUFFER;
	commands = (char **)malloc(sizeof(char *)*histSize);
	commandCount = 0;
	char *command;
	do {
		// printf("%s : %d\n", "Parent", getpid());
		printf("> ");
		command = sh_read_line();
		commands[commandCount] = (char *)malloc(sizeof(*command));
		strcpy(commands[commandCount], command);
		args = sh_split_line(command);
		status = sh_execute(args);
		free(args);
		free(command);
		commandCount++;

		if(commandCount >= histSize){
			histSize += sh_HIST_BUFFER;
			commands = realloc(commands, sizeof(char *) * histSize);
			if(!commands){
				fprintf(stderr, "%s\n", "sh: allocation error");
				exit(EXIT_FAILURE);
			}
		}
	} while (status);
}

 int main(int argc, char **argv)
{
	system("clear");
	sh_loop();

	return EXIT_SUCCESS;
}