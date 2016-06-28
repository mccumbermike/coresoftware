#ifndef __PHSIMPLEEVENTMENTOD_H__
#define __PHSIMPLEEVENTMETHOD_H__

#include "PHEventGeneratorMethod.h"
#include "PHEventGeneratorBase.h"

#include <map>
#include <vector>
#include <string>

class PHSimpleEventMethod : public PHEventGeneratorMethod {

public:

  PHSimpleEventMethod(const std::string& name = "PHSimpleEventMethod");
  virtual ~PHSimpleEventMethod() {}

  bool generate_event(PHGenEvent *event);

  //! interface for adding particles by name
  //void add_particles(const std::string &name, const unsigned int count);

  //! interface for adding particle by pid
  void add_particles(const int pid, const unsigned int count);

  //! range of randomized eta values
  void set_eta_range(const double eta_min, const double eta_max);

  //! range of randomized phi values
  void set_phi_range(const double phi_min, const double phi_max);

  //! range of randomized pt values
  //! \param[in] pt_gaus_width   if non-zero, further apply a Gauss smearing to the pt_min - pt_max flat distribution
  void set_pt_range(const double pt_min, const double pt_max, const double pt_gaus_width = 0);

  //! range of randomized p values
  //! \param[in] p_gaus_width   if non-zero, further apply a Gauss smearing to the p_min - p_max flat distribution
  void set_p_range(const double p_min, const double p_max, const double p_gaus_width = 0);

  //! set the distribution function of particles about the vertex
  void set_vertex_size_function(PHEventGeneratorBase::FUNCTION r);

  //! set the dimensions of the distribution of particles about the vertex
  void set_vertex_size_parameters(const double mean, const double width);

private:

  std::vector<std::pair<int, unsigned int> > _particle_codes; // <pdgcode, count>

  PHEventGeneratorBase::FUNCTION _vertex_size_func_r;
  double _vertex_size_mean;
  double _vertex_size_width;
  double _eta_min;
  double _eta_max;
  double _phi_min;
  double _phi_max;
  double _pt_min;
  double _pt_max;
  double _pt_gaus_width;
  double _p_min;
  double _p_max; 
  double _p_gaus_width;

  ClassDef(PHSimpleEventMethod,1)  
};

#endif
