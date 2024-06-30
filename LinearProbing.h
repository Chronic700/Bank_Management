#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    // Other data members and functions specific to Linear Probing
    bool initialized=false;
    // Node* balances;
    // std::vector<bool> mark;
    void insert(Account new_account);
    int database_size=0;
    // void insert_balance(int count);
    // Node* delete_balance(int count);

    // int find_index(std::string id);
    void merge1(std::vector<int>& v, int s, int m, int e);
    void mergesort1(std::vector<int>& v, int s, int e);
    int pow(int x, int y);
};

#endif // LINEARPROBING_H
