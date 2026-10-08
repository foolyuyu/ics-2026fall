# Use Intel assembly syntax
set disassembly-flavor att

# Set default input file, avoiding manual input each time
set args psol.txt

# Stop before entering the explosion function
b explode_bomb

# Set breakpoints at each phase function to monitor execution
b phase_1
b phase_2
b phase_3
b phase_4
b phase_5
b phase_6