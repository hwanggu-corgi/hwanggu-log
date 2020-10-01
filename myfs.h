
// A directory entry has a very short name and an inode number.
struct dir_entry {
	char name[8];
	int inode;
};

// We only care about two fields in the inode: type and block_no.
// Note that files will always be empty and have a block_no of -1
struct inode {
	char type; 	   // 'f' or 'd'
	int block_no;  // directories use only one data block
};


