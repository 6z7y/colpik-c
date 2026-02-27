CC := cc
LIBS := -lm

PROG_NAME := colpik
INSTALL_PATH := /usr/local/bin

all: $(PROG_NAME)

$(PROG_NAME): main.c
	$(CC) main.c -o $(PROG_NAME) $(LIBS)

install: $(PROG_NAME)
	sudo install -m755 $(PROG_NAME) $(INSTALL_PATH)

clean:
	rm -f $(PROG_NAME)

uninstall:
	sudo rm -f $(INSTALL_PATH)/$(PROG_NAME)

.PHONY: all install uninstall clean
