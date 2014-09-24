#include "n_dimensional.h"
#include <iostream>

int main(){
    NDimensionalSLL<int, 3> test;

    // test.fill_short_from(4, true, test.get(0, 0, 0), 4, 4, 4);
    Node<int, 3>* secondStart = test.fill_short_from(4, true, test.get(0, 0, 0), 4, 4, 4);
    test.fill_short_from(4, true, secondStart, 4, 4, 4);

    try{
        std::cout << test.get(4,4,0)->value << std::endl;
    }catch (const char* exception){
        std::cerr << exception << std::endl;
    }


    int coords[3] = {0};
    bool done = false;
    try{
        while (!done){
            std::cout << "Point [" << coords[0] << ", " << coords[1] << ", " << coords[2] << "](" << test.get(coords[0], coords[1], coords[2])->value << ")";
            for (int i = 0; i < 3; ++i){
                if (test.get(coords[0], coords[1], coords[2])->next(i)){
                    ++coords[i];
                    std::cout << " => [" << coords[0] << ", " << coords[1] << ", " << coords[2] << "](" << test.get(coords[0], coords[1], coords[2])->value << ")" << std::endl;
                    break;
                }else if (i == 2){
                    done = true;
                    std::cout << " => NULL" << std::endl;
                    break;
                }
            }
        }
    }catch (const char* exception){
        std::cerr << exception << std::endl;
    }

    
    getchar();
    return 0;
}
