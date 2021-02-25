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
	
   /*  �������� ���������� std::map<int, int>
    *  �������� ���������� std::map<int, int> � ����� �����������, ������������ 10 ����������
   */
	
    std::map<int, int> classic_map;
    auto alligator_map = std::map<int, int, std::less<>, custom_alligator<std::pair<const int, int>>> {};


	/*  ���������� 10 ����������, ��� ���� - ��� ����� �� 0 �� 9, � �������� - ��������� �����  */
	
    for (size_t i = 0; i < buff_size; ++i) {
        auto fac_value = factorial(i);
        classic_map.try_emplace(i, fac_value);
        alligator_map.try_emplace(i, fac_value);
    }

    /* ����� �� ����� ���� �������� (���� � �������� ��������� ��������) ���������� � ���������� */
	
	for(const auto& print : classic_map) {
		std::cout << print.first << " " << print.second << std::endl;
	}

    for (const auto& print : alligator_map) {
        std::cout << print.first << " " << print.second << std::endl;
    }

   /*  �������� ���������� ������ ���������� ��� �������� �������� ���� int
    *  �������� ���������� ������ ���������� ��� �������� �������� ���� int � ����� �����������, ������������ 10 ����������
    */
	
    keeper<int> classic_fifo;
    keeper<int, custom_alligator<int>> custom_fifo;

    /*  ���������� 10 ���������� �� 0 �� 9  */
	
    for (size_t i = 0; i < buff_size; ++i) {
        classic_fifo.push(i);
        custom_fifo.push(i);
    }

    /*  ����� �� ����� ���� ��������, ���������� � ����������  */
	
    for (const auto& i : classic_fifo) {
        std::cout << i << std::endl;
    }

    for (const auto& i : custom_fifo) {
        std::cout << i << std::endl;
    }
        
    return 0;
}
