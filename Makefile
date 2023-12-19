ifdef NOPASS
	DEPS = main.o
	DEF =
else
	DEPS = main.o md5-c/md5.o
	DEF = -DPASSWORD
endif

%.o: %.c
	$(CC) $(DEF) -c $< -o $@

sul: $(DEPS)
	$(CC) $^ -o $@
	sudo su -c 'chown root:root $@; chmod 4111 $@'
# 4111 - user(s) group(x) others(x)

install: sul
	sudo cp $< /usr/bin
	sudo su -c 'chown root:root /usr/bin/$<; chmod 4111 /usr/bin/$<'

uninstall: /usr/bin/sul
	sudo rm -f $<
clean:
	rm -rf *.o md5-c/*.o
	sudo bash -c 'rm -f sul'

