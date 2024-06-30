#include "LinearProbing.h"
#define vector_size 109919
using namespace std;

void LinearProbing::createAccount(std::string id, int count) {
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
        // mark[hash_value]=true;

        // balances->data=count;
        // balances->count=1;
        database_size++;
        return;
    }
    else{
        insert(a);
    }
    database_size++;
    // std::cout<<"DataSize= "<<database_size<<"\n";
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std:: vector<int> balances;
    if (k==0 || initialized==false) return balances;
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
    return topK;
    // Placeholder return value
}

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    if(initialized==false) return -1;

    int hash_value=hash(id);

    for(int i=0;i<vector_size;i++){
        int x=(hash_value+i)%vector_size;

        if(bankStorage1d[x].id=="") return -1;

        else if(bankStorage1d[x].id==id) return bankStorage1d[x].balance;
    }
    return -1;
    // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
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
        int x=(hash_value+i)%vector_size;

        if(bankStorage1d[x].id==id) {
            bankStorage1d[x].balance+=count;
            // insert_balance(count);
            return;
        }

        if(bankStorage1d[x].id=="") {
            bankStorage1d[x].id=id;
            bankStorage1d[x].balance=count;
            // mark[x]=true;
            database_size++;
            // insert_balance(count);
            return;
        }

    }

    for(int i=0;i<vector_size; i++){
        int x=(hash_value+i)%vector_size;
        if(bankStorage1d[x].id=="X"){
            bankStorage1d[x].id=id;
            bankStorage1d[x].balance=count;
            database_size++;
            // insert_balance(count);
            return;
        }
    }
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return false;
    // if(id.size()<22) return false;

    int hash_value=hash(id);
    for(int i=0;i<vector_size;i++){
        int x=(hash_value+ i)%vector_size;
        if(bankStorage1d[x].id=="") return false;
        if(bankStorage1d[x].id==id) return true;
    }
    return false;
    // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(!initialized) return false;
    int hash_value=hash(id);
    for(int i=0; i<vector_size; i++){
        int x=(hash_value+i)%vector_size;


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

int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return database_size; 
    // Placeholder return value
}

int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    // int hash_value=0;
    // for(int i=0; i<22;i++){
    //     hash_value+=(int) id[i];
    // }
    // return hash_value;

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

void LinearProbing::insert(Account new_account){
    int hash_value=hash(new_account.id);

    for(int i=0; i<vector_size;i++){
        int x=(hash_value+i)%vector_size;

        if(bankStorage1d[x].id==""){
            // cout<<"___________________"<<i<<" "<<new_account.id<<"\n";
            bankStorage1d[x].id=new_account.id;
            bankStorage1d[x].balance=new_account.balance;
            return;
        }

        if(bankStorage1d[x].id=="X"){
            bankStorage1d[x].id=new_account.id;
            bankStorage1d[x].balance=new_account.balance;
            // mark[x]=false;
            return;
        }
    }
}

void LinearProbing:: merge1(std::vector<int>&v, int s, int m, int e) {
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
void LinearProbing:: mergesort1(std::vector<int>& v, int s, int e) {
	if (s<e) {
		int m=(s+e)/2;
		mergesort1(v,s,m);
		mergesort1(v,m+1,e);
		merge1(v,s,m,e);
	}
}

int LinearProbing:: pow(int x, int y){
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

// int main(){
//     LinearProbing l;
//     // vector<int>v1=l.getTopK(1);
//     // for(int i=0; i<v1.size();i++){
//     //     cout<<v1[i]<<" ";
//     // }
//     l.createAccount( "CDAD7786825_7990768648", 648);
//     l.createAccount ("DCDA7547234_9919615552", 552);
//     l.createAccount( "AACB1850545_7974534788", 788);
//     // std::cout<<l.databaseSize()<<"\n";
//     l.createAccount ("CDBD5250777_1124276711", 711);
//     l.createAccount ("ABCB8377155_0656808575", 575);
//     // std:: vector<int> v= l.getTopK (1);;
//     // std:: cout<<v.size()<<"\n";
//     // for(int i=0;i<v.size();i++){
//     //     std:: cout<<v[i]<<" ";
//     // }
//     // std::cout<<"\n";

//     l.createAccount ("CDDC3792028_3313680038", 38);
//     l.createAccount ("CBBA9574444_7470182321" ,321);
//     l.createAccount ("DBCC4334636_8057544188" ,188);
//     // v= l.getTopK (3);
//     std:: cout<<"Hello\n";
//     // for(int i=0;i<v.size();i++){
//     //     std:: cout<<v[i]<<" ";
//     // }
//     // std:: cout<<"\n";
//     l.createAccount ("BABD5741078_5109455304", 304);
//     l.createAccount ("BCBA7529510_0817878868", 868);
//     std:: cout<<"\n";
//     std::cout<<l.databaseSize();
//     // v= l.getTopK (1);
//     // std:: cout<<"\n";
//     // for(int i=0;i<v.size();i++){
//     //     std:: cout<<v[i]<<" ";
//     // }
//     std:: cout<<"\n";
//     l.addTransaction("BABD5741078_5109455304", 5);
//     std::cout<<l.getBalance("BABD5741078_5109455304")<<"\n";
//     std:: cout<<l.getBalance("BCBA7529510_0817878868")<<"\n";
//     std:: cout<<l.deleteAccount("BABD5741078_5109455304")<<"\n";
//     std:: cout<<l.deleteAccount("BABD5741078_5109455304")<<"\n";
//     std:: cout<<l.doesExist("BABD5741078_5109455304")<<"\n";
//     std:: cout<<l.bankStorage1d[58517].id<<"\n";
//     std:: cout<<l.getBalance("BABD5741078_5109455304")<<"\n";
//     l.addTransaction("BABD5741078_5109455304", 5);
//     cout<<"Trial\n"<<l.bankStorage1d[58517].id<<"\n";
//     std:: cout<<l.getBalance("BCBA7529510_0817878868")<<"\n";
//     std:: cout<<l.doesExist("BABD5741078_5109455304")<<"\n";
//     std:: cout<<l.getBalance("BABD5741078_5109455304")<<"\n";
//     std:: cout<<l.hash("BABD5741078_5109455304")<<"\n";
//     cout<<"Hello##########################\n";
//     cout<<l.bankStorage1d[58517].id<<"\n";
//     cout<<l.bankStorage1d[58518].id<<"\n";
//     l.createAccount("BABD5741078*5109455304",10);
//     std:: cout<<l.hash("BABD5741078*5109455304")<<"\n";
//     cout<<l.bankStorage1d[58517].id<<"\n";
//     cout<<l.bankStorage1d[58518].id<<"\n";
//     cout<<"====================\n";

//     l.createAccount("BABD5741078#5109455304",10);
//     std:: cout<<l.hash("BABD5741078#5109455304")<<"\n";
//     cout<<l.bankStorage1d[58517].id<<"\n";
//     cout<<l.bankStorage1d[58518].id<<"\n";
//     cout<<l.bankStorage1d[58519].id<<"\n";

//     // l.createAccount("BABD5741078&5109455304",10);
//     // std:: cout<<l.hash("BABD5741078&5109455304")<<"\n";
//     // cout<<l.bankStorage1d[58517].id<<"\n";
//     // cout<<l.bankStorage1d[58518].id<<"\n";
//     // cout<<l.bankStorage1d[58519].id<<"\n";
//     // cout<<l.bankStorage1d[58520].id<<"\n";



//     std:: cout<<l.doesExist("BABD5741078*5109455304")<<"\n";
//     std::cout<<l.doesExist("j")<<"\n";
//     std::cout<<"hello"<<'\n';
//     std:: cout<<l.bankStorage1d[58518].id<<"\n";
//     cout<<l.databaseSize()<<"\n";
//     cout<<"&&&&&&&&&&&&&&&&&&&\n";
//     l.addTransaction("BABD5741078%5109455304",10);
//     for(int i=0;i<5;i++){
//         cout<<l.bankStorage1d[58517+i].id<<" ";
//     }
//     cout<<"\n";
//     cout<<l.bankStorage1d[58519].id<<"\n";
//     cout<<l.databaseSize()<<"\n";
//     cout<<l.getBalance("BABD5741078%5109455304")<<"\n";
//     cout<<l.deleteAccount("BABD5741078%5109455304")<<"\n";
//     cout<<l.getBalance("BABD5741078%5109455304")<<"\n";
//     cout<<l.doesExist("BABD5741078%5109455304")<<"\n";
//     cout<<l.bankStorage1d[58519].id<<"\n";
//     // l.createAccount("A",10);
//     cout<<l.hash("AWAA00000000000000000");
//     // cout<<"hello\n";
//     cout<<l.deleteAccount("BABD5741078#109455304")<<"\n";
//     for(int i=0;i<vector_size;i++){
//         if(l.bankStorage1d[i].id!="") cout<<l.bankStorage1d[i].id<<" ";
//     }

//     cout<<"\n"<< l.hash("BABD5741078_109455304")<<"\n";
//     cout<<l.hash("BABD5741078#109455304")<<"\n";
//     l.createAccount("BABD5741078#109455304", 500);
//     cout<<l.hash("ZZZ9919999999999999");

    
    // cout<<l.hash("egetgrgtvrfevcwdcerverwtbvevefvh")<<"\n";





    // addTransaction BCBA7529510_0817878868 -860
    // getBalance BCBA7529510_0817878868
    // getTopK 1
    // addTransaction DCDA7547234_9919615552 592
    // getTopK 5
    // deleteAccount DCDA7547234_9919615552
    // getTopK 4
    // databaseSize

// }