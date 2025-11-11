C_FILES = project.c func/train.c func/login.c
OBJ_FILES = project.o func/train.o func/login.o

all: $(OBJ_FILES)
	gcc $(OBJ_FILES) -o train_ticket.exe
	clear
	@echo Train Ticket Application has been compiled.

%.o: %.c
	gcc -c $< -o $@

# $< -> first dependency -> .c
# $@ -> first target -> .o

run: all
	./train_ticket.exe

clean:
	rm -f $(OBJ_FILES) train_ticket.exe

