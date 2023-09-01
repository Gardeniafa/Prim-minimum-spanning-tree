#include "stdio.h"
#include "stdlib.h"
#define inf 2147483647
typedef struct{
    char* arr;
    int length;
}charList;
typedef struct{
    char *border;
    int weight;
}weightGraphBorder;
typedef enum {false, true} boolean;
charList* appendCharArray(char, charList*);
boolean charInCharList(char, charList*);
charList* replaceCharInList(char, char, charList*);
int main(){
    int numOfBorder;
    printf("输入带权值边的数量：");
    scanf("%d", &numOfBorder);
    weightGraphBorder graph[numOfBorder];
    int n = numOfBorder;
    charList points;
    points.length = 0;
    while (n != false){
        printf("输入%d条边及其权值，以空格隔开：",numOfBorder-n+1);
        char* s = (char *) malloc(sizeof(char)*3);
        int l;
        scanf("%s %d",s,&l);
        graph[numOfBorder-n].border = s;
        graph[numOfBorder-n].weight = l;
        for(int i = 0; i < 2; i += 1){
            if(!charInCharList(s[i], &points)){
                points = *appendCharArray(s[i], &points);
            } else{
                continue;
            }
        }
        n -= true;
    }
    charList pointsAll;
    pointsAll.length = points.length;
    char* sss = (char*) malloc(sizeof(char)*points.length);
    for (int i = 0; i < pointsAll.length; i += 1){
        sss[i] = points.arr[i];
    }
    pointsAll.arr = sss;
    charList newPoints;
    char* ssss = (char*) malloc(sizeof(char)*points.length);
    newPoints.arr = ssss;
    newPoints.length=0;
    printf("选择一个开始点:");
    char startPoint;
    int borderLinked = 0;
    getchar();
    scanf("%c", &startPoint);
    newPoints = *appendCharArray(startPoint, &newPoints);
    points = *replaceCharInList(startPoint, '\0', &points);
    while (borderLinked<pointsAll.length-1){
        weightGraphBorder shortest;
        shortest.weight = inf;
        for(int i = 0; i < numOfBorder; i += 1){
            if(((charInCharList(graph[i].border[0], &newPoints) && charInCharList(graph[i].border[1], &points))||
            (charInCharList(graph[i].border[1], &newPoints) && charInCharList(graph[i].border[0], &points)))
            &&(graph[i].weight < shortest.weight)){
                shortest.border=graph[i].border;
                shortest.weight=graph[i].weight;
            } else{
                continue;
            }
        }
        if(charInCharList(shortest.border[0], &newPoints)){
            newPoints = *appendCharArray(shortest.border[1], &newPoints);
            points = *replaceCharInList(shortest.border[1], '\0', &points);
            printf("\n第%d条路径：%c-->%c  %d", borderLinked+1, shortest.border[0], shortest.border[1], shortest.weight);
        } else{
            newPoints = *appendCharArray(shortest.border[0], &newPoints);
            points = *replaceCharInList(shortest.border[0], '\0', &points);
            printf("\n第%d条路径：%c-->%c  %d", borderLinked+1, shortest.border[1], shortest.border[0], shortest.weight);
        }
        borderLinked += 1;

    }
    printf("\ndone");
    return 0;
}
charList* appendCharArray(char c, charList* arr){
    charList* p = (charList*)malloc(sizeof(charList));
    char* ss = (char*) malloc((sizeof(char)*(arr->length + 1)));
    int l = 0;
    for(int i=0; i < arr->length; i += 1){
        ss[i] = arr->arr[i];
        l += 1;
    }
    ss[arr->length] = c;
    p->arr = ss;
    p->length = arr->length + 1;
    return p;
}
boolean charInCharList(char c, charList* s){
    for (int i=0; i < s->length; i += 1){
        if(s->arr[i] == c){
            return true;
        }
    }
    return false;
}
charList* replaceCharInList(char before, char after, charList* sA){
    char* sB = (char*) malloc(sizeof(char) * (sA->length));
    charList* p = (charList*) malloc(sizeof(charList));
    for (int i = 0; i < sA->length; i += 1) {
        if(sA->arr[i]==before){
            sB[i] = after;
        } else{
            sB[i]=sA->arr[i];
        }
    }
    p->length=sA->length;
    p->arr=sB;
    return p;
}