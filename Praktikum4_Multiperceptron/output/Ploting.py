import matplotlib.pyplot as plt

# Membaca data dari file
iterations = []
errors = []

with open("E:/SEMESTER 4/SISTEM CERDAS/Latihan/Praktikum4_SistemCerdas/output/init=0.55.txt", "r") as file:
    for line in file:
        iter_num, error_val = line.split()
        iterations.append(int(iter_num))
        errors.append(float(error_val))

# Plotting data
plt.figure(figsize=(10, 5))
plt.plot(iterations, errors, marker='o', linestyle='-', color='b', label="Error")

plt.xlabel("Iterasi")
plt.ylabel("Error")
plt.title("Grafik Error selama Training")
plt.legend()
plt.grid(True)
plt.show()
