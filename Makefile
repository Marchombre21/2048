NAME := 2048

INCLUDE := includes/

BUILD_DIR := .build

RM := rm -f

CFLAGS := -Wall -Werror -Wextra

LLIB := -lncurses

FINCLUDE := -I $(INCLUDE)

DEPFLAGS := -MMD -MP

SRC_FILES := main.c\

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

.PHONY: all clean fclean re

-include $(DEPS)
