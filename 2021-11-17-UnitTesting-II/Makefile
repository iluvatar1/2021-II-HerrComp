all: factorial.x
test: test_factorial.x
	./$<
testcatch2: factorial_test_catch2.x
	./$<

factorial.x: factorial_main.cpp factorial.cpp factorial.h
	g++ $< factorial.cpp -o $@

test_factorial.x: factorial_testing.cpp factorial.cpp factorial.h
	g++ $< factorial.cpp -o $@

factorial_test_catch2.x: factorial_test_catch2.cpp factorial.cpp factorial.h
	source ${HOME}/repos/spack/share/spack/setup-env.sh;\
	spack load catch2;\
	g++ -I ${CMAKE_PREFIX_PATH} $< factorial.cpp -o $@ ;\
	spack unload catch2 

clean:
	rm -f *.x a.out *.x.* *~
