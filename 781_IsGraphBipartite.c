// bool é o tipo de retorno, já que o grafo pode ou não ser bipartido.
//__int** graph__ é o grafo que está sendo representado como lista de adjacência, como pede a questão.
//__int graphSize__ representa o número de nós no grafo.
//__int graphColSize__ armazena o número de vizinhos de cada nó.
//__int* colors__ é o array de cores. 
//__int startNode__ é o nó de onde a busca começa.

// A função __is_bipartite_bfs__ realiza a busca em largura (BFS), colore os nós e verifica os conflitos de cores
bool is_bipartite_bfs(int** graph, int graphSize, int* graphColSize, int* colors, int startNode) {
    // 1 - Cria-se uma fila que irá armazenar os nós a serem explorados
    int queue[graphSize];
    int head = 0, tail = 0;
    
    // 2 - Adiciona-se o primeiro nó a fila e o colore com a cor 1.
    queue[tail++] = startNode;
    colors[startNode] = 1;
    //Obs.: As cores são 1 ou 2, e 0 representa os nós não visitados.

    // Enquanto a fila não estiver vazia, a busca será executada(Lógica principal da BFS).
    while (head < tail) {
        // 3- O primeiro nó da u fila é pego.
        int u = queue[head++];
        
        // Função que define a cor oposta para os vizinhos.
        int nextColor = (colors[u] == 1) ? 2 : 1;
        
        // 4 - Percorre todos os vizinhos do nó u.
        for (int i = 0; i < graphColSize[u]; i++) {
            int v = graph[u][i];
            
            // 5 - Verificação 1: o vizinho v ainda não foi pintado?
            if (colors[v] == 0) {
                colors[v] = nextColor; // Pinta com a cor oposta
                queue[tail++] = v;    // Adiciona o vizinho na fila
            } 
            // 6 - Verificação 2: o vizinho v já foi pintado e tem a mesma cor que u?
            else if (colors[v] == colors[u]) {
                return false; // O grafo não é bipartido!
            }
            //Os casos restantes não implicam em "não bipartição" e a busca continua.
        }
    }
    
    // Se a busca terminou sem conflitos, a parte visitada do grafo é bipartida.
    return true;
}


// A função __isBipartite__ retorna o que de fato se quer saber, se o grafo é bipartido ou não.
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* colors = (int*)malloc(graphSize * sizeof(int));
    
    for (int i = 0; i < graphSize; i++){
        colors[i] = 0; 
    } 

    for (int i = 0; i < graphSize; i++) {
        if (colors[i] == 0) { // "Se o nó não foi pintado ainda".
            //Chama-se a função de busca e coloração.
            if (!is_bipartite_bfs(graph, graphSize, graphColSize, colors, i)) {
                // Se a função retornar "false" implica que o grafo não é bipartido e portanto temos o resultado.
                free(colors); 
                return false;
            }
        }
    } 
    free(colors); 
    return true;
}
    