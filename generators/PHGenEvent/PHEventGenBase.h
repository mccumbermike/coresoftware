#ifndef __PHEVENTGENBASE_H__
#define __PHEVENTGENBASE_H__

#include "PHEventGenMethod.h"
#include "PHEventGenTrigger.h"
#include "PHGenEvent.h"
#include "PHGenEventMap.h"

#include <string>

#ifndef __CINT__
#include <gsl/gsl_rng.h>
#endif

#include <phool/PHCompositeNode.h>
#include <fun4all/SubsysReco.h>

class PHEventGenBase : public SubsysReco {
  
public:
  
  virtual ~PHEventGenBase();

  virtual int InitRun(PHCompositeNode* topNode);
  virtual int process_event(PHCompositeNode* topNode);

  // Settings

  virtual void set_seed(const unsigned int seed);
  
  /// toss a new vertex according to a Uniform or Gaus distribution
  enum FUNCTION {Uniform,Gaus};
  virtual void   set_vertex_function(const FUNCTION x, const FUNCTION y,
				     const FUNCTION z, const FUNCTION t);
  virtual double get_vertex_function_x() {return _vertex_func_x;}
  virtual double get_vertex_function_y() {return _vertex_func_y;}
  virtual double get_vertex_function_z() {return _vertex_func_z;}
  virtual double get_vertex_function_t() {return _vertex_func_t;}

  /// set the mean value of the vertex distribution
  virtual void   set_vertex_mean(const double x, const double y,
				 const double z, const double t);
  virtual double get_vertex_mean_x() {return _vertex_mean_x;}
  virtual double get_vertex_mean_y() {return _vertex_mean_y;}
  virtual double get_vertex_mean_z() {return _vertex_mean_z;}
  virtual double get_vertex_mean_t() {return _vertex_mean_t;}

  /// set the width of the vertex distribution function about the mean
  virtual void   set_vertex_width(const double x, const double y,
				  const double z, const double t);
  virtual double get_vertex_width_x() {return _vertex_width_x;}
  virtual double get_vertex_width_y() {return _vertex_width_y;}
  virtual double get_vertex_width_z() {return _vertex_width_z;}
  virtual double get_vertex_width_t() {return _vertex_width_t;}

protected:

  PHEventGenBase(PHEventGenMethod* generator,
		 PHEventGenTrigger* trigger = NULL,
		 const std::string &name = "PHEVENTGENBASE");

  virtual bool generate_vertex(double& x, double& y, double& z, double& t);
  virtual bool shift_vertex(PHGenEvent* event,
			    const double x, const double y,
                            const double z, const double t);

  virtual PHEventGenMethod*  get_method() {return _generator;}
  virtual PHEventGenTrigger* get_trigger() {return _trigger;}
  
 private:

  double random(const FUNCTION function, const double mean, const double width);

  PHEventGenMethod*  _generator;
  PHEventGenTrigger* _trigger;
  unsigned int _seed;
  FUNCTION _vertex_func_x;
  FUNCTION _vertex_func_y;
  FUNCTION _vertex_func_z;
  FUNCTION _vertex_func_t;
  double _vertex_mean_x;
  double _vertex_mean_y;
  double _vertex_mean_z;
  double _vertex_mean_t;
  double _vertex_width_x;
  double _vertex_width_y;
  double _vertex_width_z;
  double _vertex_width_t;

  PHGenEventMap* _event_map;
  
#ifndef __CINT__
  gsl_rng *_rand;
#endif
};

#endif	/* __PHEVENTGENBASE_H__ */

