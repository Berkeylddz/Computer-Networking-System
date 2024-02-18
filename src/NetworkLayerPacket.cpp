#include "NetworkLayerPacket.h"
#include <iostream>

NetworkLayerPacket::NetworkLayerPacket(int _layer_ID, const string &_sender_IP, const string &_receiver_IP)
        : Packet(_layer_ID) {
    sender_IP_address = _sender_IP;
    receiver_IP_address = _receiver_IP;
}

void NetworkLayerPacket::print() {
    //Sender IP address: 8.8.8.8, Receiver IP address: 0.0.1.1
    std::cout<<"Sender IP address: " <<sender_IP_address
    <<", Receiver IP address: " << receiver_IP_address<< std::endl;

    // TODO: Override the virtual print function from Packet class to additionally print layer-specific properties.
}

void NetworkLayerPacket::customPrint() {
    //Layer 2 info: Sender IP address: 8.8.8.8, Receiver IP address: 0.0.1.1
    std::cout<< "Layer 2 info: Sender IP address: " << sender_IP_address
    << ", Receiver IP address: " << receiver_IP_address << std::endl;
}

NetworkLayerPacket::~NetworkLayerPacket() {
    // TODO: Free any dynamically allocated memory if necessary.
}
