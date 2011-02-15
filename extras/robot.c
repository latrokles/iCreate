/*
 * robot.c
 * latrokles - latrokles_at_gmail_dot_com
 *
 * receives udp packets from iphone app and controls the iRobot Create
 * via serial interface.
 *
 * usage: ./robot ip_address port_number serial_port
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include <createoi.h>
#include <math.h>

#define BUFFER_SIZE	1024
#define ERROR_MARGIN	   5

int socket_descriptor;
	
int main(int argc, char** argv){

	int port_number;
	int client_length;

	struct sockaddr_in server_address, client_address;
	struct hostent *host_properties;
	char buffer[BUFFER_SIZE];
	char *host_address;
	int  message_size;
	int  message_byte_size;
	
	const char delimiters[ ] = ":";


	port_number = atoi( argv[ 2 ] );

	//-- create the socket
	printf( "creating udp socket...\n" );
	socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
	if ( socket_descriptor < 0 )
		perror( "Error opening the socket" );

	//-- quick trick to avoid error on binding
	int optval = 1;
	setsockopt( socket_descriptor, SOL_SOCKET, SO_REUSEADDR, ( const void * )&optval, sizeof( int ) );

	//-- set server internet address
	bzero( ( char * )&server_address, sizeof( server_address ) );
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr( argv[ 1 ] );
	server_address.sin_port = htons( ( unsigned short )port_number );

	//-- bind socket to port
	if( bind( socket_descriptor, ( struct sockaddr * )&server_address, sizeof( server_address ) ) < 0 )
		perror( "Error binding socket to port" );

	//-- if nothing has failed up to this point, let's start the connection to the create robot
	printf( "connecting to irobot create on %s...\n", argv[ 3 ] );
	startOI_MT( argv[ 3 ] );

	//-- the main loop !
	client_length = sizeof( client_address );
	while( 1 ){
		//-- receive the packets from the iphone app
		bzero( buffer, BUFFER_SIZE );
		message_byte_size = recvfrom( socket_descriptor, buffer, BUFFER_SIZE, 0, ( struct sockaddr * )&client_address, &client_length );
		if( message_byte_size < 0 )
			perror("Error in recvfrom");

		printf("%s\n", buffer);
		fflush(stdout);

		//-- split the control instruction and extract left wheel velocity and right wheel velocity
		char *left; 
		char *right; 
		left  =	strtok( buffer, delimiters );	// left = "Left";
		left  = strtok( NULL, delimiters );	// left = string with actual value for left wheel velocity
		right = strtok( NULL, delimiters );	// right = "Right"
		right = strtok( NULL, delimiters );	// right = string with actual value for right wheel velocity

		int left_velocity  = atoi( left );
		int right_velocity = atoi( right );
		
		//-- quick fix so that if the velocities of the wheels are too close 
		//   together then set them to the same, this should be handled on the 
		//   iphone code.
		if( abs( left_velocity - right_velocity ) < ERROR_MARGIN )
			left_velocity = right_velocity;

		//-- send command to the robot
		directDrive( left_velocity, right_velocity );
	}
	//-- stop robot 
	stopOI_MT();
}
