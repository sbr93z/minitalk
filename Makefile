RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
RESET   := \033[0m
BLUE:= \e[0;34m

NAME_SERVER= server
NAME_CLIENT= client
CC = cc
CFLAGS = -Wall -Werror -Wextra
MAKE= make
LIBFT_NAME= libft.a
LIBFT_DIR= ./libft

# Regular 
SRCS_DIR=./src
SRCS=$(SRCS_DIR)/server.c
QQQQ=$(SRCS_DIR)/client.c
OBJS_DIR=objs
OBJS=$(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(LIBFT_DIR)/$(LIBFT_NAME) $(NAME_SERVER) $(NAME_CLIENT)
	@echo  "$(GREEN)[INFO] Compilation completed successfully.$(RESET)"
	@echo "$(RESET)"
	@echo " .----------------.  .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  .----------------.  .----------------. "
	@echo "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |"
	@echo "| | ____    ____ | || |     _____    | || | ____  _____  | || |     _____    | || |  _________   | || |      __      | || |   _____      | || |  ___  ____   | |"
	@echo "| ||_   \  /   _|| || |    |_   _|   | || ||_   \|_   _| | || |    |_   _|   | || | |  _   _  |  | || |     /  \     | || |  |_   _|     | || | |_  ||_  _|  | |"
	@echo "| |  |   \/   |  | || |      | |     | || |  |   \ | |   | || |      | |     | || | |_/ | | \_|  | || |    / /\ \    | || |    | |       | || |   | |_/ /    | |"
	@echo "| |  | |\  /| |  | || |      | |     | || |  | |\ \| |   | || |      | |     | || |     | |      | || |   / ____ \   | || |    | |   _   | || |   |  __'.    | |"
	@echo "| | _| |_\/_| |_ | || |     _| |_    | || | _| |_\   |_  | || |     _| |_    | || |    _| |_     | || | _/ /    \ \_ | || |   _| |__/ |  | || |  _| |  \ \_  | |"
	@echo "| ||_____||_____|| || |    |_____|   | || ||_____|\____| | || |    |_____|   | || |   |_____|    | || ||____|  |____|| || |  |________|  | || | |____||____| | |"
	@echo "| |              | || |              | || |              | || |              | || |              | || |              | || |              | || |              | |"
	@echo " '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |"
	@echo " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' "
	@echo "$(RESET)"

$(LIBFT_DIR)/$(LIBFT_NAME):
	@echo "\n${YELLOW}Making libft...${RESET}"
	@cd $(LIBFT_DIR) && $(MAKE) all
	@echo "${GREEN}Done.${RESET}"

$(NAME_SERVER): $(LIBFT_DIR)/$(LIBFT_NAME) $(OBJS)
	@echo "\n${YELLOW}Compiling minitalk...${RESET}"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME_SERVER) $(LIBFT_DIR)/$(LIBFT_NAME)
	@echo "${GREEN}Server ready to use !${RESET}"

$(NAME_CLIENT): $(LIBFT_DIR)/$(LIBFT_NAME) $(QQQQ)
	@echo "\n${YELLOW}Compiling minitalk...${RESET}"
	$(CC) $(CFLAGS) $(QQQQ) -o $(NAME_CLIENT) $(LIBFT_DIR)/$(LIBFT_NAME)
	@echo "${GREEN}Client ready to use !${RESET}"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@echo -n "${BLUE}$@ ${RESET}" 
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "${YELLOW}Cleaning minitalk object...${RESET}"
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@echo "${RED}File cleaned: $(OBJS)${RESET}"
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@echo "${GREEN}Done.${RESET}"

fclean: clean
	@echo "${YELLOW}Cleaning minitalk program...${RESET}"
	@rm -f $(NAME_SERVER) $(NAME_CLIENT)
	@echo "${RED}File cleaned: $(NAME_SERVER) $(NAME_CLIENT)${RESET}"
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@echo "${GREEN}Done.${RESET}"

re: fclean all

.PHONY: all clean fclean re