// #include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

// using namespace std;

#include<readline/readline.h> 
#include<sys/types.h>
#include<sys/wait.h>
#include <unistd.h>
#define MAX 1000
#define MAXLINE 100

char PATH[]="/usr/bin/";

void init_shell()
{
	printf("My shell\n");
	// sh_term = STDIN_FILENO;
	// is_interactive = isatty(sh_term);
	char* username = getenv("USER"); 
	printf("\nUSER is: @%s \n",username); 
	// char* var = getenv("PATH");
	// printf("\nPATH is: @%s \n",var); 
    sleep(1);
    // clear();
}

char* get_cwd()
{
	long size = pathconf(".", _PC_PATH_MAX);
	char* buffer, *ptr;
	buffer = (char*)malloc((size_t)size);

	if(buffer !=NULL)
	{
		ptr = getcwd(buffer, (size_t)size);
		// printf("%s \n",ptr);
	}
	return ptr;
}

void front_end()
{
	char name[1024] = "";
	char* us_er;
	gethostname(name,sizeof(name));
	char* PATH="/usr/bin/";
	us_er=getenv("USER");
	if(us_er=="root")
		printf("%s@%s: #", us_er,name);
	else
		printf("\n%s@%s:%s $ ", getenv("USER"), name, get_cwd());
}


int changedirec(char *args[])
{
	if (args[1]==NULL)
	{
		printf("Expected Argument");
		return -1;
	}
	else if(args[1] == "~")
	{
		chdir(getenv("HOME"));
		return 1;
	}
	else if(chdir(args[1]) == -1)
	{
		printf("Error : no such directory");
		return -1;
	}
	return 0;
}

int prog_fork(char** args)
{
	pid_t pid = fork();
	int status;

	if (pid<0)
	{
		printf("Error: Failed Forking child");
	}
	else if(pid==0)
		//Child process
	{
		if(execvp(*args,args)<0)
		{
			printf("\nCommand not executed");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}
		while(!WIFEXITED(status)&& !WIFSIGNALED(status));
		// printf("dg");
	}
	return 1;
}

int base(char *args[])
{
	int i=0,j=0;
	// printf("%s\n",args[0]);
	if(strcmp(args[0],"pwd")==0)
	{
		char* c=get_cwd();
		printf("\n%s", c);
		// get_cwd();
	}

	else if(strcmp(args[0],"exit") == 0)
	{
		exit(0);
	}

	else if(strcmp(args[0],"cd") == 0)
	{
		changedirec(args);
	}

	return 1;
}




int main(int argc, char* argv[])
{
	// char* line;
	// char* args[MAXARGS];
	// prog_fork(args);
	init_shell();
	// get_cwd();
	front_end();

	char in_put[MAXLINE];
	char* token[MAX];
	int n=1;
	char* var1=getenv("PATH");
	// setenv("PATH");


	while(1)
	{
		front_end();
		// memset(in_put,'\0', MAXLINE);
		fgets(in_put,MAXLINE,stdin);
		if((token[0]=strtok(in_put,"\n\t")) == NULL)
			continue;
		while((token[n]=strtok(NULL,"\n\t"))!=NULL)
			n++;
		base(token);
		// prog_fork(token);

	}
	exit(0);
}