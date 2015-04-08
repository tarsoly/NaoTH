#!/bin/bash

aplay /usr/share/naoqi/wav/chimes_short.wav

infoFile="/home/nao/Config/nao.info"

current_date=$(date +"%y%m%d-%H%M")
current_nao=$(sed -n "2p" $infoFile)

mkdir $current_date-$current_nao

find -L /tmp -type d -name media -prune -o -name "*.log" -exec cp {} /media/brainwasher/$current_date-$current_nao \;

