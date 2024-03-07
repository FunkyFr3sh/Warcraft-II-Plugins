
OBJS = cursor.o dllmain.o lamb.o pudthumb.o
       



lobby_map.w2p: cursor.o dllmain.o lamb.o pudthumb.o exp.def
	gcc -mdll -o $@ $^ 
	$(RM) $(OBJS)
clean:
	$(RM) lobby_map.w2p