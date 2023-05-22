#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#include <IoData.h>
#include <LatticeVariables.h>
#include <Vector3D.h>
#include <vector>
#include <string>
#include <mpi.h>

/*******************************************************
 * class Output is responsible for outputing solutions
 * to files.
 *****************************************************/

class Output {

  MPI_Comm &comm;
  IoData &iod;

  int iFrame;
  double last_snapshot_time;

  std::vector<Vec3D> axis_a, axis_b, axis_c, origin; //!< one per lattice
  std::vector<string> periodic_a, periodic_b, periodic_c; //!< one per lattice, "T" or "F".

  std::vector<string> material_name;

public:

  Output(MPI_Comm &comm_, IoData &iod_);
  ~Output();
  
  void OutputSolution(double time, double dt, int time_step, std::vector<LatticeVariables> &LV,
                      bool force_write = false);

private:

  void OutputSolutionVTP(double time, [[maybe_unused]] int time_step, std::vector<LatticeVariables> &LV);
  void OutputSolutionOnLatticeVTP(double time, int lattice_id, LatticeVariables &V);
  void OutputSolutionXYZ(double time, [[maybe_unused]] int time_step, std::vector<LatticeVariables> &LV);
  void OutputSolutionOnLatticeXYZ(double time, int lattice_id, LatticeVariables &V);

};
#endif
