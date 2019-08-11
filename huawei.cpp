//
// Created by ??? on 2019/6/21.
//
#include <iostream>
#include <bitset>
#include <cmath>
#include <string>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <tuple>
#include <mutex>
#include <thread>
#include <iomanip>
using namespace std;

//???????int??????????????????int????????????д洢?1???????
//?·?????bitset???????????
int one_numbers(int a){
    bitset<32> b(a);
    int count=0;
    for(int i=0;i<32;i++){
        if(b[i]==1)
            count++;
    }
    return count;
}

//??1??2??4??Щ2??η?????λ??????
int one_numbers_2(int a){
    int count=0;
    for(int i=0;i<32;i++){
        if(a&static_cast<int>(pow(2,i)))
            count++;
    }
    return count;
}

//?????????????????????????????????????????
//??????????????????????????0????????????????0?????????100????????001
//?·?????to_string????
string int_to_str(int x){
   auto str=to_string(x);
   auto n=str.size();
   string s="";
   for(int i=n-1;i>=0;i--){
        s+=str[i];
   }
   return s;
}

//?????????????????????????????????????
//?·?????string??rfind????
int length_of_last_str(string str){
    auto x=str.rfind(" ");
    if(x==string::npos)
        return str.size();
    return str.size()-x-1;
}

//д?????????????????????????????????????
//??????????????????????????к??и??????????????????Сд??
//?·?????STL?е?count?????
int numbers_of_char(string str,char c){
    return count_if(str.begin(),str.end(),[=](char a){
        return tolower(c)==tolower(a);
    });
}

//????????
//?·?????????set
void deduplication_and_sort(){
    int n;
    while(cin>>n) {
        set<int> s;
        while (n--) {
            int x;
            cin >> x;
            s.insert(x);
        }
        for (auto ss:s) {
            cout << ss << endl;
        }
    }
}

//??????????????????????8?????????????????????????????飻
//????????8???????????????????油????0???????????????
//?·?????string??substr????
void str_split(string str){
    if(str.size()<=8){
        str.insert(str.size(),8-str.size(),'0');
        cout<<str<<endl;
        return ;
    }
    vector<string> v;
    for(int i=0;i<str.size();i+=8){
        v.push_back(str.substr(i,8));
    }
    auto n=v.size();
    if(v[n-1].size()<=8){
        v[n-1].insert(v[n-1].size(),8-v[n-1].size(),'0');
    }
    for(auto xx:v){
        cout<<xx<<endl;
    }
}

//д?????????????????????????????????
//?????????????????????????????????? ??
//?·?????stoi??????????????汾
void hex_to_dec(){
    string s;
    while(cin>>s){
      //cin>>s;
        cout<<stoi(s, nullptr,16)<<endl;
    }
}

//????:????????????????????С????????????????????????????????180???????????2 2 3 3 5 ??
//???????????????п??
//?·????2??????????????????????????ж??????????????????????????????????2????3???????????????
void getResult(long input){
    while (input!=1){
        for(int i=2;i<=input;i++){
            if(input%i==0){
                cout<<i<<" ";
                input/=i;
                break;
            }
        }
    }
}

//д??????????????????????????????????????????????
//???С???????????????5,?????????С??5?????????????
//?·?????to_string()????
void double_to_int(){
    double x;
    cin>>x;
    auto s=to_string(x);
    auto it=s.find(".");
    if(it==string::npos)
        cout<<x;
    else{
        auto y=s[it+1];
        if(y>='5')
            cout<<(int)x+1;
        else
            cout<<(int)x;
    }
}

//??????????????????????????????????????????к????
//??????????????????????????????????key?????????????
//?·?????map????
void sum_of_value(){
    int n;
    cin>>n;
    map<int,int> m;
    while(n--){
        int index,value;
        cin>>index>>value;
        if(m.find(index)==m.end()){
            m[index]=value;
        }else{
            m[index]+=value;
        }
    }
    for(auto xx:m){
        cout<<xx.first<<" "<<xx.second<<endl;
    }
}

//???????int??????????????????????????
//????????????????????????????
//?·???????????鼴??
void de_duplicate(){
    int x;
    cin>>x;
    auto s=to_string(x);
    auto n=s.size();
    vector<int> v(10,-1);
    string str="";
    for(int i=n-1;i>=0;i--){
        if(v[s[i]-'0']==-1) {
            str += to_string(s[i]-'0');
            v[s[i]-'0']=0;
        }
    }
    cout<<str;
}

//??д???????????????????к??е?????????????
//?????ACSII??Χ??(0~127)???????Χ??????????
//?·????????????
void different_number(){
    string s;
    cin>>s;
    vector<int> v(128,-1);
    auto n=s.size();
    int count=0;
    for(int i=0;i<n;i++){
        if(v[s[i]]==-1){
            count++;
            v[s[i]]=0;
        }
    }
    cout<<count<<endl;
}

//д????????????????????????????????????????????????
//????????STL?е?reverse????
void str_reverse(){
    string s;cin>>s;
    reverse(s.begin(),s.end());
    cout<<s<<endl;
}

//???????????????????λ???????????硰I am a boy???????????????boy a am I??
//???е???????????????????????г?????????????????????????
//?·?????getline??STL?е?reverse
void str_reverse_without_word(){
    string s;
    getline(cin,s);
    reverse(s.begin(),s.end());
    stringstream s1(s);
    string ss;
    string str="";
    while(s1>>ss){
        reverse(ss.begin(),ss.end());
        str+=(" "+ss);
    }
    str.erase(str.begin());
    cout<<str;
}

//????n????????????n???????????????????С?
//?·?????sort????????
void str_sort(){
    int n;cin>>n;
    vector<string> v;
    while(n--){
        string s;
        cin>>s;
        v.push_back(s);
    }
    sort(v.begin(),v.end());
    for(auto xx:v){
        cout<<xx<<endl;
    }
}

//??????????????????С??飬????????????????????????????к??
//????
//1?? ??????8???????????????????????????????????????????к????????????????????????????
//2?? ????16?????????????????????????????Ч16???????
//3?? ?????????????·??????????????????·????
//?·?????string???????????STL???find_if??
string get_filename(string str){
    auto x=str.rfind("\\");
    if(x==string::npos)
        return str;
    else
        return str.substr(x+1);
}
void mistake_log(){
    vector<tuple<string,int,int>> log;
    string s;
    while(getline(cin,s)){
        auto it=s.find(" ");
        auto filename=s.substr(0,it);
        auto number=stoi(s.substr(it+1));
        auto x=find_if(log.begin(),log.end(),[filename,number](tuple<string,int,int> t1){
            return get_filename(get<0>(t1))==get_filename(filename)&&get<1>(t1)==number;
        });
        if(x==log.end()){
            log.push_back(make_tuple(filename,number,1));
        }else{
            get<2>(*x)+=1;
        }
    }
    int j=0;
    if(log.size()>8)
        j=log.size()-8;
    for(int i=j;i<log.size();i++){
        auto ss=get<0>(log[i]);
        auto it1=ss.rfind("\\");
        if(it1==string::npos){
            if(ss.size()<=16)
                cout<<ss<<" ";
            else
                cout<<ss.substr(ss.size()-16)<<" ";
        }else{
            auto sss=ss.substr(it1+1);
            if(sss.size()<=16)
                cout<<sss<<" ";
            else
                cout<<sss.substr(sss.size()-16)<<" ";
        }
        cout<<get<1>(log[i])<<" "<<get<2>(log[i])<<endl;
    }
}

//???????:
//1.???????8λ
//2.??????Сд???.????.????????,????????????????
//3.??????????????2????????
void passwd_verify(){
    string s;
    while(cin>>s){
        if(s.size()<=8)
            cout<<"NG"<<endl;
        else{
            int count=0;
            auto it=find_if(s.begin(),s.end(),[](char c){
                return c>='0'&&c<='9';
            });
            if(it!=s.end())
                count++;
            auto it1=find_if(s.begin(),s.end(),[](char c){
                return c>='a'&&c<='z';
            });
            if(it1!=s.end())
                count++;
            auto it2=find_if(s.begin(),s.end(),[](char c){
                return c>='A'&&c<='Z';
            });
            if(it2!=s.end())
                count++;
            auto it3=find_if(s.begin(),s.end(),[](char c){
                return (c<'0'||c>'9')&&(c<'a'||c>'z')&&(c<'A'||c>'Z');
            });
            if(it3!=s.end())
                count++;
            if(count<3)
                cout<<"NG"<<endl;
            else{
                map<string,int> ss;bool flag=true;
                for(int i=0;i<s.size()-2;i++){
                    auto str=s.substr(i,3);
                    if(ss.find(str)!=ss.end()&&ss[str]!=i-2&&ss[str]!=i-1){
                        flag= false;
                        break;
                    }else{
                        ss.insert(make_pair(str,i));
                    }
                }
                if(flag==true)
                    cout<<"OK"<<endl;
                else
                    cout<<"NG"<<endl;
            }
        }
    }
}

//????????????????? A????????????D????????????W????????????S????????????
//???0,0????????????????????????????Щ????????????????????????????????档
//????
//????????A(????D????W????S) + ???????λ?????
//?·????????????????ж?
pair<int,int> move_one_step(string s,pair<int,int> p){
    //cout<<s[0]<<endl;
    if(s.size()<=1||s.size()>3||(s[0]!='A'&&s[0]!='S'&&s[0]!='W'&&s[0]!='D'))
        return p;
    else{
        bool flag=true;
        for(int i=1;i<s.size();i++){
            if(s[i]<'0'||s[i]>'9'){
                flag= false;break;
            }
        }
        //cout<<flag<<endl;
        if(!flag)
            return p;
        auto x=stoi(s.substr(1));
        if(s[0]=='A'){
            auto pp=p;pp.first-=x;
            return pp;
        }else if(s[0]=='W'){
            auto pp=p;pp.second+=x;
            return pp;
        }else if(s[0]=='S'){
            auto pp=p;pp.second-=x;
            //cout<<pp.first<<" "<<pp.second<<endl;
            return pp;
        }else{
            auto pp=p;pp.first+=x;
            return pp;
        }
    }
}

void move(){
    string s;
    cin>>s;
    auto start=0;
    auto it=s.find(";");
    pair<int,int> p(0,0);
    while(it!=string::npos){
        auto ss=s.substr(start,it-start);
        p=move_one_step(ss,p);
        //cout<<p.first<<" "<<p.second<<endl;
        start=it+1;
        it=s.find(";",it+1);
    }
    cout<<p.first<<","<<p.second<<endl;
}


//?????IP????????????????з???????????A/B/C/D/E?????????????????????????????
//????????????????????1????????0???????磺255.255.255.32????????????????
//????????????0?????IP??????????????0.1.1.2?????????
bool mask_judge(string s){
    auto it=find(s.begin(),s.end(),'0');
    if(find(it,s.end(),'1')!=s.end())
        return false;
    return true;
}

int ip_address_judge(string s){
    auto it=s.find("~");
    auto ip=s.substr(0,it);
    auto mask=s.substr(it+1);
    if(ip>="1.0.0.0"&&ip<="126.255.255.255"&&ip.substr(0,2)!="10"&&mask_judge(mask)){
        return 0;
    }else if(ip>="128.0.0.0"&&ip<="191.255.255.255"&&(ip<"172.16.0.0"||ip>"172.31.255.255")&&mask_judge(mask)){
        return 1;
    }else if(ip>="192.0.0.0"&&ip<="223.255.255.255"&&(ip<"192.168.0.0"||ip>"192.168.255.255")&&mask_judge(mask)){
        return 2;
    }else if(ip>="224.0.0.0"&&ip<="239.255.255.255"&&mask_judge(mask)){
        return 3;
    }else if(ip>="240.0.0.0"&&ip<="255.255.255.255"&&mask_judge(mask)){
        return 4;
    }else if((ip>="10.0.0.0"&&ip<="10.255.255.255")||(ip>="172.16.0.0"&&ip<="172.31.255.255")||(ip>="192.168.0.0"&&ip<="192.168.255.255")&&mask_judge(mask)){
        return 6;
    }else if(ip>="0.0.0.0"&&ip<="0.255.255.255"&&mask_judge(mask)){
        return 10;
    }else{
        return 5;
    }
}

void ip_address_classify(){
    string s;
    vector<int> v(6,0);
    int i=0;
    while(i++<4){
        cin>>s;
        if(ip_address_judge(s)<=v.size()-1)
            v[ip_address_judge(s)]+=1;
    }
    for(auto xx:v){
        cout<<xx<<" ";
    }
}

//??????
//???????滻????
void simple_password(){
    string s;
    while(cin>>s){
        string s1="";
        for(auto xx:s){
            if(xx>=65&&xx<=90){
                if(xx==90)
                    s1+='a';
                else
                    s1+=(xx+33);
            }else if(xx>=97&&xx<=122){
                char c;
                if(xx=='s')
                    c=7;
                else if(xx<='r')
                    c=(xx-97)/3+2;
                else if(xx!='z')
                    c=(xx-116)/3+8;
                else
                    c=9;
                s1+=to_string(c);
            } else
                s1+=xx;
        }
        cout<<s1<<endl;
    }
}

//????????????г????????????????
//???????????????????????????????????Щ?????????????
//??????????????????????????
//?·???????????
void delete_least_char(){
    string s;
    while(cin>>s){
        map<char,int> m;
        for(auto ss:s){
            if(m.find(ss)!=m.end())
                m[ss]+=1;
            else
                m[ss]=1;
        }
        set<char> v;
        int count=s.size();
        for(auto mm:m){
            if(mm.second<count){
                v.clear();
                v.insert(mm.first);
                count=mm.second;
            }else if(mm.second==count)
                v.insert(mm.first);
        }
        for(auto i=0;i<s.size();i++){
            if(v.find(s[i])!=v.end()){
                s.erase(s.begin()+i);
                i--;
            }
        }
        cout<<s<<endl;
    }
}

//???????
void transfer_bottle(){
    int n;
    while(cin>>n){
        int Count=0;
        while(n>=3){
            auto x=n/3;
            auto y=n%3;
            Count+=x;
            n-=(3*x);
            n+=x;
        }
        if(n==2)
            Count+=1;
        cout<<Count<<endl;
    }
}

//?????
void sing_and_song(){
    int n;
    while(cin>>n){
        vector<int> v;
        while(n--){
            int x;cin>>x;
            v.push_back(x);
        }
        int Count=v.size();
        for(int i=0;i<v.size();i++){
            int count=0;
            for(int j=0;j<i;j++){
                if(v[j]>=v[j+1])
                    count++;
            }
            for(int j=i+1;j<v.size();j++){
                if(v[j]<=v[j-1])
                    count++;
            }
                Count=min(count,Count);
        }
        cout<<Count<<endl;
    }
}

//?????
//??M??????????????N??????????????????е????????????
//????ж?????????????????K?????5??1??1??1??5??1 ??????????
static set<vector<int>> distribution;
void apple_count(int m,int n,vector<int>& v){
    if(m==0&&n<=v.size()){
        auto x=v;
        sort(x.begin(),x.end());
        distribution.insert(x);
    }else if(m>0&&n==v.size()){
      return ;
    }else{
        for(int i=0;i<=m;i++){
            v[n]=i;
            apple_count(m-i,n+1,v);
            v[n]=0;
        }
    }
}

void apple(){
    int m,n;
    while(cin>>m>>n){
        vector<int> v(n,0);
        apple_count(m,0,v);
        cout<<distribution.size()<<endl;
        distribution.clear();
    }
}

//???????????
//?????????ε?????????????????1????????е?????????????????????????????????????????????3???????????????????????????????????0????
//???n?е????????????λ?á?????????????????-1??????????3,?????2??????4?????3??
void triangle_sum(){
    int n;
    while(cin>>n){
        vector<vector<int>> v(n+1,vector<int>());
        v[1].push_back(1);
        for(int i=2;i<=n;i++){
            for(int j=0;j<v[i-1].size()+2;j++){
                int x=v[i-1].size();
                auto y=(j-2>=0?v[i-1][j-2]:0)+(j-1>=0&&j-1<x?v[i-1][j-1]:0)+(j<x?v[i-1][j]:0);
                v[i].push_back(y);
            }
        }
        for(int i=1;i<v[n].size();i++){
            if((v[n][i]&0x1)==0) {
                cout << i+1 << endl;
                break;
            }
        }
    }
}

//????????????????1?????
//???biteset
void number_of_one_binary(){
    int num;
    while(cin>>num){
        bitset<32> b(num);
        int Count=0;
        for(int i=0;i<32;i++){
            if(b[i]==1)
                Count++;
        }
        cout<<Count<<endl;
    }
}

//??д????????????????????????????????????????????????????????????
//???????????????????????"??ABC"4???????"??AB"??????"??ABC??DEF"6??
//???????"??ABC"??????"??ABC+??????"??
//???string?ж???????
void str_intercept(){
    string s;int num;
    while(cin>>s>>num){
        string str="";
        for(int i=0;i<s.size()&&num>=1;){
            if((s[i]>=65&&s[i]<=90)||(s[i]>=97&&s[i]<=122)){
                str+=s[i];num-=1;i++;
            }
            else{
                if(num<=1)
                    break;
                else
                {
                    cout<<s[i]<<endl;
                    str+=(string(s.begin()+i,s.begin()+1));num-=2;i+=1;
                }
            }
        }
        cout<<str<<endl;
    }
}

//?????????????????????????????????
//???????????????????????????±??????????????±??????????????С????????
void SortString(string &s){
    string s1="";
    string s2="";
    for(int i=0;i<s.size();i++){
        if(i&0x1){
            s1+=s[i];
        }else{
            s2+=s[i];
        }
    }
    sort(s1.begin(),s1.end());sort(s2.begin(),s2.end());
    for(int i=0,j=0,k=0;i<s.size();i++){
        if(i&0x1){
            s[i]=s1[j];j++;
        }else{
            s[i]=s2[k];k++;
        }
    }
}

char TransferChar(char a,char b){
    int x;
    if(b=='0')
        x=a-'0';
    else if(b=='a')
        x=a-'a'+10;
    else
        x=a-'A'+10;
    bitset<4> b1(x);
    int i=0,j=3;
    while(i<j){
        int y=b1[i];
        b1[i]=b1[j];
        b1[j]=y;
        i++;j--;
    }
    if(b=='0'&&b1.to_ulong()<10)
        return b1.to_ulong()+'0';
    else if(b1.to_ulong()<10)
        return b1.to_ulong()+'0';
    else{
        return b1.to_ulong()-10+'A';
    }
}

void TransferString(string &s){
    for(int i=0;i<s.size();i++){
        if(s[i]>='0'&&s[i]<='9'){
            s[i]=TransferChar(s[i],'0');
        }else if(s[i]>='A'&&s[i]<='F')
            s[i]=TransferChar(s[i],'A');
        else if(s[i]>='a'&&s[i]<='f')
            s[i]=TransferChar(s[i],'a');
        else{
            continue;
        }
    }
}

void ProcessString(string s1,string s2){
    auto s=s1+s2;
    SortString(s);
    TransferString(s);
    cout<<s<<endl;
}

//????????????????
void max_symmetrical_substring(string s){
    vector<int> v;
    for(int i=0;i<s.size();i++){
        int j=i,k=i+1,tmp=0;
        if(j>=0&&k<s.size()&&s[j]!=s[k])
            tmp=1;
        else if(j<0||k>=s.size()){
            tmp=1;
        }else {
            while (j>=0&&k<s.size()){
                if(s[j]==s[k]){
                j--;k++;}
                else
                    break;
            }
            tmp=max(tmp,k-j-1);
        }
        j=i-1,k=i+1;int tmp1=0;
        if(j>=0&&k<s.size()&&s[j]!=s[k])
            tmp1=1;
        else if(j<0||k>=s.size()){
            tmp1=1;
        }else {
            while (j>=0&&k<s.size()){
                if(s[j]==s[k]){
                    j--;k++;}
                else
                    break;
            }
            tmp1=max(tmp1,k-j-1);
        }
        v.push_back(max(tmp,tmp1));
    }
    int Max=0;
    for(auto xx:v)
        Max=max(xx,Max);
    cout<<Max<<endl;
}

//???????
void Reverse_String(){
    string s;
    while(getline(cin,s)){
        for(auto &xx:s){
            if(xx<'A'||(xx>'Z'&&xx<'a')||xx>'z')
                xx=' ';
        }
        stringstream s1(s);
        string str;vector<string> v;
        while(s1>>str){
            v.push_back(str);
        }
        string ss="";
        for(auto i=v.rbegin();i<v.rend();i++){
            ss+=(*i);
            ss+=" ";
        }
        ss.erase(ss.end()-1);
        cout<<ss<<endl;
    }
}

//??????IP????????

vector<string> str_split1(string s){
    vector<string> v;
    auto start=s.begin();
    while(find(start,s.end(),'.')!=s.end()){
        auto it=find(start,s.end(),'.');
        string s1(start,it);
        v.push_back(s1);
        start=it+1;
    }
    v.push_back(string(start,s.end()));
    return v;
}

string int_to_ip(string s){
    string ss;
    auto s1=s.substr(0,8);
    bitset<8> b1(s1);
    ss+=to_string(b1.to_ulong());
    ss+=".";
    auto s2=s.substr(8,8);
    bitset<8> b2(s2);
    ss+=to_string(b2.to_ulong());
    ss+=".";
    auto s3=s.substr(16,8);
    bitset<8> b3(s3);
    ss+=to_string(b3.to_ulong());
    ss+=".";
    auto s4=s.substr(24,8);
    bitset<8> b4(s4);
    ss+=to_string(b4.to_ulong());
    return ss;
}

void int_transfer_ip(){
    string ip_str,ip_int;
    while(cin>>ip_str>>ip_int){
        auto v=str_split1(ip_str);
        string s1;
        for(auto xx:v){
            bitset<8> b(stoi(xx));
            s1+=b.to_string();
        }
        bitset<32> b1(s1);
        cout<<b1.to_ulong()<<endl;
        bitset<32> b2(stoi(ip_int));
        cout<<int_to_ip(b2.to_string())<<endl;
    }
}

//????Щ???????С??ASCII?????С???????????
//???sort????
void picture_sort(){
    string s;
    while(cin>>s){
        sort(s.begin(),s.end());
        cout<<s<<endl;
    }
}

//???ξ???????1?????????????????г????????????????Ρ?
//?????
void print_row(set<int>& v,int n,int m){
    auto x=(*v.begin());
    for(int i=0;i<n;i++){
        cout<<x<<" ";
        v.erase(x);
        x+=(m++);
    }
    cout<<endl;
}
void snake_rectangle(){
    int n;
    while(cin>>n){
        int x=n,y=1;
        set<int> v;
        while(x){
            for(int i=1;i<=x;i++){
                v.insert(y++);
            }
            x--;
        }
        int z=n;
        for(int i=0;i<n;i++){
            print_row(v,z,n-z+2);
            z--;
        }
    }
}

void str_encryption(){
    string key,str;
    while(cin>>key>>str){
        set<char> s;
        string ss="";
        for(int i=0;i<key.size();i++){
            if(s.find(key[i])==s.end()){
                s.insert(key[i]);
                ss+=string(1,key[i]);
            }else{
                continue;
            }
        }
        //cout<<ss<<endl;
        for(char c='A';c<='Z';c++){
            if(s.find(c)==s.end()&&s.find(c+32)==s.end())
                ss+=c;
        }
        map<char,char> m;int i=0;
        for(char c='A';c<='Z';c++){
            if(ss[i]>='a'&&ss[i]<='z') {
                m[c+32] = ss[i];
                i++;
            }else{
            m[c]=ss[i++];
            m[c+32]=m[c]+32;}
        }
        string sss="";
        for(auto xx:str){
            sss+=m[xx];
        }
        cout<<sss<<endl;
    }
}

//?????????????临???????????????
void sum_of_fama(int n,vector<int> &v,vector<int> &v1,int &count,set<int>& sum){
    if(n<v.size()){
        for(int i=0;i<=v1[n];i++){
            auto x=count;
            count+=v[n]*i;
            sum_of_fama(n+1,v,v1,count,sum);
            count=x;
        }
    } else{
        sum.insert(count);
        }
}

void fama(){
    int n;
    while(cin>>n){
        int n1=n;
        vector<int> v;
        while(n1--){
            int x;
            cin>>x;
            v.push_back(x);
        }
        n1=n;
        vector<int> v1;
        while(n1--){
            int x;cin>>x;v1.push_back(x);
        }
        int count=0;
        set<int> sum;
        sum_of_fama(0,v,v1,count,sum);
        cout<<sum.size()<<endl;//??????,????????
    }
}

//??????滮????????????
void fama_1(){
    int n;
    while(cin>>n){
        int n1=n;
        vector<int> v;
        while(n1--){
            int x;
            cin>>x;
            v.push_back(x);
        }
        n1=n;
        vector<int> v1;int sum=0;
        while(n1--){
            int x;cin>>x;
            v1.push_back(x);
        }
        for(int i=0;i<n;i++)
            sum+=(v1[i]*v[i]);
        vector<int> dp(sum+1,0);
        dp[0]=1;
        for(int i=0;i<n;i++){
            for(int j=0;j<v1[i];j++){
                for(int k=sum;k>=v[i];k--){
                    if(dp[k-v[i]]==1)
                        dp[k]=1;
            }
        }
        }
        int Count=0;
        for(auto xx:dp){
            if(xx==1)
                Count+=1;
        }
        cout<<Count<<endl;
    }
}

//????????????????????????????????????????????????????????????
void str_judge(){
    string str;
    while(getline(cin,str)){
        int word=0,space=0,number=0,other=0;
        for(auto xx:str){
            if((xx>='A'&&xx<='Z')||(xx>='a'&&xx<='z')){
                word+=1;
            }else if(xx==' ')
                space+=1;
            else if(xx>='0'&&xx<='9')
                number+=1;
            else
                other+=1;
        }
        cout<<word<<endl;
        cout<<space<<endl;
        cout<<number<<endl;
        cout<<other<<endl;
    }
}

//???????????????????????д????????????????
static map<char,string> mm1{{'2',"twenty"},{'3',"thirty"},{'4',"forty"},{'5',"fifty"},{'6',"sixty"},{'7',"seventy"},{'8',"eighty"},{'9',"ninty"}};
static map<string,string> mm2{{"10","ten"},{"11","eleven"},{"12","twelve"},{"13","thirteen"},{"14","fourteen"},{"15","fifteen"},{"16","sixteen"},{"17","seventeen"},{"18","eighteen"},{"19","ninteen"}};
static map<char,string> mm3{{'1',"one"},{'2',"two"},{'3',"three"},{'4',"four"},{'5',"five"},{'6',"six"},{'7',"seven"},{'8',"eight"},{'9',"nine"},{'0',""}};
static bool flag=1;
void recursive_parse(string s){
    if(s.empty())
        return ;
    else{
        if(s.size()<=9&&s.size()>=7){
            int index=0;
            if(s.size()==7)
                index=1;
            else if(s.size()==8)
                index=2;
            else
                index=3;
            recursive_parse(s.substr(0,index));
            if(s[0]!='0')
            cout<<"million"<<" ";
            recursive_parse(s.substr(index));
        }else if(s.size()<=6&&s.size()>=4){
            int index=0;
            if(s.size()==4)
                index=1;
            else if(s.size()==5)
                index=2;
            else
                index=3;
            recursive_parse(s.substr(0,index));
            if(s[0]!='0')
            cout<<"thousand"<<" ";
            recursive_parse(s.substr(index));
        }else if(s.size()==3){
            recursive_parse(s.substr(0,1));
            if(s[0]!='0'){
                cout<<"hundred"<<" ";
            }else
                flag=false;
            recursive_parse(s.substr(1));
        }else if(s.size()==2){
            if(s[0]!='0'||s[1]!='0') {
                if(flag==true)
                cout << "and ";
            }
            if(s[0]>='2') {
                //cout<<s[1]<<endl;
                cout << mm1[s[0]] << " ";
                recursive_parse(s.substr(1, 1));
            }
            else if(s[0]=='1'){
                cout<<mm2[s]<<" ";
            }else{
                recursive_parse(s.substr(1, 1));
            }

        }else{
            cout<<mm3[s[0]]<<" ";
        }

    }
}

void parse(){
    long number;
    while(cin>>number){
        auto s=to_string(number);
        if(s.size()<=2)
            flag= false;
        if(s.size()<=9)
            recursive_parse(s);
        else
            cout<<"error";
        cout<<endl;
    }
}

void beautify_of_one(string name){
    vector<pair<char,int>> v;
    for(auto xx:name){
        auto it=find_if(v.begin(),v.end(),[=](pair<char,int> p){
            return p.first==xx||p.first==xx-32?true: false;
        });
        if(it==v.end()){
            if(xx<='Z'&&xx>='A')
                v.push_back(make_pair(xx+32,1));
            else
                v.push_back(make_pair(xx,1));
        }else{
            (*it).second+=1;
        }
    }
    sort(v.begin(),v.end(),[](pair<char,int> p1,pair<char,int> p2){
        return p1.second>p2.second?true: false;
    });
    int Count=0;
    for(int i=0;i<v.size();i++){
        Count+=((26-i)*v[i].second);
    }
    cout<<Count<<endl;
}

void beautity_of_name(){
    int n;
    cin>>n;
    string name;
    vector<string> v;
    while(n--){
        cin>>name;
        v.push_back(name);
    }
    for(auto xx:v){
        beautify_of_one(xx);
    }
}

//??????
void linear_insert(){
    int m, n;
    while (cin >> m >> n)
    {
        int M, N, A, B;
        cin >> M >> A;
        cout << M << " " << A << endl;
        for (int i = 1; i < m; ++i)
        {
            cin >> N >> B;
            if (N == M) continue;
            else
            {
                // ??????????M-N?????
                for (int j = 1; j < N - M; ++j)
                {
                    cout << M + j << " " << A + ((B - A) / (N - M))*j << endl;
                }
                cout << N << " " << B << endl;
                M = N;
                A = B;
            }
        }
    }
}

//????????????????
namespace huawei {
    struct ListNode {
        int m_nKey;
        ListNode *m_pNext;
    };
}

void list_insert_and_delete(){
    int n;
    while(cin>>n){
        int head_value;
        cin>>head_value;
        auto head=new huawei::ListNode;
        head->m_nKey=head_value;
        head->m_pNext= nullptr;
        int delete_value;
        vector<pair<int,int>> v;
        while(n--!=1){
            int node,next;
            cin>>next>>node;
            v.push_back(make_pair(next,node));
        }
        cin>>delete_value;
        auto it=find_if(v.begin(),v.end(),[=](pair<int,int> p1){
            return p1.second==head_value;
        });
        while(it!=v.end()) {
            if(!head->m_pNext){
            head->m_pNext = new huawei::ListNode;
            head->m_pNext->m_nKey = (*it).first;
            head->m_pNext->m_pNext= nullptr;
            }
            else{
                auto y=head->m_pNext;
                head->m_pNext = new huawei::ListNode;
                head->m_pNext->m_nKey = (*it).first;
                head->m_pNext->m_pNext=y;
            }
            it=find_if(it+1,v.end(),[=](pair<int,int> p1){
                return p1.second==head_value;
            });
        }
        for(auto xx:v){
            if(xx.second!=head_value){
                auto x=head;
                while(x){
                    if(x->m_nKey==xx.second){
                        if(!x->m_pNext){
                            x->m_pNext = new huawei::ListNode;
                            x->m_pNext->m_nKey = xx.first;
                            x->m_pNext->m_pNext= nullptr;
                        }
                        else{
                            auto y=x->m_pNext;
                            x->m_pNext = new huawei::ListNode;
                            x->m_pNext->m_nKey = xx.first;
                            x->m_pNext->m_pNext=y;
                        }
                    }
                    x=x->m_pNext;
                }
            }
        }
        if(head->m_nKey==delete_value){
            auto x=head;
            head=head->m_pNext;
            delete x;
        }else{
            auto z=head;
            while(z->m_pNext){
                if(z->m_pNext->m_nKey==delete_value){
                    auto x=z->m_pNext->m_pNext;
                    auto delete_node=z->m_pNext;
                    z->m_pNext=x;
                    delete delete_node;
                }
                z=z->m_pNext;
            }
        }
        auto p=head;
        while(p!= nullptr){
            cout<<p->m_nKey<<" ";
            p=p->m_pNext;
        }
    }
}

//???????????????k?????
using namespace huawei;
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k){
    auto p=pListHead;
    while(--k&&pListHead!= nullptr){
        pListHead=pListHead->m_pNext;
    }
    if(k>0)
        return nullptr;
    while(pListHead!= nullptr){
        pListHead=pListHead->m_pNext;
        p=p->m_pNext;
    }
    return p;
}

//????С??????
void min_common_multiple(){
    int m,n;
    while(cin>>m>>n){
        auto x=max(m,n);
        while(1){
            if(x%m==0&&x%n==0)
                break;
            else
                x++;
        }
        cout<<x<<endl;
    }
}

//?????????
void cube_root(){
    double num;
    while(cin>>num){
        double i=0;
        while(1){
            auto j=i+1;
            if(i*i*i<=num&&j*j*j>num){
                break;
            }
            i++;

        }
        double j=i;
        while(1){
            auto k=j+0.1;
            if(j*j*j<=num&&k*k*k>num){
                break;
            }
            j+=0.1;
        }
        double k=j;
        while(1){
            auto l=k+0.01;
            if(k*k*k<=num&&l*l*l>num){
                break;
            }
            k+=0.01;
        }
        double z=k-j-(j+0.1-k);
        if(z>=0||abs(z)<=0.000000001) {
            j = j + 0.1;
        }
        cout.setf(ios::fixed);
        cout<<setprecision(1);
        cout<<j<<endl;
    }
}

//???????2
void count_negative_equal_postive(){
    double x;
    vector<double> v;
    while(cin>>x){
        v.push_back(x);
    }
    auto n=count_if(v.begin(),v.end(),[](double a){
       return a<0;
    });
    double y=0.0;
    for(auto xx:v){
        if(xx>=0)
            y+=xx;
    }
    cout<<n<<endl;
    if(n==v.size())
        cout<<0.0<<endl;
    else{
        cout.setf(ios::fixed);
        cout<<setprecision(1);
        cout<<y/(v.size()-n)<<endl;}
}

void recursive_str_split(string s){
    if(s.size()<=8){
        int n=8-s.size();
        while(n--){
            s.push_back('0');
        }
        cout<<s<<endl;
    }else{
        cout<<s.substr(0,8)<<endl;
        recursive_str_split(s.substr(8));
    }
}

//???????????8????????????8????????油0
void str_split(){
    int n;
    while(cin>>n){
        string s;
        vector<string> v;
        while(n--){
            cin>>s;
            v.push_back(s);
        }
        for(auto ss:v)
            recursive_str_split(ss);
    }
}

//?????????????????????????????????????????????
void sortIntegerArray(){
    int n;
    while(cin>>n){
        vector<int> v;
        while(n--){
            int x;cin>>x;v.push_back(x);
        }
        int flag;
        cin>>flag;
        if(flag==0){
            sort(v.begin(),v.end());
        }else{
            sort(v.begin(),v.end(),[](int a,int b){
                return a>b;
            });
        }
        for(auto xx:v)
            cout<<xx<<" ";
        cout<<endl;
    }
}

//??????
void character_sort(){
    string str;
    while(cin>>str){
        vector<pair<char,int>> v;
        for(auto ss:str){
            auto it=find_if(v.begin(),v.end(),[=](pair<char,int> p){
                return p.first==ss;
            });
            if(it==v.end()){
                v.push_back(make_pair(ss,1));
            } else{
                (*it).second+=1;
            }
        }
        sort(v.begin(),v.end(),[](pair<char,int> p1,pair<char,int> p2){
            if(p1.second>p2.second)
                return true;
            else if(p1.second==p2.second)
                return p1.first<p2.first;
            else
                return false;
        });
        for(auto xx:v)
            cout<<xx.first;
        cout<<endl;
    }
}

//????????????
//?·?????DP
void LIS(){
    int n;
    while (cin>>n){
        vector<int> v;
        while(n--){
            int x;cin>>x;v.push_back(x);
        }
        vector<int> v1(v.size(),1);
        for(int i=1;i<v1.size();i++){
            for(int j=i-1;j>=0;j--){
                if(v[i]>v[j]){
                    v1[i]=max(v1[i],v1[j]+1);
                }
            }
        }
        int Max=0;
        for(auto xx:v1)
            Max=max(xx,Max);
        cout<<Max<<endl;
    }
}

//??????????
void sum_of_array(){
    int n;
    while(cin>>n){
        if(n&0x1){
            auto x=2+(n/2)*3;
            cout<<x*n<<endl;
        }else{
            auto x=2+(n/2-1)*3;
            cout<<x*(n-1)+2+(n-1)*3<<endl;
        }
    }
}

//??????
void CalcAutomorphicNumbers(){
    int n;
    while(cin>>n){
        int Count=1;
        for(int i=1;i<=n;i++){
            string s1=to_string(i);
            long x=i*i;
            string s2=to_string(x);
            if(s2.substr(s2.size()-s1.size())==s1) {
                Count += 1;
            }
        }
        cout<<Count<<endl;
    }
};

//???????
void neg_count_pos_equal(){
    int n;
    while(cin>>n){
        vector<int> v;
        while (n--){
            int x;cin>>x;v.push_back(x);
        }
        auto x=count_if(v.begin(),v.end(),[](int a){
            return a<0;
        });
        auto y=count_if(v.begin(),v.end(),[](int a){
            return a==0;
        });
        double sum=0;
        for(auto xx:v){
            if(xx>=0)
                sum+=xx;
        }
        int z=v.size();
        cout.setf(ios::fixed);
        cout<<setprecision(1);
        cout<<x<<" "<<sum/(v.size()-x-y)<<endl;
    }
}

void mark_number(){
    string s;
    while(cin>>s){
        auto it=find_if(s.begin(),s.end(),[](char a){
            return a>='0'&&a<='9';
        });
        while(it!=s.end()){
            s.insert(it,'*');
            auto it1=find_if_not(it+1,s.end(),[](char a){
                return a>='0'&&a<='9';
            });
            s.insert(it1,'*');
            it=find_if(it1,s.end(),[](char a){
                return a>='0'&&a<='9';
            });
        }
        cout<<s<<endl;
    }
}

static map<string,string> m1{{"1","?"},{"2","??"},{"3","??"},{"4","??"},{"5","??"},{"6","?"},{"7","??"},{"8","??"},{"9","??"},{"10","?"}};

void recursive_transfer(string s){
    if(s.size()>=9){
        recursive_transfer(s.substr(0,s.size()-8));
        cout<<"??";
        recursive_transfer(s.substr(s.size()-8));
    }else if(s.size()>=5&&s.size()<=8){
        auto index=s.find_first_not_of("0");
        recursive_transfer(s.substr(index,s.size()-4));
        cout<<"??";
        recursive_transfer(s.substr(s.size()-4));
    } else if(s.size()==4){
        auto index=s.find_first_not_of("0");
        if(index==0) {
            recursive_transfer(s.substr(0, 1));
            cout<<"?";
            recursive_transfer(s.substr(1));
        }else {
            recursive_transfer(s.substr(index));
        }
    }else if(s.size()==3){
        auto index=s.find_first_not_of("0");
        if(index==0) {
            recursive_transfer(s.substr(0, 1));
            cout<<"??";
            recursive_transfer(s.substr(1));
        }else {
            recursive_transfer(s.substr(index));
        }
    }else if(s.size()==2){
        auto index=s.find_first_not_of("0");
        if(index==0&&s[0]!='1') {
            recursive_transfer(s.substr(0, 1));
            cout<<"?";
            recursive_transfer(s.substr(1));
        }else if(s[0]=='1'){
            cout<<"?";
            recursive_transfer(s.substr(1));
        }else if(index!=string::npos){
            recursive_transfer(s.substr(index));
        }
        else{
            ;
        }
    }else{
        cout<<m1[s];
    }
}

//????????
void rmb_transfer(){
    double x;
    while(cin>>x){
        string s=to_string(x);
        auto index=s.find('.');
        cout<<"?????";
        auto s1=s.substr(0,index);
        recursive_transfer(s1);
        if(s1.size()==1&&s1[0]=='0')
            ;
        else{
        cout<<"?";}
        if(index!=string::npos){
        auto ss=s.substr(index+1,2);
        if(ss[0]!='0'){
            cout<<m1[string(1,ss[0])]<<"??";
        }
        if(ss[1]!='0'){
            cout<<m1[string(1,ss[1])]<<"??";
        }
        if(ss[0]=='0'&&ss[1]=='0')
            cout<<"??";
        }else{
            cout<<"??";
        }
        cout<<endl;
    }
}

void caulate_grade(){
    int n;
    cin>>n;
    vector<int> grades;
    while(n--){
        int grade;
        cin>>grade;grades.push_back(grade);
    }
    int q;cin>>q;vector<int> query;
    while(q--){
        int id;cin>>id;
        query.push_back(id);
    }
    for(int xx:query){
        double x=count_if(grades.begin(),grades.end(),[=](int a){
            return a<grades[xx-1];
        });
        cout.setf(ios::fixed);
        cout<<setprecision(6);
        cout<<x/grades.size()*100<<endl;
    }
}

void great_sequence(){
    int n;
   cin>>n;
   vector<pair<string,string>> v;
   while(n--){
    string s1,s2;
    cin>>s1>>s2;
    v.push_back(make_pair(s1,s2));
   }
   for(auto x:v){
       auto index=x.second.find(x.first);
       if(index!=string::npos){
           auto ss=x.second.substr(index+x.first.size());
           if(x.first.find(ss)!=string::npos)
               cout<<"YES"<<endl;
           else{
               for(auto& cc:ss){
                   if(cc=='1')
                       cc='0';
                   else
                       cc='1';
               }
               auto index1=ss.find_first_not_of("0");
               auto sss=ss.substr(index1);
               if(sss==x.first)
                   cout<<"YES"<<endl;
               else
                   cout<<"NO"<<endl;
           }
       }else{
           for(auto& cc:x.second){
               if(cc=='1')
                   cc='0';
               else
                   cc='1';
           }
           auto index1=x.second.find_first_not_of("0");
           auto sss=x.second.substr(index1);
           if(sss==x.first)
               cout<<"YES"<<endl;
           else
               cout<<"NO"<<endl;
       }
   }
}

bool judge(vector<int>& v){
    bool flag=true;
    if(v.size()<3)
        return true;
    for(int i=1;i<v.size()-1;i++){
        if(v[i]>v[i-1]+v[i+1]){
            flag= false;
            break;
        }
    }
    if(v[0]>v[v.size()-1]+v[1])
        flag= false;
    if(v[v.size()-1]>v[v.size()-2]+v[0])
        flag= false;
    return flag;
}

void number_circle(){
    int n;
    cin>>n;
    vector<vector<int>> v;
    while(n--){
        int n1;cin>>n1;
        vector<int> v1;
        while(n1--){
            int x;cin>>x;v1.push_back(x);
        }
        v.push_back(v1);
    }
    for(auto case1:v){
        sort(case1.begin(),case1.end());
        if(judge(case1))
            cout<<"YES"<<endl;
        else{
            bool flag=false;
            while(next_permutation(case1.begin(),case1.end())){
                if(judge(case1)) {
                 flag=true;break;
                }
            }
            if(flag)
                cout<<"YES"<<endl;
            else
                cout<<"NO"<<endl;
        }
    }
}

void sequence_exchange(){
    int n;cin>>n;vector<int> v;
    while(n--){
        int x;
        v.push_back(x);
    }
    sort(v.begin(),v.end());
    for(auto xx:v)
        cout<<xx<<" ";
}

struct window{
    int x;
    int y;
    int w;
    int h;
};

void simulate_click(){
    int n,m;
    cin>>n>>m;
    vector<pair<int,window>> v;
    int j=1;
    while(n--){
        int x,y,w,h;
        window win;
        cin>>x>>y>>w>>h;
        win.x=x;win.y=y;win.w=w;win.h=h;
        v.push_back(make_pair(j++,win));
    }
    vector<pair<int,int>> clicks;
    while(m--){
        int x,y;
        cin>>x>>y;
        clicks.push_back(make_pair(x,y));
    }
    for(auto p:clicks){
        bool flag=false;
        for(int i=v.size()-1;i>=0;i--){
            if((p.first>=v[i].second.x&&p.first<=v[i].second.x+v[i].second.w)&&(p.second>=v[i].second.y&&p.second<=v[i].second.y+v[i].second.h)){
                cout<<v[i].first<<endl;flag=true;
                auto z=v[i];v.erase(v.begin()+i);v.push_back(z);break;
            }
        }
        if(flag==false)
            cout<<-1<<endl;
    }
}

void select(vector<int> &v1,vector<int> &v2) {
    if(v2.empty()){
        return ;
    }else {
        if (v1.empty()) {
            if (abs(v2[0] - 0) > abs(v2[v2.size() - 1] - 0)) {
                v1.push_back(v2[0]);
                v2.erase(v2.begin());
            } else {
                v1.push_back(v2[v2.size() - 1]);
                v2.pop_back();
            }
        } else {
            if (abs(v1[v1.size() - 1] - v2[0]) > abs(v1[v1.size() - 1] - v2[v2.size() - 1])) {
                v1.push_back(v2[0]);
                v2.erase(v2.begin());
            } else {
                v1.push_back(v2[v2.size() - 1]);
                v2.pop_back();
            }
        }
    }
}
//
void double_number_game(){
    int n;
    cin>>n;
    vector<int> v;
    while(n--){
    int x;cin>>x;
    v.push_back(x);
    }
    vector<int> v1;vector<int> v2;
    while(!v.empty()){
        select(v1,v);
        select(v2,v);
    }
    int sum1=abs(v1[0]-0);
    for(int i=1;i<v1.size();i++){
        sum1+=abs(v1[i]-v1[i-1]);
    }
    int sum2=abs(v2[0]-0);
    for(int i=1;i<v2.size();i++){
        sum2+=abs(v2[i]-v2[i-1]);
    }
    cout<<sum1<<" "<<sum2<<endl;
}

void variance(){
    int n;
    cin>>n;
    vector<double> v;
    while(n--){
        double x;
        cin>>x;
        v.push_back(x);
    }
    sort(v.begin(),v.end());
    double variance=1000000000;
    for(int i=1;i<(int)v.size()-1;i++){
        double average=(v[i]+v[i-1]+v[i+1])/3;
        double x=(v[i-1]-average)*(v[i-1]-average)+(v[i]-average)*(v[i]-average)+(v[i+1]-average)*(v[i+1]-average);
        double y=x/3;
        variance=min(y,variance);
    }
    cout.setf(ios::fixed);
    cout<<setprecision(2);
    cout<<variance<<endl;
}

int main(){
    variance();
    return 0;
}