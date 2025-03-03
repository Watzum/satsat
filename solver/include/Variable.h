//
// Created by Emil Watz on 21.02.2025.
//

#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <unordered_map>

class Variable {
public:
    explicit Variable(long i, long f) : internal_id{i}, file_id{f}, negative_occurrences(0), positive_occurrences(0) {}
    //TODO...
    explicit Variable(long i) : internal_id{i}, file_id{-1}, negative_occurrences(0), positive_occurrences(0) {}

    void addClause(long clauseId, bool polarity);
    void removeClause(long clauseId);

    [[nodiscard]] long getInternalId() const;
    [[nodiscard]] size_t getNumberOfClauses() const;
    [[nodiscard]] long getCompareValue() const;
    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] bool isPure() const;
    [[nodiscard]] bool getPolarity() const;
    bool operator<(const Variable& v) const;

private:
    std::unordered_map<long, bool> clauses;
    long internal_id;
    long file_id;
    long negative_occurrences;
    long positive_occurrences;
};

inline bool variable_comparison(const Variable& a, const Variable& b) {
    return a.getCompareValue() > b.getCompareValue();
}

#endif //VARIABLE_H
