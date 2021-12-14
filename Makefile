CC		= g++ 
CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wc++0x-compat -Wc++11-compat -Wc++14-compat
CFLAGS += -Waggressive-loop-optimizations -Walloc-zero -Walloca -Walloca-larger-than=8192 -Warray-bounds 
CFLAGS += -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy 
CFLAGS += -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security 
CFLAGS += -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline 
CFLAGS += -Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd 
CFLAGS += -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wrestrict -Wshadow -Wsign-promo 
CFLAGS += -Wstrict-null-sentinel -Wstrict-overflow=2 -Wstringop-overflow=4 
CFLAGS += -Wsuggest-attribute=noreturn -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum 
CFLAGS += -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-suffix 
CFLAGS += -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -Waligned-new 
CFLAGS += -Walloc-size-larger-than=1073741824 -Walloc-zero -Walloca -Walloca-larger-than=8192 -Wcast-align=strict 
CFLAGS += -Wdangling-else -Wduplicated-branches -Wformat-overflow=2 -Wformat-truncation=2 -Wmissing-attributes 
CFLAGS += -Wmultistatement-macros -Wrestrict -Wshadow=global -Wsuggest-attribute=malloc -fcheck-new 
CFLAGS += -fsized-deallocation -fstrict-overflow 
CFLAGS += -flto-odr-type-merging -fno-omit-frame-pointer -I include
BIN		= asteroids 
RM		= rm -rf
HDR		= include 
SRC		= src
OBJ		= obj
HDRS	= $(wildcard $(HDR)/*.hpp)
SRCS	= $(wildcard $(SRC)/*.cpp)
OBJS	= $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

all:		$(BIN)

$(BIN):		$(HDRS) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system -o $(BIN)

$(OBJ)/%.o:	$(SRC)/%.cpp
			mkdir -p $(OBJ)
			$(CC) $(CFLAGS) -c $< -o $@

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(BIN)

re:			fclean all

.PHONY:		all clean fclean re
