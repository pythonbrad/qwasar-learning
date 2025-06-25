# Welcome to Quest Shell Screen
***

## Task

The task consisted to learn how to use the `screen` and `script` command.

## Description

The `screen` command is useful to handle multiple screen sessions.
While the `script` command allows to record the outputs of the executed commands. That is useful to record what we are doing.

## Installation

The `screen` command can be missing in your linux distribution and you will need to install it.
If you use debian, you can install it as follow.

```
sudo apt install screen
```

## Usage

Use the `script` command to record the output of the command that we will enter after.

```
mkdir -p ex00
screen ex00/my_first_screen.txt
```

Type the `screen` command to start managing multiple terminal session.

```
screen
```

Now, we will execute an idle program to test the multiple terminal session.

```
ping google.com
```

We noticed that the program in running without stop.
Press "ctrl+a" followed by "d" to detach the running program from the screen session.

Using `screen -ls`, we can consult the list of active screen sessions.

```
screen -ls
```

To reattach the previous program, you can use 

```
screen -r [session_id]
```

You will see the output of the previous `ping` command

If you consult your `ex00/my_first_screen.txt` file, you will see the outputs of the previous executed commands.

### The Core Team

Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
