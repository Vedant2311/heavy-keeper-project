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
unsigned int maxVal;

using namespace std;

class doubleSS
{

	private:
		spacesaving *T1;
		spacesaving *T2;
		BOBHash32 *bobhash;
		int M2,K;
		double delta;

	public:

		doubleSS(int M2, int K, double delta): M2(M2), delta(delta), K(K) {

			maxVal = (floor((2.0 * M2 * M2 / delta)));			
			T1= new spacesaving((M2/30) * K); T2= new spacesaving(M2); bobhash=new BOBHash32(1003);

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

		struct Node {string x; int y;} q1[MAX_MEM+10];
		Node q[MAX_MEM+10];
        static int cmp(Node i,Node j) {return i.y>j.y;}
        
        int isTopK(Node* q1, string str){

        	for(int i=0; i<K; i++){
        		if (q1[i].x==str) return i;
        	}

        	return -1;

        }

		int work()
		{
            int CNT1=0;
            for(int i=N;i;i=T2->ss->Left[i])
                for(int j=T2->ss->head[i];j;j=T2->ss->Next[j]) {q1[CNT1].x=T2->ss->str[j]; q1[CNT1].y=T2->ss->sum[j]; CNT1++; }

            sort(q1,q1+CNT1,cmp);

        	for(int i=0; i<K;i++)	cout <<"Top " << i << " is " << q1[i].y << endl;

            int CNT=0;
            for(int i=N;i;i=T1->ss->Left[i])
                for(int j=T1->ss->head[i];j;j=T1->ss->Next[j]){

                	unsigned int v = Hash(T1->ss->str[j]);
					unsigned int final = floor(maxVal * ((A*v) - (floor(A*v))));

					int ind = isTopK(q1,to_string(final));

					if (ind==-1) continue;

					q[CNT].x=T1->ss->str[j]; 
					q[CNT].y=q1[ind].y; 
					CNT++; 					

                }

            sort(q,q+CNT,cmp);
            return CNT;

		}

	pair<string ,int> Query(int k)
        {
            return make_pair(q[k].x,q[k].y);
        }

};
