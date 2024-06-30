#include "Comp.h"
#define vector_size 100003

void Comp::createAccount(std::string id, int count) {
    Account a;
    a.id=id;
    a.balance=count;

    if(!initialized){
        for(int i=0; i<vector_size; i++){
            Account fake;
            fake.id="";
            fake.balance=-1;
            bankStorage1d.push_back(fake);
            // mark.push_back(false);
        }

        initialized=true;

        int hash_value=hash(id);

        bankStorage1d[hash_value]=a;
        // mark[hash_value]=true;
        database_size++;
        return;
    }
    else{
        insert(a);
    }
    database_size++;
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> Comp::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std:: vector<int> balances;
    if(k==0 || !initialized) return balances;
    for(int i=0; i<vector_size;i++){
        if(bankStorage1d[i].id!="" && bankStorage1d[i].id!="X"){
            balances.push_back(bankStorage1d[i].balance);
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

int Comp::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return -1;

    int hash_value=hash(id);

    for(int i=0;i<vector_size;i++){
        int x=0;

        if(i%2==0) x=(hash_value+i*i)%vector_size;
        else x=(hash_value-i*i)%vector_size;

        if(bankStorage1d[x].id=="") return -1;

        else if(bankStorage1d[x].id==id) return bankStorage1d[x].balance;
    }
    return -1;
    // Placeholder return value
}

void Comp::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized){
        for(int i=0; i<vector_size; i++){
            Account fake;
            fake.id="";
            fake.balance=-1;
            bankStorage1d.push_back(fake);
            // mark.push_back(false);
        }

        initialized=true;

        int hash_value=hash(id);

        bankStorage1d[hash_value].id=id;
        bankStorage1d[hash_value].balance=count;
        // mark[hash_value]=true;

        // balances->data=count;
        // balances->count=1;
        database_size++;
        return;
    }


    int hash_value=hash(id);
    for(int i=0;i<vector_size;i++){

        int x=0;
        if(i%2==0) x=(hash_value+i*i)%vector_size;
        else x=(hash_value-i*i)%vector_size;

        if(bankStorage1d[x].id==id) {
            bankStorage1d[x].balance+=count;
            return;
        }

        if(bankStorage1d[x].id=="") {
            // cout<<"\nHHHHHHHHHHHHHHHHHH i= "<<i<<" x="<< x<<"\n";
            bankStorage1d[x].id=id;
            bankStorage1d[x].balance=count;
            // mark[x]=true;
            database_size++;
            return;
        }

    }

    // for(int i=0;i<vector_size; i++){
    //     int x=(hash_value+i)%vector_size;
    //     if(mark[x]){
    //         bankStorage1d[x].id=id;
    //         bankStorage1d[x].balance=count;
    //     }
    // }
}

bool Comp::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return false;
    int hash_value=hash(id);
    for(int i=0;i<vector_size;i++){
        
        int x=0;
        if(i%2==0) x=(hash_value+i*i)%vector_size;
        else x=(hash_value-i*i)%vector_size;

        if(bankStorage1d[x].id=="") return false;
        else if(bankStorage1d[x].id==id) return true;
    }
    return false;
    // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return false;
    int hash_value=hash(id);
    for(int i=0; i<vector_size; i++){
        
        int x=0;
        if(i%2==0) x=(hash_value+i*i)%vector_size;
        else x=(hash_value-i*i)%vector_size;
        
        if(bankStorage1d[x].id=="") return false;
        else if(bankStorage1d[x].id==id){
            bankStorage1d[x].id="X";
            bankStorage1d[x].balance=-1;
            database_size--;
            return true;
        }
        
        
        
    }
    return false; 
    // Placeholder return value
}
int Comp::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return database_size; 
    // Placeholder return value
}

int Comp::hash(std::string id) {
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
    return hash_value%vector_size;
    // Placeholder return value
}

void Comp::insert(Account new_account){
    int hash_value=hash(new_account.id);
    for(int i=0; i<vector_size;i++){
        int x=0;

        if(i%2==0) x=(hash_value+i*i)%vector_size;
        else x=(hash_value-i*i)%vector_size;

        if(bankStorage1d[x].id=="X"){
            bankStorage1d[x].id=new_account.id;
            bankStorage1d[x].balance=new_account.balance;
            return;
        }
        if(bankStorage1d[x].id==""){
            bankStorage1d[x].id=new_account.id;
            bankStorage1d[x].balance=new_account.balance;
            return;
        }
    }
}

void Comp:: merge1(std::vector<int>&v, int s, int m, int e) {
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
void Comp:: mergesort1(std::vector<int>& v, int s, int e) {
	if (s<e) {
		int m=(s+e)/2;
		mergesort1(v,s,m);
		mergesort1(v,m+1,e);
		merge1(v,s,m,e);
	}
}


int Comp:: pow(int x, int y){
    long long z=(long long) x;
    long long res = 1;
    z=z%vector_size;
  
    if (z==0) return 0;

    while (y>0){
        if (y%2==1) res=(res*z)%vector_size;
        y=y/2; 
        z=(z*z)%vector_size;
    }
    int r=(int) z;
    return r;
}


// Feel free to add any other helper functions you need
// Good Luck!