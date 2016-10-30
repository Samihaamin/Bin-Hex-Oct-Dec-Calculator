calc: calc.c
	gcc calc.c -o calc -lm
clean:
	rm -rf calc
