#include "CubicProbing.h"
#define vector_size 109919

void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
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
        database_size++;
        // mark[hash_value]=true;
        return;
    }
    else{
        insert(a);
    }
    database_size++;
}

std::vector<int> CubicProbing::getTopK(int k) {
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

int CubicProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return -1;

    long long hash_value= (long long) hash(id);

    for(long long i=0;i<vector_size;i++){
        long long x=0;

        if(i%2==0) x= /*(int)*/(hash_value+i*i*i)%vector_size;
        else x= /*(int)*/ (hash_value-i*i*i)%vector_size;

        if(bankStorage1d[x].id=="") return -1;

        else if(bankStorage1d[x].id==id) return bankStorage1d[x].balance;
    }
    return -1;
    // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {
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


    long long hash_value= (long long) hash(id);
    for(long long i=0;i<vector_size;i++){

        long long x=0;
        if(i%2==0) x= /*(int)*/ (hash_value+i*i*i)%vector_size;
        else x= /*(int)*/ (hash_value-i*i*i)%vector_size;

        if(bankStorage1d[x].id==id) {
            bankStorage1d[x].balance+=count;
            return;
        }

        if(bankStorage1d[x].id=="") {
            bankStorage1d[x].id=id;
            bankStorage1d[x].balance=count;
            // mark[x]=true;
            database_size++;
            return;
        }

    }

    // for(int i=0;i<vector_size; i++){
    //     long long x=(hash_value+i)%vector_size;
    //     if(mark[x]){
    //         bankStorage1d[x].id=id;
    //         bankStorage1d[x].balance=count;
    //     }
    // }
}

bool CubicProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return false;
    long long hash_value= (long long) hash(id);
    for(long long i=0;i<vector_size;i++){
        
        long long x=0;
        if(i%2==0) x= /*(int)*/ (hash_value+i*i*i)%vector_size;
        else x= /*(int)*/ (hash_value-i*i*i)%vector_size;

        if(bankStorage1d[x].id=="") return false;
        if(bankStorage1d[x].id==id) return true;
    }
    return false;
    // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return false;
    long long hash_value= (long long) hash(id);
    for(long long i=0; i<vector_size; i++){
        
        long long x=0;
        if(i%2==0) x= /*(int)*/ (hash_value+i*i*i)%vector_size;
        else x= /*(int)*/ (hash_value-i*i*i)%vector_size;

        
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
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return database_size; 
    // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hash_value=0;
    for(int i=0;i<4;i++){
        long long x=id[i]-'A';
        hash_value+=pow(x,i+1);
    }
    for(int i=4;i<11;i++){
        long long x=id[i]-'0';
        hash_value+=pow(x,i+1);
    }
    for(int i=12;i<22;i++){
        long long x=id[i]-'0';
        hash_value+=pow(x,i+1);
    }
    return hash_value%vector_size;
    // Placeholder return value
}


void CubicProbing::insert(Account new_account){
    long long hash_value= (long long) hash(new_account.id);
    for(long long i=0; i<vector_size;i++){
        long long x=0;

        if(i%2==0) x= /*(int)*/(hash_value+i*i*i)%vector_size;
        else x= /*(int)*/ (hash_value-i*i*i)%vector_size;

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


int CubicProbing:: pow(int x, int y){
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
void CubicProbing:: merge1(std::vector<int>&v, int s, int m, int e) {
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
void CubicProbing:: mergesort1(std::vector<int>& v, int s, int e) {
	if (s<e) {
		int m=(s+e)/2;
		mergesort1(v,s,m);
		mergesort1(v,m+1,e);
		merge1(v,s,m,e);
	}
}