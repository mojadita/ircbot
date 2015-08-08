targets = input

input_objs = main.o input.o config.o
input_libs =
input_ldflags = 

input: $(input_objs)
	$(CC) $(LDFLAGS) $($@_ldflags) -o $@ $($@_objs) $($@_libs)
