SRC_DIR:=src

$(SRC_DIR):
	mkdir -p $@

fetch-catch: $(SRC_DIR)
	wget -O $(SRC_DIR)/catch.hpp https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp