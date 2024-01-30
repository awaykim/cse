#include <stdio.h>
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
}Graph;

int selected[MAX_VERTICES];
int dist[MAX_VERTICES];


int get_min_vertex(int n)
{
    int v, i; 
    for (i = 0; i < n; i++) {
        if (!selected[i]) {
            v = i; 
            break;
        }
    }
    for (i = 0; i < n; i++) 
        if (!selected[i] && (dist[i] < dist[v])) v = i;  
     return(v);
    
    
}

// Prim, s는 시작 정점
void prim(Graph* g, int s)
{
    int i, u, v;

    for (u = 0; u < g->n; u++)  // dist배열과 selected배열의 정보를 초기화
    {
        dist[u] = INF;
        
    }

    dist[s] = 0;  // 시작정점과 시작정점간의 거리는 0이다. 자기자신을 순환하는 경로는 없다고 가정한다.

    for (i = 0; i < g->n; i++)
    {
        u = get_min_vertex(g->n);
        selected[u] = TRUE; // 최소거리를 갖는 정점의 정보(u)를 알아냈으니 해당 정점을 선택했다고 표시한다.

        // 만약 경로가 없다면 함수를 종료한다. 정상적인 신장트리의 정보가 들어왔다면 실행될 일은 없을 것이다.
        if (dist[u] == INF) return;

        printf("정점 %d \n ", u); // 방문한 정점(u)을 출력한다.
        for (int k = 0; k < 6; k++)
            printf("dist[%d] %d  .. ", k, dist[k]);

        for (v = 0; v < g->n; v++)  
        {
            // 선택된 u 정점을 기준으로 정점(u)과 연결되어 있는 정점까지의 거리를 각각 비교한다.
            if (g->weight[u][v] != INF)  // 정점 u와 연결이 되어있고
            {
                // 아직 선택되지 않았으며 해당 변(weight[u][v])의 길이가 기존의 dist[v] 값보다 작다면
                if (!selected[v] && g->weight[u][v] < dist[v])
                    dist[v] = g->weight[u][v]; // dist[v]의 값을 갱신해준다.

    
            }
        }
    }
}

void main()
{
    Graph g = { 6, {
  {0 , 20 ,  24 , INF , 25 , INF },
  {20 , 0 , INF , 7,   12 ,    5 },
  {24 , INF, 0,   22,  30,   INF},
  {INF, 7,   22,  0,   15,    10},
  {25,  12,  30,  15,   0,   INF},
  {INF,  5,  INF,  10, INF,   0}, } };

    prim(&g, 0);
    
}