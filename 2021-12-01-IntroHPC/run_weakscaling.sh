source $HOME/repos/spack/share/spack/setup-env.sh
spack load blas
g++ -fopenmp -O3 -I $CMAKE_PREFIX_PATH/include -L $CMAKE_PREFIX_PATH/lib eigen-matmul.cpp -DEIGEN_USE_BLAS -lopenblas -o eigen_blas.x
parallel -j 1 'echo -n "{}  "; OMP_NUM_THREADS={} ./eigen_blas.x 4000 10 2>/dev//null' ::: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
