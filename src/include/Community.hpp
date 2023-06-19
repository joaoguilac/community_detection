#ifndef _COMMUNITY_H_
#define _COMMUNITY_H_

#include "Node.hpp"

class Community {
    private:
        std::set<Node*> members;
    public:
        Community(std::set<Node*> = {});
        ~Community() = default;

        std::set<Node*> getNeighbors();
        bool neighborsIsSubset(Node*);
        double sim(Node*);
        std::set<Node*> getMembers();

        void addNodes(std::set<Node*>);

        void printCommunity();
};

#include "Community.inl"

#endif