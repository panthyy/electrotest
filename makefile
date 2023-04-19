CC = gcc
prefix= /usr/local

main = electrotest-standalone

$(main): $(main).c
	@echo "CFLAGS=$(CFLAGS)" | \
			fold -s -w 70 | \
			sed -e 's/^/# /'

	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDCFLAGS) -o $@ $^

$(main).c: $(main).h

.PHONY: install uninstall clean

install: $(main)
	install -D $(main) \
			$(DESTDIR)$(prefix)/bin/electrotest

uninstall:
	rm -f $(DESTDIR)$(prefix)/bin/$(main)

clean:
	rm -f $(main)

