# sample Makefile that you can quickly adapt to your needs
# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11

# set the name of the executable file to compile here
program=wwbot_booking

# list object files needed to compile the program
objects=wwbot_booking.o Free.o List.o 

# arguments to run the program
# args = -c inputA.txt -b 102400

# this makes the program. It's the first rule so it will be executed if you give just 'make'
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program)

# list .h dependencies for each .o (dependency on .c is automatically set by make!)
wwbot_booking.o : Interface.h
Free.o : Interface.h
List.o : List.h

# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects) 

# run the program with 'make run'. Sometimes useful to avoid rewriting long commands.
run: $(program)
	./$(program) 

valgrind: $(program)
	valgrind --track-origins=yes ./$(program) 