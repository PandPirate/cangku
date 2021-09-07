CC=arm-linux-gnueabihf-gcc
NAME ?= 

$(NAME).cgi : 
	$(CC) $(NAME).c cgic.c  -o $(NAME).cgi -L./lib -lsqlite3 -I./include
	sudo cp $(NAME).cgi ~/nfs/rootfs/html/cgi-bin/

clean :
	rm $(NAME).cgi 


