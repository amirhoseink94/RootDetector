#include <string>
class Counter
{
	private:
		int n;
		int* counter;
	public:
		Counter(int,int);
		std::string plus();
		std::string now(); 
};
