# Macros

NETCP_CODE = netcp.cpp
NETCP_EXE = netcp
DEFAULT_PORT = 8080
DEFAULT_ORIGIN_FILE = textfiles/testfile_1kb.txt
DEFAULT_DESTINATION_FILE = textfiles/testfile_1kb_receive.txt

# Reglas explícitas
# g++ -std=c++14 -g -Wall -o bin/main main/main.cc
# g++ $(MAIN_FILE) $(SRC_FILES) -o $(OUT_FILE)
default:
	g++-13 -o $(NETCP_EXE) -std=c++23 -g $(NETCP_CODE)

# file:
# 	$(EXE_FILE) $(IN_FILE)

server: 
	./$(NETCP_EXE) $(DEFAULT_PORT) $(DEFAULT_ORIGIN_FILE)

server-env: 
	./$(NETCP_EXE) $(DEFAULT_ORIGIN_FILE)

client: 
	./$(NETCP_EXE) -l $(DEFAULT_PORT) $(DEFAULT_DESTINATION_FILE)

client-env: 
	./$(NETCP_EXE) -l $(DEFAULT_DESTINATION_FILE)

# run-file: 
# 	default file

clean:
	rm $(NETCP_EXE)