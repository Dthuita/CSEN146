// COEN 146L : Lab 2 - template to use for creating multiple thread to make file transfers (step 1)

#include <stdio.h>	 // fprintf(), fread(), fwrite(), fopen(), fclose()
#include <stdlib.h>	 // malloc(), free()
#include <pthread.h> // pthread_create()
#include <unistd.h>	 // read(), write()
#include <fcntl.h>	 // open(), close()
#include <errno.h>	 // errno
#include <time.h>	 // clock()

#define BUF_SIZE 2048 // buffer size

// data structure to hold copy
struct copy_struct
{
	int thread_id;
	char *src_filename;
	char *dst_filename;
};

// copies a files from src_filename to dst_filename using functions fopen(), fread(), fwrite(), fclose()
int func_copy(char *src_filename, char *dst_filename)
{

	src = fopen(src_filename, "r"); // opens a file for reading
	if (src == NULL)
	{ // fopen() error checking
		fprintf(stderr, "unable to open %s for reading: %i\n", src_filename, errno);
		exit(0);
	}
	dst = fopen(dst_filename, "w"); // opens a file for writing; erases old file/creates a new file
	if (dst == NULL)
	{ // fopen() error checking
		fprintf(stderr, "unable to open/create %s for writing: %i\n", dst_filename, errno);
		exit(0);
	}

	void *buf = malloc((size_t)BUF_SIZE); // allocate a buffer to store read data
	// reads content of file is loop iterations until end of file
	int content;
	while ((content = fread(buf, sizeof(char), BUF_SIZE, src)) > 0)
	{
		fwrite(buf, sizeof(char), content, dst); // writes bytes_read to dst_filename
	}

	// closes src file pointer
	// closes dst file pointer
	fclose(src);
	fclose(dst);
	// frees memory used for buf
	free(buf);

	return 0;
}

// thread function to copy one file
void *copy_thread(void *arg)
{
	struct copy_struct params = *(struct copy_struct *)arg; // cast/dereference void* to copy_struct
	printf("thread[%i] - copying %s to %s\n", params.thread_id, params.src_filename, params.dst_filename);
	// call file copy function
	func_copy(args.src_filename, args.dst_filename);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	// check correct usage of arguments in command line
	if (argc != ....)
	{
		fprintf(stderr, "usage: %s <n connections> ........\n", argv[0]);
		exit(1);
	}
	char *src_filename;
	char *dst_filename;
	char *src_filenames[]; // array of source files
	char *dst_filenames[]; // array of desintation files
	int num_threads;	   // number of threads to create

	pthread_t threads[num_threads];				   // initialize threads
	struct copy_struct thread_params[num_threads]; // structure for each thread
	int i;
	for (i = 0; i < num_threads; i++)
	{
		// initialize thread parameters
		thread_params[i].thread_id = i + 2000;
		thread_params[i].src_filename = src_filename;
		sprintf(thread_params[i].dst_filename, "%s_%d", dst_filename, i + 100); // store string [dst_file]_[number]

		// create each copy thread
		// use pthread_create(.....);
		// ??SHOULD THIS BE DONE ALL AT ONCE??
		pthread_create(&threads[i], NULL, &copy_thread, (void *)&thread_params);
	}

	// wait for all threads to finish
	for (i = 0; i < num_threads; i++)
	{
		pthread_join(threads[i], NULL);
	}
	pthread_exit(NULL);
}