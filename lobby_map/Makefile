-include config.mk

TARGET       = lobby_map.w2p

LDFLAGS      = -Wl,--enable-stdcall-fixup -s -shared -static
CFLAGS       = -Iinc -O2 -march=i486 -Wall -masm=intel -Wno-pointer-sign 
CXXFLAGS     = -Iinc -O2 -march=i486 -Wall -masm=intel
LIBS         = 

CC           = i686-w64-mingw32-gcc
CXX          = i686-w64-mingw32-g++
STRIP       ?= i686-w64-mingw32-strip
WINDRES     ?= i686-w64-mingw32-windres

OBJS = cursor.o dllmain.o lamb.o pudthumb.o

.PHONY: default clean
default: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)
