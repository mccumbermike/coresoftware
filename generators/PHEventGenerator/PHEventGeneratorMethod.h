#ifndef __PHEVENTGENERATORMETHOD_H__
#define __PHEVENTGENERATORMETHOD_H__

#include "PHGenEvent.h"

#include <string>

#include <phool/PHObject.h>

class PHEventGeneratorMethod : public PHObject {
  
public:
  
  virtual ~PHEventGeneratorMethod();

  virtual std::string  get_name() const {return _name;}
  
  virtual void         set_seed(const unsigned int seed) {return;}
  virtual unsigned int get_seed() const {return 0;}
  
  virtual bool generate_event(PHGenEvent* eventdata) const {return false;}
  
 protected:

  PHEventGeneratorMethod(const std::string &name = "PHEVENTGENMETHOD");

 private:

  std::string _name;
};

#endif	/* __PHEVENTGENERATORMETHOD_H__ */

