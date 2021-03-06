#ifndef SLIDINGBLOCKS_INCLUDE_NETWORK_CLIENT_H_
#define SLIDINGBLOCKS_INCLUDE_NETWORK_CLIENT_H_

#include <enet/enet.h>
#include "handler.h"

namespace sliding_blocks {

class NetworkClient {

 public:
  NetworkClient();
  ~NetworkClient();
  void CheckHostService();
  bool Connect(std::string hostname, int port);
  void Disconnect();
  void SendData(std::string data);
  void RegisterHandler(Handler &handler);
  void DeregisterHandler();
  void SetClientId(int client_id);
  int GetClientId() const;
  void ResetClientId();

 private:
  ENetHost *client_;
  ENetPeer *connected_peer_;
  Handler *handler_;
  int client_id_;

};

}

#endif //SLIDINGBLOCKS_INCLUDE_NETWORK_CLIENT_H_
