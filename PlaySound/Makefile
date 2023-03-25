-include config.mk

W2P          = PlaySound
LDFLAGS      = -mdll -Wl,--enable-stdcall-fixup -Wl,--strip-all -Wl,--exclude-all-symbols
CFLAGS       = -std=gnu99 -masm=intel

OBJS = w2p.o

.PHONY: default
default: $(W2P).w2p

$(W2P).w2p: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lmsvcrt -lwinmm

clean:
	$(RM) $(OBJS) $(W2P).w2p
