//
// Created by Emil Watz on 26.02.2025.
//

#ifndef CLAUSE_H
#define CLAUSE_H
#include <set>
#include <unordered_map>


class Clause {
public:
    void addVariable(size_t varId, bool polarity);
    bool removeVariable(size_t varId);
    bool isEmpty() const;
    std::unordered_map<size_t,bool>::const_iterator begin();
    std::unordered_map<size_t,bool>::const_iterator end();
private:
    std::unordered_map<size_t, bool> variables;
};



#endif //CLAUSE_H
