#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define fastio() cin.tie(nullptr); cout.tie(nullptr); ios_base::sync_with_stdio(false);
#define lli long long int
struct UnionFind{
	vector<lli> father;				//Mi vector que va a guardar cual es mi raiz padre para cada nodo
	vector<lli> size;				//Número de nodos en un conjunto
	lli numConj;					//Número de conjuntos
	UnionFind(lli n): father(n),size(n,1),numConj(n){		//El constructor, al inicio mi padre soy yo mismo porque ningún nodo se ha unido
		for(lli i=0;i<n;i++) father[i] = i;		
	}
	lli find(lli u){						//Función find, si mi padre soy yo mismo entonces soy el nodo raiz padre de todos
	return father[u] = (u == father[u]? u: find(father[u]));	//ya terminé la búsqueda, regresa el valor obtenido.
								//Si no soy mi propio padre entonces busca a mi padre(porque es el mismo para el mismo conjunto) y
							 	//por cuestiones de optimización ve actualizando a mi padre. USAMOS PATH COMPRESSION
	}
	void union_set(lli u, lli v){			//Función union_set, une dos conjuntos, para esto primero encuentra el padre de los nodos del conjunto
		auto u_father = find(u);		//Hacemos la union por tamaño (también podemos hacer la unión por rango(unir el que tiene mayor altura
		auto v_father = find(v);		//con el que tiene menos altura)).
							//Si el padre de u es más grande que el padre de v, intercámbialos
		if(u_father != v_father){
			numConj--;
			if(size[u_father] < size[v_father]) swap(u_father, v_father);
			father[v_father] = u_father;
		}
	}
	bool same_set(lli u, lli v){			//Funcion de same, indica si dos elementos están dentro del mismo conjunto.
	return find(u) == find(v);
		}
}; //Complejidad es igual a O(1) (estrictamente es la funcion inversa de ackerman)

struct Arista{
	lli origen,destino,peso;
	Arista(lli origen,lli destino, lli peso):origen(origen), destino(destino),peso(peso){};
	bool operator <(const Arista& e){
	return peso < e.peso;		
	}
};
bool operator<(const Arista& a,const Arista& b){
		return a.peso > b.peso;
	}

struct Grafo{
	vector<vector<Arista>> lista_ad;
	vector<Arista> aristas;
	lli V;
	Grafo(lli n): lista_ad(n), V(n){}
	void agregar_arista(lli u, lli v, lli peso){
		lista_ad[u].push_back(Arista(u,v,peso));			//Agregamos para aristas "no dirigidas"
		lista_ad[v].push_back(Arista(v,u,peso));			//por eso es para u y v
		aristas.push_back({u,v,peso});
	}
	vector<Arista> kruskal(){
		vector<Arista> minimum_spanning_tree_kruskal;
		UnionFind uf(V);
		sort(aristas.begin(),aristas.end());
		for(Arista& e: aristas){
			if(!uf.same_set(e.origen,e.destino)){
				uf.union_set(e.origen,e.destino);
				minimum_spanning_tree_kruskal.push_back(e);					
			}
		if(minimum_spanning_tree_kruskal.size() == V-1) break;
		}
	return minimum_spanning_tree_kruskal;
	}
	void procesa(lli u, priority_queue<Arista>& pq, vector<bool>& usada){
		usada[u] = true;
		for(Arista& e: lista_ad[u]){
			if(!usada[e.destino]){
				pq.push(e);			
			}			
		}
	}
	vector<Arista> prim(){
		priority_queue<Arista> pq;
		vector<bool> visitado(V);
		vector<Arista> minimum_spanning_tree_prim;
		procesa(0,pq,visitado);							//Mete las aristas adyacentes a mi nodo inicial
		while(!pq.empty()){							//Mientras haya aristas sigue intentando conectarlas con nodos
			Arista e = pq.top(); pq.pop();					//Saca la del inicio y revisa si conecta nodos no conectados
			if(visitado[e.destino]) continue;
			minimum_spanning_tree_prim.push_back(e);
			procesa(e.destino,pq,visitado);					//Mete las aristas adyacentes a mi nodo
			if(minimum_spanning_tree_prim.size() == V-1) break;
					
		}
		return minimum_spanning_tree_prim;	
	}
};

void dijkstra(lli n, Grafo g, lli source){
	priority_queue<pair<lli,lli>,vector<pair<lli,lli>>,greater<pair<lli,lli>>> pq;
	vector<lli> pesos(n,LLONG_MAX);
	pq.push({0,source});
	pesos[source] = 0;

	while(!pq.empty()){
		lli v = pq.top().second; pq.pop();
		for(Arista& e: g.lista_ad[v]){
			lli u = e.destino;
			lli peso = e.peso;
			if(pesos[u] > pesos[v]+peso){
				pesos[u] = pesos[v]+peso;
				pq.push({pesos[u],u});
			}
		}
	}
	for(auto i=0;i<n;i++){
		cout << "Nodo: " << i << " Peso: "<< pesos[i] << endl;
	}
	return;
}

int main(){
	fastio();
	auto n=0,m=0; cin >> n >> m;
	Grafo g(n);
	for(auto i=0;i<m;i++){
		lli u,v,w;
		cin >> u >> v >> w;
		g.agregar_arista(u,v,w);		
	}
	auto source=0; cin >> source;
	dijkstra(n,g,source);
	return 0;
	}
