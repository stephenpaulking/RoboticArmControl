#!/bin/sh
#
# generated.sh - shell script fragment - not very useful on its own
#
# Machine generated for a CPU named "cpu" as defined in:
# /home/netlab/s2king/quartus_project/DE0_SOPC.ptf
#
# Generated: 2013-04-03 12:25:02.137

# DO NOT MODIFY THIS FILE
#
#   Changing this file will have subtle consequences
#   which will almost certainly lead to a nonfunctioning
#   system. If you do modify this file, be aware that your
#   changes will be overwritten and lost when this file
#   is generated again.
#
# DO NOT MODIFY THIS FILE

# This variable indicates where the PTF file for this design is located
ptf=/home/netlab/s2king/quartus_project/DE0_SOPC.ptf

# This variable indicates whether there is a CPU debug core
nios2_debug_core=yes

# This variable indicates how to connect to the CPU debug core
nios2_instance=0

# This variable indicates the CPU module name
nios2_cpu_name=cpu

# These variables indicate what the System ID peripheral should hold
sidp=0x000000e0
id=0u
timestamp=1363684272u

# Include operating system specific parameters, if they are supplied.

if test -f /altera/11.0/nios2eds/components/altera_hal/build/os.sh ; then
   . /altera/11.0/nios2eds/components/altera_hal/build/os.sh
fi
