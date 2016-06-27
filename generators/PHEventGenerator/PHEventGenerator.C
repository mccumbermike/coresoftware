#include "PHEventGen.h"

#include <fun4all/Fun4AllReturnCodes.h>
#include <phool/getClass.h>
#include <phool/PHCompositeNode.h>

using namespace std;

PHEventGen::PHEventGen(PHEventGenMethod* generator,
		       PHEventGenTrigger* trigger,
		       const std::string &name): 
  PHEventGenBase(generator,trigger,name) {}

PHEventGen::~PHEventGen() {}

