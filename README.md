# ft_script
42 - script - make typescript of terminal session


DESCRIPTION
     The script utility makes a typescript of everything printed on your ter-
     minal.  It is useful for students who need a hardcopy record of an inter-
     active session as proof of an assignment, as the typescript file can be
     printed out later with lpr(1).

     If the argument file is given, script saves all dialogue in file.  If no
     file name is given, the typescript is saved in the file typescript.

     If the argument command is given, script will run the specified command
     with an optional argument vector instead of an interactive shell.

     The following options are available:

     -a      Append the output to file or typescript, retaining the prior con-
             tents.

     -d      When playing back a session with the -p flag, do not sleep
             between records when playing back a timestamped session.

     -F pipe
             Immediately flush output after each write.  This will allow a
             user to create a named pipe using mkfifo(1) and another user may
             watch the live session using a utility like cat(1).

     -k      Log keys sent to the program as well as output.

     -p      Play back a session recorded with the -r flag in real time.

     -q      Run in quiet mode, omit the start, stop and command status mes-
             sages.

     -r      Record a session with input, output, and timestamping.

     -t time
             Specify the interval at which the script output file will be
             flushed to disk, in seconds.  A value of 0 causes script to flush
             after every character I/O event.  The default interval is 30 sec-


TUTORIAL & INFO:
http://rachid.koucha.free.fr/tech_corner/pty_pdip_fr.html

http://jdb.github.io/pty.html

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/e/ef/Termios-script-diagram.png/220px-Termios-script-diagram.png"/>
