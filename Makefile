CC = gcc
CFLAGS = -Wall
LDFLAGS = -lX11 -lXss

TARGET = power_management

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(TARGET)
