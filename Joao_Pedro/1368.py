from collections import deque

class Solution(object):
    def minCost(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        
        # direções: direita, esquerda, baixo, cima
        dirs = [(0,1), (0,-1), (1,0), (-1,0)]
        
        # fila deque para 0-1 BFS
        dq = deque()
        dq.append((0,0,0))  # (linha, coluna, custo)
        
        # matriz de distâncias
        dist = [[float("inf")] * n for _ in range(m)]
        dist[0][0] = 0
        
        while dq:
            x, y, cost = dq.popleft()
            
            # se chegamos ao destino
            if x == m-1 and y == n-1:
                return cost
            
            for d, (dx, dy) in enumerate(dirs, start=1):
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n:
                    # se a direção do grid coincide com a seta, custo extra = 0
                    ncost = cost + (0 if grid[x][y] == d else 1)
                    
                    if ncost < dist[nx][ny]:
                        dist[nx][ny] = ncost
                        if grid[x][y] == d:
                            dq.appendleft((nx, ny, ncost))  # custo 0 → frente
                        else:
                            dq.append((nx, ny, ncost))      # custo 1 → trás
        
        return -1  # nunca deve acontecer
