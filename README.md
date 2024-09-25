# OS-Assignment-2

Implementation: 
--------------

The code implements a Unix Simple Shell that waits for user input, executes commands provided in the user input, and then repeats until terminated using ctrl-c. It supports handling commands, managing background and foreground processes, and handling pipes. The shell also maintains a history of executed commands. 

1. A struct has been implemented to keep track of all commands in history with various attributes.
2. Signals have been handled. (Ctrl+c to exit the session)
3. Shell loop runs infinitely until given an exit signal.
4. The inputted command has been first stripped of any leading or following white spaces.
5. It has then been searched for any pipes present, and has been dealt with accordingly in various functions.
6. (BONUS) Background processes have been handled as and when needed.
7. Error handling has been implement wherever vital.

Limitations:
------------
1. cd.. command: we cannot exit the primary directory. 

Contributions:
------------
Aakanksha(2023004): History implementation, Signal handling, Trim white spaces, Create process & run, History displays, Error handling

Palak(2023363): Shell loop, Reading user input, Pipe command, Launch command, Error handling


Link to repository: https://github.com/aakanksha-27/OS-Assignment-2
