
#include <vector>
#include <print>


void test(std::vector<int>& vec1){
    int size = vec1.size();

    //should print 5
    std::println("{}", vec1[size-1]);
}

int main(){
    std::vector<int> vec;

    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    test(vec);

}
