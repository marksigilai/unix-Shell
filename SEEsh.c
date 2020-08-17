#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void sheesh_loop();
char* sheesh_readline();
char** sheesh_splitline();
void sheesh_execute();
void cd();
void help();
void perform_exit();
void unset();
void set();
void other_function();
extern char **environ;
void pwd();



int main(int argc, char **argv){

        sheesh_loop();

}
void sheesh_loop(){

    char lines[50];
    FILE *fptr;
    char* input = (char*) malloc(sizeof(char*)*50);
    char** tokenized;

    //if the rc file exists
    if((fptr = fopen(".SEEshrc","r")) != NULL){
        while(fgets(lines, 100, fptr)){
            //lines contains a command from file
            printf("? %s", lines);
            //split into commands stored in tokenized
            tokenized = sheesh_splitline(lines);
            //execute them
            sheesh_execute(tokenized);
        }
        fclose(fptr);
    }

    while (!feof(stdin)) {
        printf(">  ");
        //read
        input = sheesh_readline();
        if(strcmp(input, "\n") == 0){
            continue;
        }
        //split
        tokenized = sheesh_splitline(input);
        //execute
        sheesh_execute(tokenized);

    }
    free(input);

}
char* sheesh_readline(char* input){
    fgets(input, 512, stdin);
    return input;
}
char **sheesh_splitline(char* input) {
    char **tokenized = (char**)malloc(sizeof(char[50]));
    char* token;
    int i = 0;
    if(!tokenized){
        printf("failed");
        return tokenized;
    }
    token = strtok(input, " \n");
    while (token != NULL) {
        tokenized[i++] = token;
        token = strtok(NULL, " \n");
    }
    //printf("%s\n", tokenized[4]);
    tokenized[i] = NULL;
    return tokenized;
}
void sheesh_execute(char** tokenized){
    if(strcmp(&(*tokenized[0]), "cd" ) == 0){
        cd(&(*tokenized[1]));
    }
    else if(strcmp(&(*tokenized[0]), "help" ) == 0){
        help();
    }
    else if(strcmp(&(*tokenized[0]), "exit" ) == 0){
        perform_exit();
    }
    else if(strcmp(&(*tokenized[0]), "set" ) == 0){
        set(&(*tokenized[1]), &(*tokenized[2]));
    }
    else if(strcmp(&(*tokenized[0]), "unset" ) == 0){
        unset(&(*tokenized[1]));
    }
    else if(strcmp(&(*tokenized[0]), "pwd" ) == 0){
        pwd();
    }
    else{
        other_function((tokenized));
    }
}
void cd(char directory[]){
    if(directory == NULL){
        printf("No directory has been given\n");
    }else{
        if (chdir(directory) != 0) {
            printf("Could not find directory\n");
        }
    }
};
void help(){
    printf("These are the built in commands:\n");
    char *all_commands[] = { "cd - change a directory", "pwd - list the present directory",
                             "help - lists all the commands and explains how to use them", "exit - closes the shell", "set - set var [value]\n sets environment variables to the value specified\n",
                             "unset - destroys the specified environment variable\n" };
    for(int i = 0; i < 6; i++){
        printf("%s\n", all_commands[i]);
    }
};
void perform_exit(){
    printf("Exiting...\n");
    exit(0);
};
void unset(char var[]){
    if(unsetenv(var) != 0){
        printf("Error %s\n", strerror(errno));
    }
};
void set(char var[], char value[]){
    if(var == NULL && value == NULL){
        int i = 0;
        while(environ[i]) {
            printf("%s\n", environ[i++]);
        }
    }else{
        if(setenv(var, value, 1) != 0){
            printf("Error %s\n", strerror(errno));
        }
    }
};
void pwd(){
    char buf[512];
    printf("%s\n", getcwd(buf, 512));
}
void other_function(char **tokenized)
{
    pid_t pid;
    int status;
    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(tokenized[0], tokenized) == -1) {
            perror("error ");
        }else{
            printf("Done!");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

}