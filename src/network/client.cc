#include <enet/enet.h>
#include <boost/format.hpp>
#include "network/client.h"
#include "network/handler.h"

namespace sliding_blocks {

NetworkClient::NetworkClient()
    : client_(nullptr),
      connected_peer_(nullptr),
      handler_(nullptr),
      client_id_(-1) {

  if (enet_initialize() != 0) {
    throw std::runtime_error(
        boost::str(boost::format("Failed to initialize ENet\n"))
    );
  }

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

void NetworkClient::RegisterHandler(Handler &handler) {
  printf("Registering handler.\n");
  handler_ = &handler;
}

void NetworkClient::DeregisterHandler() {
  printf("De-registering handler.\n");
  handler_ = nullptr;
}

void NetworkClient::CheckHostService() {

  ENetEvent event;

  while (enet_host_service(client_, &event, 0) > 0) {

    switch (event.type) {

      case ENET_EVENT_TYPE_CONNECT:
        printf("A new client connected from %x:%u.\n",
               event.peer->address.host,
               event.peer->address.port);
        /* Store any relevant client information here. */
        event.peer->data = (void *) "Client information";
        break;

      case ENET_EVENT_TYPE_RECEIVE:
        printf("A packet of length %u containing %s was received from %s on channel %u.\n",
               event.packet->dataLength,
               event.packet->data,
               event.peer->data,
               event.channelID);
        if (handler_ != nullptr) {
          handler_->HandleReceivedData((char *) event.packet->data);
        }
        enet_packet_destroy(event.packet);
        break;

      case ENET_EVENT_TYPE_DISCONNECT:
        printf("%s disconnected.\n", event.peer->data);
        event.peer->data = NULL;

    }

  }

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

void NetworkClient::SendData(std::string data) {

  // TODO: Add function to send data unreliably
  ENetPacket *packet = enet_packet_create(data.c_str(), data.length() + 1, ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(connected_peer_, 0, packet);
  enet_host_flush(client_);

}

void NetworkClient::SetClientId(int client_id) {
  client_id_ = client_id;
}

int NetworkClient::GetClientId() const {
  return client_id_;
}

void NetworkClient::ResetClientId() {
  client_id_ = -1; // indicates not set
}

}
