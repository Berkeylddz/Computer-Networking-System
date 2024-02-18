#include "PhysicalLayerPacket.h"
#include "iostream"
PhysicalLayerPacket::PhysicalLayerPacket(int _layer_ID, const string& _sender_MAC, const string& _receiver_MAC)
        : Packet(_layer_ID) {
    sender_MAC_address = _sender_MAC;
    receiver_MAC_address = _receiver_MAC;
}

void PhysicalLayerPacket::print() {
    std::cout<< "Sender MAC address: " << sender_MAC_address
    << ", Receiver MAC address: " << receiver_MAC_address<< std::endl;
    // TODO: Override the virtual print function from Packet class to additionally print layer-specific properties.
}

void PhysicalLayerPacket::customPrint() {
    //Layer 3 info: Sender MAC address: CCCCCCCCCC, Receiver MAC address: BBBBBBBBBB
    std::cout<< "Layer 3 info: Sender MAC address: " << sender_MAC_address
    <<  ", Receiver MAC address: " << receiver_MAC_address << std::endl;
}

PhysicalLayerPacket::~PhysicalLayerPacket() {
    // TODO: Free any dynamically allocated memory if necessary.
}