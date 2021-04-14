#include "shell.h"

short int in_the_background, end_of_file = 0;
char *line;

short int change_dir(char***);

char*** get_arguments(int input)
{
    unsigned char c;
    int buffer_size = BUF_SIZE;
    char *word = malloc(sizeof(char) * buffer_size);
    char **arg = malloc(sizeof(char*) * buffer_size);
    char ***args = malloc(sizeof(char**) * buffer_size);
    short int i = 0, j = 0, q = 0, z = 0;
    line = malloc(sizeof(char) * MAX_PATH);
    in_the_background = 0;

    read(input, &c, 1);

    while (c != '\n')
    {
        word[i++] = line[z++] = c;

        if (i >= buffer_size)
        {
            word = realloc(word, buffer_size + BUF_SIZE);

            if (!word)
            {
                write(STDERR_FILENO, "Can't reallocate memory in shell.c, get_arguments.\n", 51);
                exit(EXIT_FAILURE);
            }
        }

        if (!read(input, &c, 1))
        {
            end_of_file = 1;
            break;
        }

        if (c == ' ')
        {
            word[i] = '\0';
            line[z++] = c;
            arg[j++] = word;

            if (j >= buffer_size)
            {
                arg = realloc(arg, (buffer_size + BUF_SIZE) * sizeof(char*));

                if (!arg)
                {
                    write(STDERR_FILENO, "Can't reallocate memory in chell.c, get_arguments.\n", 51);
                    exit(EXIT_FAILURE);
                }
            }

            word = malloc(sizeof(char) * buffer_size);
            i = 0;
            read(input, &c, 1);

            if (c == '|')
            {
                arg[j] == NULL;
                args[q++] = arg;
                arg = malloc(sizeof(char*) * buffer_size);
                j = 0;
                read(input, &c, 1);
                read(input, &c, 1);
            }
        }

        if (c == '~')
        {
            char *home = getenv("HOME");
            for (int d = 0; d < strlen(home); d++)
            {
                word[i++] = home[d];
            }
            if (!read(input, &c, 1))
                break;
        }
    }

    if (word[i - 1] == '&')
        in_the_background = 1;
    else
    {
        word[i] = line[z] = '\0';
        arg[j++] = word;
        arg[j] = NULL;
    }
    
    args[q] = arg;
    return args;
}

short int execute(char ***args)
{
    if (!strcmp((*args)[0], "\0"))
        return -1;
    if (!strcmp((*args)[0], "cd"))
    {
        return change_dir(args);
    }
    if (!strcmp((*args)[0], "exit"))
    {
        return 0;
    }

    pid_t pid;
    int pipe_fds[2];
    int fd_in = 0;

    while (*args != NULL)
    {
        pipe(pipe_fds);

        if ((pid = fork()) < (pid_t)0)
        {
            write(STDERR_FILENO, "In shell.c, fork failed.\n", 25);
            exit(EXIT_FAILURE);
        }
        else if (pid == (pid_t)0)
        {
            dup2(fd_in, STDIN_FILENO);

            if (*(args + 1) != NULL)
                dup2(pipe_fds[1], STDOUT_FILENO);
            else
            {
                for (int i = 0; (*args)[i]; i++)
                {
                    if (!strcmp((*args)[i], ">>"))
                    {
                        int redirect_to;
                        if ((redirect_to = open((*args)[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
                        {
                            write(STDERR_FILENO, "Error in shell.c, cannot open redirect file.\n", 45);
                            exit(EXIT_FAILURE);
                        }
                        dup2(redirect_to, STDOUT_FILENO);
                        close(redirect_to);
                        (*args)[i] = NULL;
                    }
                }
            }
            
            close(pipe_fds[0]);
            execvp((*args)[0], *args);
            perror("Shell");
            exit(EXIT_FAILURE);
        }
        else
        {
            if (!in_the_background)
                waitpid(pid, NULL, 0);
            close(pipe_fds[1]);
            fd_in = pipe_fds[0];
            args++;
        }
    }
    if (end_of_file)
        return 0;
    else    
        return 1;
}

short int change_dir(char ***args)
{
    if ((*args)[2] != NULL)
        write(STDERR_FILENO, "cd usage: cd <path>\n", 20);
    else if ((*args)[1] == NULL)
    {
        if (chdir(getenv("HOME")))
            perror("Shell cd");
    }
    else if (chdir((*args)[1]))
        perror("Shell cd");

    return 1;                    
}

char *get_line()
{
    return line;
}