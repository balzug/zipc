#!/bin/bash

set -m

FIFO_A=./app_a_in

rm -f $FIFO_A
mkfifo $FIFO_A

./app A < $FIFO_A > a.out.txt 2>&1 &
echo "receive" > $FIFO_A
sleep 1 

echo "quit" > $FIFO_A
sleep 1

rm -f $FIFO_A

