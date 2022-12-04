#include "maze.h"
#include <cstdlib>
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;




SquareMaze::SquareMaze() {}


void SquareMaze::makeMaze(int width, int height) {
    mazeWidth = width;
    mazeHeight = height;
    size = mazeHeight * mazeWidth;
    
    //Clear if not empty
    if (!down.empty()) {
        down.clear();
    }
    if (!right.empty()) {
        right.clear();
    }


    for (int i = 0; i < size; i++) {
        down.push_back(true);
        right.push_back(true);
    }

    set.addelements(size);
    int counter = 0;
    
    while (counter < size - 1) {
        int randomX = rand() % width;
        int randomY = rand() % height;
        int randomDir = rand() % 2;

        //when direction is pointing down
        if (randomDir == 0) {
            //check if X is in bounds, and if location in right vector exists/equals true, and if set.find(randX + randY * width) != dsets.find(randX + 1 + randY * width
            if (randomX < mazeWidth - 1 && (right[randomX + randomY * mazeWidth] == true)) {
                if (set.find(randomX + randomY * mazeWidth) != set.find(randomX + 1 + randomY * mazeWidth)) {
                    //right[randomX + randomY * mazeWidth] = false;
                    //setWall
                    setWall(randomX,randomY,0,false);
                    set.setunion(set.find(randomX + randomY * mazeWidth), set.find(randomX + 1 + randomY * mazeWidth));
                    counter++;
                }
            }
        }
        //when direction points right
        if (randomDir == 1) {
            if ((randomY < mazeHeight - 1) && (down[randomX + randomY * mazeWidth] == true)) {
                if (set.find(randomX + randomY * mazeWidth) != set.find(randomX + randomY * mazeWidth + mazeWidth)) {
                    //down[randomX + randomY * mazeWidth] = false;
                    setWall(randomX,randomY,1,false);
                    set.setunion(set.find(randomX + randomY * mazeWidth), set.find(randomX + randomY * mazeWidth + mazeWidth));
                    counter++;
                    //setWall

                }
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir ) const {

    if (dir == 0 && x < mazeWidth - 1 && (right[x + y * mazeWidth] == false)) {
        return true;
    }
    if (dir == 1 && y < mazeHeight - 1 && (down[x + y * mazeWidth] == false)) {
        return true;
    }
    if (dir == 2 && x - 1 >= 0 && (right[x + y * mazeWidth - 1] == false)) {
        return true;
    }
    if (dir == 3 && y - 1 >= 0 && (down[x + y * mazeWidth - mazeWidth] == false)) {
        return true;
    }
    return false;



}

PNG * SquareMaze::drawMaze() const {
    PNG* maze = new PNG(mazeWidth*10+1, mazeHeight*10+1);

    for (int i = 0; i < mazeWidth * 10 + 1; i++) {
        if (i >= 1 && i <= 9) {
            continue;
        } else {
            maze->getPixel(i, 0) = HSLAPixel(0,0,0);
        }
    }
    for (int i = 0; i < mazeHeight * 10 + 1; i++) {
        maze->getPixel(0, i) = HSLAPixel(0,0,0);
    }
    //makeMaze(mazeWidth*10+1,mazeHeight*10+1);
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            if (right[x + y * mazeWidth] == true) {
                for (int k = 0; k <= 10; k++) {
                    maze->getPixel((x+1)*10,(y*10+k)) = HSLAPixel(0,0,0);
                }
            }
            if (down[x + y * mazeWidth] == true) {
                for (int k = 0; k <= 10; k++) {
                    maze->getPixel(x*10+k,(y+1)*10) = HSLAPixel(0,0,0);
                }
            }
        }
    }

    return maze;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* unsolved = new PNG(mazeHeight, mazeWidth);
    return unsolved;

}


void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (dir == 0) {
        right[x + y * mazeWidth] = exists;
    } else if (dir == 1) {
        down[x + y * mazeWidth] = exists;
    }
}

vector<int> SquareMaze::solveMaze() {
    
    std::map<int,int> steps;
    std::vector<bool> beenVisited;

    for (int i = 0; i < size; i++) {
        beenVisited.push_back(false);
    }
    std::queue<int> q;
    q.push(0);
    beenVisited[0] = true;

    //std::cout << "last row" << lastRows.size() << " XX " << "been visited" << beenVisited.size() << std::endl;


    while (!q.empty()) {
        int current = q.front();
        q.pop();
        int x = current % mazeWidth;
        int y = current / mazeWidth;

        //bfs
        if (canTravel(x,y,0) && beenVisited[current + 1] == false) {
            beenVisited[current + 1] = true;
            //steps.insert(std::pair<int,int> (current + 1, current));
            steps[current + 1] = current;
            q.push(current + 1);
        }
        //std::cout << "after right" << std::endl;
        if (canTravel(x,y,1) && beenVisited[current + mazeWidth] == false) {
            beenVisited[current + mazeWidth] = true;
            //steps.insert(std::pair<int,int> (current + mazeWidth, current));
            steps[current + mazeWidth] = current;
            q.push(current + mazeWidth);
        }
        //std::cout << "after down" << std::endl;
        if (canTravel(x,y,2) && beenVisited[current - 1] == false) {
            beenVisited[current - 1] = true;
            //steps.insert(std::pair<int,int> (current - 1, current));
            steps[current - 1] = current;
            q.push(current - 1);
        }
        //std::cout << "after left" << std::endl;
        if (canTravel(x,y,3) && beenVisited[current - mazeWidth] == false) {
            beenVisited[current - mazeWidth] = true;
            //steps.insert(std::pair<int,int> (current - mazeWidth, current));
            steps[current - mazeWidth] = current;
            q.push(current - mazeWidth);
        }
        //std::cout << "after up" << std::endl;
    }

    std::vector<int> return_path;
    int max_distance = 0;
    int startCell = 0;
    int end = 0;
    for (int i = 0; i < mazeWidth; i++) {
        int cell = ((mazeHeight - 1) * mazeWidth) + i;
        int path_length = 0;
        while (cell != startCell) {
            cell = steps[cell];
            path_length++;
        }
        if (path_length > max_distance) {
            max_distance = path_length;
            end = i;
        }
    }
    int endCell = ((mazeHeight - 1) * mazeWidth) + end;
    while (endCell != startCell) {
        int prev = steps[endCell];
        if (prev == endCell - 1) { // if L->R
            return_path.push_back(0);
        } else if (prev == endCell - mazeWidth) { // if U->D
            return_path.push_back(1);
        } else if (prev == endCell + 1) { // if R->L
            return_path.push_back(2);
        } else if (prev == endCell + mazeWidth) { // if D->U
            return_path.push_back(3);
        }
        endCell = prev;
    }
    std::reverse(return_path.begin(), return_path.end());
    return return_path;
}
