#include <enet/enet.h>
#include <boost/format.hpp>
#include "network/client.h"

namespace sliding_blocks {

NetworkClient::NetworkClient() {

  client_ = enet_host_create(NULL, 1, 2, 0, 0);
  if (client_ == nullptr) {
    throw std::runtime_error(
        boost::str(boost::format("Client creation error\n"))
    );
  }

}

NetworkClient::~NetworkClient() {

  Disconnect();
  enet_host_destroy(client_);

}

bool NetworkClient::Connect(std::string hostname, int port) {

  ENetAddress address;
  ENetEvent event;
  enet_address_set_host(&address, hostname.c_str());
  address.port = port;

  connected_peer_ = enet_host_connect(client_, &address, 2, 0);

  if (connected_peer_ == nullptr) {
    throw std::runtime_error(
        boost::str(boost::format("No available peers for initiating connection\n"))
    );
  }

  /* Wait up to 5 seconds for the connection attempt to succeed. */
  if (enet_host_service(client_, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
    printf("Connection to server succeeded.");
    return true;
  } else {
    enet_peer_reset(connected_peer_);
    printf("Connection to some.server.net:1234 failed.");
    return false;
  }

}

void NetworkClient::Disconnect() {

  if (connected_peer_ == nullptr) {
    return;
  }

  enet_peer_disconnect(connected_peer_, 0);

}

void NetworkClient::SendData() {

  ENetPacket *packet = enet_packet_create("packet", strlen("packet") + 1, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(connected_peer_, 0, packet);
  enet_host_flush(client_);

}

}
