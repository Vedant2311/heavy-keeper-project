#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <fstream>
#include "BOBHASH64.h"
#include "params.h"
#include "ssummary.h"
#include "heavykeeper.h"
#include "spacesaving.h"
#include "LossyCounting.h"
#include "doubleSS.h"
#include "CSS.h"
using namespace std;
map <string ,int> B,C;
struct node {string x;int y;} p[10000005];
ifstream fin("Data/data10.csv",ios::in|ios::binary);
ifstream fin_movie("MovieTweetings-master/latest/ratings.dat",ios::in|ios::binary);
char a[105];

// Input reading function for the network packets
string Read()
{
	string aa;
	std::getline (fin,aa);
	int l,last,count;
	l = aa.length();
	last = 0;
	count = 0;
	for(int i=0; i<l; i++){

		if (aa.at(i) == ','){
			count ++;
			if(count == 1) aa.at(i) = ' ';

			if (count == 2){
				last=i;
				break;
			}
		}

	}

    string tmp=aa.substr(0,last);

    if (tmp.find(':') == std::string::npos)
  		return tmp;

    return "-1";

}

void tokenize(std::string const &str, const char* delim,
			std::vector<std::string> &out)
{
	char *token = strtok(const_cast<char*>(str.c_str()), delim);
	while (token != nullptr)
	{
		out.push_back(std::string(token));
		token = strtok(nullptr, delim);
	}
}

// Input reading function for the movie ratings. Note that the ratings would actually go from 0-10, rather than a 0-1 score for the network packets
string Read_movie()
{
	string aa;
	std::getline (fin_movie,aa);
	int l,last,count;
	l = aa.length();

	const char* delim = "::";
	std::vector<std::string> out;
	tokenize(aa, delim, out);

	string temp;
	string uid = out[0];
	return uid; 
}


int cmp(node i,node j) {return i.y>j.y;}
int main()
{
	cout << "Enter the Memory Size and K and data" << endl;

/*
	Data will be:
		0 -> Network
		1 -> Movies
*/ 
    int MEM,K,datatype;
    cin >> MEM >> K >> datatype;

    int m =0;
    if (datatype==0)
		m=7000000; 
	else
	    m=800000; 
    float delta = 0.2;

    cout<<"preparing all algorithms"<<endl;

 //    // preparing heavykeeper
 //    int hk_M;
 //    for (hk_M=1; 32*hk_M*HK_d+432*(10)<=MEM*1024*8; hk_M++); if (hk_M%2==0) hk_M--;
 //    heavykeeper *hk; hk=new heavykeeper(hk_M); hk->clear();

 //    // preparing spacesaving
 //    int ss_M;
 //    for (ss_M=1; 432*ss_M<=MEM*1024*8; ss_M++);
 //    spacesaving *ss; ss=new spacesaving(ss_M);


 //    // preparing LossyCounting
 //    int LC_M;
 //    for (LC_M=1; 227*LC_M<=MEM*1024*8; LC_M++);
 //    LossyCounting *LC; LC=new LossyCounting();

 //    // preparing CSS
 //    int css_M;
 //    for (css_M=1; 179*css_M+4*css_M*log(css_M)/log(2)<=MEM*1024*8; css_M++);
 //    CSS *css; css=new CSS(css_M); css->clear();

	// // preparing double spacesaving
	// int d_ss_M;
 //    for (d_ss_M=1; 216*d_ss_M<=MEM*1024*8; d_ss_M++);
 //    doubleSS *d_ss; d_ss=new doubleSS(d_ss_M,epsilon,phi,delta, m);


 //    // preparing heavykeeper
 //    int hk_M;
 //    for (hk_M=1; 32*hk_M*HK_d+451*(floor(1/phi))<=MEM*1024*8; hk_M++); if (hk_M%2==0) hk_M--;
 //    heavykeeper *hk; hk=new heavykeeper(hk_M,(floor(1/phi))); hk->clear();


 //    // preparing spacesaving
 //    int ss_M;
 //    for (ss_M=1; 451*ss_M<=MEM*1024*8; ss_M++);
 //    spacesaving *ss; ss=new spacesaving(ss_M);


 //    // preparing LossyCounting
 //    int LC_M;
 //    for (LC_M=1; 246*LC_M<=MEM*1024*8; LC_M++);
 //    LossyCounting *LC; LC=new LossyCounting();

 //    // preparing CSS
 //    int css_M;
 //    for (css_M=1; 198*css_M+4*css_M*log(css_M)/log(2)<=MEM*1024*8; css_M++);
 //    CSS *css; css=new CSS(css_M); css->clear();

	// // preparing double spacesaving
	// int d_ss_M;
 //    for (d_ss_M=1; (419 + floor(log2(floor(2 * (d_ss_M) * (d_ss_M) / delta))/8.0))*d_ss_M + 451*(floor(2/phi))<=MEM*1024*8; d_ss_M++);
 //    doubleSS *d_ss; d_ss=new doubleSS(d_ss_M,epsilon,phi,delta, m);


	// preparing Heavy keeper
    int hk_M;
    for (hk_M=1; 32*hk_M*HK_d+584*(K)<=MEM*1024*8; hk_M++); if (hk_M%2==0) hk_M--;
    heavykeeper *hk; hk=new heavykeeper(hk_M,K); hk->clear();


    // preparing spacesaving
    int ss_M;
    for (ss_M=1; 584*ss_M<=MEM*1024*8; ss_M++);
    spacesaving *ss; ss=new spacesaving(ss_M);


    // preparing LossyCounting
    int LC_M;
    for (LC_M=1; 379*LC_M<=MEM*1024*8; LC_M++);
    LossyCounting *LC; LC=new LossyCounting();

    // preparing CSS
    int css_M;
    for (css_M=1; 331*css_M+4*css_M*log(css_M)/log(2)<=MEM*1024*8; css_M++);
    CSS *css; css=new CSS(css_M,K); css->clear();

	// preparing double spacesaving
	int d_ss_M;
    for (d_ss_M=1; (328 + floor(log2(floor(2 * (d_ss_M) * (d_ss_M) / delta))))*d_ss_M + 584*((d_ss_M/30) * K)<=MEM*1024*8; d_ss_M++);
    doubleSS *d_ss; d_ss=new doubleSS(d_ss_M,K,delta);


    // Inserting
    for (int i=1; i<=m; i++)
	{
		string s;
		if (datatype==0)
			s=Read();
		else
			s = Read_movie();

		if (s=="-1"){
			continue;
		}

		B[s]++;
		hk->Insert(s);
		ss->Insert(s);
		LC->Insert(s,i/LC_M); if (i%LC_M==0) LC->clear(i/LC_M);
		css->Insert(s);
		d_ss -> Insert(s);
	}

	int hkV =	hk->work();
	int ssV =	ss->work();
	int LCV =	LC->work();
	int cssV =	css->work();
	int dssV =	d_ss -> work();


	cout << endl;
    cout<<"preparing true flow"<<endl;
	// preparing true flow
	int cnt=0;
    for (map <string,int>::iterator sit=B.begin(); sit!=B.end(); sit++)
    {
        p[++cnt].x=sit->first;
        p[cnt].y=sit->second;
    }
    sort(p+1,p+cnt+1,cmp);

    for (int i=1; i<=K; i++) {

        C[p[i].x]=p[i].y;
        cout << "True String " << p[i].x << " " << p[i].y <<  endl;
    }

    cout << endl;
    // Calculating PRE, ARE, AAE
    cout<<"Calculating"<<endl;
    int hk_sum=0,hk_AAE=0; double hk_ARE=0;
    string hk_string; int hk_num;
    for (int i=0; i<K; i++)
    {
        hk_string=(hk->Query(i)).first; hk_num=(hk->Query(i)).second;

		cout << "HK string " << hk_string <<  " " << hk_num <<  endl;        
        hk_AAE+=abs(B[hk_string]-hk_num); hk_ARE+=abs(B[hk_string]-hk_num)/(B[hk_string]+0.0);
        if (C[hk_string]) hk_sum++;
    }
    cout << endl;

    int LC_sum=0,LC_AAE=0; double LC_ARE=0;
    string LC_string; int LC_num;
    for (int i=0; i<K; i++)
    {
        LC_string=(LC->Query(i)).first; LC_num=(LC->Query(i)).second;

		cout << "LC string " << LC_string << " " << LC_num << endl;        
        LC_AAE+=abs(B[LC_string]-LC_num); LC_ARE+=abs(B[LC_string]-LC_num)/(B[LC_string]+0.0);
        if (C[LC_string]) LC_sum++;
    }
    cout << endl;

    int ss_sum=0,ss_AAE=0; double ss_ARE=0;
    string ss_string; int ss_num;
    for (int i=0; i<K; i++)
    {
        ss_string=(ss->Query(i)).first; ss_num=(ss->Query(i)).second;

		cout << "SS string " << ss_string << " " << ss_num << endl;        
        ss_AAE+=abs(B[ss_string]-ss_num); ss_ARE+=abs(B[ss_string]-ss_num)/(B[ss_string]+0.0);
        if (C[ss_string]) ss_sum++;
    }
    cout << endl;


    int css_sum=0,css_AAE=0; double css_ARE=0;
    string css_string; int css_num;
    for (int i=0; i<K; i++)
    {
        css_string=(css->Query(i)).first; css_num=(css->Query(i)).second;

		cout << "CSS string " << css_string << " " << css_num << endl;        
        css_AAE+=abs(B[css_string]-css_num); css_ARE+=abs(B[css_string]-css_num)/(B[css_string]+0.0);
        if (C[css_string]) css_sum++;
    }
    cout << endl;

    int d_ss_sum=0,d_ss_AAE=0; double d_ss_ARE=0;
    string d_ss_string; int d_ss_num;
    for (int i=0; i<K; i++)
    {
        d_ss_string=(d_ss->Query(i)).first; d_ss_num=(d_ss->Query(i)).second;
        
		cout << "Double SS string " << d_ss_string << " " << d_ss_num << endl;        
        d_ss_AAE+=abs(B[d_ss_string]-d_ss_num); d_ss_ARE+=abs(B[d_ss_string]-d_ss_num)/(B[d_ss_string]+0.0);
        if (C[d_ss_string]) d_ss_sum++;
    }
    cout << endl;


    printf("heavkeeper:\nAccepted: %d  \nARE: %.10f\nAAE: %.10f\n\n",hk_sum,hk_ARE/(K+0.0),hk_AAE/(K+0.00));
    printf("LossyCounting:\nAccepted: %d  \nARE: %.10f\nAAE: %.10f\n\n",LC_sum,LC_ARE/(K+0.0),LC_AAE/(K+0.00));
    printf("spacesaving:\nAccepted: %d  \nARE: %.10f\nAAE: %.10f\n\n",ss_sum,ss_ARE/(K+0.0),ss_AAE/(K+0.00));
    printf("CSS:\nAccepted: %d  \nARE: %.10f\nAAE: %.10f\n\n",css_sum,css_ARE/(K+0.0),css_AAE/(K+0.00));
    printf("doubleSS:\nAccepted: %d  \nARE: %.10f\nAAE: %.10f\n\n",d_ss_sum,d_ss_ARE/(K+0.0),d_ss_AAE/(K+0.00));    

    return 0;
}

