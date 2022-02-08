#!/usr/bin/env bash

#SBATCH --job-name="testmulti"
# #SBATCH --account="HerrComp" # not used
#SBATCH --mail-type=ALL
#SBATCH --mail-user=wfoquendop@unal.edu.co
#SBATCH --time=01:00:00
#SBATCH --nodes=3
#SBATCH --ntasks-per-node=6
#SBATCH --cpus-per-task=1
#SBATCH --partition=12threads

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
cd $HOME/repos/2021-II-HerrComp/2022-02-09-Slurm/
mpic++ MPI_laplace_v5.cpp
date
srun --mpi=pmi2 ./a.out 180 1.4705 200 | gnuplot
date
