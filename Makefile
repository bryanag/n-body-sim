run: n-body.c physics.c
	gcc -lm -o n-body-sim n-body.c physics.c -I.

clean:
	rm n-body-sim
