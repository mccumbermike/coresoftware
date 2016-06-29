#ifndef __PHEVENTGENERATORMETHOD_H__
#define __PHEVENTGENERATORMETHOD_H__

#include "PHGenEvent.h"

#include <string>

#ifndef __CINT__
#include <gsl/gsl_rng.h>
#endif

#include <phool/PHObject.h>

class PHEventGeneratorMethod : public PHObject {
  
public:
  
  virtual ~PHEventGeneratorMethod();

  virtual bool init() {return true;}
  virtual bool generate_event(PHGenEvent* eventdata) {return true;}
  
  virtual void         set_name(const std::string& name) {_name = name;}
  virtual std::string  get_name() const {return _name;}
  
  virtual void         set_seed(const unsigned int seed);
  virtual unsigned int get_seed() const {return _seed;}

  virtual void         set_verbosity(const unsigned int verb) {_verbosity = verb;}
  virtual unsigned int get_verbosity() const {return _verbosity;}

protected:

  PHEventGeneratorMethod(const std::string &name = "PHEVENTGENERATORMETHOD");

  virtual const gsl_rng* get_rand() const {return _rand;}
  
  virtual int         get_pdgcode(const std::string &name) const;
  virtual std::string get_pdgname(const int pdgcode) const;
  virtual double      get_mass(const int pdgcode) const;
  
 private:

  std::string _name;
  unsigned int _seed;
  unsigned int _verbosity;

#ifndef __CINT__
  gsl_rng* _rand;
#endif
};

#endif	/* __PHEVENTGENERATORMETHOD_H__ */

