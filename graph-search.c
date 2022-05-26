/*[2021076029] [장정환]*/
#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0

#define MAX_VERTEX 10
typedef struct vertex{	//graph의 vertex 구조체
	int key;	//vertex에 저장된 값
	int vertex_num;	//vertex 번호
	struct vertex* link;	//인접리스트에서 다음 vertex를 가리킬 포인터
}vertex;
int visited[MAX_VERTEX];	//DFS시 방문한 노드를 체크할 배열
vertex* list[MAX_VERTEX];	//각 vertex의 연결리스트를 가리킬 포인터배열
int ptr_vertex;				//저장된 vertex개수를 카운트



vertex* InitializeGraph(vertex* h);	//그래프 초기화(ptr_vertex, visited, list)
int InsertVertex();					//그래프에 정점(vertex)추가
int InsertEdge();					//그래프에 간선(edge)추가
void DFS(int v);				//깊이우선 탐색
void BFS(int v);				//너비우선 탐색
void PrintGraph(vertex* h);			//그래프의 인접리스트 출력
int FreeVertex();					//list에 저장된 각 vertex 해제

int main(void){
	printf("-----[2021076029] [장정환]-----\n");
	
	char choice;
	int v;
	vertex* h;	//그래프의 임의의 정점을 시작 정점 h로 지정

	do{
		printf("===============================================\n");
		printf("					Graph Searches				\n");
		printf("===============================================\n");
		printf("Initialize Graph	= z\n");
		printf("Insert Vertex 		= v		Insert Edge			= e\n");
		printf("Depth Frist Search	= d		Breath First Serach = b\n");
		printf("Print Graph			= p\n");
		printf("================================================\n");

		printf("choice : ");
		scanf("%c",&choice);

		switch(choice){
			case 'z': case 'Z':{
				h = InitializeGraph(h);
				break;
			}
			case 'v': case 'V':{
				InsertVertex();
				break;
			}
			case 'e': case 'E':{
				InsertEdge();
				break;
			}
			case 'd': case 'D':{
				printf("start point : ");
				scanf("%d",&v);
				DFS(v);
				break;
			}
			case 'b': case 'B':{
				printf("start point : ");
				scanf("%d",&v);
				BFS(v);
				break;
			}
			case 'p': case 'P':{
				PrintGraph(h);
				break;
			}
			case 'q': case 'Q':{
				FreeVertex(h);
				break;
			}
		}
		getchar();
	}while(choice != 'q' && choice != 'Q');

	return 0;
}

vertex* InitializeGraph(vertex* h){
	if(ptr_vertex == 0){	//저장된 vertex가 없는 경우
		printf("nothing to initialize\n"); return NULL;
	}
	else{
		FreeVertex();
		ptr_vertex=0;
		for(int i=0; i < MAX_VERTEX; i++){
			visited[i]=false;
		}
	}
}	//그래프 초기화
int InsertVertex(){
	/*새로운 vertex가 가지는 값*/
	int key;
	printf("key (int형) : ");
	scanf("%d",&key);

	vertex* new = (vertex*)malloc(sizeof(vertex));
	if(new == NULL){
		printf("fail to malloc\n"); return -1;
	}
	new->key=key;
	new->vertex_num=ptr_vertex;	//vertex의 고유 vertex번호

	list[ptr_vertex++]=new;		//vertex를 인접리스트에 추가
	return 1;
}				//그래프에 정점(vertex)추가

int InsertEdge(){
	int to, from;	//간선의 시작정점, 종료정점
	vertex* ptr;
	/*현재 존재하는 정점을 입력할때 까지 반복*/
	while(1){
		printf("시작 정점 : ");
		scanf("%d",&from);
		printf("종료 정점 : ");
		scanf("%d",&to);
		/*if(to==from){
			printf("시작과 종료를 다르게 해주세요\n"); continue;
		}*/
		if(from < 0 || from >ptr_vertex || to < 0 || to >ptr_vertex){
			printf("정점의 범위를 벗어났습니다.\n"); continue;
		}
		break;
	}
	/* 인접리스트에 저장된 vertex에 연결할 새로운 vertex*/
	vertex* new = (vertex*)malloc(sizeof(vertex));
	new->vertex_num = to;
	new->link = NULL;

	ptr=list[from];
	while(ptr->link != NULL){
		ptr = ptr->link;
	}
	ptr->link = new;

	return 1;
}					//그래프에 간선(edge)추가
void DFS(int v){
	if(ptr_vertex == 0){printf("nothing to Search\n"); return;}
	if(v > ptr_vertex || v < 0){printf("%d is out of range",v); return;}

	vertex* h;
	visited[v] = true;
	printf("%3d",v);
	for(h=list[v]; h; h = h->link){
		if(!visited[h->vertex_num]){
			DFS(h->vertex_num);
		}
	}
}	//깊이우선 탐색
void BFS(int v){
	
}				//너비우선 탐색
void PrintGraph(vertex* h);			//그래프의 인접리스트 출력
int FreeVertex();		//각 vertex 해제

