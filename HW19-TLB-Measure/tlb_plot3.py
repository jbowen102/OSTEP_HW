import matplotlib.pyplot as plt
import subprocess


trials = 1000000
page_max_exp = 10

run_avg_list = []
run_avg_dict = {}

for page_count_exp in range(1, page_max_exp+1):
    # run_count_list.append(2**page_count_exp * trials)

    page_count = 2**page_count_exp

    CompletedTLB = subprocess.run(['./tlb3', str(page_count), str(trials)])
    avg_runtime = CompletedTLB.returncode
    if avg_runtime < 0:
        print("tlb failed.")
        quit()
    run_avg_dict[page_count] = avg_runtime
    run_avg_list.append(avg_runtime)
    print("%d pages:\t%d ns avg" % (page_count, run_avg_dict[page_count]))

list_of_page_counts = sorted(run_avg_dict.keys())

fig, ax = plt.subplots()
ax.plot(list_of_page_counts, run_avg_list)
ax.set_title("Access Time vs. Page Count")
ax.set_xlabel("Page Count")
ax.semilogx()
ax.set_xticks(list_of_page_counts)
ax.set_xticklabels([str(label) for label in list_of_page_counts])
ax.set_ylabel("Avg Access Time (ns)")
plt.show()
