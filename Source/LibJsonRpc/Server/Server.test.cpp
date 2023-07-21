#include <gtest/gtest.h>

#include <LibJsonRpc/Server/Server.hpp>

TEST(Server, development)
{
	const size_t REQUEST_AMOUNT = 10;

	LibJsonRpc::Server server("https://eth.llamarpc.com");

	std::vector<std::future<std::string>> futures;
	for(size_t count = 0; count < REQUEST_AMOUNT; ++count)
		futures.emplace_back(server.batch_request("eth_blockNumber", "[]", [](const std::string& json){return daw::json::from_json<std::string>(json, "result");}));

	server.send_batch();

	for(auto& future: futures)
		std::cout << future.get() << '\n';
}