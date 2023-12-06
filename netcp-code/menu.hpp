#include <string>
#include <optional>
#include <vector>
#include <iostream>

struct program_options
{
	bool show_help = false;
	std::string output_filename;
	bool listen = false;
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

		if (*it == "-o" || *it == "--output") {
			if (++it != end) {
				options.output_filename = *it;
			} else {
				std::cerr << "Error...\n";
				return std::nullopt;
			}
		}
		if (*it == "-l" || *it == "--listen")
		{
			options.listen = true;
		}
		// Opciones adicionales...
	}
	return options;
}