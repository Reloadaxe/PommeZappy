SRC			=	Connection.cpp \
				FontManager.cpp \
				Player.cpp \
				Map.cpp \
				main.cpp

OBJ			=	$(SRC:%.cpp=%.o)

NAME		=	client

CXX			=	g++
CXXFLAGS	=	-Wall -Wextra -Wpedantic -Werror -std=c++14

RM			=	rm -rf

IPATH		= 	-ISFML/include -ISockpp/include

LPATH		= 	-LSFML/lib -LSockpp/lib

LIBRARIES	= 	-lsfml-graphics -lsfml-window -lsfml-system -lsockpp

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) $(IPATH) $(LPATH) $(LIBRARIES) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re