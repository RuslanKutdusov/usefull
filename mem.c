#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <execinfo.h>

// http://habrahabr.ru/post/199090/

//
static void* ( *malloc_orig )( size_t size ) = NULL;
static void  ( *free_orig )( void* ptr ) = NULL;
static void* ( *calloc_orig )( size_t nmemb, size_t size ) = NULL;
static void* ( *realloc_orig )( void* ptr, size_t size ) = NULL;


//
void* malloc( size_t size )
{
	if( malloc_orig == NULL )
		malloc_orig = dlsym( RTLD_NEXT, "malloc" );

	printf("malloc %lu\n", size );

	return malloc_orig( size );
}
    

//   
void free( void* ptr )
{
	if( free_orig == NULL )
		free_orig = dlsym( RTLD_NEXT, "free" );

	printf("free\n" );

	free_orig( ptr );
}


//
void* calloc( size_t nmemb, size_t size )
{
	printf("calloc\n");
	if( calloc_orig == NULL )
		calloc_orig = dlsym( RTLD_NEXT, "calloc" );

	printf("calloc %lu\n", nmemb * size );

	return calloc_orig( nmemb, size );
}


//
void* realloc( void *ptr, size_t size )
{
	if( realloc_orig == NULL )
		realloc_orig = dlsym( RTLD_NEXT, "realloc" );

	printf("realloc %lu\n", size );

	return realloc_orig( ptr, size );
}
