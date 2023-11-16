## ```Pipes, Pipes, Pipes ...```
![Screenshot 2023-11-13 at 08 58 27](https://github.com/AshParker19/42_pipex/assets/117525743/13c1076b-a26f-4d78-9b84-2e8e5f96c13d)

---

_This project is the introduction to the pipes in C. The goal is to create a program that will read the content of a file, rediect the output to another program which will send it to the next program and so on. The last program will write the result in a file._

## ```The functions that I used are:```
| Function | Functionality |
| --- | --- |
| ```access``` | check real user's permissions for a file |
| ```fork``` | create a child process |
| ```execve``` | execute program |
| ```waitpid``` | wait for process to change state |
| ```pipe``` | create pipe |
| ```dup2``` | duplicate a file descriptor and redirect IO|
| ```open``` | open and possibly create a file |
| ```close``` | close a file descriptor |

---

## ```The new concepts of this project are```:

### `Environment and PATH`

The environment is a set of system variables that are passed to a program when it is started. Each variable is a string with a name and a value. The environment is inherited by child processes from their parent. The environment is stored in a global variable ```char **env```.
It contains all the needed information to execute a program. For example, the ```PATH``` variable contains the paths to the binaries that can be executed.
Example:
```command ls```
The shell will search for the ```ls``` binary in the paths contained in the ```PATH``` variable. If it finds it, it will execute it. If not, it will return an error.

### ```Processes and forks```
Process is an instance of a program. When we start our computers we start the process, when we open the terminal we start the process, when we open the browser we start the process. Each process has a unique identifier called PID (process identifier). We can artificially create a process with the ```fork``` function. The ```fork``` function creates a child process that is an exact copy of the parent process. The child process has its own PID and its own memory space. The parent process can communicate with the child process through pipes.

### ```Execve```
`execve` is fucntion which gives as a possibity to execute a program within the other program. It takes 3 arguments: `path`, `av`, `env`.
* `path` is a path to the program that we want to execute, we can use `PATH` variable to find the program in the system.
* `av` is NULL-terminated array of strings which contains the arguments for the program that we want to execute.
    if our input was `ls -l -a` then `av` will be `["ls", "-l", "-a", NULL]`
*  `env` is NULL-terminated array of strings which contains the environment variables for the program that we want to execute.
    We get them via `main` fucntion as a third argument.
    `int main(int ac, char **av, char **env)`

### ```Pipes```
As it was already said, pipes are the way to communicate between processes. A pipe is a unidirectional data channel. It has two ends: the read end and the write end. The read end is used to read data from the pipe and the write end is used to write data to the pipe. The pipe is created with the ```pipe``` function. The ```pipe``` function takes as an argument an array of two integers. The first integer is the read end and the second integer is the write end. The ```pipe``` function returns 0 if it was successful and -1 if it failed.
When we fork, we duplicate all the data related to the parent process including the file descriptors. So, if we create a pipe before the fork, both the parent and the child process will have access to the pipe. The parent process will close the read end of the pipe and the child process will close the write end of the pipe. 
![Screenshot 2023-11-13 at 09 31 08](https://github.com/AshParker19/42_pipex/assets/117525743/15da8c9d-07a8-4752-855e-2340fef0caca)

### ```Duplicates and redirections```
The way to redirect the content of the file to the command and then output of the command to another command is to duplicate the file descriptors and redirect the IO using he ```dup2``` function. The ```dup2``` function takes as an argument the file descriptor to duplicate and the file descriptor to redirect to. The ```dup2``` function returns the new file descriptor if it was successful and -1 if it failed. The ```open``` function opens a file and returns the file descriptor. 

_In a case of opening the `infile` the program depends on the funcion `open`:_
The ```open``` function takes as an argument the path to the file and the flags. The ```open``` function returns the file descriptor if it was successful and -1 if it failed. The flags are the following:
| Flag | Functionality |
| :---: | :--- |
| ```O_RDONLY``` | open for reading only |
| ```O_WRONLY``` | open for writing only |
| ```O_RDWR``` | open for reading and writing |
| ```O_CREAT``` | create file if it does not exist |
| ```O_TRUNC``` | truncate file to zero length |
| ```O_APPEND``` | append to file |

**After we finished all the fd's manipulations, we need to close them using `close`.**
---

## `The bonus:`
The bonus consists of 2 parts:
1. `multiple pipes`
2. `heredoc`

### `Multiple pipes`
The idea is the same as for the mandatory part, but instead of 1 pipe we have multiple pipes. The number of pipes is equal to the number of commands minus 1. The first command reads from the file and writes to the first pipe. The second command reads from the first pipe and writes to the second pipe. The last command reads from the last pipe and writes to the file. The commands in the middle read from the previous pipe and write to the next pipe. The parent process closes all the pipes and waits for the child processes to finish.

### `Heredoc`
The `heredoc` is a tool which allows to write a multiline string text in the terminal. The `heredoc` is used in the shell scripts. It is written between the ```<<``` and ```LIMITER``` keywords. The `heredoc` is used in the following way:
```command << LIMITER```

![Screenshot 2023-11-13 at 09 50 08](https://github.com/AshParker19/42_pipex/assets/117525743/bb98d030-f3c0-4edc-a2f7-9d8953e5c3b9)

_We can use heredoc with multiple commands and pipes._

In terms of pipex, when we have the `heredoc` in the command, the output of the last command will be appended to the `outfile`, so we use `open`
with `O_APPEND` flag to append the output to the file.

---

## `IMPORTANT!!!`
As it was mentioned early, we need to close all the used file descriptors at the end of the program. If we don't close them, we will have a memory leak. The memory leak is a situation when the program allocates memory and doesn't free it. 
In this case a very weln known tool `valgrind` will help us to find the leaks.
We used to use `valgrind` to find leaks related to dynamic memory allocation. But in this case we need to use `valgrind` to find leaks related to file descriptors.
`valgrind --track-fds=yes` is the flag to check the state of all the fd's in the program.
At the end we can only have 3 opened fd's: `0` - `stdin`, `1` - `stdout`, `2` - `stderr`, all the other ones are considered as leaks.

---

## ```How to use it```
1. Clone the repository with the command ```git clone```
2. Compile the program with the command ```make```
3. Run the program with the command ```./pipex infile cmd1 cmd2 outfile``` where ```infile``` is the file to read, ```cmd1``` is the first command to execute, ```cmd2``` is the second command to execute and ```outfile``` is the file to write.

---

### ```Recources:```
- [**Unix Processes in C**](https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY&si=x-rILlIutnl-Okes)
- [**Pipes in C**](https://youtu.be/uHH7nHkgZ4w?si=YVMnzdPH-JNMdFRT)
- [**Environment and PATH**](https://www.geeksforgeeks.org/environment-variables-in-linux-unix/)
- [**File descriptors**](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
