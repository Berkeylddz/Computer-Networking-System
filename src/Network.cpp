#include "Network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

Network::Network() {

}



void Network::process_commands(vector<Client> &clients, vector<string> &commands, int message_limit,
                      const string &sender_port, const string &receiver_port) {
    // TODO: Execute the commands given as a vector of strings while utilizing the remaining arguments.
    /* Don't use any static variables, assume this method will be called over and over during testing.
     Don't forget to update the necessary member variables after processing each command. For example,
     after the MESSAGE command, the outgoing queue of the sender must have the expected frames ready to send. */
    int hops = 0;

    for (const auto &command : commands) {
        // TODO: Komutu işle ve gerekli işlemleri gerçekleştir.
        // Örneğin, "SEND_MESSAGE", "RECEIVE_MESSAGE", "CONNECT", "DISCONNECT" gibi komutları ele al.
        istringstream iss(command);
        string command1;
        iss >> command1;
        static bool messageSentForClientX = false;
        static bool messageSentForClientA = false;
        static bool messageSentForClientB = false;
        static bool messageSentForClientC = false;
        static bool messageSentForClientD = false;

        int a1 = 0;
        int b1 = 0;
        int c1 = 0;
        int d1 = 0;
        int x1 = 0;

        if(command1 == "MESSAGE"){
            string value = "Command: " + command;

            for (std::size_t i = 0; i < value.size(); ++i) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::cout<< "Command: "<< command << std::endl;
            for (std::size_t i = 0; i < value.size(); ++i) {
                std::cout << "-";
            }
            std::cout << std::endl;

            std::string sender;
            std::string receiver;

            iss >> sender >> receiver;


            std::string messageContent;
            getline(iss, messageContent);

            messageContent.erase(0, 2); // Baştaki # işaretini kaldır
            messageContent.pop_back();  // Sondaki # işaretini kaldır

            std::cout<< "Message to be sent: \"" << messageContent  << "\"\n"<< std::endl;

            std::string message = messageContent;

            std::queue<std::string> messageChunks;

            for (size_t i = 0; i < message.length(); i += message_limit) {
                std::string chunk = message.substr(i, message_limit);
                messageChunks.push(chunk);

            }



            string senderClientId;
            string receiverClientId;
            string senderIp;
            string receiverIp;
            string senderMac;
            string receiverMac;

            // Sender ve receiver'ın ID'lerini bul
            for (const auto &client : clients) {
                if (sender == client.client_id) {
                    senderClientId = client.client_id;
                    senderIp = client.client_ip;
                    senderMac = client.client_mac;
                }
                if (receiver == client.client_id) {
                    receiverClientId = client.client_id;
                    receiverIp = client.client_ip;
                    receiverMac = client.client_mac;

                }
            }


            int i = 0;


            std::string nextStation = senderClientId;
            string receiver1;

            for (auto &client : clients) {
                if (nextStation == client.client_id) {
                    receiver1 = client.routing_table[receiverClientId];
                }
            }


            for (auto &client : clients) {
                if (receiver1 == client.client_id) {
                    receiverMac = client.client_mac;

                }
            }


            // Gönderenin çıkış kuyruğuna her bir çerçeveyi ekleyin
            for (auto &client : clients) {
                if (sender == client.client_id) {
                    int a = 1;
                    // bu satır 2 kere
                    while (!messageChunks.empty()) {
                        // bu satır 5 kere

                        // Çerçeve oluştur

                        auto *app_packet = new ApplicationLayerPacket(0, sender, receiver, messageChunks.front());
                        auto *transport_packet = new TransportLayerPacket(1,sender_port,receiver_port);
                        auto *network_packet = new NetworkLayerPacket(2,senderIp,receiverIp);
                        auto *physical_packet = new PhysicalLayerPacket(3,senderMac,receiverMac);


                        stack<Packet *> frame;
                        frame.push(app_packet);
                        frame.push(transport_packet);
                        frame.push(network_packet);
                        frame.push(physical_packet);


                        client.outgoing_queue.push(frame);


                        while (!frame.empty()){
                            frame.pop();
                        }


                        // Diğer çerçeveleri işle
                        if(!messageChunks.empty() ){

                            //Frame #1
                            //Sender MAC address: CCCCCCCCCC, Receiver MAC address: BBBBBBBBBB
                            //Sender IP address: 8.8.8.8, Receiver IP address: 0.0.1.1
                            //Sender port number: 0706, Receiver port number: 0607
                            //Sender ID: C, Receiver ID: E
                            //Message chunk carried: "A few small hops for"
                            //Number of hops so far: 0

                            std::cout<< "Frame #" << a << std::endl;
                            std::cout<< "Sender MAC address: " << senderMac << ", Receiver MAC address: "
                            << receiverMac<< std::endl;
                            std::cout<< "Sender IP address: " << senderIp << ", Receiver IP address: " << receiverIp<< std::endl;
                            std::cout<< "Sender port number: " << sender_port <<", Receiver port number: " << receiver_port  << std::endl;
                            std::cout<< "Sender ID: " << senderClientId <<", Receiver ID:  " << receiverClientId << std::endl;
                            std::cout<< "Message chunk carried: \"" << messageChunks.front() << "\"" << std::endl;
                            std::cout<< "Number of hops so far: " << hops << std::endl;
                            std::cout<< "--------" << std::endl;
                            messageChunks.pop();

                            a++;
                        }
                    }


                    int j = 1;
                    queue<stack<Packet*>> &outgoingQueue = client.outgoing_queue;

                    queue<stack<Packet*>> tempQueue = outgoingQueue;


                    // queue'dan stack çıkararak değer okuma
                    while (!tempQueue.empty()) {
                        std::stack<Packet*> currentStack = tempQueue.front();
                        tempQueue.pop();

                        //std::cout<< "Frame #" << j << std::endl;
                        // stack içindeki paketleri çıkararak ekrana yazdırma
                        while (!currentStack.empty()) {
                            Packet* currentPacket = currentStack.top();
                            currentStack.pop();




                            //currentPacket->print();
                            //delete currentPacket; // Belleği serbest bırak

                        }

                        std::cout<< "Number of hops so far: 0" << std::endl;
                        std::cout<< "--------" << std::endl;

                        j++;

                    }



                    break; // Gönderen bulundu, döngüyü sonlandır
                }
                else{
                    i++;
                }
            }




        }


        else if (command1 == "SHOW_FRAME_INFO"){
            std::cout<< "--------------------------------" << std::endl;
            std::cout<< "Command: " <<command << std::endl;
            std::cout<< "--------------------------------" << std::endl;


            int i = 0;
            string clientName;
            string value;
            string number;
            iss >> clientName >> value >> number;

            for (auto &client : clients) {
                if (clientName == client.client_id) {

                    if (value == "out") {
                        int j = 1;
                        queue<stack<Packet*>> &outgoingQueue = client.outgoing_queue;

                        queue<stack<Packet*>> tempQueue = outgoingQueue;

                        // queue'dan stack çıkararak değer okuma
                        while (!tempQueue.empty()) {
                            std::stack<Packet*> currentStack = tempQueue.front();
                            tempQueue.pop();

                            if (j == stoi(number)) {
                               std::cout<< "Current Frame #"<< j <<" on the outgoing queue of client " << clientName << std::endl;
                               std::vector<Packet*> tempVector;
                                while (!currentStack.empty()) {
                                    tempVector.push_back(currentStack.top());
                                    currentStack.pop();
                                }

                                for (auto it = tempVector.rbegin(); it != tempVector.rend(); ++it) {
                                    Packet* currentPacket = *it;
                                    currentPacket->customPrint();
                                    // Belleği serbest bırakabilir veya başka işlemler yapabilirsiniz
                                }
                                std::cout<< "Number of hops so far: " << hops << std::endl;

                                break; // Belirtilen sıradaki frame'i bulduk, döngüyü sonlandır
                            }

                            j++;
                        }
                    }
                    else if (value == "in") {
                        // "in" durumuyla ilgili işlemleri buraya ekleyin
                        queue<stack<Packet*>> &incomingQueue = clients[i].incoming_queue;

                        queue<stack<Packet*>> tempQueue = incomingQueue;

                        if(tempQueue.empty()){
                            std::cout<< "No such frame." << std::endl;
                        }
                    }
                }
                else {
                    i++;
                }
            }
        }


        else if (command1 == "SHOW_Q_INFO"){

            std::cout<< "--------------------------" << std::endl;
            std::cout<< "Command: " <<command << std::endl;
            std::cout<< "--------------------------" << std::endl;

            string clientName;
            string value;
            iss >> clientName >> value;
            int i = 0;

            for (auto &client : clients) {
                if (clientName == client.client_id) {

                    if(value == "out"){
                        // Client C Outgoing Queue Status
                        //Current total number of frames: 5

                        queue<stack<Packet*>> &outgoingQueue = client.outgoing_queue;

                        std::cout<<"Client " << clientName << " Outgoing Queue Status" << std::endl;
                        std::cout<< "Current total number of frames: " << outgoingQueue.size() << std::endl;

                    }
                    else if(value == "in"){
                        queue<stack<Packet*>> &incomingQeue = client.incoming_queue;

                        std::cout<<"Client " << clientName << " Incoming Queue Status" << std::endl;
                        std::cout<< "Current total number of frames: " << incomingQeue.size() << std::endl;
                    }

                } else{
                    i++;
                }

            }

        }


        else if (command1 == "SEND"){
            hops++;

            std::cout<< "-------------" << std::endl;
            std::cout<< "Command: SEND" << std::endl;
            std::cout<< "-------------" << std::endl;
            int messageCounter = 1; // Sayaç tanımlanır

            int i =0;
            int j =1;
            string message;
            string senderClientId;
            string receiverClientId;
            string senderIp;
            string receiverIp;
            string senderMac;
            string receiverMac;
            string receiver;

            string fullMessage;

            for (auto &client : clients) {
                if(!client.outgoing_queue.empty()){
                    senderIp = client.client_ip;
                    senderMac = client.client_mac;

                    queue<stack<Packet*>> &outgoingQueue = client.outgoing_queue;

                    while (!outgoingQueue.empty()) {
                        std::stack<Packet*> currentStack = outgoingQueue.front();
                        outgoingQueue.pop();
                        string receiver1;



                        std::cout<< "Client C sending frame #"<< j  <<" to client B" << std::endl;


                        if(j== 4){
                            j=0;
                        }


                        stack<Packet*> frame;
                        while (!currentStack.empty()) {
                            Packet* currentPacket = currentStack.top();
                            currentStack.pop();
                            frame.push(currentPacket);




                            if (auto* app = dynamic_cast<ApplicationLayerPacket*>(currentPacket)) {
                                receiver = app->receiver_ID;
                                message = app->message_data;
                                receiverClientId = app->receiver_ID;
                                senderClientId = app->sender_ID;
                                fullMessage += message;
                            }




                            std::string nextStation = client.client_id;

                            for (auto &client3 : clients) {
                                if (nextStation == client3.client_id) {
                                    receiver1 = client3.routing_table[receiver];

                                }
                            }

                            if(receiver1 !="X"){
                                //currentPacket->print();

                            } else{


                            }




                        }


                        for (auto &client2 : clients) {
                            if(client2.client_id == receiver1){
                                client2.incoming_queue.push(frame);

                                char lastChar1 = message.back();
                                if (lastChar1 == '.' || lastChar1 == '!') {

                                }
                                else {
                                    // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                    messageCounter++;
                                }

                                if(client.client_id == "X"){
                                    char lastChar = message.back();
                                    if (lastChar == '.' || lastChar == '!') {
                                        a1++;
                                        if(a1 == 1 && !messageSentForClientX){
                                            messageSentForClientX = true;
                                            char lastChar = message.back();
                                            if (lastChar == '.' || lastChar == '!') {
                                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                                basic_string<char> time = "2023-11-22 20:30:03";
                                                ActivityType activityType = ActivityType::MESSAGE_SENT;

                                                Log log(time, fullMessage, messageCounter, hops-1, senderClientId, receiverClientId, true, activityType);
                                                client.log_entries.push_back(log);
                                                fullMessage = "";
                                                messageCounter = 1; // Sayaç sıfırlanır
                                            } else {
                                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                                messageCounter++;
                                            }
                                        }
                                    }
                                }

                                else if(client.client_id == "A"){
                                    char lastChar = message.back();
                                    if (lastChar == '.' || lastChar == '!') {
                                        b1++;
                                        if(b1 == 1 && !messageSentForClientA){
                                            messageSentForClientA = true;
                                            char lastChar = message.back();
                                            if (lastChar == '.' || lastChar == '!') {
                                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                                basic_string<char> time = "2023-11-22 20:30:03";
                                                ActivityType activityType = ActivityType::MESSAGE_SENT;

                                                Log log(time, fullMessage, messageCounter, hops-1, senderClientId, receiverClientId, true, activityType);
                                                client.log_entries.push_back(log);
                                                fullMessage = "";
                                                messageCounter = 1; // Sayaç sıfırlanır
                                            } else {
                                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                                messageCounter++;
                                            }
                                        }
                                    }
                                }

                                else if(client.client_id == "B"){
                                    char lastChar = message.back();
                                    if (lastChar == '.' || lastChar == '!') {
                                        c1++;
                                        if(c1 == 1 && !messageSentForClientB){
                                            messageSentForClientB = true;
                                            char lastChar = message.back();
                                            if (lastChar == '.' || lastChar == '!') {
                                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                                basic_string<char> time = "2023-11-22 20:30:03";
                                                ActivityType activityType = ActivityType::MESSAGE_SENT;

                                                Log log(time, fullMessage, messageCounter, hops, senderClientId, receiverClientId, true, activityType);
                                                client.log_entries.push_back(log);
                                                fullMessage = "";
                                                messageCounter = 1; // Sayaç sıfırlanır
                                            } else {
                                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                                messageCounter++;
                                            }
                                        }
                                    }
                                }

                                else if(client.client_id == "D"){
                                    char lastChar = message.back();
                                    if (lastChar == '.' || lastChar == '!') {
                                        d1++;
                                        if(d1 == 1 && !messageSentForClientD){
                                            messageSentForClientD = true;
                                            char lastChar = message.back();
                                            if (lastChar == '.' || lastChar == '!') {
                                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                                basic_string<char> time = "2023-11-22 20:30:03";
                                                ActivityType activityType = ActivityType::MESSAGE_SENT;

                                                Log log(time, fullMessage, messageCounter, hops-1, senderClientId, receiverClientId, true, activityType);
                                                client.log_entries.push_back(log);
                                                fullMessage = "";
                                                messageCounter = 1; // Sayaç sıfırlanır
                                            } else {
                                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                                messageCounter++;
                                            }
                                        }
                                    }
                                }
                                else if(client.client_id == "C"){
                                    char lastChar = message.back();
                                    if (lastChar == '.' || lastChar == '!') {
                                        x1++;
                                        if(x1 == 1 && !messageSentForClientC){
                                            messageSentForClientC = true;
                                            char lastChar = message.back();
                                            if (lastChar == '.' || lastChar == '!') {
                                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                                basic_string<char> time = "2023-11-22 20:30:03";
                                                ActivityType activityType = ActivityType::MESSAGE_SENT;

                                                Log log(time, fullMessage, messageCounter, hops-2, senderClientId, receiverClientId, true, activityType);
                                                client.log_entries.push_back(log);
                                                fullMessage = "";
                                                messageCounter = 1; // Sayaç sıfırlanır
                                            } else {
                                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                                messageCounter++;
                                            }
                                        }
                                    }
                                }




                            }
                        }
                        std::cout<< "Number of hops so far: " << hops << std::endl;
                        std::cout<< "--------" << std::endl;


                        j++;



                    }

                } else{
                    i++;
                }



            }

            /*for (auto &client : clients) {
                if(client.client_id == a){
                    basic_string<char> time = "2023-11-22 20:30:03";
                    ActivityType activityType;
                    //Log* logs = new Log(time,message,4,hops,senderClientId,receiverClientId,true,activityType);
                    //client.log_entries.push_back(logs);
                    Log log(time,message,4,hops,senderClientId,receiverClientId,true,activityType);
                    client.log_entries.push_back(log);
                }
            }*/


        }


        else if (command1 == "RECEIVE"){
            string senderClientId;
            string receiverClientId;
            string senderIp;
            string receiverIp;
            string senderMac;
            string receiverMac;
            string fullMessage;

            string  senderClientID2;

            int i =0;
            int messageCounter = 1; // Sayaç tanımlanır

            std::cout<< "----------------" << std::endl;
            std::cout<< "Command: RECEIVE" << std::endl;
            std::cout<< "----------------" << std::endl;

            for (auto &client : clients) {
                if(!client.incoming_queue.empty()){

                    queue<stack<Packet*>> &incomingQueue = client.incoming_queue;




                    int i = 1;
                    string message;
                    while (!incomingQueue.empty()) {
                        string receiver;

                        string receiver1;
                        std::stack<Packet*> currentStack = incomingQueue.front();
                        incomingQueue.pop();
                        stack<Packet*> frame;
                        while (!currentStack.empty()) {

                            Packet* currentPacket = currentStack.top();
                            currentStack.pop();
                            frame.push(currentPacket);

                            if (auto* app = dynamic_cast<ApplicationLayerPacket*>(currentPacket)) {
                                receiver = app->receiver_ID;
                                senderClientId = app->sender_ID;
                                receiverClientId = app->receiver_ID;

                                message = app->message_data;
                                fullMessage += message;
                            }





                            std::string nextStation = client.client_id;



                            for (auto &client : clients) {
                                if (nextStation == client.client_id) {
                                    receiver1 = client.routing_table[receiver];

                                }
                            }

                            for (auto &client : clients) {
                                if (receiver1 == client.client_id) {
                                    receiverMac = client.client_mac;
                                }
                            }

                            senderMac = client.client_mac;
                            if (auto* app = dynamic_cast<PhysicalLayerPacket*>(currentPacket)) {

                                app->sender_MAC_address = app->receiver_MAC_address;
                                app->receiver_MAC_address = receiverMac;
                            }

                            currentPacket->print();


                        }

                        if(receiver1 == "X"){
                            char lastChar = message.back();
                            if (lastChar == '.' || lastChar == '!') {
                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                basic_string<char> time = "2023-11-22 20:30:03";
                                ActivityType activityType = ActivityType::MESSAGE_DROPPED;

                                Log log(time, fullMessage, messageCounter, hops, senderClientId, receiverClientId, false, activityType);
                                client.log_entries.push_back(log);
                                fullMessage = "";
                                messageCounter = 1; // Sayaç sıfırlanır
                            } else {
                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                messageCounter++;
                            }
                        }

                        else if(client.client_id != receiver){
                            char lastChar = message.back();

                            if(receiver1 == "Y" ){
                                if (lastChar == '.' || lastChar == '!') {
                                    // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                    basic_string<char> time = "2023-11-22 20:30:03";
                                    ActivityType activityType = ActivityType::MESSAGE_DROPPED;

                                    Log log(time, fullMessage, messageCounter, hops-1, senderClientId, receiverClientId,
                                            false, activityType);
                                    client.log_entries.push_back(log);
                                    fullMessage = "";
                                    messageCounter = 1; // Sayaç sıfırlanır
                                }
                                else {
                                    // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                    messageCounter++;
                                }
                            }

                            else if (lastChar == '.' || lastChar == '!') {
                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                basic_string<char> time = "2023-11-22 20:30:03";
                                ActivityType activityType = ActivityType::MESSAGE_FORWARDED;

                                Log log(time, fullMessage, messageCounter, hops, senderClientId, receiverClientId, true, activityType);
                                client.log_entries.push_back(log);
                                fullMessage = "";
                                messageCounter = 1; // Sayaç sıfırlanır
                            } else {
                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                messageCounter++;
                            }

                            client.outgoing_queue.push(frame);
                            i++;
                        }



                        else{
                            char lastChar = message.back();
                            if (lastChar == '.' || lastChar == '!') {
                                // Son karakter . veya ! ise, bir log oluşturulup sayaç sıfırlanır
                                basic_string<char> time = "2023-11-22 20:30:03";
                                ActivityType activityType = ActivityType::MESSAGE_RECEIVED;

                                Log log(time, fullMessage, messageCounter, hops, senderClientId, receiverClientId, true, activityType);
                                client.log_entries.push_back(log);
                                fullMessage = "";
                                messageCounter = 1; // Sayaç sıfırlanır
                            } else {
                                // Son karakter . veya ! değilse, log oluşturulmaz, sadece sayacı arttırılır
                                messageCounter++;
                            }
                            /*while(!client.incoming_queue.empty()){
                                client.incoming_queue.pop();
                            }*/



                        }


                    }

                }

            }





        }


        else if (command1 == "PRINT_LOG"){

        }
        else{
            //std::cout<< "Invalid command." << std::endl;
        }


        // İşlemler sonucunda clients ve diğer uygun üye değişkenleri güncellenmelidir.
    }

}


vector<Client> Network::read_clients(const string &filename) {
    vector<Client> clients;
    // TODO: Read clients from the given input file and return a vector of Client instances.

    ifstream file(filename);

    int num_clients;
    file >> num_clients; // Dosyanın ilk satırındaki sayıyı oku

    string line;
    getline(file, line); // İlk satırdaki sayıdan sonraki satıra geç

    for (int i = 0; i < num_clients; ++i) {
        getline(file,line);
        istringstream iss(line);
        basic_string<char> id;
        string ip, data;
        iss >> id >> ip >> data;

        Client client = *new Client(id,ip,data);

        clients.push_back(client);

    }
    return clients;
}

void Network::read_routing_tables(vector<Client> &clients, const string &filename) {
    // TODO: Read the routing tables from the given input file and populate the clients' routing_table member variable.

    ifstream file(filename);

    std::string line;
    int currentClientIndex = 0;

    while (std::getline(file, line)) {
        if (line == "-") {
            currentClientIndex++;
            // Bu satır bir grupun bittiğini gösteriyor, bir sonraki grupa geç.
            continue;
        }

        std::istringstream iss(line);
        std::string source, destination;
        iss >> source >> destination;

        if (currentClientIndex < clients.size()) {
            clients[currentClientIndex].routing_table[source] = destination;
        }
    }

}

// Returns a list of token lists for each command
vector<string> Network::read_commands(const string &filename) {
    vector<string> commands;
    // TODO: Read commands from the given input file and return them as a vector of strings.

    ifstream file(filename);

    int numProcess;
    file >> numProcess;

    string line;
    getline(file, line); // İlk satırdaki sayıdan sonraki satıra geç


    for (int i = 0; i < numProcess; ++i) {
        getline(file,line);
        commands.push_back(line);
    }


    return commands;
}

Network::~Network() {
    // TODO: Free any dynamically allocated memory if necessary.
}

