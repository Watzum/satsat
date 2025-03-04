//
// Created by Emil Watz on 26.02.2025.
//

#ifndef CLAUSE_H
#define CLAUSE_H
#include <set>
#include <unordered_map>


class Clause {
public:
    void addVariable(long varId, bool polarity);
    bool removeVariable(long varId);
    bool isEmpty() const;
    std::unordered_map<long,bool>::const_iterator begin();
    std::unordered_map<long,bool>::const_iterator end();


private:
    std::unordered_map<long, bool> variables;
};



#endif //CLAUSE_H
