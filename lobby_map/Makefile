
OBJS = cursor.o dllmain.o lamb.o pudthumb.o
       



lobby_map.w2p: cursor.o dllmain.o lamb.o pudthumb.o exp.def
	gcc -mdll -Wl,--strip-all -Wl,--exclude-all-symbols -o $@ $^ 
	$(RM) $(OBJS)
clean:
	$(RM) lobby_map.w2p