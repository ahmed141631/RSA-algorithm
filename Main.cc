#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
using namespace std;
class KeyGenerator{
    public:
    unsigned p;
    unsigned q;
    unsigned n; //n=pq
    unsigned phi_n; //phi_n= (p-1)(q-1)
    unsigned e; // where gcd(e,phi_n) is 1
    unsigned d; 

    void prime_input();
    void prime_check();
    unsigned calculate_n();
    unsigned calculate_phi_n();
    unsigned calculate_e();
    unsigned calculate_d();
    void Encrypt();
    void Decrypt();
};

void KeyGenerator::prime_input(){
    cout<<"what is the prime number p : ";
    cin >> p;
    cout<<"what is the prime number q : ";
    cin >> q;
}

void KeyGenerator::prime_check(){
 vector<unsigned> factors_p;

 for(unsigned i=0; i<=static_cast<unsigned>(sqrt(p )); i++){
    if(p%i==0){
        factors_p.push_back(i);
        factors_p.push_back(p/i);
    }
 }
 vector<unsigned> factors_q;

 for(unsigned i=0; i<=static_cast<unsigned>(sqrt(p )); i++){
    if(q%i==0){
        factors_q.push_back(i);
        factors_q.push_back(q/i);
    }
 }

 if(factors_p.size()!=0 || factors_q.size()!=0){
    throw runtime_error("p or q are not primes");
 }

}

unsigned KeyGenerator::calculate_n(){
    n=p*q;
    return n;
    }

unsigned KeyGenerator::calculate_phi_n(){
    phi_n=(p-1)*(q-1);
    return phi_n;
}

unsigned KeyGenerator::calculate_e(){
    /* e  should be  e>1 and gcd(e,phi_n)=1 */
    unsigned i=2;
    while(gcd(i,phi_n)!=1){
        i++;
    }
    e=i;
    if(e>=phi_n) throw runtime_error("e is greater than phi_n or equal");

    return e;
}

unsigned KeyGenerator::calculate_d(){
    /* e*d mod phi_n =1 */
    unsigned k=1;
    while(((k*phi_n)+1)%e!=0){
        k++;
        d=((k*phi_n)+1)/e;
    }
    return d;
}

void KeyGenerator::Encrypt(){
    cout<<"enter the numbre M  to encrypt : ";
     unsigned  M;
    cin>>M;
    
   long power =pow(M,e);
   long result= power %n;

    cout<<result<<endl;

    }

    void KeyGenerator::Decrypt(){
        cout<<"enter the numbre c  to decrypt : ";
        unsigned  c;
        cin>>c;
        long power=pow(c,d);
        long result= power %n;
        cout<<result<<endl;
    }


int main()
{
    
    try{
       
    KeyGenerator kg;
    kg.prime_input();
    kg.prime_check();
    cout<< kg.calculate_n()<<endl;
    cout<<kg.calculate_phi_n()<<endl;
    cout<<kg.calculate_e()<<endl;
    cout<<kg.calculate_d()<<endl;
    cout<< "Do you want to encrypt or decrypt "<<endl;
    cout<< "Enter 1 for encrypt or 0 for decrypt"<<endl;
    int choice;
    cin>>choice;
    if(choice==1){
        kg.Encrypt();
    }else if(choice==0){
        kg.Decrypt();
    }else{
        main();
    }
    }catch(runtime_error &s){
        cout<<s.what()<<endl;
    }
   
 
    return 0;
}
