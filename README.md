<p align="center">
	<img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/adriapriego/minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/adriapriego/minishell" />
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/adriapriego/minishell?color=red" />
	<img alt="GitHub last commit (by committer)" src="https://img.shields.io/github/last-commit/adriapriego/minishell" />
	<img alt="MacOS compatibility" src="https://img.shields.io/badge/macOS-compatible-brightgreen.svg" />
</p>

<h3 align="center">Minishell, recreating bash. (42 school project)</h3>

  <p align="center">
    The aim of this project is to create a shell using bash (bourne-again shell) as reference.
    <br/>
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project
<img width="700" alt="minishell_screenshot" src="https://github.com/adriapriego/minishell/assets/19575860/82977658-8af7-4e6e-98bf-af69bb83e507">

**Minishell is a Unix shell** really similar to bash but with some reduced functionalities. The project is written from scratch in C.
Some of the functionalities are:
- Displays current directory when waiting for a new command.
- Working history of commands.
- Searches and launches the right executable (based on the PATH variable or using a
relative or an absolute path).
- Variable expansion of environment variables, tilde characater '~' and $?.
- Single and double quotes as bash would, single quotes prevent the shell from interpreting the metacharacters in the quoted sequence.
- Redirections:
	- '<' Redirects input.
	- '\>' Redirects output.
	- '\<<' + DELIMITER, reads the input until a line containing the
	delimiter is seen. It doesn’t update the history.
	- '\>>' Redirects output in append mode.

- Works with pipes '|'. The output of each command in the pipeline is connected to the input of the next command via a pipe.
- $? is updated with the exit code of the last executed command in the pipe.
- Handles signals ctrl-C, ctrl-D and ctrl-\ which behave like in bash.
- To finish, the following built-in commands were implemented from scratch:
	- **echo** with option -n
 	- **cd** with only a relative or absolute path
	- **pwd** with no options
	- **export** with no options
	- **unset** with no options
	- **env** with no options or arguments
	- **exit**
> [!NOTE]
> This project doesn't handle the following functionalities:
> - STDERR redirection like '2>' or STDERR + STDOUT redirection like '&>'.
> - Unclosed quotes. If quotes are left unclosed minishell will interpret there is a closing quote at the end of the command.
> - Commands ending with a pipe character '|'. Minishell will throw a syntax error on that case.
> - Logical operators like '&&' and '||'.
> - Special characters like '/' and ';'.
> - Wildcards '*'.


<!-- GETTING STARTED -->
## Getting Started
In order to run the program first clone the repository:
```bash
git clone git@github.com:adriapriego/minishell.git
```
Open the folder:
```bash
cd minishell/
```
Compile the program:
```bash
make
```
Run the program:
```bash
./minishell
```
> [!NOTE]
> Additionally the executable could be moved to a directory in the $PATH to make it work from anywhere in the computer typing 'minishell', like bash.

<!-- Authors -->
## Authors
This project is written by @ferri17 and me as part of 42 School core curriculum. I was mainly focused on the focused on the built-ins, expansor, and signals, while Ferran focused on the built-ins, expansor, and signals.
