# ZIPC README

ZIPC provides local inter process communication in the form of the shared library `libzipc.so`.
A process can registed/deregister itself (identified with a max 31 char long string) to the message borker `zipc::broker`.
```C++
#include "zipc.h"

zipc::broker &msg_broker = zipc::broker::get_instance();
msg_broker.register_proc(proc_id))
```
Then it can send and reveive (blocking or non-blocking) messages.

```C++
zipc::msg rx_msg;
msg_broker.receive_message(rx_msg)

```

```C++
zipc::msg tx_msg;
memcpy(tx_msg.data, data, num);
tx_msg.data_size = num;
msg_broker.send_message(recipient_id, tx_msg);
```

In the end, the process can deregiser itself and its Rx message queue is deleted.
ZIPC uses `boost::interprocess::message_queue.`

## Build
```shell
$ make
```
This builds the `libzipc.so` shared library and the sample application `app`.

## Usage
```shell
$ export LD_LIBRARY_PATH=.
$ ./app [APP_ID]
```

Once started, the application registers itself as APP_ID at the zipc message broker.
Then it is waiting for input commands.

```shell
$ ./app A
[I] registering process at zipc::broker as 'A'.
[D] [zipc::broker::register_proc] mq_name    : zipc_rx_fifo_A
[>] Enter command: 
```
When registered, an Rx messages queue is created for the process.

There are three type of commands:
``` shell
 - receive 
   Process is waiting for incomming message in its Rx message queue.
 - send <DEST_ID> <NUM>
   Process sends NUM randomized bytes to process registered with DEST_ID.
 - quit
   Process quits.
```

## Testing
There are two bash scripts in order to demonstrate IPC between two processes.
```shell
 - test_01.sh
   App B sends some random data to app A. Standard output is stored in text files.
 - test_02.sh
   Same as before, but App A terminates abnormally before receiving the message, 
   then it is started again and its Rx message queue is processed.
```