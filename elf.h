/* elf.h - */
#include "scheduler.h"

#define EI_NIDENT 16
#define PT_LOAD 1

typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half    e_type;
    Elf32_Half    e_machine;
    Elf32_Word    e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    Elf32_Word    e_flags;
    Elf32_Half    e_ehsize;
    Elf32_Half    e_phentsize;
    Elf32_Half    e_phnum;
    Elf32_Half    e_shentsize;
    Elf32_Half    e_shnum;
    Elf32_Half    e_shstrndx;
} Elf32_Ehdr;

typedef struct {
    Elf32_Word p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Elf32_Word p_filesz;
    Elf32_Word p_memsz;
    Elf32_Word p_flags;
    Elf32_Word p_align;
} Elf32_Phdr;

/*----------------------------------------------------------------------
 * loadProgramFromELF - Creates a process from given ELF file
 * Input:
 *  elfStart    -   Start address of ELF file in memory
 * 
 * Outputs:
 *            
 ----------------------------------------------------------------------*/
void loadProgramFromELF(uint32_t elfStart) {
    // TODO: Add validation code to ensure the ELF file can actually run on our system

    Elf32_Ehdr * elf = (Elf32_Ehdr *)elfStart;

    Elf32_Phdr * phdr = (Elf32_Phdr *) (elfStart + elf->e_phoff);
    uint32_t loadaddr = 0;
    uint32_t poff = 0;
    for (int i = 0; i < elf->e_phnum; i++) {
        if (phdr[i].p_type == PT_LOAD) {
            loadaddr = phdr[i].p_vaddr;
            poff = phdr[i].p_offset;
            break;
        }
    }


    printf("ELF Start at 0x%08X\n", (uint32_t)elfStart);
    uint32_t entryPoint = elf->e_entry;
    uint32_t offset = entryPoint - loadaddr;
    entryPoint = elfStart + (uint32_t)offset + poff;
    printf("ELF entry at 0x%08X\n", (uint32_t)entryPoint);

    printf("First Instruction: 0x%04X\n", *(uint16_t *)((uint32_t)entryPoint & 0xfffffff0));
    createProc((void *)entryPoint, 512);
}