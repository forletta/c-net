BUILD_DIR := ./build
SRC_DIR := ./src

CC := clang
CFLAGS := -std=c11

.PHONY: client
client: $(BUILD_DIR)/client

.PHONY: server
server: $(BUILD_DIR)/server

$(BUILD_DIR)/client: $(BUILD_DIR)/client.o
	$(CC) $< -o $@

$(BUILD_DIR)/client.o: $(SRC_DIR)/client.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/server: $(BUILD_DIR)/server.o
	$(CC) $< -o $@

$(BUILD_DIR)/server.o: $(SRC_DIR)/server.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
