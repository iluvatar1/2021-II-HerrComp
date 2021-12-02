source $HOME/repos/spack/share/spack/setup-env.sh
spack load blas
g++ -fopenmp -O3 -I $CMAKE_PREFIX_PATH/include -L $CMAKE_PREFIX_PATH/lib eigen-matmul.cpp -DEIGEN_USE_BLAS -lopenblas -o eigen_blas.x
parallel 'OMP_NUM_THREADS=1 ./eigen_blas.x {} 10 2>/dev//null' ::: 10 50 100 200 500 700 1000 2000 5000
