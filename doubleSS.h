#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "BOBHASH32.h"
#include "params.h"
#include "ssummary.h"
#include "BOBHASH64.h"
#include "spacesaving.h"

using namespace std;

class doubleSS
{

	private:
		spacesaving *T1;
		spacesaving *T2;
		BOBHash64 *bobhash;
		int M2,m;
		double phi, epsilon, delta;

	public:

		doubleSS(int M2, double epsilon, double phi, double delta, int m): M2(M2), phi(phi), epsilon(epsilon), delta(delta), m(m) {

			cout << "The size of T1 is" << floor(2.0/phi) << endl;
			cout << "The size of T2 is" << M2 << endl;

			T1= new spacesaving((int)floor(2.0/phi),epsilon,phi,m); T2= new spacesaving(M2,epsilon,phi,m); bobhash=new BOBHash64(floor(2 * M2 * M2 / delta));}

		unsigned long long Hash(string ST)
        {
            return (bobhash->run(ST.c_str(),ST.size()));
        }

		void Insert(string x)
		{

			T1 ->Insert(x);
//			cout << "Original String is " << x << endl;
//			cout << "Hashed value is " << Hash(x) << endl;
//			cout << "Hashed String is " << to_string(Hash(x)) << endl;

//			cout << endl;
			T2 ->Insert(to_string(Hash(x)));
		}

		struct Node {string x; int y;} q[MAX_MEM+10];
        static int cmp(Node i,Node j) {return i.y>j.y;}
        
		void work()
		{
			int CNT=0;
            for(int i=N;i;i=T1->ss->Left[i]){
                for(int j=T1->ss->head[i];j;j=T1->ss->Next[j]) {


                	if((T1->ss->sum[j] >= (floor(phi*m/2.0)))){
//                		cout << "Pass" << endl;
			//			cout << "Combo " << j << " " << T2->ss->sum[j] << endl;              
				//		cout << "Comparision value " << (floor((phi - epsilon)*m)) << endl;

                		if (T1->ss->str[j] == "221.112.135.201 100.70.27.133")
                		{
	                		// cout << "The string is " << "221.112.135.201 100.70.27.133 " << "; " << T1->ss->sum[j] << endl;
	                		// cout << "The Hashed string is " << to_string(Hash("221.112.135.201 100.70.27.133")) << endl;
	                		// cout << "T2 string is " << T2->ss->str[j] << endl;
	                		// cout << "T2 string value is" << T2 -> ss->sum[j] << endl;

                		}

                		int flag = 0;
                		for(int i1=N; i1; i1 = T2 -> ss -> Left[i1]){

                			if(flag==1) break;

                			for(int j1 = T2 -> ss -> head[i1]; j1; j1 = T2 -> ss -> Next[j1]){
                				if (T2 -> ss -> str[j1] == to_string(Hash(T1->ss->str[j]))){
                					flag=1;
		                			q[CNT].x=T1->ss->str[j]; q[CNT].y=T2->ss->sum[j1]; CNT++;
		                			break;
                				}
                			}

                		}

                	/*	
                		if(T2->ss->sum[j] >= (floor((phi - epsilon)*m))){
                			q[CNT].x=T1->ss->str[j]; q[CNT].y=T2->ss->sum[j]; CNT++;
                		}
					*/
                	}
                }
            }
            sort(q,q+CNT,cmp);

		}

		pair<string ,int> Query(int k)
        {
            return make_pair(q[k].x,q[k].y);
        }

};
