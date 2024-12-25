#ifndef SLIDINGBLOCKS_INCLUDE_NETWORK_CLIENT_H_
#define SLIDINGBLOCKS_INCLUDE_NETWORK_CLIENT_H_

#include <enet/enet.h>

namespace sliding_blocks {

class NetworkClient {

 public:
  NetworkClient();
  ~NetworkClient();
  void CheckHostService();
  bool Connect(std::string hostname, int port);
  void Disconnect();
  void SendData(std::string data);

 private:
  ENetHost *client_;
  ENetPeer *connected_peer_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_NETWORK_CLIENT_H_
