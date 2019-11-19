fase.png : x.txt
	python ejercicio.py
x.txt : ejercicio.x
	./ejercicio.x
	rm ejercicio.x
ejercicio.x : ejercicio.cpp
	c++ ejercicio.cpp -o ejercicio.x
