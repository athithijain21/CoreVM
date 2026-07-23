#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

// Cross-Platform Compatibility Headers
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <cstdlib>
#endif

class CoreVM {
private:
    uint8_t memory[4096] = {0};   // 4KB Memory Array
    uint16_t registers[4] = {0};  // R0, R1, R2, R3
    uint16_t PC = 0x0;            // Program Counter
    bool running = true;
    std::string system_status = "SYSTEM READY";

public:
    void clear_screen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void write_memory(uint16_t address, int value) {
        if (address >= 0x1000) {
            system_status = "!!! KERNEL PANIC: OUT OF BOUNDS @ 0x" + std::to_string(address) + " !!!";
            running = false;
        } else {
            memory[address] = static_cast<uint8_t>(value);
            system_status = "Memory Write Successful.";
        }
    }

    // ALU OPERATIONS
    void op_add() {
        registers[0] = registers[1] + registers[2];
        PC += 2;
        system_status = "EXEC: ADD -> R0 = " + std::to_string(registers[0]);
    }

    void op_sub() {
        registers[0] = registers[1] - registers[2];
        PC += 2;
        system_status = "EXEC: SUB -> R0 = " + std::to_string(registers[0]);
    }

    void op_and() {
        registers[0] = registers[1] & registers[2];
        PC += 2;
        system_status = "EXEC: AND -> R0 = " + std::to_string(registers[0]);
    }

    void op_or() {
        registers[0] = registers[1] | registers[2];
        PC += 2;
        system_status = "EXEC: OR  -> R0 = " + std::to_string(registers[0]);
    }

    void load_inputs(uint16_t val1, uint16_t val2) {
        registers[1] = val1;
        registers[2] = val2;
        system_status = "LOADED: R1=" + std::to_string(val1) + ", R2=" + std::to_string(val2);
    }

    void render_ui() {
        clear_screen();
        std::cout << "=========================================\n";
        std::cout << "||        CORE-VM INTERFACE            ||\n";
        std::cout << "=========================================\n";
        std::cout << "[ CPU STATUS ]          [ PROGRAM COUNTER ]\n";
        std::cout << "R0: " << (int)registers[0] << "  R1: " << (int)registers[1] << "      PC: 0x" << std::hex << PC << "\n";
        std::cout << "R2: " << (int)registers[2] << "  R3: " << (int)registers[3] << "      STATE: " << (running ? "ACTIVE" : "HALTED") << "\n";
        std::cout << "-----------------------------------------\n";
        std::cout << "[ MEMORY MAP (Hex) ]\n";
        for(int i = 0; i < 16; i++) {
            std::cout << (i < 10 ? "0" : "") << std::hex << (int)memory[i] << " ";
        }
        std::cout << "\n-----------------------------------------\n";
        std::cout << "[ MESSAGE ]: " << system_status << "\n";
        std::cout << "=========================================\n";
        std::cout << " Commands: load <val1> <val2> | add | sub | and | or | panic | exit\n";
    }

    void start_shell() {
        std::string command;
        while (running) {
            render_ui();
            std::cout << "\nCoreOS> ";
            std::cin >> command;

            if (command == "load") {
                uint16_t v1, v2;
                std::cin >> v1 >> v2;
                load_inputs(v1, v2);
            } else if (command == "add") {
                op_add();
            } else if (command == "sub") {
                op_sub();
            } else if (command == "and") {
                op_and();
            } else if (command == "or") {
                op_or();
            } else if (command == "panic") {
                write_memory(0x1000, 99);
            } else if (command == "exit") {
                break;
            }
        }
    }
};

int main() {
    CoreVM vm;
    vm.start_shell();
    return 0;
}