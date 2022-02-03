#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "mpi.h"

// constants
// const double DELTA = 0.05;
// const double L = 1.479;
// const int N = int(L/DELTA)+1;
// const int STEPS = 200;

typedef std::vector<double> Matrix; // alias

void initial_conditions(Matrix & m, int nrows, int ncols);
void boundary_conditions(Matrix & m, int nrows, int ncols);
void evolve(Matrix & m, int nrows, int ncols);
void print(const Matrix & m, double delta, int nrows, int ncols);
void init_gnuplot(void);
void plot_gnuplot(const Matrix & m, double delta, int nrows, int ncols);

// parallel versions
void initial_conditions(Matrix & m, int nrows, int ncols, int pid, int np);
void boundary_conditions(Matrix & m, int nrows, int ncols, int pid, int np);
void print_screen(const Matrix & m, int nrows, int ncols, int pid, int np, bool ghosts = false);
void print_slab(const Matrix & m, int nrows, int ncols, bool ghosts);
void send_rows(Matrix & m, int nrows, int ncols, int pid, int np);
void send_rows_non_blocking(Matrix & m, int nrows, int ncols, int pid, int np);
void send_rows_sendrecv(Matrix & m, int nrows, int ncols, int pid, int np);
void send_rows_topology(Matrix & m, int nrows, int ncols, int pid, int np);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int pid, np;
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  const int N = std::atoi(argv[1]);
  const double L = std::atof(argv[2]);
  const int STEPS = std::atoi(argv[3]);
  const double DELTA = L/N;

  // problem partition
  int NCOLS = N, NROWS = N/np + 2; // include ghosts
  Matrix data(NROWS*NCOLS); // include ghosts cells
  initial_conditions(data, NROWS, NCOLS, pid, np);
  if (0 == pid) {std::cout << " After initial conditions ...\n";}
  print_screen(data, NROWS, NCOLS, pid, np); // todo

  boundary_conditions(data, NROWS, NCOLS, pid, np); // todo
  if (0 == pid) {std::cout << " After boundary conditions ...\n";}
  print_screen(data, NROWS, NCOLS, pid, np, true); // todo

  //send_rows(data, NROWS, NCOLS, pid, np); // todo
  //send_rows_non_blocking(data, NROWS, NCOLS, pid, np); // todo
  //send_rows_sendrecv(data, NROWS, NCOLS, pid, np); // todo
  send_rows_topology(data, NROWS, NCOLS, pid, np); // todo
  if (0 == pid) {std::cout << " After one comm ...\n";}
  print_screen(data, NROWS, NCOLS, pid, np, true); // todo

  /*
  // Serial version
  Matrix data(N*N);
  initial_conditions(data, N, N, ...);
  print_screen(...);
  boundary_conditions(data, N, N, ...);
  init_gnuplot();
  for (int istep = 0; istep < STEPS; ++istep) {
    evolve(data, N, N);
    plot_gnuplot(data, DELTA, N, N);
  }
  */

  MPI_Finalize();
  return 0;
}
/////////////////////////////////////////////////////
// Parallel implementations
void initial_conditions(Matrix & m, int nrows, int ncols, int pid, int np)
{
  // same task for all pids, but fill with the pids to distinguish among thems
  for(int ii=0; ii<nrows; ++ii) {
    for(int jj=0; jj<ncols; ++jj) {
      m[ii*ncols + jj] = pid;
    }
  }
}

void boundary_conditions(Matrix & m, int nrows, int ncols, int pid, int np)
{
  // TODO
  // Take into account each pid
  int ii = 0, jj = 0;

  if (0 == pid) {
    // ghost
    ii = 0;
    for (jj = 0; jj < ncols; ++jj)
      m[ii*ncols + jj] = 100;
    // actual row
    ii = 1;
    for (jj = 0; jj < ncols; ++jj)
      m[ii*ncols + jj] = 100;
  }

  if (np-1 == pid) {
    // actual row
    ii = nrows-2;
    for (jj = 0; jj < ncols; ++jj)
      m[ii*ncols + jj] = 0;
    // ghost
    ii = nrows-1;
    for (jj = 0; jj < ncols; ++jj)
      m[ii*ncols + jj] = 0;
  }

  // all pids
  jj = 0;
  for (ii = 1; ii < nrows-1; ++ii)
    m[ii*ncols + jj] = 0;

  jj = ncols-1;
  for (ii = 1; ii < nrows-1; ++ii)
    m[ii*ncols + jj] = 0;
}

void print_screen(const Matrix & m, int nrows, int ncols, int pid, int np, bool ghosts)
{
  // TODO
  // Master pid prints
  if (0 == pid) {
    // print master data
    print_slab(m, nrows, ncols, ghosts);
    // now receive and print other pdis data
    Matrix buffer(nrows*ncols);
    for (int ipid = 1; ipid < np; ++ipid) {
      MPI_Recv(&buffer[0], nrows*ncols, MPI_DOUBLE, ipid, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      print_slab(buffer, nrows, ncols, ghosts);
    }
  } else { // workers send
    MPI_Send(&m[0], nrows*ncols, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
}

void print_slab(const Matrix & m, int nrows, int ncols, bool ghosts)
{
  int imin = 0, imax = nrows;
  if (false == ghosts) {
    imin = 1; imax = nrows-1;
  }
  for(int ii = imin; ii < imax; ++ii) {
    for(int jj = 0; jj < ncols; ++jj) {
      std::cout << std::setw(3) <<  m[ii*ncols + jj] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void send_rows(Matrix & m, int nrows, int ncols, int pid, int np)
{
  // send data forwards
  if (pid <= np-2) {
    MPI_Send(&m[(nrows-2)*ncols], ncols, MPI_DOUBLE, pid+1, 0, MPI_COMM_WORLD);
  }
  if (pid >= 1) {
    MPI_Recv(&m[0], ncols, MPI_DOUBLE, pid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  // send data backwards
  if (pid >= 1) {
    MPI_Send(&m[(1)*ncols], ncols, MPI_DOUBLE, pid-1, 1, MPI_COMM_WORLD);
  }
  if (pid <= np-2) {
    MPI_Recv(&m[(nrows-1)*ncols], ncols, MPI_DOUBLE, pid+1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
}

void send_rows_non_blocking(Matrix & m, int nrows, int ncols, int pid, int np)
{
  // send data forwards
  MPI_Request r1;
  if (pid <= np-2) {
    //MPI_Send(&m[(nrows-2)*ncols], ncols, MPI_DOUBLE, pid+1, 0, MPI_COMM_WORLD);
    MPI_Isend(&m[(nrows-2)*ncols], ncols, MPI_DOUBLE, pid+1, 0, MPI_COMM_WORLD, &r1);
  }
  if (pid >= 1) {
    MPI_Recv(&m[0], ncols, MPI_DOUBLE, pid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  // send data backwards
  MPI_Request r2;
  if (pid >= 1) {
    MPI_Isend(&m[(1)*ncols], ncols, MPI_DOUBLE, pid-1, 1, MPI_COMM_WORLD, &r2);
  }
  if (pid <= np-2) {
    MPI_Recv(&m[(nrows-1)*ncols], ncols, MPI_DOUBLE, pid+1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  if (pid <- np-2) {
    MPI_Wait(&r1, MPI_STATUS_IGNORE);
  }

  if (pid >= 1) {
    MPI_Wait(&r2, MPI_STATUS_IGNORE);
  }
}

void send_rows_sendrecv(Matrix & m, int nrows, int ncols, int pid, int np)
{
  // send data forwards
  if (0 == pid) {
    MPI_Send(&m[(nrows-2)*ncols], ncols, MPI_DOUBLE, pid+1, 0, MPI_COMM_WORLD);
  }
  if (1 <= pid && pid <= np-2) {
    MPI_Sendrecv(&m[(nrows-2)*ncols], ncols, MPI_DOUBLE, pid+1, 0,
                 &m[(0)*ncols], ncols, MPI_DOUBLE, pid-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  // send data backwards
  if (np-1 == pid) {
    MPI_Send(&m[(1)*ncols], ncols, MPI_DOUBLE, pid-1, 1, MPI_COMM_WORLD);
  }
  if (1 <= pid && pid <= np-2) {
    MPI_Sendrecv(&m[(1)*ncols], ncols, MPI_DOUBLE, pid-1, 1,
                 &m[(nrows-1)*ncols], ncols, MPI_DOUBLE, pid+1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
}

void send_rows_topology(Matrix & m, int nrows, int ncols, int pid, int np)
{
  // create a cartesian 1D topology representing the non-periodic ring
  // https://wgropp.cs.illinois.edu/courses/cs598-s15/lectures/lecture28.pdf
  // https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/mpi-process-topologies
  // MPI_Cart_create(MPI_Comm old_comm, int ndims, const int *dims, const int *periods, int reorder, MPI_Comm *comm_cart)
  int ndims = 1, reorder = 1;
  int dimsize[ndims] {np};
  int periods[ndims] {0};
  MPI_Comm comm;
  MPI_Cart_create(MPI_COMM_WORLD, 1, &dimsize[0], &periods[0], reorder, &comm);

  // Now use the network topology to communicate data in one pass for each direction
  // https://www.open-mpi.org/doc/v3.0/man3/MPI_Neighbor_alltoallw.3.php
  // https://www.events.prace-ri.eu/event/967/contributions/1110/attachments/1287/2213/MPI_virtual_topologies.pdf
  MPI_Datatype types[2] = {MPI_DOUBLE, MPI_DOUBLE};
  // NOTE: scounts[0] goes with rcounts[1] (left and right)
  int scounts[2] = {ncols, ncols};
  int rcounts[2] = {ncols, ncols};
  MPI_Aint sdispl[2]{0}, rdispl[2] {0};
  MPI_Get_address(&m[0]+(nrows-2)*ncols, &sdispl[1]); // send to next
  MPI_Get_address(&m[0]+(0)*ncols, &rdispl[0]); // receive from previous
  MPI_Get_address(&m[0]+(1)*ncols, &sdispl[0]); // send to previous
  MPI_Get_address(&m[0]+(nrows-1)*ncols, &rdispl[1]); // receive from next
  MPI_Neighbor_alltoallw(MPI_BOTTOM, scounts, sdispl, types,
                         MPI_BOTTOM, rcounts, rdispl, types, comm);
}

/////////////////////////////////////////////////////
// SERIAL VERSIONS

void initial_conditions(Matrix & m, int nrows, int ncols)
{
  for(int ii=0; ii<nrows; ++ii) {
    for(int jj=0; jj<ncols; ++jj) {
      m[ii*ncols + jj] = 1.0;
    }
  }
}
void boundary_conditions(Matrix & m, int nrows, int ncols)
{
  int ii = 0, jj = 0;

  ii = 0;
  for (jj = 0; jj < ncols; ++jj)
    m[ii*ncols + jj] = 100;

  ii = nrows-1;
  for (jj = 0; jj < ncols; ++jj)
    m[ii*ncols + jj] = 0;

  jj = 0;
  for (ii = 1; ii < nrows-1; ++ii)
    m[ii*ncols + jj] = 0;

  jj = ncols-1;
  for (ii = 1; ii < nrows-1; ++ii)
    m[ii*ncols + jj] = 0;
}

void evolve(Matrix & m, int nrows, int ncols)
{
  for(int ii=0; ii<nrows; ++ii) {
    for(int jj=0; jj<ncols; ++jj) {
      // check if boundary
      if(ii == 0) continue;
      if(ii == nrows-1) continue;
      if(jj == 0) continue;
      if(jj == ncols-1) continue;
      // evolve non boundary
      m[ii*ncols+jj] = (m[(ii+1)*ncols + jj] +
                    m[(ii-1)*ncols + jj] +
                    m[ii*ncols + jj + 1] +
                    m[ii*ncols + jj - 1] )/4.0;
    }
  }
}

void print(const Matrix & m, double delta, int nrows, int ncols)
{
  for(int ii=0; ii<nrows; ++ii) {
    for(int jj=0; jj<ncols; ++jj) {
      std::cout << ii*delta << " " << jj*delta << " " <<  m[ii*ncols + jj] << "\n";
    }
    std::cout << "\n";
  }  
}

void init_gnuplot(void)
{
  std::cout << "set contour " << std::endl;
  //std::cout << "set terminal gif animate " << std::endl;
  //std::cout << "set out 'anim.gif' " << std::endl;
}

void plot_gnuplot(const Matrix & m, double delta, int nrows, int ncols)
{
  std::cout << "splot '-' w pm3d " << std::endl;
  print(m, delta, nrows, ncols);
  std::cout << "e" << std::endl;
}
