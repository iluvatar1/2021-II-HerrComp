# $< : La primera dependencia
# $@: target

sumas.x: sumas.cpp

%.x: %.cpp
	g++ $< -o $@

datos.txt: sumas.x
	./$< > $@

clean:
	rm -f a.out *.x *.txt
