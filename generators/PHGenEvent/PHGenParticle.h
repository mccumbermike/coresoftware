#ifndef __PHGENPARTICLE_H__
#define __PHGENPARTICLE_H__

#include <phool/phool.h>
#include <phool/PHObject.h>

#include <HepMC/GenParticle.h>

class PHGenParticle : public PHObject, public HepMC::GenParticle {
  
 public:
  
  PHGenParticle();
  virtual ~PHGenParticle();
  
private:
  
  ClassDef(PHGenParticle,1)  
};

#endif	// __PHGENPARTICLE_H__
