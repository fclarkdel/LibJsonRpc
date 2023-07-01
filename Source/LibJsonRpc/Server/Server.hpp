#ifndef LIBJSONRPC_SERVER_HPP
#define LIBJSONRPC_SERVER_HPP

#include <future>
#include <mutex>
#include <string>
#include <vector>

#include <curl/curl.h>

#include <LibJsonRpc/Request/Request.hpp>

namespace LibJsonRpc
{
class Server
{
public:
	Server();

	explicit Server(std::string url);

	~Server();

	std::string_view
	get_url();

	void
	set_url(std::string url);

	///@{
	/// @brief
	/// 	Adds a request object to the current batch.
	/// @param method
	/// 	The name of the method to be invoked on the server.
	/// @param params
	/// 	The parameters to be passed to the invoked method.
	/// @return
	///		A future that will be fulfilled once the server processes the batch request.
	///		The future will contain the JSON response object from the server.
	std::future<std::string>
	batch_request(std::string method);

	std::future<std::string>
	batch_request(std::string method, std::string params);
	///@}

	/// @brief
	///		Sends the current batch object to the server,
	///		and fulfills the promises associated with the requests
	/// 	in the batch by 'id'.
	void
	execute_batch();

private:
	static inline std::mutex global_lock;
	static inline size_t server_instance_count;

	std::string url;

	std::mutex local_lock;

	std::vector<Request> batch;

	static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata);
};
}
#endif