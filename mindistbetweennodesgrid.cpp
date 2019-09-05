
#include <iostream>
#include <queue>

using namespace std;

/*
 Notes:
 1. input is a matrix
 2. BFS - Level order traversal and also maintain a visited node so there aren't any loops
 3. Understand time complexity and space complexity
 4. 
 */

/* rows and coloumn */
#define M 6
#define N 6

/* self defined queue which maintains the distance at every node 
* Change way of thinking: used a structure before class is a better approach.
*/
class Queue1
{
    public:
        int row;
        int col;
        int dest;
        Queue1(int x, int y, int dist):
           row(x), col(y), dest(dist)
    {

    }
};

int mindistancebetweennodes(int grid[M][N]) {
    Queue1 source(0,0,0);
    //Queue1 dest(M-1, N-1, 0);
    queue<Queue1> trav;
    bool visited[M][N];

    for(int i = 0; i < M; i++) {
        for(int j=0; j< N; j++) {
            if (grid[i][j] == 0)
                visited[i][j] = false;
            else if (grid[i][j] == 1)
                visited[i][j] = true;
        }
    }
    

    /* set source node to visited */
    visited[source.row][source.col] = true;
    trav.push(source);
    while(!trav.empty()) {
        Queue1 item = trav.front();
        trav.pop();
        cout << item.row << " " << item.col << " " << item.dest << endl;
        if (item.row == M-1 && item.col == N-1){
            cout << "found";
            return item.dest;
        }
        
        /* move up */
        if (item.row - 1 >= 0 && visited[item.row-1][item.col] == false) {
            trav.push(Queue1(item.row-1, item.col, item.dest + 1));
            visited[item.row-1][item.col] = true;
        }

        /* move down */
        if (item.row + 1 < M && visited[item.row+1][item.col] == false) {
            trav.push(Queue1(item.row+1, item.col, item.dest + 1));
            visited[item.row+1][item.col] = true;
        }

        /* move left */
        if (item.col - 1 >= 0 && visited[item.row][item.col-1] == false) {
            trav.push(Queue1(item.row, item.col - 1, item.dest + 1));
            visited[item.row][item.col-1] = true;
        }

        /* move right */
        if (item.col + 1 < N && visited[item.row][item.col+1] == false) {
            trav.push(Queue1(item.row, item.col + 1, item.dest + 1));
            visited[item.row][item.col+1] = true;
        }
    }

    return -1;
}
int main(void) {
    int grid[M][N] = { {0, 1, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0},
                        {0, 1, 0, 0, 0, 0}};
    
    cout << mindistancebetweennodes(grid);
    return 0;
}