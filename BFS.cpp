/*
* Osvaldo Rodrigues de Faria Junior 201911203 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

typedef vector<int> vi; // vetor de inteiros

// cores dos vertices
#define BRANCO 0 // vertice nao descoberto
#define CINZA 1 // vertice descoberto
#define PRETO 2 // vertice fechado

int main()
{ 
  vector<vi> respostas; 
  int n, m, l, p;
  cin >> n >> m >> l >> p;
  int testes = 0;

  while(n != 0 and m != 0 and l != 0 and p != 0)
  {
    // alocando as estruturas auxiliares
    int* dist = new int[n+1]; // distancia de todos os vertices em relacao a origem s
    int* pai = new int[n+1]; // armazena o pai de cada vertice
    int* cor = new int[n+1]; // armazena a cor de cada vertice
    
    // iniciando as estruturas auxiliares
    for(int i = 1; i <= n; i++)
    {
        dist[i] = 0;
        pai[i] = -1;
        cor[i] = BRANCO;
    }
   
    vector<int>* lista_adj = new vector<int>[n+1];

    // leitura do grafo
    int u, v;
    for(int i = 0; i < m; i++)
    {
      cin >> u >> v; // lendo as arestas do grafo

      // evitando a leitura de vertices repetidos nas listas
      if(find(lista_adj[u].begin(), lista_adj[u].end(), v) != lista_adj[u].end())
      {
        continue;
      }

      // grafo nao-orientado
      lista_adj[u].push_back(v); //u -> v
      lista_adj[v].push_back(u); //v -> u
    }

    int s = l; // vertice origem
    queue<int> fila; // fila de vertices a serem explorados na BFS
    fila.push(s);
    cor[s] = CINZA;
   
    //para cada um que nao vai na festa, reduz o numero dos seus amigos
    while(!fila.empty())
    {
      int u = fila.front();
      fila.pop();
      cor[u]= PRETO;

      for(auto it = lista_adj[u].begin(); it != lista_adj[u].end(); it++)
      { 
          // se o vertice ainda nao foi descoberto
          if(cor[*it] == BRANCO)
          {
              cor[*it] = CINZA;
              pai[*it] = u;
              dist[*it] = dist[u] + 1;
              fila.push(*it);
          }   
      }
    }

    vi respostaparcial;
    
    for(int k = 1; k <= n; k++)
    {
      if(dist[k] <= p and ( k!= l))
      {
        respostaparcial.push_back(k);
      }
    }
    respostas.push_back(respostaparcial);
    respostaparcial.clear();

    testes++;
   
   
    delete[] pai;
    delete[] cor;
    delete[] dist;
    
    cin >> n >> m >> l >> p;
  }

  for(int i=0 ; i < testes ; i++)
  {
    cout << "Teste " << i +1 <<"\n";
    for(int j= 0 ; j < respostas[i].size() ; j++)
    {
      cout << respostas[i][j] << " ";
    }
  if(i != (testes -1))
  {
    cout << "\n";
  }
    cout << "\n";
  }
  

return 0;
}