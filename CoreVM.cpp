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
    // Helper function for cross-platform screen clearing
    void clear_screen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    // Helper function for cross-platform delays
    void sleep_ms(int milliseconds) {
#ifdef _WIN32
        Sleep(milliseconds);
#else
        usleep(milliseconds * 1000);
#endif
    }

    void write_memory(uint16_t address, int value) {
        if (address >= 0x1000) {
            // Kernel Panic Logic
            system_status = "!!! KERNEL PANIC: OUT OF BOUNDS @ 0x" + std::to_string(address) + " !!!";
            running = false;
        } else {
            memory[address] = static_cast<uint8_t>(value);
            system_status = "Memory Write Successful.";
        }
    }

    void render_ui() {
        clear_screen(); // Clears terminal based on OS
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
    }

    void start_shell() {
        std::string input;
        while (running) {
            render_ui();
            std::cout << "\nCoreOS> ";
            std::getline(std::cin, input);
            if (input == "exit") break;
        }
    }
};