#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void slowPrint( const char * slowString, unsigned long milliseconds );
void wait( unsigned long milliseconds );

int main( int argc , char const *argv[] ) {
	if( argc < 2 ) {
    	printf( "USAGE:\n" );
    	printf( "%s <ms per character print> <string to print>\n",argv[0] );
    }
    int i;
    for( i=2 ; i < argc ; i++ ) {
        slowPrint( argv[i], atoi( argv[1] ) );
        if ( i < argc - 1 )
        {
        	printf(" ");
        }
    }
	return 0;
}

void slowPrint( const char * slowString, unsigned long milliseconds ) {
	unsigned long strSize = strlen( slowString );
	int i = 0;
	for ( ; i < strSize ; ++i ) {
		if ( i < strSize - 1)
		{
			if (*(slowString+i) == '\\') {
				printf("\n");
				i++;
				fflush(stdout);	
				continue;
			}
		}
		printf( "%c", *(slowString+i) );
		fflush( stdout );
		wait( milliseconds );
	}
}

void wait( unsigned long milliseconds ) {
    unsigned long millisecs = milliseconds;
    struct timespec req = { 0 };
    time_t sec=(int)(millisecs/1000);
    millisecs=millisecs-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=millisecs*1000000L;
    nanosleep(&req,&req);
}