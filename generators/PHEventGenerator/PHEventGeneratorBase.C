#include "PHEventGenBase.h"

#include "PHGenEvent.h"
#include "PHGenEvent_v1.h"
#include "PHGenEventMap.h"
#include "PHGenEventMap_v1.h"

#include <fun4all/Fun4AllReturnCodes.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>
#include <phool/PHRandomSeed.h>

#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include <iostream>
#include <sstream>
 
using namespace std;

PHEventGenBase::PHEventGenBase(PHEventGenMethod* generator,
			       PHEventGenTrigger* trigger,
			       const std::string &name): 
  SubsysReco(name),
  _generator(generator),
  _trigger(trigger),
  _seed(0),
  _vertex_func_x(Uniform),
  _vertex_func_y(Uniform),
  _vertex_func_z(Uniform),
  _vertex_func_t(Uniform),
  _vertex_mean_x(0.0),
  _vertex_mean_y(0.0),
  _vertex_mean_z(0.0),
  _vertex_mean_t(0.0),
  _vertex_width_x(0.0),
  _vertex_width_y(0.0),
  _vertex_width_z(0.0),
  _vertex_width_t(0.0),
  _event_map(NULL),
  _rand(NULL) {

  if (!_trigger) _trigger = new PHEventGenTrigger();
  
  _rand = gsl_rng_alloc(gsl_rng_mt19937);
  _seed = PHRandomSeed(); // fixed seed is handled in this funtcion
  gsl_rng_set(_rand,_seed);
  return;
}

PHEventGenBase::~PHEventGenBase() {
  if (_generator) delete _generator;
  if (_trigger) delete _trigger;
  if (_rand) gsl_rng_free (_rand);
  return;
}

int PHEventGenBase::InitRun(PHCompositeNode* topNode) {

  // create nodes...
  PHNodeIterator iter(topNode);

  PHCompositeNode* dstNode =
    static_cast<PHCompositeNode*>(iter.findFirst("PHCompositeNode", "DST"));
  if (!dstNode) {
    cerr << PHWHERE << "DST Node missing, doing nothing." << endl;
    return Fun4AllReturnCodes::ABORTEVENT;
  }

  _event_map = findNode::getClass<PHGenEventMap>(topNode, "PHGenEventMap");
  if (!_event_map) {
    _event_map = new PHGenEventMap_v1;
    PHIODataNode<PHObject>* event_node =
      new PHIODataNode<PHObject>(_event_map, "PHGenEventMap", "PHObject");
    dstNode->addNode(event_node);
    if (verbosity > 0) cout << "PHGenEventMap node added" << endl;
  }

  return Fun4AllReturnCodes::EVENT_OK;
}

int PHEventGenBase::process_event(PHCompositeNode* topNode) {

  PHGenEvent_v1 event;
  
  while (true) {
    get_method()->generate_event(&event);

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    double t = 0.0;
    generate_vertex(x,y,z,t);  
    shift_vertex(&event,x,y,z,t);
    
    if (get_trigger()->trigger_event(&event)) break;
  }

  _event_map->insert(&event);
  
  return Fun4AllReturnCodes::EVENT_OK;
}

void PHEventGenBase::set_seed(const unsigned int seed) {
  _seed = seed;
  gsl_rng_set(_rand,_seed);
}

void PHEventGenBase::set_vertex_function(const FUNCTION x,
					 const FUNCTION y,
					 const FUNCTION z,
					 const FUNCTION t) {
  _vertex_func_x = x;
  _vertex_func_y = y;
  _vertex_func_z = z;
  _vertex_func_t = t;
}

void PHEventGenBase::set_vertex_mean(const double x, const double y,
					   const double z, const double t) {
  _vertex_mean_x = x;
  _vertex_mean_y = y;
  _vertex_mean_z = z;
  _vertex_mean_t = t;
}

void PHEventGenBase::set_vertex_width(const double x, const double y,
					    const double z, const double t) {
  _vertex_width_x = x;
  _vertex_width_y = y;
  _vertex_width_z = z;
  _vertex_width_t = t;
}

bool PHEventGenBase::generate_vertex(double& x, double& y,
				     double& z, double& t) {
  x = random(_vertex_func_x,_vertex_mean_x,_vertex_width_x);
  y = random(_vertex_func_y,_vertex_mean_y,_vertex_width_y);
  z = random(_vertex_func_z,_vertex_mean_z,_vertex_width_z);
  t = random(_vertex_func_t,_vertex_mean_t,_vertex_width_t);
  return true;
}

bool PHEventGenBase::shift_vertex(PHGenEvent* event,
		  const double x, const double y,
		  const double z, const double t) {
  cout << "you need to write me" << endl;
  return true;
}

double PHEventGenBase::random(const FUNCTION function,
				    const double mean,
				    const double width) {
  double value = mean;
  if (width != 0.0) {
    if (function == Uniform) {
      value = (mean-width) + 2*gsl_rng_uniform_pos(_rand)*width;
    } else if (function == Gaus) {
      value = mean + gsl_ran_gaussian(_rand,width);
    }
  }
  
  return value;
}
