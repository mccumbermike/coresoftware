#ifndef __PHGENVERTEX_H__
#define __PHGENVERTEX_H__

#include <phool/phool.h>
#include <phool/PHObject.h>

#include <HepMC/GenVertex.h>

class PHGenVertex : public PHObject, public HepMC::GenVertex {
  
 public:
  
  PHGenVertex();
  virtual ~PHGenVertex();
  
private:
  
  ClassDef(PHGenVertex,1)  
};

#endif	// __PHGENVERTEX_H__
