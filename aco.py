import subprocess
import numpy as np
import matplotlib.pyplot as plt

def load_inst(src):
    global n
    f = open(src,"r")
    data = f.read().split()
    n = int(data[0])
    data = data[1:]
    data = list(map(float, data))
    px = np.array([data[1::3]]).T
    py = np.array([data[2::3]]).T
    return px,py

def change_init(ant_number=10,iteration_number=100,pher_start_value=0.1,pher_evap=0.5,pher_infl=1.5,length_infl=5,const_Q=100):
    f = open("aco_config.txt", "w")
    f.write("ant_number "+str(int(ant_number))+"\n")
    f.write("iteration_number "+str(int(iteration_number))+"\n")
    f.write("pheromone_start_value "+str(pher_start_value)+"\n")
    f.write("pheromone_evaporation "+str(pher_evap)+"\n")
    f.write("pheromone_influence "+str(pher_infl)+"\n")
    f.write("length_influence "+str(length_infl)+"\n")
    f.write("const_Q "+str(const_Q)+"\n")
    f.close()

def do_aco(print_output=False, src="inst.txt"):
    f = open(src,"r")
    b = bytearray()
    b.extend(map(ord, f.read()))
    f.close()
    
    proc = subprocess.run(["./aco"],input=b,capture_output=True)
    result = proc.stdout.splitlines()
    time = result[0].decode("utf-8").split()[1]
    cost = result[1].decode("utf-8").split()[1]
    solution = list(map(int,result[2].decode("utf-8").split()[1:]))
    if print_output:
        print("Czas: ", time)
        print("Wynik: ", cost)
        print("Rozwiązanie: ", solution)
    return time,cost,solution

def plot_solution(px,py,solution):
    plt.scatter(px,py)
    x = []
    y = []
    for i in solution:
        x.append(px[i])
        y.append(py[i])
    x.append(x[0])
    y.append(y[0])
    plt.plot(x,y)
    plt.show()

px,py = load_inst("inst.txt")
change_init(ant_number=n/3,iteration_number=200)

time,cost,solution = do_aco(print_output=True, src="inst.txt")
plot_solution(px,py,solution)