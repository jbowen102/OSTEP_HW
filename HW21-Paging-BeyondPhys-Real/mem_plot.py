import matplotlib.pyplot as plt
import subprocess


trials = 1
array_sizes_MB = [1000, 2000, 4000]
# array_sizes_MB = [1000, 2000, 4000, 8000, 12000]

run_avg_list = []
runtime_sum = 0

for array_size in array_sizes_MB:

    for trial in range(trials):

        CompletedMem = subprocess.run(['./mem2', str(array_size)])
        # CompletedMem = subprocess.Popen(['./mem2', str(array_size)])
        # CompletedMem.wait()
        # # https://stackoverflow.com/questions/15107714/wait-process-until-all-subprocess-finish
        runtime_ms = CompletedMem.returncode
        print("runtime_ms returned: %d" % runtime_ms)
        if runtime_ms == 0:
            print("mem failed.")
            quit()
        runtime_sum += runtime_ms

    avg_runtime = runtime_sum / trials
    print("avg_runtime: %d" % avg_runtime)
    run_avg_list.append(avg_runtime)
    print("%d MB:\t%d ms avg" % (array_size, avg_runtime))
    runtime_sum = 0

fig, ax = plt.subplots()
ax.plot(array_sizes_MB, run_avg_list)
ax.set_title("Run Time vs. Array Size")
ax.set_xlabel("Array Size")
ax.semilogx()
ax.set_xticks(array_sizes_MB)
ax.set_xticklabels([str(label) for label in array_sizes_MB])
ax.set_ylabel("Avg Runtime (ms)")
plt.show()

# can't get this to work right because subprocess.run() not returning correct
# return code
