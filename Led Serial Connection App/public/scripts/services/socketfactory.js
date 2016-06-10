'use strict';

angular.module( 'wqLed' ).factory( 'socket', function ( socketFactory )
{
	var myIoSocket = io.connect( 'http://localhost:4567' );
	var socket = socketFactory( );
	return socket;
} );