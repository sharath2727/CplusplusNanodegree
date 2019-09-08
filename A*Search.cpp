#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;
using std::sort;
using std::endl;

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};


vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️  ";
    case State::kPath: return "🚗  ";
    case State::kStart: return "🚦  ";
    case State::kFinish: return "🏁  ";
    default: return "0  "; 
  }
}

void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

bool Compare(vector<int> v1, vector<int> v2)
{
  int f1 = v1[2] + v1[3];
  int f2 = v2[2] + v2[3];
  
  return ((f1 > f2) ? true: false);
}

void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}


int Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{
  bool is_valid_x = (x >= 0 && x < grid.size());
  bool is_valid_y = (y >= 0 && y < grid[0].size());
  
  if (is_valid_x && is_valid_y && grid[x][y] == State::kEmpty)
    	return true;
  else
    	return false;
}

void AddToOpen(int x, int y, int g, int h,
               vector<vector<int>> &openlist, vector<vector<State>> &grid)
{
    openlist.push_back(vector<int>{x,y,g,h});
    grid[x][y] = State::kClosed;
}

const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void ExpandNeighbors(vector<int> current_node, vector<vector<int>> &open,
                    vector<vector<State>> &grid,
                    int goal[2])
{

    int x = current_node[0];
    int y = current_node[1];
    int g = current_node[2];

    for (int i = 0; i < 4; i++)
    {
        int neigh_x = x + delta[i][0];
        int neigh_y = y + delta[i][1];
        cout << "check_validity: " << neigh_x << " " << neigh_y << endl; 
        if(CheckValidCell(neigh_x, neigh_y, grid))
        {
            int g_value = g + 1;
            int h_value = Heuristic(neigh_x, neigh_y, goal[0], goal[1]);
            int f_value = g_value + h_value;
            cout << "add node: " << neigh_x << " " << neigh_y << " " << g_value << " " << h_value << f_value << " " << std::endl;
            AddToOpen(neigh_x, neigh_y, g_value, h_value, open, grid);
        }
    }
}

// TODO: Write the Search function stub here.
auto Search(vector<vector<State>> &grid, int init[2], int goal[2])
{
    vector<vector<State>> v{};
    vector<vector<int>> open {};
    
    /* Initialize the first open node */
    AddToOpen(init[0], init[1], 0, Heuristic(init[0], init[1] , goal[0] , goal[1]), open, grid);
    grid[init[0]][init[1]] =  State::kStart;
    while(open.size() > 0)
    {
        CellSort(&open);

        auto current_node = open.back();
        open.pop_back();
        grid[current_node[0]][current_node[1]] = State::kPath;
        if (current_node[0] == goal[0] && current_node[1] == goal[1]) {
            grid[current_node[0]][current_node[1]] = State::kFinish;
            grid[init[0]][init[1]] = State::kStart;
            cout << "current_node.distance: " << current_node[3] << endl;
            return grid;
        }
        cout << current_node[0] << " " << current_node[1] << std::endl;
        ExpandNeighbors(current_node, open, grid, goal);
    }
    cout << "No path found" <<  std::endl << std::endl;
    PrintBoard(grid);
    grid[init[0]][init[1]] = State::kStart;
    return grid; 
}

int main() {
  // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
  int init[] = {0,0};
  int goal[] = {4,5};
  auto board = ReadBoardFile("1.board");
  // TODO: Call Search with "board", "init", and "goal". Store the results in the variable "solution".
  // TODO: Change the following line to pass "solution" to PrintBoard.
  auto solution = Search(board, init, goal);
  cout << std::endl;
  PrintBoard(board);
  cout << std::endl;
}
