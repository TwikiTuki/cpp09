NAME = PmergeMe
_SRC = main.cpp
_OBJ = $(_SRC: .cpp=.o)
SRC_DIR = ./
OBJ_DIR = ./objs/
SRC = $(addprefix $(SRC_DIR), $(_SRC))
OBJ = $(addprefix $(OBJ_DIR), $(_OBJ:.cpp=.o))
DEP = $(OBJ:.o=.d)

PPF = -std=c++98 -Wall -Werror -Wextra  #-fsanitize=address

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJ) 
	mkdir -p $(OBJ_DIR)
	c++ $(PPF) $(OBJ) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp Makefile
	mkdir -p $(OBJ_DIR)
	c++ $(PPF)  -MMD -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

prnt:
	@echo SRC $(SRC)
	@echo OBJ $(OBJ)
	@echo DEP $(DEP)
	@echo SRC_DIR $(SRC_DIR)
	@echo OBJ_DIR $(OBJ_DIR)

.PHONY: all clean fclean re
