import numpy as np

# Example execution times for each configuration
times_100_1 = [0.000050, 0.000049, 0.000050, 0.000049, 0.000093, 0.000050, 0.000050, 0.000051, 0.000050, 0.000057]
times_100_10000 = [0.059234, 0.048930, 0.059467, 0.050815, 0.049749 , 0.050127, 0.059059, 0.050606, 0.048266, 0.049441]
times_1000_1000 = [0.049937, 0.059918, 0.051224, 0.059840, 0.049153, 0.058530, 0.050406, 0.050920, 0.050416, 0.060223]
times_10000_1 = [0.001810, 0.001434, 0.001449, 0.001838, 0.001626, 0.001437, 0.001534, 0.001739, 0.001498, 0.001624]

# Calculate mean and standard deviation
def calculate_stats(times):
    mean = np.mean(times)
    std_dev = np.std(times, ddof=1)  # Sample standard deviation
    return mean, std_dev

means = [
    calculate_stats(times_100_1),
    calculate_stats(times_100_10000),
    calculate_stats(times_1000_1000),
    calculate_stats(times_10000_1)
]

for i, (mean, std_dev) in enumerate(means):
    print(f"Configuration {i + 1}: Mean = {mean:.6f}, Standard Deviation = {std_dev:.6f}")
