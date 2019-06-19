/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: rpf.h

*/

#ifndef _rpf_h_
#define _rpf_h_

#define RPF_SIGNATURE   "RPFA"
#define RPF_ENCRYPTION_KEY "FbMTjG4B7mCWTqA9TWgDIi76nywaD5sp"

enum rpf_identifier {
    rpf_file,
    rpf_directory
};

struct rpf_header {
    char signature[4];
    unsigned char isEncrypted;
    rpf_directory_entry rootDirectory{ 0x00000000, 0x00000000, "RSEngine Root" };
};

struct rpf_file_entry {
    long nextentry;
    long startloc;
    long endloc;
    long root;
    char filename[32];
};

struct rpf_directory_entry {
    long nextentry;
    long root;
    char dirname[32];
};

#endif // _rpf_h_
