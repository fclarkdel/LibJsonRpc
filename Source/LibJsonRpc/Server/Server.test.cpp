#include <gtest/gtest.h>

//#include <LibJsonRpc/Server/Server.hpp>

#include <LibJsonRpc.hpp>

TEST(Server, development)
{
	const size_t REQUEST_AMOUNT = 1000;

	LibJsonRpc::Server server("localhost:8545");

	std::vector<std::future<std::string>> futures;
	for(size_t count = 0; count < REQUEST_AMOUNT; ++count)
		futures.emplace_back(server.batch_request("eth_blockNumber"));

	server.execute_batch();

	for(auto& future: futures)
		std::cout << future.get() << '\n';
}