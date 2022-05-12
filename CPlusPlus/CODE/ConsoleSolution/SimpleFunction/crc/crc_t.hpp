#pragma once
#include <boost/crc.hpp>
#include<iostream>
// ʵ��ɵã�����ȽϺã����ҿ�
uint32_t GetCrc32(const std::string& my_string) {
	boost::crc_32_type result;
	result.process_bytes(my_string.data(), my_string.length());
	return result.checksum();
}
void use_crc_t()
{
	std::string data_s = "abcdefg";
	std::cout << "boost crc_optimal2:" << GetCrc32(data_s);
}