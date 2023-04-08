#ifndef __RESTORE_ROM_ADDR__
#define __RESTORE_ROM_ADDR__

#define CPT_MAGIC_BUMBER    0xbeef
#define BOOT_CODE           0x80000000
#define BOOT_FLAGS          0x80000f00
#define INT_REG_CPT_ADDR    0x80001000
#define FLOAT_REG_CPT_ADDR  0x80001100
#define PC_CPT_ADDR         0x80001200
#define CSR_CPT_ADDR        0x80001300

#ifndef RESET_VECTOR
    #define RESET_VECTOR        0x800a0000
#endif

#define CLINT_MMIO 0x38000000
#define CLINT_MTIMECMP 0x4000
#define CLINT_MTIME 0xBFF8

#define CP_MMIO_BASE 0x20000
#define MEMORY_8G_OFFSET 0x200000000
#define IO_OFFSET 0x3000000
#define CP_IDSEL 0x0
#define CP_HARTSEL 0x8
#define CP_MEM_OFFSET 0x10
#define CP_IO_OFFSET 0x18
#define CP_WAYMASK 0x20
#define CP_NOHYPE_BARRIER 0x28
#define CP_HARTNUM 0x30

#define CSR_RHARTID 0xBC0
#define CSR_VHARTID 0xBC1
#define CSR_MEMOFF 0xBC2
#define CSR_IOOFF 0xBC3
#define CSR_NOHYPEMODE 0xBC4
#define CSR_DSID 0x9C0


#endif //__RESTORE_ROM_ADDR__
