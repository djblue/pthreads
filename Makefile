p1: p1.c
	gcc -std=c99 -lpthread -lrt -o p1 p1.c

p2: p2.c
	gcc -std=c99 -lpthread -lrt -o p2 p2.c

p3: p3.c
	gcc -std=c99 -lpthread -lrt -o p3 p3.c

inc: inc.c
	gcc -std=c99 -lpthread -lrt -o inc inc.c

inc-max: inc-max.c
	gcc -std=c99 -lpthread -lrt -o inc-max inc-max.c
