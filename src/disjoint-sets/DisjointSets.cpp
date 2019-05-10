#include "DisjointSets.hpp"
#include <climits>

/*
 * Constructs a new data structure for disjoint sets.
 *
 * @param n the new data structure's initial size.
 */
DisjointSets::DisjointSets(unsigned int n) : p(n, UINT_MAX), rank(n, 0) {}

/*
 * Constructs a new data structure for disjoint sets.
 */
DisjointSets::DisjointSets() : DisjointSets::DisjointSets(10) {}

/*
 * Links the set that has x as representative with the set that has y as representative.
 *
 * @param x the representative of the first set that will be linked.
 * @param y the representative of the second set that will be linked.
 */
void DisjointSets::linkSets(unsigned int x, unsigned int y) {
    if (x != y) {
        if (this->rank[x] > this->rank[y]) {
            this->p[y] = x;
        } else {
            this->p[x] = y;

            if (this->rank[x] == this->rank[y]) {
                this->rank[y]++;
            }
        }
    }
}

/*
 * Verifies whether there is a set containing x.
 *
 * @return true if there is a set containing x; false otherwise.
 */
bool DisjointSets::hasSet(unsigned int x) const {
    return (x < this->p.size() && this->p[x] < UINT_MAX);
}

/*
 * Creates a new set whose only member (and thus representative) is x.
 * Since the sets are disjoint, we require that x not already be in some other set.
 *
 * @param x the element of the new singleton set.
 */
void DisjointSets::makeSet(unsigned int x) {
    while (x >= this->p.size()) {
        this->p.push_back(UINT_MAX);
    }

    while (x >= this->rank.size()) {
        this->p.push_back(0);
    }

    this->p[x] = x;
    this->rank[x] = 0;
}

/*
 * Returns the representative of the (unique) set containing x.
 *
 * @param x the element whose set is being looked for.
 *
 * @return the representative of the (unique) set containing x.
 */
unsigned int DisjointSets::findSet(unsigned int x) {
    if (x != this->p[x]) {
        this->p[x] = this->findSet(this->p[x]);
    }

    return this->p[x];
}

/*
 * Unites the dynamic sets that contain x and y into a new set that is 
 * the union of these two sets.
 *
 * @param x the element of the first set that will be united.
 * @param y the element of the second set that will be united.
 */
void DisjointSets::unionSets(unsigned int x, unsigned int y) {
    this->linkSets(this->findSet(x), this->findSet(y));
}

