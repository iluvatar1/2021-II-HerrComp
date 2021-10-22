# $< : La primera dependencia
# $@: target

all: fig.pdf

sumas.x: sumas.cpp

%.x: %.cpp
	g++ $< -o $@

datos.txt: sumas.x
	./$< > $@

fig.pdf: plot.gp datos.txt
	gnuplot $<

clean:
	rm -f a.out *.x *.txt *.pdf
