#include <string>
#include <optional>
#include <vector>
#include <iostream>
#include "netcp_errors.hpp"

struct program_options
{
	bool show_help = false;
	std::string output_filename;
	bool listen = false;
	int listen_port = 0;
	// ...
};

std::optional<program_options> parse_args(int argc, char* argv[]) {
	std::vector<std::string_view> args(argv + 1, argv + argc);
	program_options options;

	for (auto it = args.begin(), end = args.end(); it != end; ++it)
	{
		if (*it == "-h" || *it == "--help")
		{
			options.show_help = true;
		}

		if (*it == "-l" || *it == "--listen")
		{
			options.listen = true;
			if (++it != end) {
				options.listen_port = std::stoi(std::string(*it));
			} else {
				std::cerr << "Error: " << Netcp_errors::PORT_MISSING_ERROR.error_text;
				return std::nullopt;
			}
			continue;
		}
		//if (*it == "-o" || *it == "--output") {
			if (it != end) {
				options.output_filename = *it;
			} else {
				std::cerr << "Error: " << Netcp_errors::FILE_MISSING_ERROR.error_text;
				return std::nullopt;
			}
		//}
		// Opciones adicionales...
	}
	return options;
}