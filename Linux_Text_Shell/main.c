#include "shell.h"


void display_history(int);
void write_out_cwd();
void write_to_file(short int*, short int*, short int*, char**);
void get_whats_in_file(short int*, short int*, short int*, char**);

char* get_shell_history();

int main(int argc, char **argv)
{
    short int flag = 1, counter = -1, turn = 0, to_twenty = -1;
    char **arg_his = malloc(sizeof(char*) * 20);
    char ***args;

    get_whats_in_file(&counter, &turn, &to_twenty, arg_his);

    if (argc > 1)
    {
        int script;
        
        if ((script = open(argv[1], O_RDONLY)) < 0)
        {
            write(STDERR_FILENO, "Error in main.c, cannot open script file.\n", 42);
            exit(EXIT_FAILURE);
        }

        unsigned char c;

        read(script, &c, 1);

        if (c == '#')
            while (read(script, &c, 1))
                if (c == '\n')
                    break;

        while (flag)
        {
            args = get_arguments(script);
            flag = execute(args);

            if (flag != -1)
                write_to_file(&counter, &turn, &to_twenty, arg_his);
        }
        close(script);
        
        for (int i = 0; arg_his[i]; i++)
            free(arg_his[i]);
        free(arg_his);

        return 0;
    }

    if (signal(SIGQUIT, display_history) == SIG_ERR)
    {
        write(STDERR_FILENO, "Error in main.c, signal error.\n", 31);
        exit(EXIT_FAILURE);
    }

    while (flag)
    {
        write_out_cwd();

        args = get_arguments(STDIN_FILENO);
        flag = execute(args);

        if (flag != -1)
            write_to_file(&counter, &turn, &to_twenty, arg_his);
    }

    for (int i = 0; arg_his[i]; i++)
        free(arg_his[i]);
    free(arg_his);

    return 0;
}

void display_history(int signum)
{
    int read_descriptor;
    char *shell_history = get_shell_history();

    if ((read_descriptor = open(shell_history, O_RDONLY | O_CREAT, 0777)) < 0)
    {
        write(STDERR_FILENO, "Error in main.c, cannot open shell history.\n", 44);
        exit(EXIT_FAILURE);
    }

    unsigned char c;

    write(STDOUT_FILENO, "\n", 1);
    while (read(read_descriptor, &c, 1))
        write(STDOUT_FILENO, &c, 1);
    
    close(read_descriptor);
    free(shell_history);
    write_out_cwd();
}

void write_out_cwd()
{
    char *user_name = getenv("USER");
    char cwd[MAX_PATH];

    if (!getcwd(cwd, sizeof(cwd)))
    {
        write(STDERR_FILENO, "Error in main.c, getcwd function.\n", 34);
        exit(EXIT_FAILURE);
    }

    write(STDOUT_FILENO, user_name, strlen(user_name));
    write(STDOUT_FILENO, ":", 1);
    write(STDOUT_FILENO, cwd, strlen(cwd));
    write(STDOUT_FILENO, "$ ", 2);
}

char *get_shell_history()
{
    char *home_dir = getenv("HOME");
    char *history = malloc(strlen(home_dir) + strlen("/shell_history") + 1);
    strcpy(history, home_dir);
    strcat(history, "/shell_history");

    return history;
}

void write_to_file(short int *counter, short int *turn, short int *to_twenty, char **arg_his)
{
    int write_descriptor;
    char *shell_history = get_shell_history();

    if ((write_descriptor = open(shell_history, O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
    {
        write(STDERR_FILENO, "Error in main.c, cannot open shell history.\n", 44);
        exit(EXIT_FAILURE);
    }

    *counter = (*counter + 1) % 20;
    if (*to_twenty == 19)
    {
        *turn = (*turn + 1) % 20;
    }
    
    if (*to_twenty < 19) (*to_twenty)++;
    
    free(arg_his[*counter]);
    arg_his[*counter] = get_line();
    for (short int i = *turn; i <= *to_twenty; i++)
    {
        write(write_descriptor, arg_his[i], strlen(arg_his[i]));
        write(write_descriptor, "\n", 1);
    }
        
    if (*turn)
    {
        for (short int i = 0; i < *turn; i++)
        {
            write(write_descriptor, arg_his[i], strlen(arg_his[i]));
            write(write_descriptor, "\n", 1);
        }
    }
    close(write_descriptor);
    free(shell_history);
}

void get_whats_in_file(short int *counter, short int *turn, short int *to_twenty, char**arg_his)
{
    int read_descriptor;
    char *shell_history = get_shell_history();
    if ((read_descriptor = open(shell_history, O_RDONLY | O_CREAT, 0777)) < 0)
    {
        write(STDERR_FILENO, "Error in main.c, cannot open shell history\n", 43);
        exit(EXIT_FAILURE);
    }

    unsigned char c;
    char *buffer = malloc(sizeof(char) * MAX_PATH / 8);
    int i = 0;

    read(read_descriptor, &c, 1);

    while(c)
    {
        buffer[i] = c;
        
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            *counter = (*counter + 1) % 20;

            if (*to_twenty == 19) 
            {
                *turn = (*turn + 1) % 20;
            }

            if (*to_twenty < 19) (*to_twenty)++;

            free(arg_his[*counter]);
            arg_his[*counter] = buffer;
            
            buffer = malloc(sizeof(char) * MAX_PATH / 8);
            i = 0;
            read(read_descriptor, &c, 1);
            if (c == '\n')
                break;
        }
        else
        {
            read(read_descriptor, &c, 1);
            i++;
        }
    }
    free(buffer);
    close(read_descriptor);
    free(shell_history);
}