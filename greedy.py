import numpy as np
import matplotlib.pyplot as plt

def do_greedy(px,py,print_output=False):
    
    def greedy(matrix):
        point = 0
        cost = 0
        result = [point]
        best_point = point
        for j in range(len(matrix)-1):
            best_length = -1
            for i,r in enumerate(matrix[point]):
                if i not in result:
                    if best_length == -1 or r < best_length:
                        best_length = r
                        best_point = i
            result.append(best_point)
            point = best_point
            cost += best_length
        cost += matrix[result[len(result)-1]][result[0]]
        return cost,result
    
    matrix = np.sqrt((px - px.T)**2 + (py - py.T)**2)
    cost,solution = greedy(matrix)
    if print_output:
        print("Wynik: ", cost)
        print("Rozwiązanie: ", solution)
        
    return cost,solution

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
cost,solution = do_greedy(px,py,print_output=True)
plot_solution(px,py,solution)