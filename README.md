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

### `Environment`

The environment is a set of system variables that are passed to a program when it is started. Each variable is a string with a name and a value. The environment is inherited by child processes from their parent. The environment is stored in a global variable ```char **env```.
It contains all the needed information to execute a program. For example, the ```PATH``` variable contains the paths to the binaries that can be executed.
Example:
```command ls```
The shell will search for the ```ls``` binary in the paths contained in the ```PATH``` variable. If it finds it, it will execute it. If not, it will return an error.


### ```Processes and forks```
Process is an instance of a program. When we start our computers we start the process, when we open the terminal we start the process, when we open the browser we start the process. Each process has a unique identifier called PID (process identifier). We can artificially create a process with the ```fork``` function. The ```fork``` function creates a child process that is an exact copy of the parent process. The child process has its own PID and its own memory space. The parent process can communicate with the child process through pipes.


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

---

## ```How to use it```
1. Clone the repository with the command ```git clone```
2. Compile the program with the command ```make```
3. Run the program with the command ```./pipex infile cmd1 cmd2 outfile``` where ```infile``` is the file to read, ```cmd1``` is the first command to execute, ```cmd2``` is the second command to execute and ```outfile``` is the file to write.

---


