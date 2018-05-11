#ifndef __ext4_c_2018_05_09_15_52
#define __ext4_c_2018_05_09_15_52
#include <os/fs/path.h>
#include <stdint.h>

typedef struct{
  uint32_t inodeCount;
  uint32_t blockCount;
  uint32_t rootBlockCount;
  uint32_t freeInodes;
  uint32_t freeBlocks;
  uint32_t firstBlock;
  uint32_t logBlockSize;
  uint32_t logClusterSize;
  uint32_t blocksPerGroup;
  uint32_t clustersPerGroup;
  uint32_t inodesPerGroup;
  uint32_t mountTime;
  uint32_t writeTime;
  uint16_t mountCount;
  uint16_t maxMountCount;
  uint16_t magic;
  uint16_t state;
  uint16_t errors;
  uint16_t minorRev;
  uint32_t lastCheck;
  uint32_t checkMaxTime;
  uint32_t creatorOs;
  uint32_t revLevel;
  uint16_t resUid;
  uint16_t resGid;
  uint32_t firstInode;
  uint16_t inodeSize;
  uint32_t featureCompat;
  uint32_t featureIncompat;
  uint32_t roCompat;
  uint8_t uuid[16];
  char volumeName[16];
  char lastMountLocation[64];
  uint32_t algorithmUsageBitmap;
  uint8_t preallocBlocks;
  uint8_t preallocDirBlocks;
  uint16_t reservedGdtBlocks;
  uint8_t journalUuid[16];
  uint32_t journalInode;
  uint32_t journalDev;
  uint32_t lastOrphan;
  uint32_t hashSeed[4];
  uint8_t hashVersion;
  uint8_t jnlBackupType;
  uint16_t descSize
  uint32_t defaultMountOpts;
  uint32_t firstMetaBg;
  uint32_t mkfsTime;
  uint32_t journalBlocks[17];
  uint32_t blockCountHigh;
  uint32_t reservedBlockCountHigh;
  uint32_t freeBlockCountHigh;
  uint16_t inodeMinExtraSize;
  uint16_t inodeWantSize;
  uint32_t flags;
  uint16_t raidStride;
  uint16_t mmpInterval;
  uint16_t mmpBlock;
  uint32_t raidStrideWidth;
  uint8_t logGroupsPerFlex;
  uint8_t checksumType;
  uint16_t reservedPad;
  uint64_t kibWritten;
  uint32_t snapshotInode;
  uint32_t snapshotId;
  uint64_t snapshotReservedBlockCount;
  uint32_t snapshotList;
  uint32_t errorCount;
  uint32_t firstErrorTime;
  uint32_t firstErrorId;
  uint64_t firstErrorBlock;
  uint8_t firstErrorFunction[32];
  uint32_t firstErrorLine;
  uint32_t lastErrorTime;
  uint32_t lastErrorInode;
  uint32_t lastErrorLine;
  uint64_t lastErrorBlock;
  uint8_t lastErrorFunction[32];
  uint8_t mountOpts[64];
  uint32_t userQuotaInode;
  uint32_t groupQuotaInode;
  uint32_t overheadBlocks;
  uint32_t backupBgs[2];
  uint8_t encryptAlgorithms[4];
  uint8_t encryptPwdSalt[16];
  uint32_t lnfInode;
  uint32_t prjInode;
  uint32_t checksumSeed;
  uint32_t padding[98];
  uint32_t checksum;
}ext4_superblock;

typedef struct{
  uint32_t blockBitmapLo;
  uint32_t inodeBitmapLo;
  uint32_t inodeTableLo;
  uint16_t freeBlockCount;
  uint16_t freeInodeCount;
  uint16_t usedBlockCount;
  uint16_t bgFlags;
  uint32_t excludeBitmapLo;
  uint16_t blockBitmapCsumLo;
  uint16_t inodeBitmapCsumLo;
  uint16_t itableUnusedLo;
  uint16_t checksum;
  uint32_t blockBitmapHi;
  uint32_t inodeBitmapHi;
  uint16_t freeBlockCountHi;
  uint16_t freeInodeCountHi;
  uint16_t usedDirsCountHi;
  uint32_t excludeBitmapHi;
  uint16_t blockBitmapCsumHi;
  uint16_t inodeBitmapCsumHi;
  uint32_t padding;
}ext4_group_desc;

typedef struct{
  uint32_t mode;
  uint16_t uid;
  uint32_t accessTime;
  uint32_t changeTime;
  uint32_t modifyTime;
  uint32_t deletionTime;
  uint16_t gid;
  uint16_t numLinks;
  uint32_t blockCount;
  uint32_t flags;
  union{
    uint32_t linux_Version;
    uint32_t hurd_Translator;
    uint32_t masix_Reserved;
  }osd1;
  uint32_t blocks[15];
  uint32_t generation;
  uint32_t eaBlockLo;
  uint32_t sizeHi;
  uint32_t fragAddr;
  union{
    struct{
      uint16_t blockSizeHi;
      uint16_t eaBlockHi;
      uint16_t uidHi;
      uint16_t gidHi;
      uint16_t csumLo;
      uint16_t res;
    }linux;
    struct{
      uint16_t res;
      uint16_t modeHi;
      uint16_t uidHi;
      uint16_t gidHi;
      uint32_t author;
    }hurd;
    struct{
      uint16_t res1;
      uint16_t easBlockHi;
      uint32_t res2[2];
    }masix;
  }osd2;
  uint16_t inodeSize;
  uint16_t csumHi;
  uint32_t ctimeExtra;
  uint32_t mtimeExtra;
  uint32_t atimeExtra;
  uint32_t creationTime;
  uint32_t creationTimeExtra;
  uint32_t versionHi;
  uint32_t projId;
}ext4_inode;

typedef struct{
  uint16_t magic;
  uint16_t entries;
  uint16_t maxEntries;
  uint16_t depth;
  uint32_t generation;
}ext4_extent_head;

typedef struct{
  uint32_t block;
  uint32_t leafLo;
  uint16_t leafHi;
  uint16_t padding;
}ext4_extent_intern;

typedef struct{
  uint16_t firstBlock;
  uint16_t length;
  uint16_t pointedBlockHi;
  uint32_t pointedBlockLo;
}ext4_extent;

typedef struct{
  ext4_extent_head header;
  union{
    ext4_extent_intern treeNode;
    ext4_extent leaf;
  }ext4_extent_entries[];
}ext4_extent_node_nocsum;

struct{
  uint32_t inode;
  uint16_t recLen;
  uint8_t nameLen;
  uint8_t fileType;
  char name[];
}ext4_dir_entry2;

struct{
  uint32_t hash;
  uint32_t block;
}ext4_htree_entry;

struct{
  struct{
    uint32_t inode;
    uint16_t recLen;
    uint8_t nameLen;
    uint8_t fileType;
    char name[4];
  }dot;
  struct{
    uint32_t inode;
    uint16_t recLen;
    uint8_t nameLen;
    uint8_t fileType;
    char name[4];
  }dotdot;
  struct{
    uint32_t resZero;
    uint8_t hashType;
    uint8_t infoLength;
    uint8_t depth;
    uint8_t unused;
  }rootinfo;
  uint16_t limit;
  uint16_t count;
  uint32_t block;
  ext4_htree_entry entries[];
}ext4_htree_root;

struct{
  struct{
    uint32_t inode;
    uint16_t recLen;
    uint8_t nameLen;
    uint8_t fileType;
  }fake;
  uint16_t limit;
  uint16_t count;
  uint32_t block;
  ext4_htree_entry entries[];
}ext4_htree_node;

struct{
  uint32_t res;
  uint32_t csum;
}ext4_htree_tail;
#endif
