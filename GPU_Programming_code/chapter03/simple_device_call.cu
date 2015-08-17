/*
 * Copyright 1993-2010 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and 
 * proprietary rights in and to this software and related documentation. 
 * Any use, reproduction, disclosure, or distribution of this software 
 * and related documentation without an express license agreement from
 * NVIDIA Corporation is strictly prohibited.
 *
 * Please refer to the applicable NVIDIA end user license agreement (EULA) 
 * associated with this source code for terms and conditions that govern 
 * your use of this NVIDIA software.
 * 
 */


#include "../common/book.h"

//__device__ 函数在设备上被调用
__device__ int addem( int a, int b ) {
    return a + b;
}

//__global__ 告诉编译器函数应该编译为在设备上
__global__ void add( int a, int b, int *c ) {
    *c = addem( a, b );
}

int main( void ) {
    int c;
    int *dev_c;
    //设备上分配内存
    HANDLE_ERROR( cudaMalloc( (void**)&dev_c, sizeof(int) ) );

    add<<<1,1>>>( 2, 7, dev_c );

	//设备内存拷贝到主机
    HANDLE_ERROR( cudaMemcpy( &c, dev_c, sizeof(int),
                              cudaMemcpyDeviceToHost ) );
    printf( "2 + 7 = %d\n", c );
    //释放设备申请的内存
    HANDLE_ERROR( cudaFree( dev_c ) );

    return 0;
}


