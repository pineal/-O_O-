#include <iostream>
using namespace std;

class Singleton {
	private:
		Singleton() { }
		static Singleton* my_instace;
	public:
		static Singleton *GetInstance() {
			return my_instace; 
		}

}
