'use strict';

angular.module( 'wqLed' )
  .factory( 'sockMsg', ['socket', 'comList', 'modeFactory', function ( socket, comList, modeFactory )
	{
		var sockMsg = {}
		
		sockMsg.spBuffer = [];
		sockMsg.rawBuffer = {};
		sockMsg.isConnected = false;
		sockMsg.connIcon = 'screen_share';
		 
		
		
		//Connection Toggle
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
		
		//Connection functions
		sockMsg.checkConnect = function ()
		{
			return sockMsg.isConnected;
		};
		
		//Port is set. Ready to connect
		sockMsg.startConn = function ()
		{
			console.log( 'Connecting to Led Arrays' );
			socket.emit( 'tConn' );
		};

		//Serial Port Buffer Update
		sockMsg.updateBuffer = function ( buf )
		{
			
			sockMsg.rawBuffer = buf;
			var consoleOpts = buf.split( "," );
			sockMsg.spBuffer.serial = { serial: consoleOpts[0] } ;
			
			sockMsg.spBuffer.mode = { mode: consoleOpts[1] } ;
			sockMsg.spBuffer.hue = { hue: consoleOpts[2] } ;
			console.log( buf );
			console.log( sockMsg.spBuffer );
			console.log( sockMsg.rawBuffer );
			
		};

		//send selected com Port to server 
		sockMsg.selPort = function ()
		{
			console.log( comList.showComPort( ) );
			socket.emit( 'setPort', comList.showComPort( ) );
		};
		

		
		//Change strip mode
		sockMsg.modeChg = function ( data )
		{
			console.log( 'Sending mode change command ' + data );
			socket.emit( 'mChg', data );
		};
		//Change Strip Hue
		sockMsg.hueChg = function ( hue )
		{
			console.log( 'Sending hue change command h' + hue );
			socket.emit( 'hChg', hue );
		};

		//Disconnect port
		sockMsg.endConn = function ()
		{
			console.log( 'Disconnecting from Led Arrays' );
			socket.emit( 'eConn' );
			sockMsg.updateBuffer( '---[Disconnected]---' );
		};
		
		// setter/getter functions

		return {

			toggleConnect: sockMsg.toggleConnect,
			selPort: sockMsg.selPort,
			modeChg: sockMsg.modeChg,
			hueChg: sockMsg.hueChg,
			endConn: sockMsg.endConn,
			checkConnect: sockMsg.checkConnect,
			updateBuffer: sockMsg.updateBuffer,
			getConnIcon: function ()
			{
				return sockMsg.connIcon; 
			},
			setBufferArray: function (data)
			{
				sockMsg.rawBuffer = data; 
			},
			getBufferArray: function ()
			{
				return sockMsg.rawBuffer;
			},
			setConsoleBuffer: function ( buf)
			{
				sockMsg.spBuffer.serial = buf;
			},
			getConsoleBuffer: function ()
			{
				return sockMsg.spBuffer.serial;
			},
			setModeBuffer: function (buf)
			{
				sockMsg.spBuffer.mode = buf;
			},
			getModeBuffer: function ()
			{
				return sockMsg.spBuffer.mode;
			},
			setHueBuffer: function (buf)
			{
				sockMsg.spBuffer.hue = buf;
			},
			getHueBuffer: function ()
			{
				return sockMsg.spBuffer.hue;
			},
			setSerialBufferArray: function ( data )
			{
				sockMsg.spBuffer = data;
			},
			getSerialBufferArray: function ()
			{
				return sockMsg.spBuffer;
			},
			
		};
		return sockMsg;
	}] );