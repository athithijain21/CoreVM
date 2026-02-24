#include <iostream>
#include <iomanip>

class CoreVM {
private:
    uint8_t memory[0x1000]; 
    int registers[4] = {0, 0, 0, 0};
    uint16_t pc = 0;
    bool running = true;

public:
    CoreVM() {
        for (int i = 0; i < 0x1000; i++) memory[i] = 0;
        std::cout << "CoreVM Initialized. Memory Range: 0x000 - 0xFFF" << std::endl;
    }

    // Changing 'address' to uint16_t here fixes your terminal warning!
    void write_memory(uint16_t address, int value) {
        if (address >= 0x1000) {
            std::cout << "\n!!! KERNEL PANIC !!!" << std::endl;
            std::cout << "Memory Out of Bounds at: 0x" << std::hex << std::uppercase << address << std::endl;
            running = false; 
        } else {
            memory[address] = (uint8_t)value;
        }
    }

    void run() {
        std::cout << "Starting Execution..." << std::endl;
        while (running && pc < 0x1000) {
            uint8_t opcode = memory[pc];
            switch (opcode) {
                case 0x01: // SET R0
                    registers[0] = 100;
                    std::cout << "[EXEC] Set R0 to 100" << std::endl;
                    pc++;
                    break;
                case 0xFF: // HALT
                    std::cout << "[EXEC] System Halted." << std::endl;
                    running = false;
                    break;
                default:
                    pc++;
                    break;
            }
        }
    }
};

int main() {
    CoreVM vm;
    
    // 1. Set a valid instruction
    vm.write_memory(0x00, 0x01); // SET R0
    
    // 2. Trigger your intentional error!
    // This will now properly trigger the Panic without a compiler warning.
    vm.write_memory(0x5000, 0xFF); 
    
    vm.run();
    return 0;
}