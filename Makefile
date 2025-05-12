BIN_DIR = bin
APP = $(BIN_DIR)/app

run: $(APP)
	./$(APP)

$(APP):
	mkdir -p $(BIN_DIR)
	gcc -Isrc/include src/main.c src/satellite.c src/fetch.c src/util.c src/renderer.c src/TLE.c src/SGP4.c -o $(APP) -lcurl -lraylib -lm

clean:
	rm -rf $(BIN_DIR)

.PHONY: run clean
