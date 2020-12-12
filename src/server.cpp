#include "server.hpp"
#include "response.hpp"
#include "logger.hpp"

std::map<std::string, std::string> mime_types;
void run_server(int);
logger logger;
server cs557;

int main() {

  int socket_fd = cs557.initialize_server();
  unsigned int threads_supported = std::thread::hardware_concurrency();
  std::vector<std::thread> thread_pool;

  while (1) {
    if (listen(socket_fd, 5) < 0) {
      exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < threads_supported; i++) {
      thread_pool.emplace_back(run_server, socket_fd);
    }

    for (size_t i = 0; i < thread_pool.size(); i++) {
      if (thread_pool.at(i).joinable()) thread_pool.at(i).join();
    }

  }
}

server::server() {
  socket_fd = 0;
  new_socket = 0;

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = 0;
}

int server::initialize_server() {
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  int option = 1;
  create_map();

  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option));

  if (bind(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
    exit(EXIT_FAILURE);
  }

  s_len = sizeof(server_address);
  if (getsockname(socket_fd, (struct sockaddr *) &server_address, (socklen_t *) &s_len) < 0) {
    exit(EXIT_FAILURE);
  }

  std::cout << "\n ------------------------------------------------\n"
            << "   HTTP_Server => listening on port [ "
            << ntohs(server_address.sin_port) << " ]\n"
            << " ------------------------------------------------\n" << std::endl;

  return socket_fd;
}

void run_server(int socket_fd) {
  char buffer[1024] = {0};
  socklen_t c_len = cs557.c_len;
  int new_socket;

  c_len = sizeof(cs557.client_address);
  if ((new_socket = accept(socket_fd, (struct sockaddr *) &cs557.client_address, (socklen_t *) &c_len)) < 0) {
    exit(EXIT_FAILURE);
  }

  read(new_socket, buffer, 1024);

  std::string file_name = cs557.request_parser(buffer);
  std::string headers = response::header_response(file_name);

  logger.write(file_name, inet_ntoa(cs557.client_address.sin_addr), ntohs(cs557.client_address.sin_port));

  send(new_socket, headers.c_str(), strlen(headers.c_str()), 0);
  cs557.send_data(file_name, new_socket);

  close(new_socket);

}

std::string server::request_parser(char *buffer) {
  char *current_token, *string_left = buffer;
  std::vector<std::string> tokens;
  current_token = strtok_r(string_left, " ", &string_left);

  while (current_token) {
    tokens.emplace_back(current_token);
    current_token = strtok_r(string_left, " ", &string_left);
  }
  tokens[1] = tokens[1].substr(1);
  return tokens[1];
}

std::string server::check_mime_type(std::string extension) {
  std::map<std::string, std::string>::iterator it;

  it = mime_types.find(extension);
  if (it != mime_types.end()) {
    return it->second;
  } else return "application/octet-stream";
}

void server::send_data(std::string file_name, int socket) {
  response res;
  int file_size = std::stoi(res.get_content_length(file_name));

  file_name = "www/" + file_name;
  char *data = new char[file_size];
  std::ifstream file;
  file.open((file_name.c_str()));

  if (file.is_open() && file_name != "www/") {
    file.read(data, file_size);
    send(socket, data, file_size, 0);
  }
  file.close();
  delete[] data;
}

void server::create_map() {

  mime_types.insert(std::pair<std::string, std::string>("aac", "audio/aac"));
  mime_types.insert(std::pair<std::string, std::string>("abw", "application/x-abiword"));
  mime_types.insert(std::pair<std::string, std::string>("arc", "application/octet-stream"));
  mime_types.insert(std::pair<std::string, std::string>("avi", "video/x-msvideo"));
  mime_types.insert(std::pair<std::string, std::string>("azw", "application/vnd.amazon.ebook"));
  mime_types.insert(std::pair<std::string, std::string>("bin", "application/octet-stream"));
  mime_types.insert(std::pair<std::string, std::string>("bmp", "image/bmp"));
  mime_types.insert(std::pair<std::string, std::string>("bz", "application/x-bzip"));
  mime_types.insert(std::pair<std::string, std::string>("bz2", "application/x-bzip2"));
  mime_types.insert(std::pair<std::string, std::string>("csh", "application/x-csh"));
  mime_types.insert(std::pair<std::string, std::string>("css", "text/css"));
  mime_types.insert(std::pair<std::string, std::string>("csv", "text/csv"));
  mime_types.insert(std::pair<std::string, std::string>("doc", "application/msword"));
  mime_types.insert(std::pair<std::string, std::string>("docx",
                                                        "application/vnd.openxmlformats-officedocument.wordprocessingml.document"));
  mime_types.insert(std::pair<std::string, std::string>("eot", "application/vnd.ms-fontobject"));
  mime_types.insert(std::pair<std::string, std::string>("epub", "application/epub+zip"));
  mime_types.insert(std::pair<std::string, std::string>("es", "application/ecmascript"));
  mime_types.insert(std::pair<std::string, std::string>("gif", "image/gif"));
  mime_types.insert(std::pair<std::string, std::string>("htm", "text/html"));
  mime_types.insert(std::pair<std::string, std::string>("html", "text/html"));
  mime_types.insert(std::pair<std::string, std::string>("ico", "image/x-icon"));
  mime_types.insert(std::pair<std::string, std::string>("ics", "text/calendar"));
  mime_types.insert(std::pair<std::string, std::string>("jar", "application/java-archive"));
  mime_types.insert(std::pair<std::string, std::string>("jpeg", "image/jpeg"));
  mime_types.insert(std::pair<std::string, std::string>("jpg", "image/jpeg"));
  mime_types.insert(std::pair<std::string, std::string>("js", "application/javascript"));
  mime_types.insert(std::pair<std::string, std::string>("json", "application/json"));
  mime_types.insert(std::pair<std::string, std::string>("mid", "audio/x-midi"));
  mime_types.insert(std::pair<std::string, std::string>("midi", "audio/midi"));
  mime_types.insert(std::pair<std::string, std::string>("mpeg", "video/mpeg"));
  mime_types.insert(std::pair<std::string, std::string>("mpkg", "application/vnd.apple.installer+xml"));
  mime_types.insert(std::pair<std::string, std::string>("odp", "application/vnd.oasis.opendocument.presentation"));
  mime_types.insert(std::pair<std::string, std::string>("ods", "application/vnd.oasis.opendocument.spreadsheet"));
  mime_types.insert(std::pair<std::string, std::string>("odt", "application/vnd.oasis.opendocument.text"));
  mime_types.insert(std::pair<std::string, std::string>("oga", "audio/ogg"));
  mime_types.insert(std::pair<std::string, std::string>("ogv", "video/ogg"));
  mime_types.insert(std::pair<std::string, std::string>("ogx", "application/ogg"));
  mime_types.insert(std::pair<std::string, std::string>("otf", "font/otf"));
  mime_types.insert(std::pair<std::string, std::string>("png", "image/png"));
  mime_types.insert(std::pair<std::string, std::string>("pdf", "application/pdf"));
  mime_types.insert(std::pair<std::string, std::string>("ppt", "application/vnd.ms-powerpoint"));
  mime_types.insert(std::pair<std::string, std::string>("pptx",
                                                        "application/vnd.openxmlformats-officedocument.presentationml.presentation"));
  mime_types.insert(std::pair<std::string, std::string>("rar", "application/x-rar-compressed"));
  mime_types.insert(std::pair<std::string, std::string>("rtf", "application/rtf"));
  mime_types.insert(std::pair<std::string, std::string>("sh", "application/x-sh"));
  mime_types.insert(std::pair<std::string, std::string>("svg", "image/svg+xml"));
  mime_types.insert(std::pair<std::string, std::string>("swf", "application/x-shockwave-flash"));
  mime_types.insert(std::pair<std::string, std::string>("tar", "application/x-tar"));
  mime_types.insert(std::pair<std::string, std::string>("tif", "image/tiff"));
  mime_types.insert(std::pair<std::string, std::string>("tiff", "image/tiff"));
  mime_types.insert(std::pair<std::string, std::string>("ts", "application/typescript"));
  mime_types.insert(std::pair<std::string, std::string>("ttf", "font/ttf"));
  mime_types.insert(std::pair<std::string, std::string>("txt", "text/plain"));
  mime_types.insert(std::pair<std::string, std::string>("vsd", "application/vnd.visio"));
  mime_types.insert(std::pair<std::string, std::string>("wav", "audio/wav"));
  mime_types.insert(std::pair<std::string, std::string>("weba", "audio/webm"));
  mime_types.insert(std::pair<std::string, std::string>("webm", "video/webm"));
  mime_types.insert(std::pair<std::string, std::string>("webp", "image/webp"));
  mime_types.insert(std::pair<std::string, std::string>("woff", "font/woff"));
  mime_types.insert(std::pair<std::string, std::string>("woff2", "font/woff2"));
  mime_types.insert(std::pair<std::string, std::string>("xhtml", "application/xhtml+xml"));
  mime_types.insert(std::pair<std::string, std::string>("xls", "application/vnd.ms-excel"));
  mime_types.insert(std::pair<std::string, std::string>("xlsx",
                                                        "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"));
  mime_types.insert(std::pair<std::string, std::string>("xml", "application/xml"));
  mime_types.insert(std::pair<std::string, std::string>("xul", "application/vnd.mozilla.xul+xml"));
  mime_types.insert(std::pair<std::string, std::string>("zip", "application/zip"));
  mime_types.insert(std::pair<std::string, std::string>("7z", "application/x-7z-compressed"));

}

server::~server() {
  close(new_socket);
  close(socket_fd);
  std::cout << "shutting down server..." << std::endl;
  exit(0);
}

