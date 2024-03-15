-include config.mk

W2P          = lobby_map
CC           = i686-w64-mingw32-gcc
CXX          = i686-w64-mingw32-g++
WINDRES     ?= i686-w64-mingw32-windres
LDFLAGS      = -mdll -Wl,--enable-stdcall-fixup -Wl,--strip-all -Wl,--exclude-all-symbols -static
CFLAGS       = -Iinc -O2 -march=i486 -Wall -masm=intel -Wno-pointer-sign 
CXXFLAGS     = -Iinc -O2 -march=i486 -Wall -masm=intel
LIBS         = 

OBJS = cursor.o dllmain.o lamb.o pudthumb.o

.PHONY: default
default: $(W2P).w2p

$(W2P).w2p: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(OBJS) $(W2P).w2p
