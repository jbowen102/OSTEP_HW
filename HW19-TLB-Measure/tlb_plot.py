import matplotlib.pyplot as plt
import subprocess

trials = 100
page_max_exp = 10

run_avg_list = []

run_avg_dict = {}

filename = 'output.txt'

for page_count_exp in range(1, page_max_exp+1):
    # run_count_list.append(2**page_count_exp * trials)

    page_count = 2**page_count_exp

    with open(filename, 'w') as output_file:
        subprocess.call(['./tlb2', str(page_count), str(trials)], stdout=output_file)

    output_sum = 0
    # print("\n----%s-----\n" % page_count)
    with open(filename, 'r') as output_file:
        for line in output_file:
            # print("line: %s" % line)
            output_sum += int(line)

    avg_runtime = output_sum / page_count
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

    # print(mylist)
    # rc = subprocess.call(['./tlb2', str(2**page_count_exp), '10'], stdout=mylist)
    # print(rc)
#
# output_array = []
# with open(filename, 'r') as output_file:
#     for page_count in run_count_list:
#         for line in output_file:
#             output_array.append(int(line))
#             page_count -= 1;
#
# print(output_array[:10])
