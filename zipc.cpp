#include "zipc.h"

using boost::interprocess::create_only;
using boost::interprocess::open_or_create;
using boost::interprocess::open_only;

static const string mq_name_prefix = "zipc_rx_fifo_";


int zipc::broker::send_message (const string &id, msg &msg) {
    // If current process not registered -> return
    if (!this->mq)
        return -1;

    // Create message queue name from prefix and id.
    string mq_name = mq_name_prefix;
    if (id.length() >= zipc::max_id_len) {
        mq_name += id.substr(0, zipc::max_id_len - 1);
    } else {
        mq_name += id;
    }

    // Set sender and data_size in msg struct.
    strncpy(msg.sender, this->id.data(), zipc::max_id_len);
    msg.sender[zipc::max_id_len] = '\0';

    if (msg.data_size > zipc::max_data_size)
        msg.data_size = zipc::max_data_size;

    // Calculate Tx buffer size.
    size_t msg_len = sizeof (struct msg) - sizeof (msg.data) + msg.data_size;

    message_queue tx_mq (open_only, mq_name.data());
    tx_mq.send(&msg, msg_len, 0);

    return 0;
}

int zipc::broker::receive_message (zipc::msg &msg) {
    if (!this->mq)
        return -1;

    unsigned int priority;
    message_queue::size_type recvd_size;

    bool ok = this->mq->try_receive(&msg, zipc::max_msg_size, recvd_size, priority);

    if (!ok)
        return -2;

    msg.data_size = recvd_size;

    return 0;
}

int zipc::broker::register_proc (const string &id) {
    lock_guard<mutex> lock(this->mtx);

    if (this->mq)
        return -1;

    this->id = id;

    // open or create an Rx message queue for current process
    string mq_name = mq_name_prefix + id;
    this->mq = make_unique<message_queue> (open_or_create, mq_name.data(), zipc::max_msg_count, zipc::max_msg_size);

    return 0;
}

int zipc::broker::deregister_proc () {
    lock_guard<mutex> lock(this->mtx);

    this->id.clear();
    this->mq.reset();

    return 0;
}


// ha processz normálisan kilép, akkor törölje a sajtát RX queue-ját.
