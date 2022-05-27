/*[2021076029] [장정환]*/
#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0

#define MAX_VERTEX 10

typedef struct {	//BFS에서 사용할 큐
	int front;
	int rear;
	int que_list[MAX_VERTEX];	//que사이즈를 최대 vertex수 만큼으로 지정
}Queue;
typedef struct vertex{	//graph의 vertex 구조체
	int key;	//vertex에 저장된 값
	int vertex_num;	//vertex 번호
	struct vertex* link;	//인접리스트에서 다음 vertex를 가리킬 포인터
}vertex;
int visited[MAX_VERTEX];	//DFS시 방문한 노드를 체크할 배열
vertex* list[MAX_VERTEX];	//각 vertex의 연결리스트를 가리킬 포인터배열(인접리스트)
int ptr_vertex;				//저장된 vertex개수를 카운트(vertex의 고유번호를 주기위해)



vertex* InitializeGraph(vertex* h);	//그래프 초기화(ptr_vertex, visited, list)
int InsertVertex();					//그래프에 정점(vertex)추가
int InsertEdge();					//그래프에 간선(edge)추가
void DFS(int v);				//깊이우선 탐색
void BFS(int v);				//너비우선 탐색
void PrintGraph();			//그래프의 인접리스트 출력
int FreeVertex();					//list에 저장된 각 vertex 해제*/

int Initialize_visited();	//visited 배열 초기화
int addQ(Queue* Que, int v);
int deleteQ(Queue* Que);
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
				/*시작정점 입력*/
				printf("start point : ");
				scanf("%d",&v);
				Initialize_visited();	//DFS전 visited 배열 초기화
				DFS(v);
				printf("\n");
				break;
			}
			case 'b': case 'B':{
				printf("start point : ");
				scanf("%d",&v);
				BFS(v);
				break;
			}
			case 'p': case 'P':{
				PrintGraph();
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
	new->link =NULL;

	list[ptr_vertex++]=new;		//vertex를 인접리스트에 추가
	return 1;
}	//그래프에 정점(vertex)추가

int InsertEdge(){	//오름차순 으로 정렬해서 search시 vertex번호가 작은 순으로 방문하도록 한다.
	int to, from;	//간선의 시작정점, 종료정점
	vertex* ptr_1;
	vertex* ptr_2;
	/*현재 존재하는 정점을 입력할때 까지 반복*/
	while(1){
		printf("시작 정점 : ");
		scanf("%d",&from);
		printf("종료 정점 : ");
		scanf("%d",&to);
		/*if(to==from){
			printf("시작과 종료를 다르게 해주세요\n"); continue;
		}*/
		
		if(from < 0 || from >=ptr_vertex || to < 0 || to >=ptr_vertex){
			printf("현재 입력가능한 vertex의 범위를 벗어났습니다.\n"); continue;
		}
		break;
	}
	/*무방향 그래프이기때문에 시작점의 vertex에 종료점vertex를
	 종료점의 vertex에 시작점의 vertex를  인접리스트에 추가*/
	/* 인접리스트에 저장된 vertex에 연결할 새로운 vertex*/
	vertex* new_1 = (vertex*)malloc(sizeof(vertex));
	if(new_1 == NULL){printf("fail to malloc\n"); return -1;}
	new_1->vertex_num = to;
	new_1->link = NULL;
	/* 인접리스트에 저장된 vertex에 연결할 새로운 vertex*/
	vertex* new_2 = (vertex*)malloc(sizeof(vertex));
	if(new_2 == NULL){printf("fail to malloc\n"); return -1;}
	new_2->vertex_num = from;
	new_2->link = NULL;
	
	/*시작정점의 인접리스트*/
	ptr_1=list[from];
	/*종료정점의 인접리스트*/
	ptr_2=list[to];

	vertex* trail=NULL;
	/*오름차순으로 정렬해서 시작정점 인접리스트에 추가*/
	while(ptr_1 != NULL)
	{	
		trail=ptr_1;
		ptr_1=ptr_1->link;
		/*인접리스트에 추가된 간선이 없는경우(처음추가할경우)*/
		if(ptr_1 == NULL){
			trail->link = new_1;
			break;}
		/*new의 vertex넘버보다 큰 넘버가 나올경우 new를 그 앞에 추가*/
		if(ptr_1->vertex_num >= new_1->vertex_num){
			trail->link=new_1;
			new_1->link=ptr_1;
			break;
		}
	}
	/*오름차순으로 정렬해서 종료정점 인접리스트에 추가*/
	while(ptr_2 != NULL)
	{	
		trail=ptr_2;
		ptr_2=ptr_2->link;
		/*인접리스트에 추가된 간선이 없는경우(처음추가할경우)*/
		if(ptr_2 == NULL){
			trail->link = new_2;
			break;}
		/*new의 vertex넘버보다 큰 넘버가 나올경우 new를 그 앞에 추가*/
		if(ptr_2->vertex_num >= new_2->vertex_num){
			trail->link=new_2;
			new_2->link=ptr_2;
			break;
		}
	}

	return 1;
}					//그래프에 간선(edge)추가
void DFS(int v){
	/*저장된 정점이 없을 경우*/
	if(ptr_vertex == 0){printf("nothing to Search\n"); return;}
	/*입력받은 정점이 없을 경우나 입력받은 정점이 음수일 경우*/
	if(v > ptr_vertex || v < 0){printf("%d is out of range",v); return;}

	vertex* h; 
	/*DFS를 시작할 시작정점을 '방문 했음'으로 바꾼다*/
	visited[v] = true;
	printf("%3d",v);
	/*처음 정점으로 부터 링크를 따라가며 재귀호출*/
	for(h=list[v]; h; h = h->link){
		/*정점을 방문하지 않았을 경우 재귀호출*/
		if(!visited[h->vertex_num]){
			DFS(h->vertex_num);
		}
	}
	return;
}	//깊이우선 탐색
void BFS(int v){
	/*저장된 정점이 없을 경우*/
	if(ptr_vertex == 0){printf("nothing to Search\n"); return;}
	/*입력받은 정점이 없을 경우나 입력받은 정점이 음수일 경우*/
	if(v > ptr_vertex || v < 0){printf("%d is out of range",v); return;}

	Initialize_visited();	//visited 배열 초기화
	vertex* h;
	Queue Que;

	Que.front=0;
	Que.rear=0;

	printf("%3d",v);
	visited[v]=true;
	addQ(&Que,v);

	while(Que.front != Que.rear){
		v=deleteQ(&Que);
		for(h=list[v]; h; h=h->link){
			if(!visited[h->vertex_num]){
				printf("%3d",h->vertex_num);
				visited[h->vertex_num]=true;
				addQ(&Que,h->vertex_num);
			}
		}
	}
	printf("\n");
}	//너비우선 탐색
void PrintGraph(){
	if(ptr_vertex==0){
		printf("nothing to print\n"); return;
	}
	
	vertex* w;	//인접리스트의 원소를 하나하나 가리킬 포인터
	
	/*저장된 vertx 개수 만큼 반복하여 각 vertex의 인접리스트 전부 출력*/
	for(int i=0; i<ptr_vertex; i++){
		w=list[i];	//각 vertex 인접리스트를 가리킨다
		/*각 vertex의 인접리스트 끝까지 출력*/
		printf("adjLists[%d] : ",i);
		while(w!=NULL){
			printf("%3d",w->vertex_num);
			w=w->link;	
		}
		printf("\n");
	}
}			//그래프의 인접리스트 출력
int FreeVertex(){
	if(ptr_vertex==0){
		printf("nothing to free\n"); return -1;
	}
	vertex* ptr = list[0];
	vertex* rear= NULL;
	for(int i=0; i<ptr_vertex; i++){
		while(ptr != NULL){
			rear=ptr;
			ptr=ptr->link;
			free(rear);
		}
	}
	return 1;
}		//각 vertex 해제
int Initialize_visited(){
	for(int i=0; i < MAX_VERTEX; i++){
		visited[i]=false;
	}
	return 1;
}

int addQ(Queue* Que,int v){
	Que->rear++;
	Que->que_list[Que->rear]=v;
	return 1;
}

int deleteQ(Queue* Que){
	int v;
	Que->front++;

	return Que->que_list[Que->front];
}
