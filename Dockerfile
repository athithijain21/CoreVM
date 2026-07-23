# 1. Use an official, lightweight C++ build environment
FROM gcc:latest

# 2. Set the working directory inside the container
WORKDIR /usr/src/corevm

# 3. Copy all project files into the container
COPY . .

# 4. Compile CoreVM C++ source files
RUN g++ main.cpp -o CoreVM

# 5. Set the default command to run your emulator when the container starts
CMD ["./CoreVM"]