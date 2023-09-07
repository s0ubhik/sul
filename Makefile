%.o: %.c
	$(CC) -c $< -o $@

all: sulock

main_wp.c: main_wp.patch
	@echo "Configuring without password..."
	cp main.c main_wp.c
	patch main_wp.c < main_wp.patch

sul: main_wp.o
	$(CC) $^ -o $@
	sudo su -c 'chown root:root $@; chmod 4111 $@'

sulock: main.o md5-c/md5.o
	$(CC) $^ -o $@
	sudo su -c 'chown root:root $@; chmod 4111 $@'
# 4111 - user(s) group(x) others(x)

clean:
	rm -rf *.o md5-c/*.o main_wp.c
	sudo su -c 'rm -f sulock sul'
