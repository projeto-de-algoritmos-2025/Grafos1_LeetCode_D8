class Solution(object):
    def findCircleNum(self, isConnected):
        n = len(isConnected) #número de cidades
        visited = [False] * n #vetor que marca as cidades visitadas
        provinces = 0 #contador de provincias

        for i in range(n):  #Para cada cidade i ate i-1 vê se já foi visitada, se não foi, indica nova provícia
            if not visited[i]:
                stack = [i] 
                while stack:
                    node = stack.pop()  # enquanto a pilha não está vazia, retira um nó
                    if not visited[node]:
                        visited[node] = True # se o nó ainda não foi visitado, marca como visitado
                        for j in range(n):
                            if isConnected[node][j] == 1 and not visited[j]:
                                stack.append(j) # Percorre todas as cidades j e caso j pertença a mesma provícia que [node] entao coloca j na pilha para vistar dps
                provinces += 1 # foi visitado toda a província iniciada em i e incrementa o contador de provicias

        return provinces
