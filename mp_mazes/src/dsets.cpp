#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        sets.push_back(-1);
    }

}
int DisjointSets::find(int elem) {
    if (sets[elem] < 0) {
        return elem;
    } else {
        sets[elem] = find(sets[elem]);
        return sets[elem];
    }

}
void DisjointSets::setunion(int a, int b) {
    int a_root = find(a);
    int b_root = find(b);
    if (a_root != b_root) {
        int newSize = sets[a_root] + sets[b_root];
        if (sets[a_root] <= sets[b_root]) {
            sets[b_root] = a_root;
            sets[a_root] = newSize;
        } else {
            sets[a_root] = b_root;
            sets[b_root] = newSize;
        }
    }


}
int DisjointSets::size(int elem) {
    int root = find(elem);
    return sets[root] * -1;
    
}