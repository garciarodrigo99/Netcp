# Macros

NETCP_CODE = netcp.cpp
NETCP_EXE = netcp
NETCP_EXE_TRACE = netcp_trace
DEFAULT_PORT = 8080
DEFAULT_ORIGIN_FILE = textfiles/block_420mb.txt
DEFAULT_DESTINATION_FILE = textfiles/block_420mb_receive.txt
TRACE_FILE = headers/trace_macro.hpp

# Reglas explícitas
# g++ -std=c++14 -g -Wall -o bin/main main/main.cc
# g++ $(MAIN_FILE) $(SRC_FILES) -o $(OUT_FILE)
default:
	g++-13 -o $(NETCP_EXE) -std=c++23 -g $(NETCP_CODE)

trace:
	g++-13 -o $(NETCP_EXE_TRACE) -std=c++23 -g -DTRACE -I/$(TRACE_FILE) $(NETCP_CODE)

server: 
	./$(NETCP_EXE) $(DEFAULT_PORT) $(DEFAULT_ORIGIN_FILE)

server-env: 
	./$(NETCP_EXE) $(DEFAULT_ORIGIN_FILE)

client: 
	./$(NETCP_EXE) -l $(DEFAULT_PORT) $(DEFAULT_DESTINATION_FILE)

client-env: 
	./$(NETCP_EXE) -l $(DEFAULT_DESTINATION_FILE)

server-trace: 
	./$(NETCP_EXE_TRACE) $(DEFAULT_PORT) $(DEFAULT_ORIGIN_FILE)

server-env-trace: 
	./$(NETCP_EXE_TRACE) $(DEFAULT_ORIGIN_FILE)

client-trace: 
	./$(NETCP_EXE_TRACE) -l $(DEFAULT_PORT) $(DEFAULT_DESTINATION_FILE)

client-env-trace: 
	./$(NETCP_EXE_TRACE) -l $(DEFAULT_DESTINATION_FILE)

# ! No se guarda en la shell en la que se ejecuta
export_:
	export NETCP_PORT=8080; \
	export NETCP_IP=192.168.0.26; \

clean:
	rm $(NETCP_EXE)
	rm $(NETCP_EXE_TRACE)