#ifndef LIBJSONRPC_REQUEST_HPP
#define LIBJSONRPC_REQUEST_HPP

#include <optional>
#include <string>

#include <daw/json/daw_json_link.h>
#include <future>

namespace LibJsonRpc
{
struct Request
{
	std::string jsonrpc;
	std::string method;
	std::optional<std::string> params;
	std::optional<size_t> id;
	std::promise<std::string> promise;
};
}
template<>
struct daw::json::json_data_contract<LibJsonRpc::Request>
{
	using type = json_member_list<
		json_string<"jsonrpc">,
		json_string<"method">,
		json_raw_null<"params", std::optional<std::string>>,
		json_number_null<"id", std::optional<size_t>>>;
	
	static inline auto
	to_json_data(const LibJsonRpc::Request& value)
	{
		return std::forward_as_tuple(
			value.jsonrpc,
			value.method,
			value.params,
			value.id);
	}
};
#endif