#ifndef __PHEVENTGEN_H__
#define __PHEVENTGEN_H__

#include "PHEventGenBase.h"
#include "PHEventGenMethod.h"
#include "PHEventGenTrigger.h"

class PHEventGen : public PHEventGenBase {
  
public:

  PHEventGen(PHEventGenMethod* generator,
	     PHEventGenTrigger* trigger = NULL,
	     const std::string &name = "PHEVENTGEN");
  virtual ~PHEventGen();

};

#endif	/* __PHEVENTGEN_H__ */

