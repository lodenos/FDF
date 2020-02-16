CC = clang
# FLAGS = -Wall -Werror -Wextra -Weverything -Wno-padded
INCLUDE = -I ./inc -I ./libft/inc -I ./SDL2-2.0.10/include
LIB = -L ./libft/ -lft -L ./SDL2-2.0.10/build/.libs/ -lSDL2
NAME = fdf.out
OBJ = $(addsuffix .o, $(basename $(SRC)))
SRC = \
	./src/main.c \
	./src/free_environment.c \
	./src/command_line_arguments.c \
\
	./src/devices/window/device_window_init.c \
	./src/devices/window/device_window_present.c \
\
	./src/engine/engine_FDF.c \
\
	./src/events/events_manager.c \
\
	./src/parser/parcer_map.c

all: $(NAME)
################################################################################
# Create Executable
################################################################################
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(LIB) $(OBJ) -o $(NAME)
################################################################################
# Compiling Source
################################################################################
$(OBJ): %.o: $(basename $@)%.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
################################################################################
# Clean *.o
################################################################################
	rm -f $(OBJ)

fclean: clean
################################################################################
# Full clean *.o & binairy
################################################################################
	rm -f $(NAME)

re: fclean all
################################################################################
# Full clean *.o & binairy & re-build
################################################################################
