#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <windows.h> // For system("cls") and Sleep

class CoreVM {
private:
    uint8_t memory[0x1000]; 
    int registers[4] = {0, 0, 0, 0};
    uint16_t pc = 0;
    bool running = true;
    std::string system_status = "SYSTEM READY";

public:
    CoreVM() {
        for (int i = 0; i < 0x1000; i++) memory[i] = 0;
    }

    // --- VIRTUAL ENVIRONMENT UI ---
    void render_ui() {
        system("cls"); // Clears terminal for the "Plain Box" look
        std::cout << "############################################\n";
        std::cout << "#             CORE-VM INTERFACE            #\n";
        std::cout << "############################################\n";

        // BOX 1: CPU STATUS
        std::cout << " [ CPU STATUS ]          [ PROGRAM COUNTER ]\n";
        std::cout << " R0: " << std::setw(3) << std::dec << registers[0] 
                  << "  R1: " << std::setw(3) << registers[1] 
                  << "      PC: 0x" << std::hex << std::uppercase << pc << "\n";
        std::cout << " R2: " << std::setw(3) << std::dec << registers[2] 
                  << "  R3: " << std::setw(3) << registers[3] 
                  << "      STATE: " << (running ? "ACTIVE" : "HALTED") << "\n";
        std::cout << "--------------------------------------------\n";

        // BOX 2: MEMORY MAP (First 16 bytes)
        std::cout << " [ MEMORY MAP (Hex) ]\n ";
        for (int i = 0; i < 16; i++) {
            std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)memory[i] << " ";
        }
        std::cout << "\n--------------------------------------------\n";

        // BOX 3: SYSTEM LOGS
        std::cout << " [ MESSAGE ]: " << system_status << "\n";
        std::cout << "############################################\n";
    }

    // --- HARDWARE LOGIC ---
    void write_memory(uint16_t address, int value) {
        if (address >= 0x1000) {
            // Your unique Kernel Panic logic
            system_status = "!!! KERNEL PANIC: OUT OF BOUNDS @ 0x" + std::to_string(address) + " !!!";
            running = false; 
        } else {
            memory[address] = (uint8_t)value;
            system_status = "Memory Write Successful.";
        }
    }

    // --- COMMAND SHELL ---
    void start_shell() {
        std::string input;
        while (true) {
            render_ui();
            std::cout << "\nCoreOS> "; 
            std::getline(std::cin, input);

            if (input == "exit") break;

            std::stringstream ss(input);
            std::string cmd;
            ss >> cmd;

            if (cmd == "write") {
                uint16_t addr;
                int val;
                // Command format: write <hex_address> <decimal_value>
                if (ss >> std::hex >> addr >> std::dec >> val) {
                    write_memory(addr, val);
                } else {
                    system_status = "Error: Use 'write <hex_addr> <dec_val>'";
                }
            } else if (input != "") {
                system_status = "Unknown command: " + cmd;
            }
        }
    }
};

int main() {
    CoreVM vm;
    vm.start_shell(); // Launch the interactive virtual environment
    return 0;
}