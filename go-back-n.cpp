#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cstring>
using namespace std;

const int WINDOW_SIZE = 4;
const int TIMEOUT = 5;

struct packet {
    int seq_num;
    bool ack_received;
    string data;
};

int main() {
    srand(time(NULL));

    // Create a list of packets to send
    string message;
    cout << "Enter your message:\n";
    std::getline(std::cin, message);
    cout<< "\n";
    int num_packets = message.size();
    packet packets[num_packets];
    for (int i = 0; i < num_packets; i++) {
        packets[i].seq_num = i;
        packets[i].ack_received = false;
        packets[i].data = message[i];
    }

    // Send packets using GBN protocol
    int base = 0;
    int next_seq_num = 0;
    while (base < num_packets) {
        // Send packets in window
        for (int i = base; i < min(base + WINDOW_SIZE, num_packets); i++) {
            std::cout << "Sending packet: " << packets[i].seq_num << " \"" << message[i]<< "\"" << endl;
        }

        // Wait for ACKs
        int num_acks_received = 0;
        int timeout_count = 0;
        while (num_acks_received < WINDOW_SIZE && timeout_count < TIMEOUT) {
            usleep(1000000); // Wait 1 second
            for (int i = base; i < min(base + WINDOW_SIZE, num_packets); i++) {
                if (packets[i].ack_received == false && rand() % 2 == 1) {
                    cout << "\t\t\tReceived ACK for packet: " << packets[i].seq_num << " \"" << message[i]<< "\""<< endl;
                    packets[i].ack_received = true;
                    num_acks_received++;
                }
            }
            timeout_count++;
        }

        // Resend packets that did not receive an ACK
        for (int i = base; i < min(base + WINDOW_SIZE, num_packets); i++){
            if (num_acks_received < WINDOW_SIZE && packets[i].ack_received == false) {
                    cout << "Timeout occurred, resending packet: " << packets[i].seq_num << " \""<< message[i]<< "\""<< endl;
            }
        }
        // Slide the window
        while (packets[base].ack_received == true) {
            base++;
            next_seq_num++;
        }
    }
    cout<< "\nAll packets has been sent succesfully!"<<endl;
    return 0;
}
