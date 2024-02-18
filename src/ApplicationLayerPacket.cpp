#include "ApplicationLayerPacket.h"

ApplicationLayerPacket::ApplicationLayerPacket(int _layer_ID, const string &_sender_ID, const string &_receiver_ID, const string& _message_data) : Packet(_layer_ID) {
    sender_ID = _sender_ID;
    receiver_ID = _receiver_ID;
    message_data = _message_data;
}

void ApplicationLayerPacket::print() {
    std::cout<< "Sender ID: " << sender_ID << ", Receiver ID: " << receiver_ID << std::endl;

    std::cout << "Message chunk carried: \"" << message_data << "\"" << std::endl;

    // TODO: Override the virtual print function from Packet class to additionally print layer-specific properties.
}

void ApplicationLayerPacket::customPrint() {
    //Carried Message: " leap for this messa"
    //Layer 0 info: Sender ID: C, Receiver ID: E
    std::cout<< "Carried Message: \"" << message_data << "\"" << std::endl;
    std::cout<< "Layer 0 info: Sender ID: " << sender_ID << ", Receiver ID: " << receiver_ID << std::endl;
}

ApplicationLayerPacket::~ApplicationLayerPacket() {
    // TODO: Free any dynamically allocated memory if necessary.
}
