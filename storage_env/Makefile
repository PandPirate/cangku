ARCH ?=
OBJS = main.c pthread_client_request.c pthread_refresh.c pthread_sqlite.c pthread_transfer.c pthread_analysis.c pthread_buzzer.c pthread_led.c pthread_camera.c link_list.c 
SQLITE = -L../../cgi/lib -lsqlite3 -I../../cgi/include
CFLAGS += -pthread  
ifeq ($(ARCH), arm)
CC = arm-linux-gnueabihf-gcc
storage:$(OBJS)
	$(CC) $^ $(CFLAGS) $(SQLITE) -Wall  -o $@

else
CC = gcc
CFLAGS += -lsqlite3
storage:$(OBJS)
	$(CC) $^ $(CFLAGS) -Wall  -o $@
endif



clean:
	rm *.o storage

cp:
	cp storage ~/nfs/rootfs/
