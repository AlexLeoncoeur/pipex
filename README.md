# Pipex

## Introduction 🔗

Pipex is a project that simulates the behavior of shell pipelines using pipes in Unix-like operating systems. This implementation executes a series of commands, taking input from a file, processing it through multiple commands, and writing the output to another file.

## Table of Contents 📑

- [Introduction 🔗](#introduction-🔗)
- [Features 🌟](#features-🌟)
- [Requirements 📋](#requirements-📋)
- [Usage 💻](#usage-💻)
- [Normal vs. Bonus Pipex 📊](#normal-vs-bonus-pipex-📊)
- [Testing ✅](#testing-✅)

## Features 🌟

- Executes a series of commands using Unix pipes.
- Reads input from a specified file and writes output to another file.
- Handles multiple commands in sequence.
- Provides error handling for common issues like command not found.

## Requirements 📋

- A Unix-like operating system (Linux or macOS).
- A C compiler (gcc or clang).

## Usage 💻

### Basic
Run the `pipex` program with the following syntax:

```bash
./pipex infile cmd1 cmd2 outfile
```

For example:

```bash
./pipex infile "grep a" "wc -l" outfile
```
This command will execute `grep a` on `infile`, pipe the output to `wc -l`, and save the final result in `outfile`.

### Bonus
The `bonus` allows for here_doc and more commands to be used:

```bash
./pipex infile cmd1 cmd2 ... cmdn outfile
```

```bash
./pipex here\_doc LIMITER cmd1 cmd2 ... cmdn outfile
```

```bash
./pipex here\_doc . "cat" "grep hello" outfile
```


## Normal vs. Bonus Pipex 📊

### Normal Pipex

- **Basic Pipeline**: Executes a fixed number of commands with a single input file and a single output file.
- **Command Handling**: Handles commands using pipes and forks to create a simple linear pipeline.
- **Output File Behavior**: Overwrites the output file each time the program is run.

### Bonus Pipex

- **Here Document Support**: Allows the use of `here_doc` to take input directly from the command line, facilitating interactive input.
- **Unlimited Commands**: Capable of handling an indefinite number of commands, providing more flexibility and scalability.
- **Append Mode**: Supports appending to the output file instead of overwriting it, preserving previous output.

## Testing ✅

To verify the correctness of your solution, compare the output of your `pipex` program with the equivalent shell pipeline command:

```bash
< infile cmd1 | cmd2 > outfile
```

For example:

```bash
< infile ls -l | wc -l > outfile
```
