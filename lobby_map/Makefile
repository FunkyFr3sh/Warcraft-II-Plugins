
OBJS = cursor.o dllmain.o lamb.o pudthumb.o
       



plugin_test.w2p: cursor.o dllmain.o lamb.o pudthumb.o exp.def
	gcc -mdll -o $@ $^ 
	$(RM) $(OBJS)
clean:
	$(RM) plugin_test.w2p