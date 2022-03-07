#!/bin/bash -i

FVP="/opt/VHT/VHT_Corstone_SSE-300_Ethos-U55"
FVP_ARGS="-C cpu_core.mps3_board.smsc_91c111.enabled=1 -C cpu_core.mps3_board.hostbridge.userNetworking=1 -C cpu_core.cpu0.semihosting-enable=1 -C cpu_core.mps3_board.telnetterminal0.start_telnet=0 -C cpu_core.mps3_board.uart0.out_file="-"  -C cpu_core.mps3_board.uart0.unbuffered_output=1 -C cpu_core.mps3_board.uart0.shutdown_on_eot=1 --stat -C cpu_core.mps3_board.DISABLE_GATING=1 -a cpu_core.cpu0*=$1"

set -x;

if [[ $DISPLAY ]]; then
    eval "x-terminal-emulator -e /bin/bash -i -c '$FVP $FVP_ARGS' &"
else
    eval "$FVP $FVP_ARGS"
fi
