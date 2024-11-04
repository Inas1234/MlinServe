CXX = gcc
FILES = ./src/main.c -o main
LINKERS = ./src/HttpServer.c ./src/HttpParser.c ./src/Route.c

all:
	$(CXX) $(LINKERS) $(FILES)

test:
	curl -X POST http://localhost:8080/submit \
     -H "Content-Type: application/json" \
     -H "Custom-Header: TestHeaderValue" \
     -d '{"gay": "sex"}'
