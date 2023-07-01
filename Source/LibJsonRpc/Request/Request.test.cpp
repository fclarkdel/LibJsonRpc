#include <daw/json/daw_json_link.h>
#include <gtest/gtest.h>

#include <LibJsonRpc/Request/Request.hpp>

TEST(Request, shouldSerializeToJson)
{
	LibJsonRpc::Request request{"2.0", "method", "[]", 0};

	std::string expected_json = R"({"jsonrpc":"2.0","method":"method","params":[],"id":0})";
	std::string result_json = daw::json::to_json(request);

	EXPECT_EQ(expected_json, result_json);
}
TEST(Request, shouldDeserializeFromJson)
{
	std::string json = R"({"jsonrpc":"2.0","method":"method","params":[],"id":0})";

	LibJsonRpc::Request expected_request{"2.0", "method", "[]", 0};
	auto result_request = daw::json::from_json<LibJsonRpc::Request>(json);

	EXPECT_EQ(expected_request.jsonrpc, result_request.jsonrpc);
	EXPECT_EQ(expected_request.method, result_request.method);
	EXPECT_EQ(expected_request.params, result_request.params);
	EXPECT_EQ(expected_request.id, result_request.id);
}
TEST(Request_no_params, shouldSerializeToJson)
{
	LibJsonRpc::Request request{"2.0", "method", std::nullopt, 0};

	std::string expected_json = R"({"jsonrpc":"2.0","method":"method","id":0})";
	std::string result_json = daw::json::to_json(request);

	EXPECT_EQ(expected_json, result_json);
}
TEST(Request_no_params, shouldDeserializeFromJson)
{
	std::string json = R"({"jsonrpc":"2.0","method":"method","id":0})";

	LibJsonRpc::Request expected_request{"2.0", "method", std::nullopt, 0};
	auto result_request = daw::json::from_json<LibJsonRpc::Request>(json);

	EXPECT_EQ(expected_request.jsonrpc, result_request.jsonrpc);
	EXPECT_EQ(expected_request.method, result_request.method);
	EXPECT_EQ(expected_request.params, result_request.params);
	EXPECT_EQ(expected_request.id, result_request.id);
}
TEST(Request_no_id, shouldSerializeToJson)
{
	LibJsonRpc::Request request{"2.0", "method", "[]", std::nullopt};

	std::string expected_json = R"({"jsonrpc":"2.0","method":"method","params":[]})";
	std::string result_json = daw::json::to_json(request);

	EXPECT_EQ(expected_json, result_json);
}
TEST(Request_no_id, shouldDeserializeFromJson)
{
	std::string json = R"({"jsonrpc":"2.0","method":"method","params":[]})";

	LibJsonRpc::Request expected_request{"2.0", "method", "[]", std::nullopt};
	auto result_request = daw::json::from_json<LibJsonRpc::Request>(json);

	EXPECT_EQ(expected_request.jsonrpc, result_request.jsonrpc);
	EXPECT_EQ(expected_request.method, result_request.method);
	EXPECT_EQ(expected_request.params, result_request.params);
	EXPECT_EQ(expected_request.id, result_request.id);
}
TEST(Request_no_params_nor_id, shouldSerializeToJson)
{
	LibJsonRpc::Request request{"2.0", "method", std::nullopt, std::nullopt};

	std::string expected_json = R"({"jsonrpc":"2.0","method":"method"})";
	std::string result_json = daw::json::to_json(request);

	EXPECT_EQ(expected_json, result_json);
}
TEST(Request_no_params_nor_id, shouldDeserializeFromJson)
{
	std::string json = R"({"jsonrpc":"2.0","method":"method"})";

	LibJsonRpc::Request expected_request{"2.0", "method", std::nullopt, std::nullopt};
	auto result_request = daw::json::from_json<LibJsonRpc::Request>(json);

	EXPECT_EQ(expected_request.jsonrpc, result_request.jsonrpc);
	EXPECT_EQ(expected_request.method, result_request.method);
	EXPECT_EQ(expected_request.params, result_request.params);
	EXPECT_EQ(expected_request.id, result_request.id);
}