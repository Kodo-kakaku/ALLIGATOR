#include "alligator.h"
#include "keeper.h"

#include <map>
#include <iostream>


int factorial(const int x) {
    return x == 0 ? 1 : x * factorial(x - 1);
}


int main()
{
    const auto buff_size = 10;
	
   /*  ñîçäàíèå ýêçåìïëÿðà std::map<int, int>
    *  ñîçäàíèå ýêçåìïëÿðà std::map<int, int> ñ íîâûì àëëîêàòîðîì, îãðàíè÷åííûì 10 ýëåìåíòàìè
   */
	
    std::map<int, int> classic_map;
    auto alligator_map = std::map<int, int, std::less<>, custom_alligator<std::pair<const int, int>>> {};


	/*  çàïîëíåíèå 10 ýëåìåíòàìè, ãäå êëþ÷ - ýòî ÷èñëî îò 0 äî 9, à çíà÷åíèå - ôàêòîðèàë êëþ÷à  */
	
    for (size_t i = 0; i < buff_size; ++i) {
        auto fac_value = factorial(i);
        classic_map.emplace(std::make_pair (i, fac_value));
        alligator_map.emplace(std::make_pair(i, fac_value));
    }

    /* âûâîä íà ýêðàí âñåõ çíà÷åíèé (êëþ÷ è çíà÷åíèå ðàçäåëåíû ïðîáåëîì) õðàíÿùèõñÿ â êîíòåéíåðå */
	
	for(const auto& print : classic_map) {
		std::cout << print.first << " " << print.second << std::endl;
	}

    for (const auto& print : alligator_map) {
        std::cout << print.first << " " << print.second << std::endl;
    }

   /*  ñîçäàíèå ýêçåìïëÿðà ñâîåãî êîíòåéíåðà äëÿ õðàíåíèÿ çíà÷åíèé òèïà int
    *  ñîçäàíèå ýêçåìïëÿðà ñâîåãî êîíòåéíåðà äëÿ õðàíåíèÿ çíà÷åíèé òèïà int ñ íîâûì àëëîêàòîðîì, îãðàíè÷åííûì 10 ýëåìåíòàìè
    */
	
    keeper<int> classic_fifo;
    keeper<int, custom_alligator<int>> custom_fifo;

    /*  çàïîëíåíèå 10 ýëåìåíòàìè îò 0 äî 9  */
	
    for (size_t i = 0; i < buff_size; ++i) {
        classic_fifo.push(i);
        custom_fifo.push(i);
    }

    /*  âûâîä íà ýêðàí âñåõ çíà÷åíèé, õðàíÿùèõñÿ â êîíòåéíåðå  */
	
    for (const auto& i : classic_fifo) {
        std::cout << i << std::endl;
    }

    for (const auto& i : custom_fifo) {
        std::cout << i << std::endl;
    }
        
    return 0;
}
