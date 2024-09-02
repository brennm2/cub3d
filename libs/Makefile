NAME = libft.a

AR = ar
ARFLAGS = rcs

CC = cc
CCFLAGS = -Wall -Werror -Wextra

RM = rm
RMFLAGS= -f

OBJ = ft_isalnum.o \
	ft_isalpha.o \
	ft_isascii.o \
	ft_isdigit.o \
	ft_isprint.o \
	ft_memset.o \
	ft_strchr.o \
	ft_strlcat.o \
	ft_strlcpy.o \
	ft_strlen.o \
	ft_strncmp.o \
	ft_strrchr.o \
	ft_tolower.o \
	ft_toupper.o \
	ft_bzero.o \
	ft_memcpy.o \
	ft_memmove.o \
	ft_memchr.o \
	ft_memcmp.o \
	ft_strnstr.o \
	ft_atoi.o	\
	ft_strdup.o \
	ft_calloc.o	\
	ft_putchar_fd.o \
	ft_putstr_fd.o \
	ft_putendl_fd.o \
	ft_putnbr_fd.o \
	ft_substr.o \
	ft_strjoin.o \
	ft_strtrim.o \
	ft_split.o \
	ft_strmapi.o \
	ft_striteri.o \
	ft_itoa.o \
	ft_is_c.o \
	ft_is_d.o \
	ft_is_s.o \
	ft_is_u.o \
	ft_is_x.o \
	ft_is_xup.o \
	ft_is_ptr.o \
	ft_printf.o \
	get_next_line.o



OBJ_BONUS = ft_lstnew_bonus.o \
	ft_lstadd_front_bonus.o \
	ft_lstlast_bonus.o \
	ft_lstsize_bonus.o \
	ft_lstadd_back_bonus.o \
	ft_lstdelone_bonus.o \
	ft_lstclear_bonus.o \
	ft_lstiter_bonus.o \
	ft_lstmap_bonus.o


all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	$(RM) $(RMFLAGS) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ) $(OBJ_BONUS)

re: fclean all
