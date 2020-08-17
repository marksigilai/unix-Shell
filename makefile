  # build an executable named SEEsh from SEEsh.c
  all: SEEsh.o
 	  gcc -Wall -o SEESh -Werror SEEsh.c

  clean:
	  $(RM) SEEsh