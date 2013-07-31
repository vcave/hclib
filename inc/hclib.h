/* Copyright (c) 2013, Rice University

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1.  Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.
3.  Neither the name of Rice University
     nor the names of its contributors may be used to endorse or
     promote products derived from this software without specific
     prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef HCLIB_H_
#define HCLIB_H_

/**
 * @file Interface to HCLIB
 */

#include "ddf.h"

void hclib_init(int * argc, char ** argv);

void hclib_finalize();

/**
 * @brief A pointer to a function to be executed asynchronously
 */
typedef void (*asyncFct_t) (int argc, void * argv[]);
typedef void (*forasyncFct_t1D) (int argc, void * argv[],int index);
typedef void (*forasyncFct_t2D) (int argc, void * argv[],int index_outter,int index_inner);
typedef void (*forasyncFct_t3D) (int argc, void * argv[],int index_out,int index_mid,int index_inner);
/**
 * @brief An async definition
 * Note: Would have like this to be opaque but
 * that would prevent stack allocation.
 */
typedef struct {
    //asyncFct_t fct_ptr;
    void* fct_ptr;
    int argc;
    void ** argv;
    struct ddf_st ** ddf_list; // Null terminated list
    void * phaser_list; // Null terminated list
} async_t;


/**
 * @brief A forasync definition
 * Note: Would have like this to be opaque but
 * that would prevent stack allocation.
 */
typedef struct {
    int high[3];
    int low[3];
    int seq[3];
    void *func;
}forasync_ctx;


typedef struct {
    //asyncFct_t fct_ptr;
    async_t base;
    forasync_ctx ctx;
} forasync_t;

typedef void (*forasyncWrapper_t) (int argc, void * argv[],forasync_t *);
/**
 * @brief: spawn a new async.
 * @param[in] fct_ptr: the function to execute
 * @param[in] argc: the number of arguments for the function
 * @param[in] argv: the actual arguments
 */
void async(async_t * async_def, asyncFct_t fct_ptr, int argc, void ** argv,
           struct ddf_st ** ddf_list, void * phaser_list);

void for_wrapper1D(int ,void **,forasync_t *);
void recursive_wrapper1D(int ,void **,forasync_t *);
void for_wrapper2D(int ,void **,forasync_t *);
void for_wrapper3D(int ,void **,forasync_t *);
void forasync_chunk(int,async_t * async_def, void* fct_ptr,int *size, int *ts, int argc, void ** argv, struct ddf_st ** ddf_list, void * phaser_list); 
void forasync1d_recursive(async_t *, void*,int low,int high, int ts, int argc, void ** argv, struct ddf_st ** ddf_list, void * phaser_list); 
void forasync1D(async_t* async_def,void* forasync_fct,int siz,int ts,int runtime_type, int argc, void ** argv,struct ddf_st ** ddf_list, void * phaser_list); 
/**
 * @brief starts a new finish scope
 */
void start_finish();

/**
 * @brief ends the current finish scope
 */
void end_finish();

#endif /* HCLIB_H_ */
