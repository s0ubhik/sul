%.o: %.c
	$(CC) -c $< -o $@

sulock: main.o md5-c/md5.o
	$(CC) $^ -o $@
	sudo su -c 'chown root:root $@; chmod 4111 $@'
# 4111 - user(s) group(x) others(x)

clean:
	rm *.o md5-c/*.o
	sudo su -c 'rm -f sulock'