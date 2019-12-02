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
		int t;
		double phi, epsilon, delta;

	public:

		doubleSS(int t, double phi, double epsilon, double delta): t(t), phi(phi), epsilon(epsilon), delta(delta) {T1= new spacesaving((int)floor(2.0/phi),M); T2= new spacesaving(t,M); bobhash=new BOBHash64(1005);}

		unsigned long long Hash(string ST)
        {
            return (bobhash->run(ST.c_str(),ST.size()));
        }

		void Insert(string x)
		{

			T1 ->Insert(x);
			T2 ->Insert(to_string(Hash(x)));
		}

		struct Node {string x; int y;} q[MAX_MEM+10];
        static int cmp(Node i,Node j) {return i.y>j.y;}
        
		void Report()
		{

			int CNT=0;
            for(int i=N;i;i=T1->ss->Left[i]){
                for(int j=T1->ss->head[i];j;j=T1->ss->Next[j]) {
                	if((T1->ss->sum[j] >= (floor(phi*M/2.0)))){

                		if(T2->ss->sum[j] >= (floor((phi - epsilon)*M))){
                			q[CNT].x=T1->ss->str[j]; q[CNT].y=T2->ss->sum[j]; CNT++;
                		}

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
