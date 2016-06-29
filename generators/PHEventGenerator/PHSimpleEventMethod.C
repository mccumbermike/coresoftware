#include "PHSimpleEventMethod.h"

#include <gsl/gsl_randist.h>

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

PHSimpleEventMethod::PHSimpleEventMethod(const string &name): 
  PHEventGeneratorMethod(name),
  _particle_codes(),
  _particle_names(),
  _vertex_size_func_r(PHEventGeneratorBase::Uniform),
  _vertex_size_mean(0.0),
  _vertex_size_width(0.0),
  _eta_min(-1.25),
  _eta_max(1.25),
  _phi_min(-M_PI),
  _phi_max(M_PI),
  _pt_min(0.0),
  _pt_max(10.0),
  _pt_gaus_width(0.0),
  _p_min(NAN),
  _p_max(NAN),
  _p_gaus_width(NAN) {
  return;
  }

void PHSimpleEventMethod::add_particles(const std::string& name, const unsigned int num) {
  _particle_names.push_back(std::make_pair(name,num));
  return;
}

void PHSimpleEventMethod::add_particles(const int pid, const unsigned int num) {
  _particle_codes.push_back(std::make_pair(pid,num));
  return;
}

void PHSimpleEventMethod::set_eta_range(const double min, const double max) {
  if (min > max) {
    cout << "not setting eta bc etamin " << min << " > etamax: " << max << endl;
    return;
  }
  _eta_min = min;
  _eta_max = max;
  return;
}

void PHSimpleEventMethod::set_phi_range(const double min, const double max) {
  if (min > max) {
    cout << "not setting phi bc phimin " << min << " > phimax: " << max << endl;
    return;
  }
  _phi_min = min;
  _phi_max = max;
  return;
}

void PHSimpleEventMethod::set_pt_range(const double min, const double max,
                                       const double pt_gaus_width) {
  if (min > max) {
    cout << "not setting pt bc ptmin " << min << " > ptmax: " << max << endl;
    return;
  }
  assert(pt_gaus_width >= 0);

  _pt_min = min;
  _pt_max = max;
  _pt_gaus_width = pt_gaus_width;
  _p_min = NAN;
  _p_max = NAN;
  _p_gaus_width = NAN;
  return;
}

void PHSimpleEventMethod::set_p_range(const double min, const double max,
                                      const double p_gaus_width) {
  if (min > max) {
    cout << "not setting p bc ptmin " << min << " > ptmax: " << max << endl;
    return;
  }
  assert(p_gaus_width >= 0);
  _pt_min = NAN;
  _pt_max = NAN;
  _pt_gaus_width = NAN;
  _p_min = min;
  _p_max = max;
  _p_gaus_width = p_gaus_width;
  return;
}

void PHSimpleEventMethod::set_vertex_size_function(PHEventGeneratorBase::FUNCTION r) {
  _vertex_size_func_r = r;
  return;
}

void PHSimpleEventMethod::set_vertex_size_parameters(const double mean, const double width) {
  _vertex_size_mean = mean;
  _vertex_size_width = width;
  return;
}

bool PHSimpleEventMethod::init() {

  if (!PHEventGeneratorMethod::init()) return false;
  
  // the definition table should be filled now, so convert codes into names
  for (unsigned int i=0;i<_particle_codes.size();++i) {
    int pdgcode = _particle_codes[i].first;
    unsigned int count = _particle_codes[i].second;
    string pdgname = PHEventGeneratorMethod::get_pdgname(pdgcode);
    _particle_names.push_back(make_pair(pdgname,count));
  }
  
  return true;
}

bool PHSimpleEventMethod::generate_event(PHGenEvent* event) {

  event->Reset();
  
  int vtxindex = -1; vtxindex*=1;
  int trackid = -1;
  for (unsigned int i=0; i<_particle_names.size(); ++i) {

    string pdgname = _particle_names[i].first;
    int pdgcode = PHEventGeneratorMethod::get_pdgcode(pdgname);
    unsigned int nparticles = _particle_names[i].second;
    
    for (unsigned int j=0; j<nparticles; ++j) {

      if ((_vertex_size_width > 0.0)||(_vertex_size_mean != 0.0)) {

	double r = toss(_vertex_size_mean,_vertex_size_width,_vertex_size_func_r);

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	gsl_ran_dir_3d(PHEventGeneratorMethod::get_rand(),&x,&y,&z);
        x *= r;
        y *= r;
        z *= r;

	//	vtxindex = _ineve->AddVtx(vtx_x+x,vtx_y+y,vtx_z+z,_t0);
      } else if ((i==0)&&(j==0)) {
	//	vtxindex = _ineve->AddVtx(vtx_x,vtx_y,vtx_z,_t0);
      }

      ++trackid;
   
      double eta = (_eta_max-_eta_min) * gsl_rng_uniform_pos(PHEventGeneratorMethod::get_rand()) + _eta_min;
      double phi = (_phi_max-_phi_min) * gsl_rng_uniform_pos(PHEventGeneratorMethod::get_rand()) + _phi_min;

      double pt;
      if (!std::isnan(_p_min) && !std::isnan(_p_max) &&
          !std::isnan(_p_gaus_width)) {
        pt = ((_p_max - _p_min) * gsl_rng_uniform_pos(PHEventGeneratorMethod::get_rand()) +
              _p_min + gsl_ran_gaussian(PHEventGeneratorMethod::get_rand(), _p_gaus_width)) /
             cosh(eta);
      } else if (!std::isnan(_pt_min) && !std::isnan(_pt_max) &&
                 !std::isnan(_pt_gaus_width)) {
        pt = (_pt_max - _pt_min) * gsl_rng_uniform_pos(PHEventGeneratorMethod::get_rand()) +
             _pt_min + gsl_ran_gaussian(PHEventGeneratorMethod::get_rand(), _pt_gaus_width);
      } else {
        cout << PHWHERE << "Error: neither a p range or pt range was specified"
             << endl;
        exit(-1);
      }

      double px = pt*cos(phi);
      double py = pt*sin(phi);
      double pz = pt*sinh(eta);
      double m = PHEventGeneratorMethod::get_mass(pdgcode);
      double e = sqrt(px*px+py*py+pz*pz+m*m);
      e*=1.0;
      /*
      PHG4Particle *particle = new PHG4Particlev2();
      particle->set_track_id(trackid);
      particle->set_vtx_id(vtxindex);
      particle->set_parent_id(0);
      particle->set_name(pdgname);
      particle->set_pid(pdgcode);
      particle->set_px(px);
      particle->set_py(py);
      particle->set_pz(pz);
      particle->set_e(e);

      _ineve->AddParticle(vtxindex, particle);
      if (embedflag != 0) _ineve->AddEmbeddedParticle(particle,embedflag);
      */
    }
  }

  if (get_verbosity() > 0) {
    cout << "====================== PHSimpleEventMethod::process_event() =====================" << endl;
    //_ineve->identify();
    cout << "======================================================================================" << endl;
  } 

  return true;
}

double PHSimpleEventMethod::toss(const double position,
				 const double width,
				 PHEventGeneratorBase::FUNCTION dist) const {
  double res = position;
  if (dist == PHEventGeneratorBase::Uniform) {
    res = (position - width) + 2 * gsl_rng_uniform_pos(PHEventGeneratorMethod::get_rand()) * width;
  } else if (dist == PHEventGeneratorBase::Gaus) {
    res = position + gsl_ran_gaussian(PHEventGeneratorMethod::get_rand(), width);
  }
  return res;
}
