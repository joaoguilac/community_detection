#ifndef _COMMUNITY_H_
#define _COMMUNITY_H_

#include "Node.hpp"

class Community {
    private:
        std::set<Node*> members;
    public:
        Community(std::set<Node*> = {});
        ~Community();

        std::set<Node*> getNeighbors();
        bool neighborsIsSubset(Node*);
};

#include "Community.inl"

#endif