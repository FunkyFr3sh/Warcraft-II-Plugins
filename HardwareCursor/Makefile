-include config.mk

WINDRES     ?= windres
W2P          = HardwareCursor
LDFLAGS      = -mdll -Wl,--enable-stdcall-fixup -Wl,--strip-all -Wl,--exclude-all-symbols
CFLAGS       = -std=gnu99 -masm=intel

OBJS = w2p.o

.PHONY: default
default: $(W2P).w2p

$(W2P).w2p: $(OBJS)
	$(WINDRES) -J rc w2p.rc w2p.rc.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ w2p.rc.o -lmsvcrt -lgdi32

clean:
	$(RM) $(OBJS) $(W2P).w2p w2p.rc.o
