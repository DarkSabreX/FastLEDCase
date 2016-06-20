'use strict';

angular.module( 'wqLed')

  .controller( 'SocketCommunicationController', ['socket','comList','sockMsg','modeFactory', function (socket, comList, sockMsg, modeFactory)
	{
		var led = this;
		led.comList = comList;
		led.sockMsg = sockMsg;
		led.modeFactory = modeFactory;

		/*Events Received From Server*/

		//connected to socket
		socket.on( 'connected', function ( data )
		{
			console.log( 'Connected, this is what I received : ', data );
			comList.updateComList( data.sPortList );
			//led.sockMsg.updateBuffer( '---[Disconnected]---' );
		} );

		//Port is set. Ready to connect
		socket.on( 'portSet', function ( data )
		{
			console.log( 'Port is Set.', data );
		} );

		//Connected
		socket.on( 'sData', function ( data )
		{
			sockMsg.updateBuffer( data );
			var sDataOpts = data.split( "," );
			//modeFactory.setCurrentMode( { mode: sDataOpts [1] } );
			modeFactory.cMode( sDataOpts [1] );
			modeFactory.cHue( sDataOpts [2] );
			console.log( data );
			console.log( 'split data: ', sDataOpts[1] );
			//console.log( 'split data: ', modeFactory.getCurrentMode( ).mode );
			console.log( 'split data: ', modeFactory.cMode( ) );
			console.log( modeFactory.cHue(  ));
		} );
		
		//Error
		socket.on( 'error', function ( err )
		{
			console.log( 'Error: ', err.message );
		} );			
}] );