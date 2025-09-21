import heapq

class Solution(object):
    def reachableNodes(self, edges, maxMoves, n):
        """
        :type edges: List[List[int]]
        :type maxMoves: int
        :type n: int
        :rtype: int
        """
        # Grafo: adj[u] = [(v, cnt), ...]
        graph = [[] for _ in range(n)]
        for u, v, cnt in edges:
            graph[u].append((v, cnt))
            graph[v].append((u, cnt))
        
        # Dijkstra
        dist = [float("inf")] * n
        dist[0] = 0
        heap = [(0, 0)]  # (dist, node)
        
        while heap:
            d, u = heapq.heappop(heap)
            if d > dist[u]:
                continue
            for v, cnt in graph[u]:
                nd = d + cnt + 1
                if nd < dist[v]:
                    dist[v] = nd
                    heapq.heappush(heap, (nd, v))
        
        # Contar nós originais alcançáveis
        result = sum(1 for d in dist if d <= maxMoves)
        
        # Contar nós subdivididos
        for u, v, cnt in edges:
            reach_from_u = max(0, maxMoves - dist[u])
            reach_from_v = max(0, maxMoves - dist[v])
            result += min(cnt, reach_from_u + reach_from_v)
        
        return result
