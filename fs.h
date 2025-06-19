/* fs.h - fs_erase, fs_program, fs_read, fs_sync, fs_init, fs_close */

#ifndef FS_H
#define FS_H
#include <pico/stdlib.h>
#include <pico/flash.h>
#include <hardware/flash.h>
#include "external/littlefs/lfs.h"

#define FS_BASE 0x10040000
#define FS_SIZE 512*1024 // 512 KB (for now)
#define FS_OFFSET FS_BASE - XIP_BASE

lfs_t fs;

/*----------------------------------------------------------------------
 * fs_erase - Wrapper to flash_range_erase, used to erase blocks of flash 
 * Input:
 *  c       -   Pointer to lfs config struct
 *  block   -   Block to erase
 * 
 * Output:
 *  int     -   Error, guaranteed to be 0
 ----------------------------------------------------------------------*/
int fs_erase(const struct lfs_config *c, lfs_block_t block) {
    int addr = c->block_size * block + FS_OFFSET;
    flash_range_erase(addr, c->block_size);
    return 0; // PicoSDK doesn't provide errors from flash_range functions
}

/*----------------------------------------------------------------------
 * fs_program - Wrapper to flash_range_program, used to prog blocks of flash 
 * Input:
 *  c       -   Pointer to lfs config struct
 *  block   -   Block to program
 *  offset  -   Offset within block, guaranteed to be aligned to prog size
 *  buffer  -   Buffer to write
 *  size    -   Size of buffer, guaranteed to be aligned to prog size
 * 
 * Output:
 *  int     -   Error, guaranteed to be 0 
 ----------------------------------------------------------------------*/
int fs_program(const struct lfs_config *c, lfs_block_t block, lfs_off_t offset, const void * buffer, lfs_size_t size) {
    uint32_t addr = c->block_size * block + offset + FS_OFFSET;
    flash_range_program((uint32_t)addr, buffer, size);
    return 0;
}

/*----------------------------------------------------------------------
 * fs_read - Reads into a buffer from flash 
 * Input:
 *  c       -   Pointer to lfs config struct
 *  block   -   Block to read from
 *  offset  -   Offset within block
 *  buffer  -   Buffer to read into
 *  size    -   Size of buffer
 * 
 * Output:
 *  int     -   Error, guaranteed to be 0                            
 ----------------------------------------------------------------------*/
int fs_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t offset, void * buffer, lfs_size_t size) {
    void * addr = (void *)(FS_BASE + block * c->block_size + offset);
    memcpy(buffer, addr, size);
    return 0;
}

/*----------------------------------------------------------------------
 * fs_sync - Does nothing    
 * Input:
 *  c       -   Pointer to lfs config struct
 * 
 * Output:
 *  int     -   Error, guaranteed to be 0                                           
 ----------------------------------------------------------------------*/
int fs_sync(const struct lfs_config *c) {
    return 0;
}

const struct lfs_config cfg = {
    .read = fs_read,
    .prog = fs_program,
    .erase = fs_erase,
    .sync = fs_sync,
    .read_size = 1,
    .prog_size = FLASH_PAGE_SIZE,
    .block_size = FLASH_SECTOR_SIZE,
    .block_count = FS_SIZE / FLASH_SECTOR_SIZE,
    .cache_size = FLASH_SECTOR_SIZE / 4,
    .lookahead_size = 32,
    .block_cycles = 500
};

/*----------------------------------------------------------------------
 * fs_init - Initializes filesystem, formats it if none available
 * Input:
 *  
 * Output:
 *  int     -   Errorcode, 0 if no issues, err from lfs if error encountered       
 ----------------------------------------------------------------------*/
int fs_init(void) {
    int err = lfs_mount(&fs, &cfg);
    if (err) {
        err = lfs_format(&fs, &cfg);
        lfs_mount(&fs, &cfg);

        if (err) return err;
    }
    return 0;
}

/*----------------------------------------------------------------------
 * fs_close - Unmounts filesystem 
 * Input:
 *  
 * Output:
 *  int     -   Errorcode, guaranteed to be 0                                      
 ----------------------------------------------------------------------*/
int fs_close(void) {
    lfs_unmount(&fs);
    return 0;
}

#endif