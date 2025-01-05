CXX = gcc
FILES = ./src/main.c -o main
LINKERS = ./src/HttpServer.c ./src/HttpParser.c ./src/Route.c ./src/Middleware.c ./src/Cors.c ./src/Env.c ./src/PGdb.c

all:
	$(CXX) -I/opt/homebrew/Cellar/postgresql@14/14.15/include/postgresql@14 \
            -L/opt/homebrew/Cellar/postgresql@14/14.15/lib/postgresql@14 \
             $(LINKERS) $(FILES) -lpq

test:
	curl -X GET http://localhost:8080/login \
     -H "Content-Type: application/json" \
     -H "Custom-Header: TestHeaderValue" \
     -d '{"gay": "sex"}'

db:
   docker run --name postgres-container -e POSTGRES_PASSWORD=secret -e POSTGRES_DB=test -p 5432:5432 -d postgres
