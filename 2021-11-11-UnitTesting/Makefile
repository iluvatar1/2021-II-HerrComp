all: factorial.x
test: test_factorial.x
	./$<

factorial.x: factorial_main.cpp factorial.cpp factorial.h
	g++ $< factorial.cpp -o $@

test_factorial.x: factorial_testing.cpp factorial.cpp factorial.h
	g++ $< factorial.cpp -o $@



clean:
	rm -f *.x a.out *.x.* *~
