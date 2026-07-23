# 1. Base Image
FROM gcc:latest

# 2. Set working directory inside container
WORKDIR /usr/src/corevm

# 3. Copy all project files from host to container
COPY . .

# 4. Compile CoreVM source code
RUN g++ CoreVM.cpp -o CoreVM

# 5. Default execution command
CMD ["./CoreVM"]