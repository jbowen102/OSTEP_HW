import matplotlib
import subprocess

trials = 10
page_max_exp = 10

run_count_list = []
with open('output.txt', 'w') as output_file:
    for pages_accessed in range(page_max_exp):
        run_count_list.append(pages_accessed * trials)
        subprocess.call(['./tlb2', str(2**pages_accessed), str(trials)], stdout=output_file)
        # print(mylist)
        # rc = subprocess.call(['./tlb2', str(2**pages_accessed), '10'], stdout=mylist)
        # print(rc)

output_array = []
with open('output.txt', 'r') as output_file:
    for page_count in run_count_list:
        for line in output_file:
            output_array.append(int(line))
            page_count -= 1;

print(output_array[:10])
