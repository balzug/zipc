#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>


#include "zipc.h"

using namespace std;


void str_to_lower(std::string& szoveg) {
    std::string eredmeny = szoveg;
    std::transform(eredmeny.begin(), eredmeny.end(), eredmeny.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return;
}


//
int main (int argc, char **argv) {

    string proc_id;
    bool loop = true;

    if (argc < 2) {
        cerr << "[E] process ID not specified as arg #1 !" << endl;
        cout << "[>] Enter process ID string: ";
        cin >> proc_id;

    } else {
        proc_id = argv[1];
    }

    zipc::broker &msg_broker = zipc::broker::get_instance();

    cout << "[I] registering process at zipc::broker as '" << proc_id << "'." << endl;
    if (0 != msg_broker.register_proc(proc_id)) {
        cerr << "[E] failed to register process at zipc::broker!" << endl;
        return -1;
    }


    while (loop) {
        // Read command from stdin.
        string line;
        cout << "[>] Enter command: ";
        getline(cin, line);

        stringstream ss(line);
        string word;

        while (ss >> word) {
            transform(word.begin(), word.end(), word.begin(),
                      [](unsigned char c) { return tolower(c); });
            if ("r" == word || "receive" == word) {
                zipc::msg rx_msg;
                if (0 != msg_broker.receive_message(rx_msg)) {
                    cerr << "[E] error receiving message at '" << proc_id << "'" << endl;
                } else {
                    cout << "[<] ZIPC message received: " << endl;
                    zipc::dump_msg(rx_msg);
                }
            } else if ("s" == word || "send" == word) {
                string recipient_id;
                ss >> recipient_id;
                size_t num;
                ss >> num;
                if (num > zipc::max_data_size)
                    num = zipc::max_data_size;

                zipc::msg tx_msg;

                // Generate random data to be sent.
                srand(time(nullptr));   // Init a random generator
                for (size_t i = 0; i < num; ++i) {
                    tx_msg.data[i] = static_cast<byte>(rand() % 255);
                }
                tx_msg.data_size = num;
                zipc::dump_msg(tx_msg);

                if (0 != msg_broker.send_message(recipient_id, tx_msg)) {
                    cerr << "[E] failed to send message to '" << recipient_id << "'" << endl;
                } else {
                    cout << "[<] ZIPC message sent to '" << recipient_id << "'" << endl;
                }
            } else if ("q" == word || "quit" == word) {
                loop = false;
                break;
            }
        } // while processing 'line'

        // Sleep for a moment. Zzzz...
        this_thread::sleep_for(chrono::milliseconds(100));
    } // while loop

    msg_broker.deregister_proc();

    return 0;
}

