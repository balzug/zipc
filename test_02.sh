#!/bin/bash

set -m

FIFO_A=./app_a_in
FIFO_B=./app_b_in

mkfifo $FIFO_A
mkfifo $FIFO_B

./app A < $FIFO_A > a.out.txt 2>&1 &
echo "receive" > $FIFO_A
sleep 1 

./app B < $FIFO_B > b.out.txt 2>&1 &
echo "send A 10" > $FIFO_B
sleep 1

echo "quit" > $FIFO_B
sleep 1
echo "quit" > $FIFO_A
sleep 1

rm -f $FIFO_A
rm -f $FIFO_B

