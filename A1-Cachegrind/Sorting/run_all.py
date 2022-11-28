import os
sort_types = ["bubble", "selection", "merge", "quick", "radix"]            # Selection and bubble sort will consume a lot of time.
array_sizes = [250000, 500000, 750000, 1000000]     # Array sort size

os.system("mkdir -p output")                        # All output files are stored inside output directory
for sort_type in sort_types:
    os.system("mkdir -p output/"+sort_type)
    for array_size in array_sizes:
        os.system("mkdir -p output/"+sort_type+"/"+str(array_size))
        print("Running", sort_type.upper(), "sort of array size", str(array_size))
        os.system("gcc -o "+sort_type+".out "+sort_type+"Sort.c")       # Compile C code
        os.system("valgrind --tool=cachegrind --I1=32768,16,32 --cachegrind-out-file=output/"+sort_type+"/"+str(array_size)+"/cache_statistics.txt ./"+sort_type+".out "+str(array_size))        # Run cachegrind to obtain the instruction count
        os.system("perf stat -o output/"+sort_type+"/"+str(array_size)+"/perf_statistics.txt "+"./"+sort_type+".out "+str(array_size))                                          # Run perf to obtain the IPC
        instr_count = int(os.popen("cg_annotate "+"output/"+sort_type+"/"+str(array_size)+"/cache_statistics.txt").read().rsplit("\n")[17].split(" ")[0].replace(",",""))       # Extract instruction count from the cachegrind output
        print("Instruction count: ", instr_count)
        ipc = open("output/"+str(sort_type)+"/"+str(array_size)+"/perf_statistics.txt").readlines()[10].split("#")[-1].split("insn")[0]                                         # Extract IPC from perf output file
        print("IPC count from perf command: ", ipc.strip())
