#include <boost/interprocess/ipc/message_queue.hpp>
#include <unistd.h>
#include <cstddef>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <memory>
#include <atomic>
#include <iostream>
#include <iomanip>


using namespace std;

using boost::interprocess::message_queue;


namespace zipc {

static constexpr size_t max_id_len    = 32;
static constexpr size_t max_data_size = 1024;

struct __attribute__((packed)) msg {
    char sender[max_id_len];
    size_t data_size;
    byte data[max_data_size];
};

void dump_msg(const msg& msg) {
    cout << "[zpic::msg] [sender]    : " << msg.sender << "\n"
         << "[zipc::msg] [data size] : " << msg.data_size << "\n"
         << "[zipc::msg] [data]      : ";

    for (size_t i = 0; i < msg.data_size; i++) {
        if (0 != i && 0 == i % 16) {
            cout << "\n[zipc::msg] [data]      : ";
        }
        cout << hex << setw(2) << setfill('0') << static_cast<unsigned int>(msg.data[i]) << " ";
    }
    cout << dec << endl;

}

static constexpr size_t max_msg_size  = sizeof (msg);
static constexpr size_t max_msg_count = 100;


class broker final {
private:

    broker () {}

    static string id_to_mq_name (const string &id);

    unique_ptr<message_queue> rx_mq;
    string id;
    mutex mtx;
public:
    static broker& get_instance () {
        static broker instance;
        return instance;
    }

    int send_message (const string &id, msg &msg);
    int receive_message (msg &msg, bool blocking = true);
    int register_proc (const string &id);
    int deregister_proc ();
};

};	// namespace zipc
