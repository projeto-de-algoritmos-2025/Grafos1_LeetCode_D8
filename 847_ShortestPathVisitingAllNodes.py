from collections import deque

class Solution(object):
    def shortestPathLength(self, graph):
        n = len(graph) #número de nós
        fila = deque() #fila da bfs
        visitados_vistos = set() #conjunto para guardar os estados já vistos

        for i in range(n): 
            visitados = frozenset([i]) 
            fila.append((i, visitados, 0))
            visitados_vistos.add((i, visitados)) #Adiciona na fila e no conjunto de estados já vistos.

        while fila:
            no_atual, visitados, distancia = fila.popleft() #Para cada nó se cria um etado (nó atual, visitados e distância). 
            if len(visitados) == n:
                return distancia #Se todos os nós froam visitados, retorna a distância

            for vizinho in graph[no_atual]: #Expande para os vizinhos. Para cada nó, cria-se o novo ocnjunto de nós visitados
                prox_visitado = visitados | frozenset([vizinho]) #Para cada nó, cria-se o novo ocnjunto de nós visitados
                if (vizinho, prox_visitado) not in visitados_vistos:
                    visitados_vistos.add((vizinho, prox_visitado))
                    fila.append((vizinho, prox_visitado, distancia + 1)) #Se o estado (vizinho, novos visitados) ainda não foi visto, adiciona na fila e no conjunto de estados vistos.

#A primeira vez que todos os nós são visitados, a distância retornada é a menor possível.