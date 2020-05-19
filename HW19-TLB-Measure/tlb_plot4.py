import matplotlib.pyplot as plt
import subprocess

# Manually plot RPi results since it can't import matplotlib
list_of_page_counts = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024]
run_avg_list = [28, 37, 42, 43, 43, 37, 100, 163, 192, 202]

fig, ax = plt.subplots()
ax.plot(list_of_page_counts, run_avg_list)
ax.set_title("Access Time vs. Page Count")
ax.set_xlabel("Page Count")
ax.semilogx()
ax.set_xticks(list_of_page_counts)
ax.set_xticklabels([str(label) for label in list_of_page_counts])
ax.set_ylabel("Avg Access Time (ns)")
plt.show()
