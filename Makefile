NAME := 2048

INCLUDE := includes/

BUILD_DIR := .build

RM := rm -f

CFLAGS := -Wall -Werror -Wextra

LLIB := -lncurses

FINCLUDE := -I $(INCLUDE)

DEPFLAGS := -MMD -MP

CLANG_FLAGS = -Wall -Wextra -Werror -Wpedantic \
  -Wshadow -Wconversion -Wsign-conversion -Wcast-qual -Wstrict-prototypes \
  -Wmissing-prototypes -Wpointer-arith -Wundef -Wwrite-strings \
  -Winit-self -Wswitch-enum -Wformat=2 -Wunreachable-code \
  -g3 -O0 -fno-omit-frame-pointer \

SRC_FILES := main.c\
	utils_display.c\
	utils.c\
	atoi.c\
	game.c\
	itoa.c\
	score_management.c\
	strlen.c \
	ft_bzero.c \
	ft_split.c \
	ft_substr.c

OBJ := $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
DEPS := $(patsubst %.o, %.d, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(FINCLUDE) $(OBJ) -o $@ $(LLIB)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(FINCLUDE) $(DEPFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@$(RM) $(OBJ) $(DEPS)
	@rm -rf $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

lint:
			clang $(CLANG_FLAGS) $(SRC_FILES) -Iincludes


.PHONY: all clean fclean re

-include $(DEPS)
