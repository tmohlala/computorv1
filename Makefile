CXX = g++

EXEC = computor

CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -g

SRC   = Computorv1.cpp\
		main.cpp\
		Term.cpp\

OBJ   = $(SRC:%.cpp=%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^
	
clean:
	@rm -rf $(OBJ)
	@echo "o files removed"

fclean: clean
	@rm -rf $(EXEC)
	@echo "executable removed"

re: fclean all