/*
 * http://cache.baiducontent.com/c?m=9f65cb4a8c8507ed4fece763105392230e54f73c6f888b442282c45f93130a1c187bb8e7737f0704a5932b2152f4174bea8631703d0524b68cc8ff109be4cc3c6ad567627f5f9141638d4efc8b1a7e9d75&p=98769a47829b13ff57ee9e744b05c1&newp=8b2a975dc5af11a05be79e644a5480231610db2151d7d01267c7ff&user=baidu&fm=sc&query=q+learning&qid=e9666d7100235ecf&p1=1
 *
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;

float R[6][6] = {
	{ -1, -1, -1, -1, 0, -1 },
	{ -1, -1, -1, 0, -1, 100},
	{ -1, -1, -1, 0, -1, -1},
	{ -1, 0, 0, -1, 0, -1},
	{ 0, -1, -1, 0, -1, 100},
	{ -1, 0, -1, -1, 0, 100}
};

float Q[6][6] = { 0 };
float gamma = 0.8;

void calculate_Q(bool print) {
	srand(time(NULL));
	for (int i = 0; i < 1000; ++i) {
		int state = rand() % 6;
		while (state != 5) {
			int next_state[6] = {0}, number_of_next_state = 0;
			for (int j = 0; j < 6; ++j) {
				if (R[state][j] == -1)
					continue;
				// next action
				next_state[number_of_next_state++] = j;
			}
			
			if (number_of_next_state == 0)
				break;
				
			int next = next_state[rand() % number_of_next_state];
			
			float value = 0;
			for (int k = 0; k < 6; ++k) {
				if (R[next][k] == -1)
					continue;
				value = max(value, Q[next][k]);
			}
			value *= gamma;
			Q[state][next] = R[state][next] + value;
			state = next;
		}
		
		if (print) {
			cout << "after " << i << " episode, the Q matrx is " << endl;
			for (int j = 0; j < 6; ++j) {
				for (int k = 0; k < 6; ++k) {
					cout << Q[j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
}

int main() {
	calculate_Q(true);
	
	// begin test
	for (int i = 0; i < 5; ++i) {
		cout << "begin at state " << i << endl;
		int state = i;
		while (state != 5) {
			float value = 0;
			int next = state;
			for (int j = 0; j < 6; ++j) {
				if (value <= Q[state][j]) {
					next = j;
					value = Q[state][j];
				}
			}
			if (next == state) {
				cout << "can't found path to state" << endl;
				break;
			}
			cout << next << " ";
			state = next;
		}
		cout << "\nend found state" << endl;
	}
	return 0;
}
