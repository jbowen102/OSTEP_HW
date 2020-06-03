import matplotlib.pyplot as plt
import subprocess


trials = 2
array_sizes_MB = [1000, 2000, 4000, 8000, 12000]
# array_sizes_MB = [1000, 2000, 4000, 8000, 12000]

run_avg_list = []

filename = 'mem3_output.txt'

for array_size in array_sizes_MB:

    runtime_sum = 0
    for trial in range(trials):

        with open(filename, 'w') as output_file:
            rc = subprocess.call(['./mem3', str(array_size)], stdout=output_file)
            if rc != 0:
                print("mem failed.")
                quit()

        with open(filename, 'r') as output_file:
            # line_no = 0;
            for line in output_file:
                print("mem3 output (%d MB, trial %d): %s" % (array_size, trial, line))
                runtime_ms = int(line)
        runtime_sum += runtime_ms

    avg_runtime = runtime_sum / trials
    run_avg_list.append(avg_runtime)
    print("%d MB:\t%d ms avg" % (array_size, avg_runtime))


fig, ax = plt.subplots()
ax.plot(array_sizes_MB, run_avg_list)
ax.set_title("Run Time vs. Array Size")
ax.set_xlabel("Array Size")
ax.semilogx()
ax.set_xticks(array_sizes_MB)
ax.set_xticklabels([str(label) for label in array_sizes_MB])
ax.set_ylabel("Avg Runtime (ms)")
plt.show()


# laptop crashed running this
