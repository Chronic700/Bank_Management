#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
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
    
    // Other data members and functions specific to Chaining
    void insert(int hash_value, Account new_account);
    // int binary_search(int hash_value, int count);
    int database_size=0;
    bool initialized=false;
    void merge1(std::vector<int>& v, int s, int m, int e);
    void mergesort1(std::vector<int>& v, int s, int e);
    int pow(int x, int y);
};

#endif // CHAINING_H
