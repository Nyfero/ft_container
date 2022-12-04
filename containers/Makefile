#    Colors
GREY = \e[90m
RED = \e[91m
GREEN = \e[92m
YELLOW = \e[93m
BLUE = \e[34m
PURPLE = \e[95m
CYAN = \e[96m
END = \e[39m

#    Showing command
DISP = TRUE

ifeq ($(DISP),TRUE)
    HIDE =
else
    HIDE = @
endif

#	Includes
CLASS_PATH = class

CLASS = $(addprefix $(CLASS_PATH)/, stack.hpp vector.hpp map.hpp iterator_traits.hpp vector_iterators.hpp \
	reverse_iterator.hpp enable_if.hpp equal.hpp is_integral.hpp lexicographical_compare.hpp \
	utils.hpp map_iterators.hpp)

#    Files
SRCS_PATH = srcs


FILES = main.cpp utils.cpp stack_test.cpp vector_test.cpp map_test.cpp

SRCS = $(addprefix $(SRCS_PATH)/, $(FILES))

#    Compilation
NAME = ft_containers

STD_NAME = std_containers

CXX = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm -rf

OBJS_PATH = objs/

STD_OBJS_PATH = objs_std/

OBJS = $(patsubst $(SRCS_PATH)%.cpp,	$(OBJS_PATH)%.o,	$(SRCS))

STD_OBJS = $(patsubst $(SRCS_PATH)%.cpp,    $(STD_OBJS_PATH)%.o,    $(SRCS))

#    Rules
all: $(NAME) $(STD_NAME)

ft: $(NAME)

std: $(STD_NAME)

$(NAME): $(OBJS_PATH) $(OBJS) $(CLASS)
	@ echo "$(BLUE)\n         ***Make $(NAME) ***\n$(END)"
	$(HIDE) $(CXX) $(CFLAGS) $(OBJS) -o $(NAME)
	@ echo "$(GREEN)\n        ---$(NAME) created ---\n$(END)"

$(STD_NAME): $(STD_OBJS_PATH) $(STD_OBJS) $(CLASS)
	@ echo "$(BLUE)\n         ***Make $(STD_NAME) ***\n$(END)"
	$(HIDE) $(CXX) $(CFLAGS) $(STD_OBJS) -o $(STD_NAME)
	 @ echo "$(GREEN)\n        ---$(STD_NAME) created ---\n$(END)"

$(OBJS_PATH):
	$(HIDE) mkdir -p $(OBJS_PATH)

$(STD_OBJS_PATH):
	$(HIDE) mkdir -p $(STD_OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp $(CLASS) Makefile
	$(HIDE) $(CXX) $(CFLAGS) -c $< -o $@
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"

$(STD_OBJS_PATH)%.o: $(SRCS_PATH)%.cpp $(CLASS) Makefile
	$(HIDE) $(CXX) $(CFLAGS) -D STD -c $< -o $@
	@ echo "$(GREEN)[ OK ]$(END) $(CYAN)${<:.s=.o}$(END)"

diff: $(NAME) $(STD_NAME)
	@./$(NAME) > $(NAME).txt
	@./$(STD_NAME) > $(STD_NAME).txt
	-@diff -ys $(NAME).txt $(STD_NAME).txt
	@rm -rf $(NAME).txt $(STD_NAME).txt

clean:
	$(HIDE) $(RM) $(OBJS_PATH)
	$(HIDE) $(RM) $(STD_OBJS_PATH)
	@ echo "$(PURPLE)\n        *** Clean objects ***\n$(END)"

fclean: clean
	$(HIDE) $(RM) $(NAME)
	$(HIDE) $(RM) $(STD_NAME)
	@ echo "$(RED)\n        *** Remove $(NAME) ***\n$(END)"

re: fclean all

.PHONY: all clean fclean re diff ft std
