-include config.mk

TARGET       = HardwareCursor.w2p

LDFLAGS      = -Wl,--enable-stdcall-fixup -s -shared -static
CFLAGS       = -Iinc -O2 -march=i486 -Wall -masm=intel -Wno-pointer-sign 
CXXFLAGS     = -Iinc -O2 -march=i486 -Wall -masm=intel
LIBS         = -lgdi32

CC           = i686-w64-mingw32-gcc
CXX          = i686-w64-mingw32-g++
STRIP       ?= i686-w64-mingw32-strip
WINDRES     ?= i686-w64-mingw32-windres

OBJS = w2p.o res.o

.PHONY: default clean
default: $(TARGET)

%.o: %.rc
	$(WINDRES) -J rc $< $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)
