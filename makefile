componentesElectricos=./componentesElectricos/

run: compilacion
	./magnetismo.out

compilacion:
	gcc -std=c2x -o magnetismo.out *.c ${componentesElectricos}*.c -L${componentesElectricos}