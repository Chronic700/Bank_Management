#include "Chaining.h"
#define vector_size1 5003
// int Chaining:: int database_size=0;

void Chaining::createAccount(std::string id, int count) {

    if(!initialized){
        initialized=true;
        bankStorage2d=std::vector<std::vector<Account>>(vector_size1);
        
    }
    // IMPLEMENT YOUR CODE HERE
    Account a;
    a.id=id;
    a.balance=count;

    int hash_value= hash(id);

    insert(hash_value, a);
    database_size++;
}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std:: vector<int> balances;
    if(!initialized || k==0) return balances;
    
    int size2=bankStorage2d.size();
    for(int i=0;i<size2; i++){
        int size=bankStorage2d[i].size();
        for(int j=0;j<size;j++){
            balances.push_back(bankStorage2d[i][j].balance);
        }
    }

    int s=balances.size();
    // std::cout<<"\nUnsorted: Size "<<s<<"\n";

    // for(int i=0; i<balances.size();i++){
    //     std:: cout<<balances[i]<<" ";
    // }
    
    // int size=balances.size();
    mergesort1(balances, 0, s-1);
    if (k>balances.size()) return balances;
    // std::cout<<"\nSorted: Size "<<balances.size()<<"\n";
    // std::cout<<"\nMerged: \n";

    // std::cout<<"\n";
    // for(int i=0; i<balances.size();i++){
    //     std:: cout<<balances[i]<<" ";
    // }

    std:: vector<int>topK;
    // topK.push_back(balances[size-1]);
    // std::cout<<"\nJ\n";
    // std::cout<<topK[0]<<"\n";
    // int temp=balances[size-1];
    // int count=k-1;
    for(int i=0;i<k;i++){
        int x=balances[s-1-i];
        topK.push_back(x);
    }
    // std::cout<<"\nSize= "<<topK.size()<<"\n";
    return std::vector<int>(topK.begin(), topK.end());
    // Placeholder return value
}

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return -1;
    int hash_value=hash(id);
    for(int i=0; i<bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id) return bankStorage2d[hash_value][i].balance;
    }
    return -1;

    // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {

    if(!initialized){
        initialized=true;
        bankStorage2d=std::vector<std::vector<Account>>(vector_size1);
        
        // IMPLEMENT YOUR CODE HERE
        Account a;
        a.id=id;
        a.balance=count;

        int hash_value= hash(id);

        insert(hash_value, a);
        database_size++;
        return;
    }


    int hash_value=hash(id);
    for(int i=0; i<bankStorage2d[hash_value].size();i++){
        if(bankStorage2d[hash_value][i].id==id){
            bankStorage2d[hash_value][i].balance+=count;
            return;
        }
    }

    createAccount(id, count);
    return;
    
    // IMPLEMENT YOUR CODE HERE
}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    if(!initialized) return false;
    int hash_value=hash(id);
    for(int i=0; i<bankStorage2d[hash_value].size(); i++){
        if(bankStorage2d[hash_value][i].id==id) return true;
    }

    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    if(!initialized) return false;
    int hash_value=hash(id);
    int i=0;
    while(i<bankStorage2d[hash_value].size()){
        if(bankStorage2d[hash_value][i].id==id){
            bankStorage2d[hash_value].erase(bankStorage2d[hash_value].begin()+i);
            database_size--;
            return true;
        }
        i++;
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return database_size;
    // Placeholder return value
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_value=0;
    for(int i=0;i<4;i++){
        int x=id[i]-'A';
        hash_value+=pow(x,i+1);
    }
    for(int i=4;i<11;i++){
        int x=id[i]-'0';
        hash_value+=pow(x,i+1);
    }
    for(int i=12;i<22;i++){
        int x=id[i]-'0';
        hash_value+=pow(x,i+1);
    }
    return hash_value%vector_size1;
    // Placeholder return value
}

void Chaining:: insert(int h, Account new_accout){
    // int index= binary_search(h, new_accout.balance);

    bankStorage2d[h].push_back(new_accout);
    return;

}

// int Chaining:: binary_search(int hash_index, int new_balance){
//     int temp=0;
//     int left=0;
//     int right=bankStorage2d[hash_index].size();
//     if(bankStorage2d[hash_index][0].balance<new_balance) return -1;

//     while(left<=right){
//         int mid=(left+right)/2;
//         int x=bankStorage2d[hash_index][mid].balance;
//         if(x==new_balance) return mid;
        
//         else if(x<new_balance) right=mid-1;

//         else if(x>new_balance){
//             temp=mid;
//             left=mid++;
//         }
//     }
//     return temp;

// }

void Chaining:: merge1(std::vector<int>&v, int s, int m, int e) {
	std::vector<int>temp;
	int i,j;
	i=s;
	j=m+1;

	while (i<=m && j<=e) {
        if (v[i]<=v[j]) {
			temp.push_back(v[i]);
			i++;
		}else {
			temp.push_back(v[j]);
			j++;
		}
	}
    while (i<=m) {
		temp.push_back(v[i]);
		i++;
	}
    while (j<=e) {
		temp.push_back(v[j]);
		j++;
	}
    for (int i=s; i<=e;++i){
        v[i] = temp[i-s];
    }
}
void Chaining:: mergesort1(std::vector<int>& v, int s, int e) {
	if (s<e) {
		int m=(s+e)/2;
		mergesort1(v,s,m);
		mergesort1(v,m+1,e);
		merge1(v,s,m,e);
	}
}

int Chaining:: pow(int x, int y){
    long long z=(long long) x;
    long long res = 1;
    z=z%vector_size1;
  
    if (z==0) return 0;

    while (y>0){
        if (y%2==1) res=(res*z)%vector_size1;
        y=y/2; 
        z=(z*z)%vector_size1;
    }
    int r=(int) z;
    return r;
}

// int main(){
//     Chaining l;
//     l.createAccount("DQJM6966758_985392816", 10);
//     std::cout<<l.doesExist("DQJM6966758_985392816");
// }