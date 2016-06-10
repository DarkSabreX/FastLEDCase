'use strict';

angular.module( 'wqLed' )
  .factory( 'sockMsg', ['socket', 'comList',function (socket, comList)
	{
		var sockMsg = {};
		sockMsg.spBuffer = '---[Disconnected]---' ;
		sockMsg.isConnected = false;
		sockMsg.connIcon = 'screen_share';


		sockMsg.toggleConnect = function ()
		{
			if ( sockMsg.isConnected === false )
			{
				sockMsg.startConn( );
				sockMsg.connIcon = 'stop_screen_share';
				sockMsg.isConnected = true;
			}
			else
			{
				sockMsg.endConn( );
				sockMsg.connIcon = 'screen_share';
				sockMsg.isConnected = false;
			}
		};
		
		sockMsg.checkConnect = function ()
		{
			return sockMsg.isConnected; 
		};

		//Serial Port Buffer Getter/Setter functions
		sockMsg.updateBuffer = function ( buf )
		{
			sockMsg.spBuffer = buf;
		};
		
		sockMsg.getBuffer = function ()
		{
			return sockMsg.spBuffer;
		};		

		//send selected com Port to server 
		sockMsg.selPort = function ()
		{
			console.log( sockMsg.portSel );
			socket.emit( 'setPort', comList.showComPort( ) );
		};
		
		//Port is set. Ready to connect
		sockMsg.startConn = function ()
		{
			console.log( 'Connecting to Led Arrays' );
			socket.emit( 'tConn' );
		};
		
		//Change strip mode
		sockMsg.modeChg = function ( data )
		{
			console.log( 'Sending mode change command ' + data );
			socket.emit( 'mChg', data );
		};
		
		//Disconnect port
		sockMsg.endConn = function ()
		{
			console.log( 'Disconnecting from Led Arrays' );
			socket.emit( 'eConn' );
			sockMsg.updateBuffer( '---[Disconnected]---' );
		};

		return sockMsg;
	}] );