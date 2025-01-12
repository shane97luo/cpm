#ifndef _CMD_FACTORY_H
#define _CMD_FACTORY_H

#include "cmd_strategy.h"

class CommandFactory {
public:
  static Command *CreateCommand(const std::string &cmd_type,
                                const std::string &param);
};

#endif // _CMD_FACTORY_H