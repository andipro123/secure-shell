all: my_shell
my_shell: authenticate.o execArgs.o parser.o builtInCommands.o shell_util.o my_shell.o color.o
	gcc authenticate.o execArgs.o parser.o builtInCommands.o shell_util.o my_shell.o color.o -o my_shell -lreadline
clean:
	rm *.o
authenticate.o: authenticate.c
	gcc -c authenticate.c -Wall
execArgs.o: execArgs.c
	gcc -c execArgs.c -Wall
parser.o: parser.c shell_util.o builtInCommands.o
	gcc -c parser.c -Wall
builtInCommands.o: builtInCommands.c shell_util.o
	gcc -c builtInCommands.c -Wall
shell_util.o: shell_util.c authenticate.o
	gcc -c shell_util.c -Wall
my_shell.o: my_shell.c builtInCommands.o shell_util.o execArgs.o authenticate.o parser.o
	gcc -c my_shell.c -Wall
color.o: color.c
	gcc -c color.c -Wall

