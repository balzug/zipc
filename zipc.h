#include <boost/interprocess/ipc/message_queue.hpp>
#include <unistd.h>
#include <cstddef>
#include <vector>
#include <map>
#include <string>
#include <mutex>
#include <memory>
#include <atomic>


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

static constexpr size_t max_msg_size  = sizeof (msg);
static constexpr size_t max_msg_count = 100;


class broker final {
private:

    broker () {}

    unique_ptr<message_queue> mq;
    string id;
    mutex mtx;
public:
    static broker& get_instance () {
        static broker instance;
        return instance;
    }

    int send_message (const string &id, msg &msg);
    int receive_message (msg &msg);
    int register_proc (const string &id);
    int deregister_proc ();
};

};	// namespace zipc
