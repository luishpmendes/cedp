#pragma once

#include <vector>

/*
 * The DisjointSets class represents a data structure for disjoint sets.
 */
class DisjointSets {
    private:
        /* This disjoint sets' representative of each element. */
        std::vector<unsigned int> p;

        /* This disjoint sets' rank of each element. */
        std::vector<unsigned int> rank;

        /*
         * Links the set that has x as representative with the set that has y as representative.
         *
         * @param x the representative of the first set that will be linked.
         * @param y the representative of the second set that will be linked.
         */
        void linkSets(unsigned int x, unsigned int y);

    public:
        /*
         * Constructs a new data structure for disjoint sets.
         *
         * @param n the new data structure's initial size.
         */
        DisjointSets(unsigned int n);

        /*
         * Constructs a new data structure for disjoint sets.
         */
        DisjointSets();

        /*
         * Verifies whether there is a set containing x.
         *
         * @return true if there is a set containing x; false otherwise.
         */
        bool hasSet(unsigned int x) const;

        /*
         * Creates a new set whose only member (and thus representative) is x.
         * Since the sets are disjoint, we require that x not already be in some other set.
         *
         * @param x the element of the new singleton set.
         */
        void makeSet(unsigned int x);

        /*
         * Returns the representative of the (unique) set containing x.
         *
         * @param x the element whose set is being looked for.
         *
         * @return the representative of the (unique) set containing x.
         */
        unsigned int findSet(unsigned int x);

        /*
         * Unites the dynamic sets that contain x and y into a new set that is 
         * the union of these two sets.
         *
         * @param x the element of the first set that will be united.
         * @param y the element of the second set that will be united.
         */
        void unionSets(unsigned int x, unsigned int y);
};

