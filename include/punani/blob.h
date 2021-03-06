/* This file is part of punani-strike
 * Copyright (c) 2011 Gianni Tedesco
 * Released under the terms of GPLv3
*/
#ifndef _PUNANI_BLOB_H
#define _PUNANI_BLOB_H

void blob_free(uint8_t *blob, size_t sz);
uint8_t *blob_from_file(const char *fn, size_t *sz);
int blob_to_file(const uint8_t *b, size_t sz, const char *fn);

#endif /* _PUNANI_BLOB_H */
