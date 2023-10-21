componentesElectricos=./componentesElectricos/
sistemas=./sistemas/

run: compilacion
	./magnetismo.out

compilacion:
	g++ -o magnetismo.out main.cpp ${componentesElectricos}*.c ${sistemas}*.cpp
		-L${componentesElectricos} -L${sistemas}