/**Joshua Yurche
CS319
HW3
iterDeep.cpp Reads in a csv text file into a 2d array which is then used
to implement the iterative deepening algorithm
**/
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stack>

using namespace std;

int main(){

  //FIND LENGTH OF ARRAY
  fstream file("adj.txt");
  vector<string> mlength;
  string line;

  int vertCount = 0;
  while(file && getline(file, line)) {
      string data;
      stringstream ss(line);
      while(ss && ss >> data) {
          mlength.push_back(data);
      }
      ++vertCount;
  }
  cout << "length is "<< vertCount << endl;


//READ IN VALUES FROM CSV TEXT FILE CONTAINING AN ADJACENCY
//MATRIX OF A DIRECTED GRAPH. SEPERATE VALUES FROM COMMAS.
//PUT THE VALUES INTO A 2D ARRAY  adjMtrx[][]
  vector<string> v_input;
  //List graph[vertCount];
  ifstream getdata("adj.txt");

  int adjMtrx[vertCount][vertCount];

  string s;
  while(getline(getdata, s, ',')) {
    v_input.push_back(s);
    //cout<< s << endl;
  }
  int j = 0;

//READ THE VALUES INTO THE adjMtrx
    for (int row = 0;row < vertCount; row++){
      for(int col = 0; col < vertCount; col++){
        const char * str1 = v_input.at(j).c_str();
        int temp = atoi(str1);
        adjMtrx[row][col] = temp;
        cout<< adjMtrx[row][col] << " ";
        j += 1;
      }
      cout<<endl;
    }

//ITERATIVE DEEPENING
    int depth;
    int maxDepth = 0;
    bool goalFound = false;
    //THE STARTING VERTEX
    int startFrom = 0;
    //VERTEX WE ARE LOOKING FOR
    int goal = 6;
    stack<int> theStack;
    int visited[vertCount];
    visited[0] = 1;


    while (!goalFound){
      int row = 0;
      int col = 0;
      theStack.push(startFrom);
      depth = 0;
      cout<< "\n\nAt depth level " << maxDepth <<
      ", the verticies visited are: "<< endl;
      cout<< startFrom << "\t";

      while(theStack.size() > 0){
        col = theStack.top();

        while(row <= vertCount){

          if(depth < maxDepth){

            if(adjMtrx[col][row] == 1){
              theStack.push(row);
              visited[row] = 1;
              cout<< row <<"\t";
              depth++;

              if (goal == row) {
                goalFound = true;
                cout<< "\nFound goal at depth level " << depth << endl;
                return 0;
              }
              //IF GOAL NOT FOUND EXIT PROGRAM
              int allVisited = 0;
              for(int i = 0; i < vertCount; i++){

                if (visited[i] == 1){
                  allVisited +=1;
                }
              }
              if (allVisited == vertCount){
                cout<< "All vertices have been visited."<<
                "\n The goal was not found." << endl;
                return 0;
              }
              col = row;
              row = 1;
            }
          }
          else{
            break;
          }
          row++;
        }
        row = theStack.top() + 1;
        theStack.pop();
        depth--;
      }
      maxDepth++;
    }
    cout<< "Found goal at " << depth << endl;

return 0;
}
