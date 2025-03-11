<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/minishelle.png" alt="Minishell 42 project badge"/>
</p>

## Description
**Minishell** is a project from 42 School that involves creating a minimalistic shell that can execute commands, manage processes, and handle user input, similar to Bash.

## Features
- Execute commands found in system paths
- Handle built-in commands like `cd`, `echo`, `pwd`, `export`, `unset`, `env`, and `exit`
- Manage process execution with forking and pipes
- Handle environment variables
- Implement redirections (`<`, `>`, `>>`)
- Support command history
- Handle signals (CTRL+C, CTRL+D, CTRL+\)

## Compilation
To compile the project, use:
```sh
make
```
This will generate the `minishell` executable.

## Usage
Run the shell by executing:
```sh
./minishell
```
You can then enter commands as you would in a standard shell.

## Example Usage
```sh
$ echo "Hello, World!"
Hello, World!
$ ls -l
$ cd ..
$ pwd
```

## Built-in Commands
- `echo`: Print messages to the terminal
- `cd`: Change the current directory
- `pwd`: Print the current directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: Display environment variables
- `exit`: Exit the shell

## Signal Handling
- `CTRL+C` (SIGINT): Interrupt the current command
- `CTRL+D`: Exit the shell
- `CTRL+\` (SIGQUIT): Quit running processes

## Bonus Features
- Command history navigation
- Advanced redirections and pipes
- Wildcard expansions
- Improved error handling

## Possible Improvements
- Add support for job control
- Implement scripting capabilities
- Improve performance and memory management

## License
This project is free to use and modify according to the 42 School guidelines.

---
