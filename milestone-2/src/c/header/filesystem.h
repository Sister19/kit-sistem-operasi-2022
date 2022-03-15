// Filesystem data structure

#include "std_datatype.h"

#define FS_MAP_SECTOR_NUMBER    0x100
#define FS_NODE_SECTOR_NUMBER   0x101
#define FS_SECTOR_SECTOR_NUMBER 0x103

#define FS_NODE_P_IDX_ROOT   0xFF
#define FS_NODE_S_IDX_FOLDER 0xFF

// Untuk filesystem map
struct map_filesystem {
    bool is_filled[512];
};


// Untuk filesystem nodes
struct node_entry {
    byte parent_node_index;
    byte sector_entry_index;
    char name[14];
};

struct node_filesystem {
    struct node_entry nodes[64];
};


// Untuk filesystem sector
struct sector_entry {
    byte sector_numbers[16];
};

struct sector_filesystem {
    struct sector_entry sector_list[32];
};


// Struktur data untuk read / write
struct file_metadata {
    byte *buffer;
    char *node_name;
    byte parent_index;
    unsigned int filesize;
};



// Untuk error code write & read
enum fs_retcode {
    FS_UNKNOWN_ERROR    = -1,
    FS_SUCCESS          = 0,
    FS_R_NODE_NOT_FOUND = 1,
    FS_R_TYPE_IS_FOLDER = 2,

    FS_W_FILE_ALREADY_EXIST   = 3,
    FS_W_NOT_ENOUGH_STORAGE   = 4,
    FS_W_MAXIMUM_NODE_ENTRY   = 5,
    FS_W_MAXIMUM_SECTOR_ENTRY = 6,
    FS_W_INVALID_FOLDER       = 7
};
