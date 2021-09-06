OBJS = main.c pthread_client_request.c pthread_refresh.c pthread_sqlite.c pthread_transfer.c pthread_analysis.c pthread_buzzer.c pthread_led.c pthread_camera.c link_list.c 
CC = arm-linux-gnueabihf-gcc
CFLAGS += -pthread  
SQLITE = -L../../cgi/lib -lsqlite3 -I../../cgi/include
storage:$(OBJS)
	$(CC) $^ $(CFLAGS) $(SQLITE) -Wall  -o $@

clean:
	rm *.o storage

cp:
	cp storage ~/nfs/rootfs/
