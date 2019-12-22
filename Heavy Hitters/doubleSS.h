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
#include "BOBHASH32.h"
#include "spacesaving.h"

double A = 0.61803398875;
int maxVal;

using namespace std;

class doubleSS
{

	private:
		spacesaving *T1;
		spacesaving *T2;
		BOBHash32 *bobhash;
		int M2,m;
		double phi, epsilon, delta;

	public:

		doubleSS(int M2, double epsilon, double phi, double delta, int m): M2(M2), phi(phi), epsilon(epsilon), delta(delta), m(m) {

			cout << "The size of T1 is" << floor(2.00000/phi) << endl;
			cout << "The size of T2 is" << M2 << endl;

			maxVal = (floor((2.0 * M2 * M2 / delta)));			
			T1= new spacesaving((int)floor(2.0/phi)); T2= new spacesaving(M2); bobhash=new BOBHash32(1003);

		}

		unsigned int Hash(string ST)
        {
            return (bobhash->run(ST.c_str(),ST.size()));
        }

		void Insert(string x)
		{

			T1 ->Insert(x);

			unsigned int out = Hash(x);
			unsigned int final = floor(maxVal * ((A*out) - (floor(A*out))));

			T2 ->Insert(to_string(final));
		}

		struct Node {string x; int y;} q[MAX_MEM+10];
        static int cmp(Node i,Node j) {return i.y>j.y;}
        
		int work()
		{
			int CNT=0;
            for(int i=N;i;i=T1->ss->Left[i]){
                for(int j=T1->ss->head[i];j;j=T1->ss->Next[j]) {

       				int v = Hash(T1->ss->str[j]);
					int final = floor(maxVal * ((A*v) - (floor(A*v))));

                	if((T1->ss->sum[j] >= (floor(phi*m/2.0)))){

                		cout << "T1 string is " << T1->ss->sum[j] << endl;

                		int flag = 0;
                		for(int i1=N; i1; i1 = T2 -> ss -> Left[i1]){

                			if(flag==1) break;

                			for(int j1 = T2 -> ss -> head[i1]; j1; j1 = T2 -> ss -> Next[j1]){

                				if (T2 -> ss -> str[j1] == to_string(final)){
                					flag=1;

			                		if(T2->ss->sum[j1] >= (floor((phi - epsilon)*m))){
			                			q[CNT].x=T1->ss->str[j]; q[CNT].y=T2->ss->sum[j1]; CNT++;
			                		}
		                			break;


                				}
                			}

                		}

                	}
                }
            }
            sort(q,q+CNT,cmp);
            return CNT;

	}

	pair<string ,int> Query(int k)
        {
            return make_pair(q[k].x,q[k].y);
        }

};
