#ifndef __PHPASSTRIGGER_H__
#define __PHPASSTRIGGER_H__

#include "PHEventGeneratorTrigger.h"

#include <string>

class PHPassTrigger : public PHEventGeneratorTrigger {
  
public:

  PHPassTrigger(const std::string &name = "PHPASSTRIGGER");
  virtual ~PHPassTrigger();

  bool trigger_event(const PHGenEvent* eventdata) const {return true;}
  
private:
};

#endif	/* __PHPASSTRIGGER_H__ */

