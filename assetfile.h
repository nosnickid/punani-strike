/* This file is part of punani-strike
 * Copyright (c) 2012 Gianni Tedesco
 * Released under the terms of GPLv3
*/
#ifndef _PUNANI_ASSETFILE_H
#define _PUNANI_ASSETFILE_H

#define ASSETFILE_MAGIC	0x55daba00

typedef int16_t fp_t;

#define RCMD_NORMAL_FLAG (1 << 15)
typedef uint16_t idx_t;

/* asset file layout
 * [ header ]
 * [ struct asset_desc * h_num_assets] - sorted by name
 * [ fp_t * D * h_verts] - vertices
 * [ fp_t * D * h_norms] - normals
 * [ idx_t * h_num_assets * a_len ] - indices in to verts/norms arrays
*/

struct assetfile_hdr {
	uint32_t h_num_assets;
	uint32_t h_verts;
	uint32_t h_norms;
	uint32_t h_magic;
}__attribute__((packed));

#define ASSET_NAMELEN 32
struct asset_desc {
	uint8_t a_name[ASSET_NAMELEN];
	uint32_t a_off;
	uint16_t a_num_cmds;
	uint16_t a_num_verts;
}__attribute__((packed));

/* Internal data structures */
struct _asset_file {
	const struct assetfile_hdr *f_hdr;
	const struct asset_desc *f_desc;
	struct _asset **f_db;
	const uint8_t *f_buf;
	const fp_t *f_verts;
	const fp_t *f_norms;
	idx_t *f_idx_begin;
	size_t f_sz;
	unsigned int f_ref;
};

struct _asset {
	struct _asset_file *a_owner;
	uint16_t *a_verts;
	uint16_t *a_norms;
	unsigned int a_idx;
	unsigned int a_ref;
};

#endif /* _PUNANI_ASSETFILE_H */