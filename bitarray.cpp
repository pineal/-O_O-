#include <iostream>
using namespace std;

class Bitarray {
	private:
		long v_;
	public:
		Bitarray() {
			v_ = 0;
		}
		void setone(int pos) {
			v_ |= (1 << pos);	
		}
		void setzero(int pos) {
			v_ |= (0 << pos);	
		}
		bool showbit(int pos) {
			if (pos >= sizeof(v_)) {
				cout<<"less than 64"<<endl;
			}
			return (v_ & (1 << pos)) != 0;
		} 
};


int main(int argc, char** argv) {
	Bitarray ab;	
	ab.setone(2);
	ab.showbit(2);

}
