CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
SRCS = main.cpp BitcoinExchange.cpp
NAME = bitcoin

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all