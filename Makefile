CXX = gcc
FILES = ./src/main.c -o main
LINKERS = ./src/HttpServer.c ./src/HttpParser.c ./src/Route.c ./src/Middleware.c

all:
	$(CXX) $(LINKERS) $(FILES)

test:
	curl -X GET http://localhost:8080/login \
     -H "Content-Type: application/json" \
     -H "Custom-Header: TestHeaderValue" \
     -d '{"gay": "sex"}'
