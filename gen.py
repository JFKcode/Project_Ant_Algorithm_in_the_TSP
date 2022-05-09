import numpy as np

print("Podaj liczbę punktów:")
n = int(input())
max_x = 100
max_y = 100
px = np.random.rand(n,1) * max_x
py = np.random.rand(n,1) * max_y
f = open("inst.txt", "w")
f.write(str(n) + "\n")
for i in range(n):
    f.write(str(i+1)+" "+str(round(px[i][0],3))+" "+str(round(py[i][0],3))+"\n")
f.close()
