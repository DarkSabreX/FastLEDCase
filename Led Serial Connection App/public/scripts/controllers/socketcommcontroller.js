'use strict';

angular.module( 'wqLed')

  .controller( 'SocketCommunicationController', ['socket','comList', 'sockMsg', function (socket, comList, sockMsg)
	{
		var led = this;
		led.comList = comList;
		led.sockMsg = sockMsg;	

	
		/*Events Received From Server*/

		//connected to socket
		socket.on( 'connected', function ( data )
		{
			console.log( 'Connected, this is what I received : ', data );
			led.comList.updateComList( data.sPortList );
			//led.sockMsg.updateBuffer( '---[Disconnected]---' );
		} );

		//Port is set. Ready to connect
		socket.on( 'portSet', function ( data )
		{
			console.log( data );
		} );

		//Connected
		socket.on( 'sData', function ( data )
		{
			led.sockMsg.updateBuffer(data);
			console.log( data );
		} );
		
		//Error
		socket.on( 'error', function ( err )
		{
			console.log( 'Error: ', err.message );
		} );			
}] );