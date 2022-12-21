files = main.c vector.c

run : $(files)
	cc $(files) -lm
