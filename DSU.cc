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

int main(){
	fastio();
	return 0;
	}
