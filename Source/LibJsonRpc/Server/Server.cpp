#include <utility>

#include <daw/json/daw_json_iterator.h>
#include <daw/json/daw_json_link.h>

#include <LibJsonRpc/Server/Server.hpp>

namespace LibJsonRpc
{
Server::Server()
{
	auto scoped_lock = std::scoped_lock(global_lock);

	if(server_instance_count == 0)
		curl_global_init(CURL_GLOBAL_DEFAULT);

	++server_instance_count;
}
Server::Server(std::string url):
	url{std::move(url)}
{
	Server();
}
Server::~Server()
{
	auto scoped_lock = std::scoped_lock(global_lock);

	if(server_instance_count == 1)
		curl_global_cleanup();

	--server_instance_count;
}
std::string_view
Server::get_url()
{
	return url;
}
void
Server::set_url(std::string url)
{
	this->url = std::move(url);
}
std::future<std::string>
Server::batch_request(std::string method, std::function<std::string(std::string)> write_callback)
{
	auto scoped_lock = std::scoped_lock(local_lock);

	int index = batch.size();

	batch.emplace_back("2.0", std::move(method), std::nullopt, index);
	write_callbacks.emplace_back(write_callback);
	promises.emplace_back();

	return promises[index].get_future();
}
std::future<std::string>
Server::batch_request(std::string method, std::string params, std::function<std::string(std::string)> write_callback)
{
	auto scoped_lock = std::scoped_lock(local_lock);

	int index = batch.size();

	batch.emplace_back("2.0", std::move(method), std::move(params), index);
	write_callbacks.emplace_back(write_callback);
	promises.emplace_back();

	return promises[index].get_future();
}
void
Server::send_batch()
{
	auto scoped_lock = std::scoped_lock(local_lock);

	auto batch_json = daw::json::to_json_array<Request>(batch);

	CURL* session = curl_easy_init();

	curl_slist* header_list = curl_slist_append(nullptr, "Content-Type: application/json");
	curl_easy_setopt(session, CURLOPT_HTTPHEADER, header_list);

	curl_easy_setopt(session, CURLOPT_URL, url.c_str());
	curl_easy_setopt(session, CURLOPT_COPYPOSTFIELDS, batch_json.c_str());

	std::string batch_response;
	curl_easy_setopt(session, CURLOPT_WRITEDATA, &batch_response);
	curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, &Server::curl_write_callback);

	CURLcode session_result = curl_easy_perform(session);
	if(session_result != CURLE_OK)
		throw std::runtime_error(curl_easy_strerror(session_result));

	auto json_iterator = daw::json::json_array_iterator<daw::json::json_value>(batch_response);
	while(json_iterator.good() && json_iterator->find_member("id"))
	{
		auto json_response = *json_iterator;

		size_t index = daw::json::from_json<size_t>(json_iterator->find_member("id"));

		auto response = daw::json::to_json(json_response);

		if(write_callbacks[index])
			response = write_callbacks[index](response);

		promises[index].set_value(std::move(response));

		json_iterator++;
	}
	batch.clear();
	write_callbacks.clear();
	promises.clear();

	curl_easy_cleanup(session);
}
size_t
Server::curl_write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	size_t total_size = size * nmemb;

	auto response = static_cast<std::string*>(userdata);

	response->append(ptr, total_size);

	return total_size;
}
}