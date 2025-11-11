#!/bin/bash

set -m

FIFO_B=./app_b_in

rm -f $FIFO_B
mkfifo $FIFO_B

./app B < $FIFO_B > b.out.txt 2>&1 &
echo "send A 10" > $FIFO_B
sleep 1

echo "quit" > $FIFO_B
sleep 1

rm -f $FIFO_B

