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
	const std::string jsonrpc;
	std::string method;
	std::optional<std::string> params;
	std::variant<std::string, long, double> id;
};
}
template<>
struct daw::json::json_data_contract<LibJsonRpc::Request>
{
	using type = json_member_list<
		json_string<"jsonrpc">,
		json_string<"method">,
		json_raw_null<"params", std::optional<std::string>>,
		json_variant<
			"id",
			std::variant<std::string, long, double>,
			json_variant_type_list<std::string, long, double>>>;

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