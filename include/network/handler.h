#ifndef SLIDINGBLOCKS_INCLUDE_NETWORK_HANDLER_H_
#define SLIDINGBLOCKS_INCLUDE_NETWORK_HANDLER_H_

#include <string>

namespace sliding_blocks {

class Handler {

 public:
  virtual void HandleReceivedData(const std::string &data) = 0;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_NETWORK_HANDLER_H_
