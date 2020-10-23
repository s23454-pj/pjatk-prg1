CXX=g++
CXXSTD=c++17
CXXWARNINGS=\
		   -Wall \
		   -Wextra \
		   -Wpedantic \
		   -Werror \
		   -Wfatal-errors
CXXINCLUDES=\
			-I./include

CXXFLAGS=\
		 -std=$(CXXSTD) \
		 $(CXXWARNINGS) \
		 $(CXXINCLUDES)

format:
	clang-format -i src/*.cpp

FILENAME=
compile:
	$(CXX) $(CXXFLAGS) -o build/${FILENAME}.out src/${FILENAME}.cpp && chmod +x build/${FILENAME}.out